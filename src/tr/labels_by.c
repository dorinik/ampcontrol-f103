#include "labels.h"

const char *const labels_by[LABEL_END] = {
    [LABEL_SUNDAY]          = "НЯДЗЕЛЯ",
    [LABEL_MONDAY]          = "ПАНЯДЗЕЛАК",
    [LABEL_TUESDAY]         = "АЎТОРАК",
    [LABEL_WEDNESDAY]       = "СЕРАДА",
    [LABEL_THURSDAY]        = "ЧАЦВЕР",
    [LABEL_FRIDAY]          = "ПЯТНІЦА",
    [LABEL_SATURDAY]        = "СУБОТА",

    [LABEL_VOLUME]          = "Гучнасць",
    [LABEL_BASS]            = "Тэмбр НЧ",
    [LABEL_MIDDLE]          = "Тэмбр СЧ",
    [LABEL_TREBLE]          = "Тэмбр ВЧ",
    [LABEL_FRONTREAR]       = "Фронт/тыл",
    [LABEL_BALANCE]         = "Баланс",
    [LABEL_CENTER]          = "Цэнтр",
    [LABEL_SUBWOOFER]       = "Сабвуфер",
    [LABEL_PREAMP]          = "Пасіленне",

    [LABEL_IN_TUNER]        = "Цюнер",
    [LABEL_IN_PC]           = "Кампутар",
    [LABEL_IN_TV]           = "Тэлевізар",
    [LABEL_IN_BLUETOOTH]    = "Bluetooth",
    [LABEL_IN_DVD]          = "DVD",
    [LABEL_IN_USB]          = "USB",
    [LABEL_IN_MICROPHONE]   = "Мікрафон",
    [LABEL_IN_GUITAR]       = "Гітара",
    [LABEL_IN_TURNTABLES]   = "Круцёлкі",
    [LABEL_IN_SDCARD]       = "SD карта",
    [LABEL_IN_PROJECTOR]    = "Праектар",
    [LABEL_IN_SATELLITE]    = "Спадарожнік",
    [LABEL_IN_MIXER]        = "Міксер",
    [LABEL_IN_KARADIO]      = "KaRadio",

    [LABEL_BOOL_OFF]        = "ВЫКЛ",
    [LABEL_BOOL_ON]         = "УКЛ",

    [LABEL_TUNER_FM_STATION_NAME]   = "Назва FM станцыі",

    [LABEL_TUNER_IC + TUNER_IC_NO]      = "Няма",

    [LABEL_TUNER_BAND + TUNER_BAND_FM_US_EUROPE]    = "ЗША/Еўропа FM",
    [LABEL_TUNER_BAND + TUNER_BAND_FM_JAPAN]        = "Японскі FM",
    [LABEL_TUNER_BAND + TUNER_BAND_FM_WORLDWIDE]    = "Сусветны FM",
    [LABEL_TUNER_BAND + TUNER_BAND_FM_EASTEUROPE]   = "Усх. Еўропа FM",

    [LABEL_TUNER_STEP + TUNER_STEP_50K]     = "50кГц",
    [LABEL_TUNER_STEP + TUNER_STEP_100K]    = "100кГц",
    [LABEL_TUNER_STEP + TUNER_STEP_200K]    = "200кГц",

    [LABEL_TUNER_DEEMPH + TUNER_DEEMPH_50u] = "50мкс",
    [LABEL_TUNER_DEEMPH + TUNER_DEEMPH_75u] = "75мкс",

    [LABEL_SPECTRUM_MODE + SP_MODE_STEREO]      = "Стэрэа",
    [LABEL_SPECTRUM_MODE + SP_MODE_MIRROR]      = "Люстэрка",
    [LABEL_SPECTRUM_MODE + SP_MODE_ANTIMIRROR]  = "Антылюстэрка",
    [LABEL_SPECTRUM_MODE + SP_MODE_MIXED]       = "Змешаны",
    [LABEL_SPECTRUM_MODE + SP_MODE_WATERFALL]   = "Вадаспад",

    [LABEL_PAL_MODE + PAL_SNOW]         = "Снег",
    [LABEL_PAL_MODE + PAL_AQUA]         = "Вада",
    [LABEL_PAL_MODE + PAL_FIRE]         = "Агонь",

    [LABEL_AUDIO_IC + AUDIO_IC_NO]      = "Няма",

    [LABEL_ALARM_DAY + ALARM_DAY_OFF]       = "Выкл",
    [LABEL_ALARM_DAY + ALARM_DAY_WEEKDAYS]  = "Будні",
    [LABEL_ALARM_DAY + ALARM_DAY_ALL_DAYS]  = "Усе дні",

    // NOTE: Keep in sync with MenuIdx in menu.h
    [LABEL_MENU + MENU_NULL]            = "Назад",

    [LABEL_MENU + MENU_SETUP]           = "Налады",

    [LABEL_MENU + MENU_SETUP_SYSTEM]    = "Сістэма",
    [LABEL_MENU + MENU_SETUP_AUDIO]     = "Аудыё",
    [LABEL_MENU + MENU_SETUP_TUNER]     = "Цюнер",
    [LABEL_MENU + MENU_SETUP_SPECTRUM]  = "Спектр",
    [LABEL_MENU + MENU_SETUP_DISPLAY]   = "Дысплэй",
    [LABEL_MENU + MENU_SETUP_ALARM]     = "Будзільнік",
    [LABEL_MENU + MENU_SETUP_RC]        = "Пульт",

    [LABEL_MENU + MENU_SYSTEM_LANG]     = "Мова",
    [LABEL_MENU + MENU_SYSTEM_I2C_EXT]  = "I2C пашыральнік",
    [LABEL_MENU + MENU_SYSTEM_ENC_RES]  = "Вырашэнне энкодера",
    [LABEL_MENU + MENU_SYSTEM_SIL_TIM]  = "Таймер цішыні",
    [LABEL_MENU + MENU_SYSTEM_RTC_CORR] = "Карэкцыя часу",
    [LABEL_MENU + MENU_SYSTEM_STBY_LOW] = "STBY актыўны 0",
    [LABEL_MENU + MENU_SYSTEM_MUTE_LOW] = "MUTE актыўны 0",

    [LABEL_MENU + MENU_I2C_EXT_IN_STAT] = "Статус уваходаў",
    [LABEL_MENU + MENU_I2C_EXT_BT]      = "Кантроль Bluetoth",

    [LABEL_MENU + MENU_AUDIO_IC]        = "Аўдыёпрацэсар",
    [LABEL_MENU + MENU_AUDIO_SHOWDB]    = "Паказваць у дБ",
    [LABEL_MENU + MENU_AUDIO_IN]        = "Уваход",

    [LABEL_MENU + MENU_TUNER_IC]        = "Чып цюнера",
    [LABEL_MENU + MENU_TUNER_BAND]      = "Дыяпазон",
    [LABEL_MENU + MENU_TUNER_STEP]      = "Крок",
    [LABEL_MENU + MENU_TUNER_DEEMPH]    = "Прадскажэнне",
    [LABEL_MENU + MENU_TUNER_STA_MODE]  = "Рэжым станцый",
    [LABEL_MENU + MENU_TUNER_FMONO]     = "Мона прымусова",
    [LABEL_MENU + MENU_TUNER_RDS]       = "Уключыць RDS",
    [LABEL_MENU + MENU_TUNER_BASS]      = "Узмацніць НЧ",
    [LABEL_MENU + MENU_TUNER_VOLUME]    = "Гучнасць",

    [LABEL_MENU + MENU_ALARM_HOUR]      = "Гадзіна",
    [LABEL_MENU + MENU_ALARM_MINUTE]    = "Хвіліна",
    [LABEL_MENU + MENU_ALARM_DAYS]      = "Дні",

    [LABEL_MENU + MENU_SPECTRUM_MODE]   = "Рэжым экрана",
    [LABEL_MENU + MENU_SPECTRUM_PEAKS]  = "Пікавы ўзровень",
    [LABEL_MENU + MENU_SPECTRUM_GRAD]   = "Градыент",

    [LABEL_MENU + MENU_DISPLAY_BR_STBY] = "Яркасць STBY",
    [LABEL_MENU + MENU_DISPLAY_BR_WORK] = "Яркасць",
    [LABEL_MENU + MENU_DISPLAY_ROTATE]  = "Круціць",
    [LABEL_MENU + MENU_DISPLAY_DEF]     = "Галоўны экран",
    [LABEL_MENU + MENU_DISPLAY_PALETTE] = "Палітра",

    // NOTE: Keep in sync with cmd.h define list
    [LABEL_MENU + MENU_RC_STBY_SWITCH]  = "Рэжым чакання",
    [LABEL_MENU + MENU_RC_MUTE]         = "Цішыня",
    [LABEL_MENU + MENU_RC_VOL_UP]       = "Гучнасць +",
    [LABEL_MENU + MENU_RC_VOL_DOWN]     = "Гучнасць -",
    [LABEL_MENU + MENU_RC_MENU]         = "Меню",
    [LABEL_MENU + MENU_RC_CHAN_NEXT]    = "Наст. канал",
    [LABEL_MENU + MENU_RC_CHAN_PREV]    = "Папяр. канал",
    [LABEL_MENU + MENU_RC_DIG]          = "Лічба",
    [LABEL_MENU + MENU_RC_IN_NEXT]      = "Наст. уваход",
    [LABEL_MENU + MENU_RC_NAV_OK]       = "OK",
    [LABEL_MENU + MENU_RC_NAV_BACK]     = "Назад",
    [LABEL_MENU + MENU_RC_NAV_RIGHT]    = "Направа",
    [LABEL_MENU + MENU_RC_NAV_UP]       = "Наверх",
    [LABEL_MENU + MENU_RC_NAV_LEFT]     = "Налева",
    [LABEL_MENU + MENU_RC_NAV_DOWN]     = "Уніз",
    [LABEL_MENU + MENU_RC_BASS_UP]      = "НЧ +",
    [LABEL_MENU + MENU_RC_BASS_DOWN]    = "НЧ -",
    [LABEL_MENU + MENU_RC_MIDDLE_UP]    = "СЧ +",
    [LABEL_MENU + MENU_RC_MIDDLE_DOWN]  = "СЧ -",
    [LABEL_MENU + MENU_RC_TREBLE_UP]    = "ВЧ +",
    [LABEL_MENU + MENU_RC_TREBLE_DOWN]  = "ВЧ -",
    [LABEL_MENU + MENU_RC_LOUDNESS]     = "Тонкампенс.",
    [LABEL_MENU + MENU_RC_SURROUND]     = "Гук вакол",
    [LABEL_MENU + MENU_RC_EFFECT_3D]    = "3D эфект",
    [LABEL_MENU + MENU_RC_TONE_BYPASS]  = "Вымкн. тон",
    [LABEL_MENU + MENU_RC_TIME]         = "Час",
    [LABEL_MENU + MENU_RC_STOP]         = "Спыніць",
    [LABEL_MENU + MENU_RC_PLAY_PAUSE]   = "Граць/паўза",
    [LABEL_MENU + MENU_RC_REW]          = "Крок назад",
    [LABEL_MENU + MENU_RC_FWD]          = "Крок наперад",
    [LABEL_MENU + MENU_RC_TIMER]        = "Таймер",
    [LABEL_MENU + MENU_RC_SP_MODE]      = "Рэжым спектру",
    [LABEL_MENU + MENU_RC_SCR_DEF]      = "Галоўны экран",
    [LABEL_MENU + MENU_RC_BT_IN_NEXT]   = "Наст. BT уваход",
};
