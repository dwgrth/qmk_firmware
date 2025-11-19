/* Copyright 2024 Yiancar-Designs
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
#include "keymap_us.h"
#include "modifiers.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H

enum my_layers {
    LY_BASE  = 0,
    LY_MEDIA = 1,
    LY_PUNC  = 2,
    LY_QMK   = 3,
};

enum my_keycodes {
    RET_RGB = QK_USER_0,
    KC_NOOP = KC_NO,
    MO_MDIA = MO(LY_MEDIA),
    MO_QMK_ = MO(LY_QMK),
    FN_MODS = MOD_BIT(KC_LALT) | MOD_BIT(KC_RSFT),
};

// This is called when the override activates and deactivates. Enable the fn layer on activation and disable on deactivation
bool momentary_layer(bool key_down, void *layer) {
    if (key_down) {
        layer_on((uint8_t)(uintptr_t)layer);
    } else {
        layer_off((uint8_t)(uintptr_t)layer);
    }

    return false;
}

// clang-format off
const key_override_t fn_override = ((const key_override_t)
                                   {.trigger_mods          = FN_MODS,
                                    .layers                = ~(1 << LY_PUNC),
                                    .suppressed_mods       = FN_MODS,
                                    .options               = ko_option_no_unregister_on_other_key_down,
                                    .negative_mod_mask     = (uint8_t) ~(FN_MODS),
                                    .custom_action         = momentary_layer,
                                    .context               = (void *) LY_PUNC,
                                    .trigger               = KC_NO,
                                    .replacement           = KC_NO,
                                    .enabled               = NULL});
// clang-format on

const key_override_t *key_overrides[] = {
    &fn_override,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RET_RGB:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL:
                        rgb_matrix_set_flags(LED_FLAG_INDICATOR);
                        break;
                    default:
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        break;
                }
            }
            return false;
    }
    return true;
}

// clang-format off

// [?] = LAYOUT_tkl_ansi_tsangan( /* template */
//     _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,          _______,
//     _______, _______, _______,                   _______,                                              _______, _______, _______, _______, _______, _______),

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[LY_BASE] = LAYOUT_tkl_ansi_tsangan( /* Base */
    KC_NOOP,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SCRL, KC_PAUS,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT,          KC_UP,
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                                               KC_RALT, KC_RCTL, MO_MDIA,   KC_LEFT, KC_DOWN, KC_RGHT),

[LY_MEDIA] = LAYOUT_tkl_ansi_tsangan( /* media, etc */
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RET_RGB, _______, KC_MUTE,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_MSTP, KC_VOLU,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_VOLD,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,          _______,
    _______, MO_QMK_, _______,                   _______,                                              _______, _______, _______, _______, _______, _______),

[LY_PUNC] = LAYOUT_tkl_ansi_tsangan( /* template */
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_PERC, KC_CIRC, KC_AMPR, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,          _______,
    _______, _______, _______,                   _______,                                              _______, _______, _______, _______, _______, _______),

[LY_QMK] = LAYOUT_tkl_ansi_tsangan( /* quantum */
    QK_BOOT,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,          _______,
    _______, _______, _______,                   _______,                                              _______, _______, _______, _______, _______, _______),

};
