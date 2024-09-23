// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H


enum revtkl_layers {
    _BASE, // 0
    _FN, // 1
};

const char* revtkl_layer_str[] = {
    [_BASE] = "Base",
    [_FN] = "FN",
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│   │PSc│   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┼───┼───┼───┤
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│Num│ / │ * │ - │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┼───┼───┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │ 7 │ 8 │ 9 │   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┼───┼───┤ + │
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │ 4 │ 5 │ 6 │   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┼───┼───┼───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │Shift │ Fn│ 1 │ 2 │ 3 │   │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴───┴───┴──┬┴──┬───┼───┼───┴───┼───┤Ent│
     * │Ctrl│GUI │Alt │            Space               │Alt│GUI│Ctl│   0   │ . │   │
     * └────┴────┴────┴────────────────────────────────┴───┴───┴───┴───────┴───┴───┘
     */
    [_BASE] = LAYOUT(
        KC_ESC,   KC_F1,     KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,  KC_F12,   KC_PSCR,
        KC_GRV,   KC_1,      KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS, KC_EQL,   KC_BSPC,          KC_NUM,    KC_PSLS,   KC_PAST,   KC_PMNS,
        KC_TAB,   KC_Q,      KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC, KC_RBRC,  KC_BSLS,          KC_P7,     KC_P8,     KC_P9,     KC_PPLS,
        KC_CAPS,  KC_A,      KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,           KC_ENT ,          KC_P4,     KC_P5,     KC_P6,
        KC_LSFT,             KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH, KC_RSFT,  TG(_FN),          KC_P1,     KC_P2,     KC_P3,     KC_PENT,
        KC_LCTL,  KC_LGUI,   KC_LALT,                            KC_SPC,                                         KC_RALT,    KC_RGUI,    KC_RCTL,           KC_P0,            KC_PDOT
    ),
    [_FN] = LAYOUT(
        KC_KB_POWER,KC_UNDO, KC_CUT ,    KC_COPY,    KC_PSTE,    KC_FIND,    KC_CALC,    KC_MYCM,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  , KC_NO  ,  KC_MUTE,
        KC_NO  ,  KC_NO  ,   KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    RGB_HUI, RGB_MOD,  KC_NO  ,          KC_SCRL,   KC_NO  ,   KC_NO  ,   KC_NO  ,
        KC_NO  ,  KC_NO  ,   KC_UP  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    RGB_SAI, RGB_VAI,  KC_NO  ,          MS_WHLL,   MS_UP  ,   MS_WHLU,   KC_NO  ,
        KC_NO  ,  KC_LEFT,   KC_DOWN,    KC_RGHT,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,           KC_NO  ,          MS_LEFT,   KC_NO  ,   MS_RGHT,
        KC_LSFT,             KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  ,    KC_NO  , KC_RSFT,  TG(_FN),          MS_WHLR,   MS_DOWN,   MS_WHLD,   KC_NO  ,
        KC_NO  ,  KC_NO  ,   KC_NO  ,                                        KC_NO  ,                                                    KC_NO  , KC_NO  ,  KC_NO  ,          MS_BTN1,              MS_BTN2
    )
};

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user (void) {
    led_t state = host_keyboard_led_state();
    uint8_t current_layer = get_highest_layer(layer_state);

    if (state.caps_lock) {
        rgb_matrix_set_color(41, 255, 0, 0);
    }
    if (state.num_lock || state.scroll_lock) {
        rgb_matrix_set_color(63, state.num_lock ? 255 : 0, state.scroll_lock ? 255 : 0, 0);
    }

    if (current_layer == _FN)
        rgb_matrix_set_color(21, 255, 0, 0);

    return false;
}
#endif
