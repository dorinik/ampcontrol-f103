#include "dispdrv.h"

#include <stdbool.h>
#include <stm32f1xx_ll_bus.h>
#include <stm32f1xx_ll_gpio.h>
#include <stm32f1xx_ll_spi.h>
#include <stm32f1xx_ll_utils.h>
#include "../pins.h"

#include "gc160x128/ili9163.h"
#include "gc160x128/st7735.h"
#include "gc176x132/ls020.h"
#include "gc176x132/lph9157.h"
#include "gc176x132/ssd1286a.h"
#include "gc220x176/hx8340.h"
#include "gc220x176/ili9225.h"
#include "gc320x240/ili9320.h"
#include "gc320x240/ili9341.h"
#include "gc320x240/s6d0139.h"
#include "gc320x240/spfd5408.h"
#include "gc320x240/mc2pa8201.h"
#include "gc400x240/ili9327.h"
#include "gc400x240/st7793.h"
#include "gc480x320/ili9481.h"
#include "gc480x320/r61581.h"

#ifdef _DISP_8BIT
static volatile bool bus_requested = false;
#endif
static int8_t brightness;

static DispDriver *drv;

#define BUS_MODE_OUT        0x33333333  // CNF=0b00, MODE=0b11 => Output push-pull 50 MHz
#define BUS_MODE_IN         0x88888888  // CNF=0b10, MODE=0b00 - Input pullup

#ifdef _DISP_SPI
static void dispdrvInitSPI()
{
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);

    LL_SPI_InitTypeDef SPI_InitStruct;
    SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
    SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
    SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2;
    SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
    SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
    SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
    SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
    SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
    SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
    SPI_InitStruct.CRCPoly = 10;
    LL_SPI_Init(SPI2, &SPI_InitStruct);

    LL_SPI_Enable(SPI2);
}
#endif

__attribute__((always_inline))
static inline void dispdrvSendByte(uint8_t data)
{
#ifdef _DISP_SPI
    while (!LL_SPI_IsActiveFlag_TXE(SPI2));
    LL_SPI_TransmitData8(SPI2, data);
#else
#if defined(_DISP_HI_BYTE) && !defined(_DISP_16BIT)
    DISP_DATA_HI_Port->BSRR = 0xFF000000 | (data << 8);
#endif
#if defined(_DISP_LO_BYTE) || defined(_DISP_16BIT)
    DISP_DATA_LO_Port->BSRR = 0x00FF0000 | data;
#endif
    CLR(DISP_WR);
    SET(DISP_WR);
#endif
}

#ifdef _DISP_8BIT

__attribute__((always_inline))
static inline void dispdrvBusIn(void)
{
#ifdef _DISP_HI_BYTE
    DISP_DATA_HI_Port->BSRR = 0x0000FF00;   // Set HIGH level on all data lines
    DISP_DATA_HI_Port->CRH = BUS_MODE_IN;
#endif
#ifdef _DISP_LO_BYTE
    DISP_DATA_LO_Port->BSRR = 0x000000FF;   // Set HIGH level on all data lines
    DISP_DATA_LO_Port->CRL = BUS_MODE_IN;
#endif
}

__attribute__((always_inline))
static inline void dispdrvBusOut(void)
{
#ifdef _DISP_HI_BYTE
    DISP_DATA_HI_Port->CRH = BUS_MODE_OUT;
#endif
#ifdef _DISP_LO_BYTE
    DISP_DATA_LO_Port->CRL = BUS_MODE_OUT;
#endif
}

__attribute__((always_inline))
static inline uint32_t dispDrvGetBusMode(void)
{
#ifdef _DISP_HI_BYTE
    return DISP_DATA_HI_Port->CRH;
#endif
#ifdef _DISP_LO_BYTE
    return DISP_DATA_LO_Port->CRL;
#endif
}

__attribute__((always_inline))
static inline void dispdrvReadInput(void)
{
#ifdef _DISP_HI_BYTE
    drv->bus = (DISP_DATA_HI_Port->IDR & 0xFF00) >> 8;
#endif
#ifdef _DISP_LO_BYTE
    drv->bus = DISP_DATA_LO_Port->IDR & 0x00FF;
#endif
}

#endif // _DISP_8BIT

