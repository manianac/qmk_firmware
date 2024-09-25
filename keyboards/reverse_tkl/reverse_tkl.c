#include "reverse_tkl.h"
#include "bongocat\bongocat.h"
#include "oled_stuff.h"
#include "print.h"
#include <ctype.h>

enum oled_mainmenu {
    _EXIT,
    _RGB_SETTINGS,
    _OLED_SETTINGS,
    _INFO_DISPLAY,

    _RGB_BACK,
    _RGB_MODE,
    _RGB_BRIGHTNESS,
    _RGB_HUE,
    _RGB_SATURATION,
    _RGB_SPEED,

    _OLED_BACK,
    _OLED_BRIGHTNESS,

    _INFO_BACK,

    _MENU_HIDDEN = 127
};

const char* oled_menu_str[] = {
    [_EXIT]             = "Back",
    [_RGB_SETTINGS]     = "RGB Settings",
    [_OLED_SETTINGS]    = "OLED Settings",
    [_INFO_DISPLAY]     = "Information",

    [_RGB_BACK]         = "Back",
    [_RGB_MODE]         = "Mode",
    [_RGB_BRIGHTNESS]   = "Brightness",
    [_RGB_HUE]          = "Hue",
    [_RGB_SATURATION]   = "Saturation",
    [_RGB_SPEED]        = "Speed",

    [_OLED_BACK]        = "Back",
    [_OLED_BRIGHTNESS]  = "Brightness",

    [_INFO_BACK]        = "Back",
};

int8_t  oled_menu_start     = _EXIT;
int8_t  oled_menu_cursor    = _MENU_HIDDEN;
int8_t  oled_menu_end       = _INFO_DISPLAY;
bool    oled_menu_selected  = false;

uint32_t oled_sleep         = 0;

void board_init(void) {
    usbpd_init();
}

bool shutdown_kb(bool jump_to_bootloader) {
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }

#ifdef RGB_MATRIX_ENABLE
    extern void rgb_matrix_update_pwm_buffers(void);
    rgb_matrix_set_color_all(RGB_OFF);
    rgb_matrix_update_pwm_buffers();
#endif
    return true;
}

//----------------------------------------------------------
// RGB Matrix naming
#if defined(RGB_MATRIX_ENABLE)
#    include <rgb_matrix.h>

#    if defined(RGB_MATRIX_EFFECT)
#        undef RGB_MATRIX_EFFECT
#    endif // defined(RGB_MATRIX_EFFECT)

#    define RGB_MATRIX_EFFECT(x) RGB_MATRIX_EFFECT_##x,
enum {
    RGB_MATRIX_EFFECT_NONE,
#    include "rgb_matrix_effects.inc"
#    undef RGB_MATRIX_EFFECT
#    ifdef RGB_MATRIX_CUSTOM_KB
#        include "rgb_matrix_kb.inc"
#    endif
#    ifdef RGB_MATRIX_CUSTOM_USER
#        include "rgb_matrix_user.inc"
#    endif
};

#    define RGB_MATRIX_EFFECT(x)    \
        case RGB_MATRIX_EFFECT_##x: \
            return #x;
const char *rgb_matrix_name(uint8_t effect) {
    switch (effect) {
        case RGB_MATRIX_EFFECT_NONE:
            return "NONE";
#    include "rgb_matrix_effects.inc"
#    undef RGB_MATRIX_EFFECT
#    ifdef RGB_MATRIX_CUSTOM_KB
#        include "rgb_matrix_kb.inc"
#    endif
#    ifdef RGB_MATRIX_CUSTOM_USER
#        include "rgb_matrix_user.inc"
#    endif
        default:
            return "UNKNOWN";
    }
}
#endif // defined(RGB_MATRIX_ENABLE)


bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }
    oled_sleep = timer_read32();
    //dprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    return true;
}

