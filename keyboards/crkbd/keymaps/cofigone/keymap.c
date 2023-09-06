/*
Copyright 2022 Joe Scotto

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <string.h>

enum corny_layers { _QWERTZ, _LOWER, _RAISE, _ADJUST };

enum corny_keycodes { QWERTZ = SAFE_RANGE, LOWER, RAISE, ADJUST, BACKLIT, RGBRST };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTZ] = LAYOUT(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_LBRC, KC_NUHS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SCLN, KC_QUOT,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_LGUI, MO(1), KC_SPC, KC_ENT, MO(2), MO(3)
        //`--------------------------'  `--------------------------'

        ),

    [_LOWER] = LAYOUT(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, KC_GRV, KC_WH_U, KC_NUHS, KC_NO, KC_PGUP, KC_LEFT, KC_UP, KC_RGHT, KC_NO, KC_RBRC, KC_HOME,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_NO, KC_WH_D, KC_NO, KC_NO, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL, KC_INS, KC_END,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_ESC, KC_TRNS, KC_SPC, KC_ENT, MO(3), KC_TRNS),
    //`--------------------------'  `--------------------------'

    [_RAISE] = LAYOUT(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TAB, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F12,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_EQL, KC_MINS, KC_EQL, KC_PSLS, KC_BSLS, KC_GRV,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_NUBS, LSFT(KC_NUBS), KC_CIRC, KC_MINS, KC_SLSH, KC_UNDS, KC_PLUS, KC_RBRC, KC_RCBR, KC_PIPE, RGB_TOG,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_ESC, KC_TRNS, KC_SPC, KC_ENT, KC_TRNS, KC_TRNS),
    //`--------------------------'  `--------------------------'

    [_ADJUST] = LAYOUT(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        LALT(KC_TAB), LSFT(KC_1), LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0), KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, RALT(KC_Q), KC_NO, RALT(KC_E), KC_NO, KC_RBRC, LSFT(KC_7), RALT(KC_7), RALT(KC_8), RALT(KC_9), RALT(KC_0), KC_UNDS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_SLSH, RALT(KC_MINS), KC_BSLS, RGB_MODE_FORWARD, KC_DEL, RALT(KC_NUBS), LSFT(KC_1),
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS)
    //`--------------------------'  `--------------------------'

};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
        layer_on(layer3);
    } else {
        layer_off(layer3);
    }
}

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_get_mode();
#endif
}

#ifdef OLED_ENABLE

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void        set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // If you want to change the display of OLED, you need to change here
        oled_write(read_layer_state(), false);
        oled_write(read_keylog(), false);
        // oled_write_ln(read_keylogs(), false);
        // oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
        // oled_write_ln(read_host_led_state(), false);
        // oled_write_ln(read_timelog(), false);
    } else {
        oled_write(read_logo(), false);
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_ENABLE
        set_keylog(keycode, record);
#endif
        // set_timelog();
    }

    switch (keycode) {
        case QWERTZ:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTZ);
            }
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case RGB_MOD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_mode(RGB_current_mode);
                rgblight_step();
                RGB_current_mode = rgblight_get_mode();
            }
#endif
            return false;
        case RGBRST:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_mode = rgblight_get_mode();
            }
#endif
            break;
    }
    return true;
}
