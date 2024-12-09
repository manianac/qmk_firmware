// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum wide75_layers {
    _BASE, // 0
    _FN, // 1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│   │PSc│Hom│End│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┼───┤
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│Ins│PgU│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │PgU│PgD│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┴───┘
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤───┐
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift    │ ↑ │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┬───┼───┼───┐
     * │Ctrl│GUI │Alt │                        │Alt│GUI│Ctl│   │ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────┴───┴───┴───┘   └───┴───┴───┘
     */
    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_PSCR,     KC_HOME, KC_END ,
        KC_GRV,  KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC,     KC_INS , KC_PGUP,
        KC_TAB,  KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS,     KC_DEL , KC_PGDN,
        KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,          KC_ENT ,
        KC_LSFT,          KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,          KC_RSFT,     KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC ,                            KC_RALT, KC_RGUI, RCTL_T(KC_NO), KC_LEFT,     KC_DOWN, KC_RGHT
    ),
    [_FN] = LAYOUT(
        KC_PWR , KC_SLEP, KC_WAKE, KC_NO  , KC_CPNL, KC_MYCM, KC_CALC, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_MUTE,     KC_VOLD, KC_VOLU,
        RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_SPI, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,     KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  , MS_UP  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,     KC_NO  , KC_NO  ,
        KC_SCRL, MS_LEFT, MS_DOWN, MS_RGHT, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,
        KC_LSFT, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,          KC_RSFT,              RGB_VAI,
        KC_NO  , KC_NO  , MS_BTN2,                            MS_BTN1,                            KC_NO  , KC_NO  , KC_TRNS,    RGB_RMOD, RGB_VAD, RGB_MOD
    )
};

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user (void) {
    led_t state = host_keyboard_led_state();
    uint8_t current_layer = get_highest_layer(layer_state);

    if (state.caps_lock || state.scroll_lock) {
        rgb_matrix_set_color(35, (state.caps_lock ? rgb_matrix_get_val(): 0), (state.scroll_lock ? rgb_matrix_get_val() : 0), 0);
    }

    if (current_layer == _FN)
        rgb_matrix_set_color(4, rgb_matrix_get_val(), 0, 0);

    return false;
}
#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == RCTL_T(KC_NO))
    {
        if (record->tap.count && record->event.pressed) {
            layer_invert(_FN); // Intercept tap function to move to base
            return false;
        }
    }
    return true;
}