#if defined(DIP_SWITCH_ENABLE)
bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) { return false; }
    if (index != 0) return false;

    if (active)
    {
        oled_sleep = timer_read32();

        switch (oled_menu_cursor)
        {
            case _MENU_HIDDEN:
                oled_menu_start = oled_menu_cursor =_EXIT;
                oled_menu_end = _INFO_DISPLAY;
                break;
            case _EXIT:
                oled_menu_cursor = _MENU_HIDDEN;
                break;
            case _RGB_BACK:
                oled_menu_start = _EXIT;
                oled_menu_cursor = _RGB_SETTINGS;
                oled_menu_end = _INFO_DISPLAY;
                break;
            case _RGB_SETTINGS:
                oled_menu_start = oled_menu_cursor = _RGB_BACK;
                oled_menu_end = _RGB_SPEED;
                break;
            case _OLED_SETTINGS:
                oled_menu_start = oled_menu_cursor = _OLED_BACK;
                oled_menu_end = _OLED_BRIGHTNESS;
                break;
            case _OLED_BACK:
                oled_menu_start = _EXIT;
                oled_menu_end = _INFO_DISPLAY;
                oled_menu_cursor = _OLED_SETTINGS;
                break;
            case _INFO_BACK:
                oled_menu_start = _EXIT;
                oled_menu_end = oled_menu_cursor = _INFO_DISPLAY;
                break;
            case _RGB_MODE:
            case _RGB_BRIGHTNESS:
            case _RGB_HUE:
            case _RGB_SATURATION:
            case _RGB_SPEED:
            case _OLED_BRIGHTNESS:
            case _INFO_DISPLAY:
                oled_menu_selected = !oled_menu_selected;
                break;
        }
    }
    return true;
}
#endif

#if defined(ENCODER_ENABLE)
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index != 0) return true; //Allow normal keycode processing

    oled_sleep = timer_read32();
    if (oled_menu_cursor != _MENU_HIDDEN)
    {
        if (oled_menu_selected)
        {
            switch (oled_menu_cursor)
            {
                case _RGB_MODE:
                    if (clockwise) rgb_matrix_step();
                    else           rgb_matrix_step_reverse();
                    break;
                case _RGB_BRIGHTNESS:
                    if (clockwise) rgb_matrix_increase_val();
                    else           rgb_matrix_decrease_val();
                    break;
                case _RGB_HUE:
                    if (clockwise) rgb_matrix_increase_hue();
                    else           rgb_matrix_decrease_hue();
                    break;
                case _RGB_SATURATION:
                    if (clockwise) rgb_matrix_increase_sat();
                    else           rgb_matrix_decrease_sat();
                    break;
                case _RGB_SPEED:
                    if (clockwise) rgb_matrix_increase_speed();
                    else           rgb_matrix_decrease_speed();
                    break;
                case _OLED_BRIGHTNESS:
                {
                    uint8_t brightness = oled_get_brightness();
                    if (clockwise) brightness += (brightness < (256-OLED_BRIGHTNESS_STEP)) ? OLED_BRIGHTNESS_STEP : 0;
                    else           brightness -= (brightness > 0) ? OLED_BRIGHTNESS_STEP : 0;
                    oled_set_brightness(brightness);
                    break;
                }
            }
        }
        else
        {
            if (clockwise && (oled_menu_cursor < oled_menu_end))
                oled_menu_cursor++;
            else if (!clockwise && (oled_menu_cursor > oled_menu_start))
                oled_menu_cursor--;
        }
        return false;
    }

    tap_code(clockwise ? KC_VOLU : KC_VOLD);
    return true;
}
#endif

#ifdef OLED_ENABLE

static uint16_t startup_timer;

#ifndef OLED_BOOT_LOGO_TIMEOUT
#define OLED_BOOT_LOGO_TIMEOUT 750
#endif

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    startup_timer = timer_read();
    return OLED_ROTATION_180;
}

void render_hostos(bool topline) {
    switch (detected_host_os())
    {
        case OS_WINDOWS:
            oled_write(topline ? "\x97\x98" : "\xB7\xB8", false);
            break;
        case OS_LINUX:
            oled_write(topline ? "\x99\x9A" : "\xB9\xBA", false);
            break;
        case OS_IOS:
        case OS_MACOS:
            oled_write(topline ? "\x95\x96" : "\xB5\xB6", false);
            break;
        case OS_UNSURE:
        default:
            break;
    }
}

void render_selected_uint8(const uint8_t value)
{
    uint8_t space = oled_max_chars() - strlen(oled_menu_str[oled_menu_cursor]);
    oled_write(oled_menu_str[oled_menu_cursor], false);

    for (int i=0;i<space-3;i++)
        oled_write_char(' ', false);
    oled_write(get_u8_str(value,'0'), false);
    for (int i=0;i<oled_max_chars()*3;i++)
        oled_write_char(' ', false);
}

