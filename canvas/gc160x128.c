#include "canvas.h"

static void showTime(RTC_type *rtc, char *wday);
static void showParam(DispParam *dp);
static void showSpectrum(SpectrumData *spData);
//static void showTuner(DispTuner *dt);
//static void showMenu(void);

static Canvas canvas = {
    .showTime = showTime,
    .showParam = showParam,
    .showSpectrum = showSpectrum,
    //.showTuner = showTuner,
    //.showMenu = showMenu,
};

void gc160x128Init(Canvas **value)
{
    *value = &canvas;
}

static void displayTm(RTC_type *rtc, uint8_t tm)
{
    int8_t time = *((int8_t *)rtc + tm);

    glcdSetFontColor(LCD_COLOR_WHITE);
    glcdWriteChar(LETTER_SPACE_CHAR);
    if (rtc->etm == tm)
        glcdSetFontColor(LCD_COLOR_OLIVE);
    if (tm == RTC_YEAR) {
        glcdWriteString("20");
        glcdWriteChar(LETTER_SPACE_CHAR);
    }
    glcdWriteNum(time, 2, '0', 10);
    glcdSetFontColor(LCD_COLOR_WHITE);
    glcdWriteChar(LETTER_SPACE_CHAR);
}

static void drawShowBar(int16_t value, int16_t min, int16_t max)
{
    static const int16_t sc = 80; // Scale count
    static const uint8_t sw = 1; // Scale width

    if (min + max) { // Non-symmectic scale => rescale to 0..sl
        value = sc * (value - min) / (max - min);
    } else { // Symmetric scale => rescale to -sl/2..sl/2
        value = (sc / 2) * value / max;
    }

    for (uint16_t i = 0; i < sc; i++) {
        uint16_t color = LCD_COLOR_WHITE;

        if (min + max) { // Non-symmetric scale
            if (i >= value) {
                color = canvas.color;
            }
        } else { // Symmetric scale
            if ((value > 0 && i >= value + (sc / 2)) ||
                (value >= 0 && i < (sc / 2 - 1)) ||
                (value < 0 && i < value + (sc / 2)) ||
                (value <= 0 && i > (sc / 2))) {
                color = canvas.color;
            }
        }

        uint16_t width = canvas.glcd->drv->width;

        glcdDrawRect(i * (width / sc) + 1, 34, sw, 6, color);
        glcdDrawRect(i * (width / sc) + 1, 40, sw, 2, LCD_COLOR_WHITE);
        glcdDrawRect(i * (width / sc) + 1, 42, sw, 6, color);
    }
}

static void drawSpCol(uint16_t xbase, uint16_t ybase, uint8_t width, uint16_t value, uint16_t max)
{
    if (value > max)
        value = max;

    glcdDrawRect(xbase, ybase - value, width, value, LCD_COLOR_AQUA);
    glcdDrawRect(xbase, ybase - max, width, max - value, LCD_COLOR_BLACK);
}

static void showTime(RTC_type *rtc, char *wday)
{
    glcdSetXY(1, 8);
    glcdSetFont(&fontterminusdig40);

    displayTm(rtc, RTC_HOUR);
    glcdWriteChar(LETTER_SPACE_CHAR);
    glcdWriteChar(':');
    glcdWriteChar(LETTER_SPACE_CHAR);
    displayTm(rtc, RTC_MIN);
    glcdWriteChar(LETTER_SPACE_CHAR);
    glcdWriteChar(':');
    glcdWriteChar(LETTER_SPACE_CHAR);
    displayTm(rtc, RTC_SEC);

    glcdSetXY(2, 58);
    glcdSetFont(&fontterminusdig30);

    displayTm(rtc, RTC_DATE);
    glcdWriteChar(LETTER_SPACE_CHAR);
    glcdWriteChar('.');
    glcdWriteChar(LETTER_SPACE_CHAR);
    displayTm(rtc, RTC_MONTH);
    glcdWriteChar(LETTER_SPACE_CHAR);
    glcdWriteChar('.');
    glcdWriteChar(LETTER_SPACE_CHAR);
    displayTm(rtc, RTC_YEAR);

    glcdSetXY(80, 94);
    glcdSetFont(&fontterminus28);
    glcdSetFontColor(LCD_COLOR_AQUA);

    static char *wdayOld = 0;
    if (wday != wdayOld) {
        glcdDrawRect(0, 94, 160, 32, canvas.color);
    }

    glcdSetFontAlign(FONT_ALIGN_CENTER);
    glcdWriteString(wday);

    wdayOld = wday;
}

static void showParam(DispParam *dp)
{
    glcdSetFont(&fontterminus28);
    glcdSetFontColor(LCD_COLOR_WHITE);

    glcdSetXY(2, 0);
    glcdWriteString((char *)dp->label);

    drawShowBar(dp->value, dp->min, dp->max);

    glcdSetXY(157, 88);
    glcdSetFont(&fontterminusdig40);

    glcdSetFontAlign(FONT_ALIGN_RIGHT);
    glcdWriteNum((dp->value * dp->step) / 8, 3, ' ', 10);
}

static void showSpectrum(SpectrumData *spData)
{
    uint8_t *buf;

    buf = spData[SP_CHAN_LEFT].show;
    for (uint16_t x = 0; x < (canvas.glcd->drv->width + 1) / 2; x++) {
        uint16_t xbase = x * 2;
        uint16_t ybase = 64;
        uint16_t width = 1;
        uint16_t value = buf[x];
        uint16_t max = 63;

        drawSpCol(xbase, ybase, width, value + 1, max);
    }

    buf = spData[SP_CHAN_RIGHT].show;
    for (uint16_t x = 0; x < (canvas.glcd->drv->width + 1) / 2; x++) {
        uint16_t xbase = x * 2;
        uint16_t ybase = 128;
        uint16_t width = 1;
        uint16_t value = buf[x];
        uint16_t max = 63;

        drawSpCol(xbase, ybase, width, value + 1, max);
    }
}
