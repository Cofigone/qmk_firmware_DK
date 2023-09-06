// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    ACCEPT_CALL = SAFE_RANGE,
    DECLINE_CALL,
    DIAL_MARKED_NUMBER,
    COPY,
    PASTE,
    LOGIN,
    GS_SCREENSHOT,
    VIV_WS_2,
    VIV_WS_3,
    VIV_WS_4,
    VIV_WS_5,
    CHECK_IP
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case ACCEPT_CALL:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_LCTL(SS_LSFT("a")));
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case DECLINE_CALL:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_LCTL(SS_LSFT("c")));
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case DIAL_MARKED_NUMBER:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("c"));
            SEND_STRING(SS_DELAY(500));
            SEND_STRING(SS_LCTL(SS_LSFT("v")));
            SEND_STRING(SS_DELAY(1000));
            SEND_STRING(SS_LCTL(SS_LSFT("x")));
            SEND_STRING(SS_DELAY(500));
            register_code(KC_ENTER);
            unregister_code(KC_ENTER);
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case COPY:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("c"));
            SEND_STRING(SS_DELAY(500));
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case PASTE:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("v"));
            SEND_STRING(SS_DELAY(500));
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case LOGIN:
        if (record->event.pressed) {
            SEND_STRING("admin");
            SEND_STRING(SS_DELAY(300));
            register_code(KC_TAB);
            unregister_code(KC_TAB);
            SEND_STRING("kasse");
            SEND_STRING(SS_DELAY(300));
            register_code(KC_ENTER);
            unregister_code(KC_ENTER);
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case VIV_WS_2:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LSFT("2")));
            SEND_STRING(SS_DELAY(500));
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case VIV_WS_3:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LSFT("3")));
            SEND_STRING(SS_DELAY(500));
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case VIV_WS_4:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LSFT("4")));
            SEND_STRING(SS_DELAY(500));
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case VIV_WS_5:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_LSFT("5")));
            SEND_STRING(SS_DELAY(500));
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case GS_SCREENSHOT:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("<"));
            SEND_STRING(SS_DELAY(500));
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case CHECK_IP:
        if (record->event.pressed) {
            register_code(KC_LEFT_GUI);
            register_code(KC_R);
            SEND_STRING(SS_DELAY(500));
            unregister_code(KC_LEFT_GUI);
            unregister_code(KC_LEFT_GUI);

            SEND_STRING("cmd");
            SEND_STRING(SS_DELAY(200));
            register_code(KC_ENTER);
            unregister_code(KC_ENTER);
            SEND_STRING(SS_DELAY(1000));

            SEND_STRING("ipconfig");
            SEND_STRING(SS_DELAY(200));
            register_code(KC_ENTER);
            unregister_code(KC_ENTER);

        } else {
            // when keycode QMKBEST is released
        }
        break;
    }
    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_ortho_3x4(
        VIV_WS_2,   VIV_WS_3,   VIV_WS_4,   VIV_WS_5,
        KC_B,   LOGIN,   CHECK_IP,   KC_A,
        ACCEPT_CALL,   DECLINE_CALL,   DIAL_MARKED_NUMBER,   PASTE
    )
};
