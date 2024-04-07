#include QMK_KEYBOARD_H

#include "queyenth.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_CANARY] = LAYOUT(
    KC_W, KC_L, KC_Y, KC_P,   KC_B,     KC_Z,    KC_F, KC_O,    KC_U,    KC_QUOT,
    KC_C, KC_R, KC_S, KC_T,   KC_G,     KC_M,    KC_N, KC_E,    KC_I,    KC_A,
    KC_Q, KC_J, KC_V, KC_D,   KC_K,     KC_X,    KC_H, KC_SLSH, KC_COMM, KC_DOT,
                      LA_NAV, KC_SPC,   KC_LSFT, LA_SYM
                     ),
  [_QWERTY] = LAYOUT(
    KC_Q, KC_W, KC_E, KC_R,   KC_T,     KC_Y,    KC_U, KC_I,    KC_O,    KC_P,
    KC_A, KC_S, KC_D, KC_F,   KC_G,     KC_H,    KC_J, KC_K,    KC_L,    KC_SCLN,
    KC_Z, KC_X, KC_C, KC_V,   KC_B,     KC_N,    KC_M, KC_COMM, KC_DOT,  KC_SLSH,
                      LA_NAV, KC_SPC,   KC_LSFT, LA_SYM
                     ),
  [_NAV] = LAYOUT(
    KC_ESC,  KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,   KC_MPLY, KC_CAPS, KC_INS,  KC_DEL,  KC_BSPC,
    OS_GUI,  OS_ALT,  OS_SFT,  OS_CTL,  KC_TAB,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,
    KC_PSCR, KC_MUTE, MW_TOGG, NW_TOGG, SW_LANG,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  CW_TOGG,
                               _______, _______,   _______, _______
                     ),
  [_SYM] = LAYOUT(
    KC_GRV,  KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,   KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS,
    KC_EXLM, KC_PLUS, KC_MINS, KC_UNDS, KC_EQL,    KC_SCLN, OS_CTL,  OS_SFT,  OS_ALT,  OS_GUI,
    KC_AT,   KC_LT,   KC_GT,   KC_DLR,  KC_HASH,   KC_PERC, KC_ASTR, KC_SCLN, KC_COLN, KC_PIPE,
                               _______, _______,   _______, _______
                     ),
  [_FN] = LAYOUT(
    KC_1,   KC_2,   KC_3,   KC_4,    KC_5,      KC_6,    KC_7,   KC_8,   KC_9,   KC_0,
    OS_GUI, OS_ALT, OS_SFT, OS_CTL,  KC_F11,    KC_F12,  OS_CTL, OS_SFT, OS_ALT, OS_GUI,
    KC_F1,  KC_F2,  KC_F3,  KC_F4,   KC_F5,     KC_F6,   KC_F7,  KC_F8,  KC_F9,  KC_F10,
                            _______, _______,   QK_BOOT, _______
                    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return process_record_user_queyenth(keycode, record);
}
