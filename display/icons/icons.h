#ifndef ICONS_H
#define ICONS_H

#include <stdint.h>

#include "../fonts/fonts.h"

typedef enum {
    ICON_EMPTY = 0x00,

    // Various icons
    ICON_BRIGHTNESS,
    ICON_TEMPERATURE,

    // Audio tune icons
    ICON_VOLUME = 0x20,
    ICON_BASS,
    ICON_MIDDLE,
    ICON_TREBLE,
    ICON_FRONTREAR,
    ICON_BALANCE,
    ICON_CENTER,
    ICON_SUBWOOFER,
    ICON_PREAMP,

    // Input icons
    ICON_TUNER = 0x40,
    ICON_PC,
    ICON_TV,
    ICON_BLUETOOTH,
    ICON_DVD,
    ICON_USB,
    ICON_MICROPHONE,
    ICON_GUITAR,
    ICON_TURNTABLES,
    ICON_CASSETTE,
    ICON_PROJECTOR,
    ICON_SATELLITE,
    ICON_MIXER,

    // On/off icons
    ICON_MUTE_ON = 0x60,
    ICON_MUTE_OFF,
    ICON_LOUDNESS_ON,
    ICON_LOUDNESS_OFF,
    ICON_SURROUND_ON,
    ICON_SURROUND_OFF,
    ICON_EFFECT_3D_ON,
    ICON_EFFECT_3D_OFF,
    ICON_TONE_BYPASS_ON,
    ICON_TONE_BYPASS_OFF,

    ICON_END
} Icon;

extern const tFont iconsamp24;
extern const tFont iconsamp32;
extern const tFont iconsamp48;
extern const tFont iconsamp64;

#endif // ICONS_H