void render_rgb_mode(const uint8_t value)
{
    char buf[64] = {0};
    //snprintf(buf, sizeof(buf), "%s", rgb_matrix_name(rgb_matrix_get_mode()));
    strcpy(buf, rgb_matrix_name(rgb_matrix_get_mode()));
    for (int i=1; i<sizeof(buf); ++i) {
        if (buf[i] == 0) break;
        else if (buf[i] == '_') buf[i] = ' ';
        else if (buf[i-1] == ' ') buf[i] = toupper(buf[i]);
        else if (buf[i-1] != ' ') buf[i] = tolower(buf[i]);
    }
    oled_write_ln(oled_menu_str[oled_menu_cursor], false);
    oled_write_ln(buf, false);
    for (int i=0;i<oled_max_chars()*(strlen(buf) > 20 ? 1 : 2);i++) //this hack just keeps the screen clean
       oled_write_char(' ', false);
}

void render_menu(void) {
    if (oled_menu_cursor > oled_menu_end || oled_menu_cursor < oled_menu_start) return;

    if (!oled_menu_selected)
    {
        const int8_t min_index = (oled_menu_start > (oled_menu_cursor-3) ? oled_menu_start : (oled_menu_cursor-3));
        const int8_t max_index = (oled_menu_end < (min_index+3) ? oled_menu_end : (min_index+3));

        //dprintf("start: %d, cursor: %d, end %d\n", min_index, oled_menu_cursor, max_index);

        for (int8_t i=min_index; i<=max_index; i++)
            oled_write_ln(oled_menu_str[i], oled_menu_cursor == i);

        for (int8_t i=max_index; i<3; i++)
        {
            oled_write_ln("", false);
        }
    }
    else
    {
        switch (oled_menu_cursor)
        {
            case _RGB_MODE:
                render_rgb_mode(rgb_matrix_get_mode());
                break;
            case _RGB_BRIGHTNESS:
                render_selected_uint8(rgb_matrix_get_val());
                break;
            case _RGB_HUE:
                render_selected_uint8(rgb_matrix_get_hue());
                break;
            case _RGB_SATURATION:
                render_selected_uint8(rgb_matrix_get_sat());
                break;
            case _RGB_SPEED:
                render_selected_uint8(rgb_matrix_get_speed());
                break;
            case _OLED_BRIGHTNESS:
                render_selected_uint8(oled_get_brightness());
                break;
            case _INFO_DISPLAY:
            {
                usbpd_allowance_t allowance = usbpd_get_allowance();
                render_hostos(true);
                oled_write_P(PSTR(" WPM:"), false);
                oled_write_ln(get_u8_str(get_current_wpm(), ' '), false);
                render_hostos(false);
                oled_write(" USB PD: ", false);
                switch (allowance)
                {
                    case USBPD_500MA: oled_write_ln_P(PSTR("500mA"), false); break;
                    case USBPD_1500MA: oled_write_ln_P(PSTR("1500mA"), false); break;
                    case USBPD_3000MA: oled_write_ln_P(PSTR("3000mA"), false); break;
                    default: oled_write_ln(get_u8_str(allowance, ' '), false); break;
                }
                oled_write("Scan Freq(Hz):", false);
                oled_write_ln(get_u16_str(get_matrix_scan_rate(), ' '), false);
                oled_write_ln(("BUILD: " __DATE__), false);
                break;
            }
        }
    }
}

bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }

    static bool finished_logo = false;

    if (!finished_logo && (timer_elapsed(startup_timer) < OLED_BOOT_LOGO_TIMEOUT))
    {
        render_qmk_logo();
        return false;

    }
    else if (!finished_logo)
    {
        finished_logo = true;
        oled_clear();
        return false;
    }

    if (timer_elapsed32(oled_sleep) > OLED_TIMEOUT) {
        oled_off();
        return false;
    }

    if (oled_menu_cursor != _MENU_HIDDEN)
    {
        render_menu();
        oled_write_ln("", false);
        render_menu_logo();
    }
    else if (timer_elapsed32(oled_sleep) > OLED_TIMEOUT/2) {
        render_starrynight();
    }
    else
    {
        for (int i=0;i<14;i++) oled_write_char(' ', false);
        oled_write("WPM:", false);
        oled_write(get_u8_str(get_current_wpm(), ' '), false);
        for (int i=0;i<oled_max_chars()*3;i++)
            oled_write_char(' ', false);
        render_bongocat();
    }

    return true;
}
#endif
