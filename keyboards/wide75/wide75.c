#include "wide75.h"
#include "oled_stuff.h"
#include "bongocat\bongocat.h"

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

#ifdef OLED_ENABLE
static uint16_t startup_timer;

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    startup_timer = timer_read();
    return OLED_ROTATION_180;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }

    static bool finished_logo = false;

    if (!finished_logo && (timer_elapsed(startup_timer) < OLED_BOOT_LOGO_TIMEOUT))
    {
        render_logo();
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

    uint8_t current_layer = get_highest_layer(layer_state);
    if (current_layer != 0)
    {
        char buf[64] = {0};
        usbpd_allowance_t allowance = usbpd_get_allowance();
        oled_write_ln(("BUILD: " __DATE__), false);
        oled_write(get_u16_str(get_matrix_scan_rate(), ' '), false);
        oled_write("Hz PD: ", false);
        switch (allowance)
        {
            case USBPD_500MA: oled_write_ln_P(PSTR("500mA"), false); break;
            case USBPD_1500MA: oled_write_ln_P(PSTR("1500mA"), false); break;
            case USBPD_3000MA: oled_write_ln_P(PSTR("3000mA"), false); break;
            default: oled_write_ln(get_u8_str(allowance, ' '), false); break;
        }
        strcpy(buf, rgb_matrix_name(rgb_matrix_get_mode()));
        for (int i=1; i<sizeof(buf); ++i) {
            if (buf[i] == 0) break;
            else if (buf[i] == '_') buf[i] = ' ';
            else if (buf[i-1] == ' ') buf[i] = toupper(buf[i]);
            else if (buf[i-1] != ' ') buf[i] = tolower(buf[i]);
        }
        oled_write("S:", false);
        oled_write(get_u8_str(rgb_matrix_get_sat(), ' '), false);
        oled_write(" H:", false);
        oled_write(get_u8_str(rgb_matrix_get_hue(), ' '), false);
        oled_write(" V:", false);
        oled_write_ln(get_u8_str(rgb_matrix_get_val(), ' '), false);
        oled_write_ln(buf, false);
    }
    else
        render_bongocat();

    return true;
}
#endif



bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }
#ifdef OLED_ENABLE
    oled_sleep = timer_read32();
#endif
    //dprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    dprintf("adc: %u", analogReadPin(C15));
    return true;
}