__attribute__((always_inline))
static inline void dispdrvSendWord(uint16_t data)
{
#ifdef _DISP_16BIT
    DISP_DATA_HI_Port->BSRR = 0xFF000000 | (data & 0xFF00);
    DISP_DATA_LO_Port->BSRR = 0x00FF0000 | (data & 0x00FF);

    CLR(DISP_WR);
    SET(DISP_WR);
#else
#ifdef _DISP_8BIT
    dispdrvBusOut();
#endif
    uint8_t dataH = data >> 8;
    uint8_t dataL = data & 0xFF;
    dispdrvSendByte(dataH);
    dispdrvSendByte(dataL);
#ifdef _DISP_8BIT
    dispdrvBusIn();
#endif
#endif
#ifdef _DISP_8BIT
    if (bus_requested) {
        dispdrvReadInput();
        bus_requested = false;
    }
#endif
}

void dispdrvInit(DispDriver **driver)
{
#ifdef _DISP_SPI
    SET(DISP_SPI_DC);
    dispdrvInitSPI();
#else
#ifdef _DISP_READ_ENABLED
    SET(DISP_RD);
#endif
    SET(DISP_WR);
    SET(DISP_RS);
    SET(DISP_CS);
#endif

#ifdef _DISP_RST_ENABLED
    CLR(DISP_RST);
    LL_mDelay(50);
    SET(DISP_RST);
#endif
    LL_mDelay(50);

#if defined (_ILI9163)
    ili9163Init(driver);
#elif defined (_ST7735)
    st7735Init(driver);
#elif defined (_LS020)
    ls020Init(driver);
#elif defined (_LPH9157)
    lph9157Init(driver);
#elif defined (_SSD1286A)
    ssd1286aInit(driver);
#elif defined (_HX8340)
    hx8340Init(driver);
#elif defined (_ILI9225)
    ili9225Init(driver);
#elif defined (_ILI9320)
    ili9320Init(driver);
#elif defined (_ILI9341)
    ili9341Init(driver);
#elif defined (_S6D0139)
    s6d0139Init(driver);
#elif defined (_SPFD5408)
    spfd5408Init(driver);
#elif defined (_MC2PA8201)
    mc2pa8201Init(driver);
#elif defined (_ILI9327)
    ili9327Init(driver);
#elif defined (_ST7793)
    st7793Init(driver);
#elif defined (_ILI9481)
    ili9481Init(driver);
#elif defined (_R61581)
    r61581Init(driver);
#else
#error "Unsupported display driver"
#endif

    SET(DISP_BCKL);

    drv = *driver;
}

void dispdrvPwm(void)
{
    static uint8_t br;

    if (++br >= LCD_BR_MAX)
        br = 0;

    if (br == brightness) {
        CLR(DISP_BCKL);
    } else if (br == 0) {
        SET(DISP_BCKL);
    }
}

void dispdrvSetBrightness(int8_t value)
{
    brightness = value;
}

uint8_t dispdrvGetBus(void)
{
    return ~drv->bus;
}

void dispdrvBusIRQ(void)
{
#ifdef _DISP_8BIT
    if (dispDrvGetBusMode() == BUS_MODE_OUT) {
        bus_requested = true;               // Postpone read bus until in input mode
    } else {
        dispdrvReadInput();                 // Read bus immediately
    }
#endif
#if defined(_DISP_SPI)
    drv->bus = INPUT_Port->IDR & 0x00FF;    // Read 8-bit bus
#endif
}

void dispdrvSendData8(uint8_t data)
{
#ifdef _DISP_8BIT
    dispdrvBusOut();
#endif
    dispdrvSendByte(data);
#ifdef _DISP_8BIT
    dispdrvBusIn();
    if (bus_requested) {
        dispdrvReadInput();
        bus_requested = false;
    }
#endif
}

void dispdrvSendData16(uint16_t data)
{
    dispdrvSendWord(data);
}

void dispdrvSendFill(int32_t size, uint16_t color)
{
    for (int32_t i = 0; i < size; i++) {
        dispdrvSendWord(color);
    }
}

void dispdrvSendImage(tImage *img, uint16_t color, uint16_t bgColor)
{
    int16_t w = img->width;
    int16_t h = img->height;

    for (uint16_t i = 0; i < w; i++) {
        for (uint16_t j = 0; j < (h + 7) / 8; j++) {
            uint8_t data = img->data[w * j + i];
            for (uint8_t bit = 0; bit < 8; bit++) {
                if (8 * j + bit < h) {
                    dispdrvSendWord(data & 0x01 ? color : bgColor);
                    data >>= 1;
                }
            }
        }
    }
}
