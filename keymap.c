#include QMK_KEYBOARD_H

#include "oneshot.h"

#define LA_RIGHT  MO(RIGHT)
#define LA_LEFT   MO(LEFT)
#define DF_MTGAP  DF(MTGAP)
#define DF_QWERTY DF(QWERTY)

enum layers {
    MTGAP,
    QWERTY,
    RIGHT,
    LEFT,
    BOTH,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SFT = SAFE_RANGE,
    OS_CTL,
    OS_ALT,
    OS_CMD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT_ortho_4x12(
                KC_Y,   KC_P, KC_O,       KC_U, KC_J,    KC_NO, KC_NO,   KC_K, KC_D,      KC_L, KC_C,  KC_W,
                KC_I,   KC_N, KC_E,       KC_A, KC_COMM, KC_NO, KC_NO,   KC_M, KC_H,      KC_T, KC_S,  KC_R,
                KC_Q,   KC_Z, KC_QUOT,  KC_DOT, KC_SCLN, KC_NO, KC_NO,   KC_B, KC_F,      KC_G, KC_V,  KC_X,
                KC_NO, KC_NO, KC_NO,   LA_LEFT, KC_LSFT, KC_NO, KC_NO, KC_SPC, LA_RIGHT, KC_NO, KC_NO, KC_NO
                ),

	[1] = LAYOUT_ortho_4x12(
                KC_Q,  KC_W,  KC_E,  KC_R,    KC_T,    KC_NO, KC_NO, KC_Y,   KC_U,     KC_I,    KC_O,   KC_P,
                KC_A,  KC_S,  KC_D,  KC_F,    KC_G,    KC_NO, KC_NO, KC_H,   KC_J,     KC_K,    KC_L,   KC_SCLN,
                KC_Z,  KC_X,  KC_C,  KC_V,    KC_B,    KC_NO, KC_NO, KC_N,   KC_M,     KC_COMM, KC_DOT, KC_QUOT,
                KC_NO, KC_NO, KC_NO, LA_LEFT, KC_LSFT, KC_NO, KC_NO, KC_SPC, LA_RIGHT, KC_NO,   KC_NO,  KC_NO
                ),

	[2] = LAYOUT_ortho_4x12(
                KC_1,   KC_2,    KC_3,   KC_4,    KC_5,    KC_NO, KC_NO, KC_6,    KC_7,    KC_8,    KC_9,   KC_0,
                KC_ESC, KC_GRV,  KC_EQL, KC_MINS, KC_LPRN, KC_NO, KC_NO, KC_RPRN, OS_CMD,  OS_ALT,  OS_CTL, OS_SFT,
                KC_LT,  KC_ASTR, KC_DLR, KC_GT,   KC_LBRC, KC_NO, KC_NO, KC_RBRC, KC_DOT,  KC_COMM, KC_NO,  KC_AMPR,
                KC_NO,  KC_NO,   KC_NO,  LA_LEFT, KC_TAB,  KC_NO, KC_NO, KC_SPC,  KC_TRNS, KC_NO,   KC_NO,  KC_NO
                ),

	[3] = LAYOUT_ortho_4x12(
                KC_1,   KC_2,   KC_3,    KC_4,    KC_5,    KC_NO, KC_NO, KC_6,    KC_7,     KC_8,    KC_9,    KC_0,
                OS_SFT, OS_CTL, OS_ALT,  OS_CMD,  KC_LPRN, KC_NO, KC_NO, KC_RPRN, KC_MINS,  KC_SLSH, KC_BSLS, KC_ENT,
                KC_NO,  KC_NO,  KC_COMM, KC_DOT,  KC_LBRC, KC_NO, KC_NO, KC_RBRC, KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT,
                KC_NO,  KC_NO,  KC_NO,   KC_TRNS, KC_LSFT, KC_NO, KC_NO, KC_BSPC, LA_RIGHT, KC_NO,   KC_NO,   KC_NO
                ),

	[4] = LAYOUT_ortho_4x12(
                KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO, KC_NO, KC_F6,   KC_F7,    KC_F8,     KC_F9, KC_F10,
                KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DEL,  KC_NO, KC_NO, KC_BSPC, KC_LEFT,  KC_DOWN,   KC_UP, KC_RGHT,
                RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_TOG, KC_NO, KC_NO, KC_NO,   DF_MTGAP, DF_QWERTY, KC_NO, KC_NO,
                KC_NO,   KC_NO,   KC_NO,   KC_TRNS, KC_LSFT, KC_NO, KC_NO, KC_SPC,  KC_TRNS,  KC_NO,     KC_NO, KC_NO
                ),

};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_RIGHT:
    case LA_LEFT:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_RIGHT:
    case LA_LEFT:
    case KC_LSFT:
    case OS_SFT:
    case OS_CTL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, RIGHT, LEFT, BOTH);
}
