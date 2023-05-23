#include QMK_KEYBOARD_H
#include "lib/achordion.h"

const uint16_t PROGMEM both_ctrl_esc[] = {LCTL_T(KC_T), RCTL_T(KC_N), COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  COMBO(both_ctrl_esc, KC_ESC)
};

enum layer_number {
  _CANARY = 0,
  _NAV,
  _NUM,
  _SYM,
  _FUN,
  _MEDIA,
  _BSPWM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_CANARY] = LAYOUT(
    KC_W,         KC_L,         KC_Y,         KC_P,         KC_B,       KC_Z, KC_F,         KC_O,         KC_U,         KC_QUOT,
    LGUI_T(KC_C), LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_T), KC_G,       KC_M, RCTL_T(KC_N), RSFT_T(KC_E), RALT_T(KC_I), RGUI_T(KC_A),
    KC_Q,         KC_J,         KC_V,         KC_D,         KC_K,       KC_X, KC_H,         KC_SLSH,      KC_COMM,      KC_DOT,
                              LT(_NAV, KC_BSPC), LT(_NUM, KC_TAB), LT(_FUN, KC_ENT), LT(_SYM, KC_SPC)
                     ),
  [_NAV] = LAYOUT(
    _______, _______, _______, _______, _______,       _______, LCTL(KC_TAB), RCS(KC_TAB), LGUI(KC_TAB), _______,
    _______, _______, _______, _______, _______,       KC_LEFT, KC_DOWN,      KC_UP,       KC_RGHT,      KC_CAPS,
    _______, _______, _______, _______, _______,       KC_HOME, KC_PGDN,      KC_PGUP,     KC_END,       KC_INS,
                               _______, _______,       _______, _______
                     ),
  [_NUM] = LAYOUT(
    _______, _______, _______, _______, _______,       KC_LCBR, KC_7, KC_8, KC_9, KC_RCBR,
    _______, _______, _______, _______, _______,       KC_LPRN, KC_4, KC_5, KC_6, KC_RPRN,
    _______, _______, _______, _______, _______,       KC_LBRC, KC_1, KC_2, KC_3, KC_RBRC,
                               _______, _______,       _______, KC_0
                     ),
  [_SYM] = LAYOUT(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       _______, _______, _______, _______, _______,
    KC_CIRC, KC_AMPR, KC_ASTR, KC_PLUS, KC_EQL,        _______, _______, _______, _______, _______,
    KC_GRV,  KC_TILD, KC_MINS, KC_SCLN, KC_NUHS,       _______, _______, _______, _______, _______,
                               _______, _______,       _______, _______
                     ),
  [_FUN] = LAYOUT(
    KC_F10, KC_F7, KC_F8, KC_F9, KC_COLN,              _______, _______, _______, _______, _______,
    KC_F11, KC_F4, KC_F5, KC_F6, KC_UNDS,              _______, _______, _______, _______, _______,
    KC_F12, KC_F1, KC_F2, KC_F3, KC_PIPE,              _______, _______, _______, _______, _______,
                               _______, _______,       _______, _______
                     ),
  [_MEDIA] = LAYOUT(
    QK_BOOT,    _______,      _______, _______, _______,       _______, _______, _______, _______, _______,
    LCTL(KC_C), LSFT(KC_INS), KC_PSCR, _______, _______,       KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MNXT,
    _______,    _______,      _______, _______, _______,       _______, KC_MPLY, _______, _______, _______,
                                       _______, _______,       _______, _______
                     ),
  [_BSPWM] = LAYOUT(
    SGUI(KC_1),  SGUI(KC_2),  SGUI(KC_3),  SGUI(KC_4),  SGUI(KC_5),  SGUI(KC_6),  SGUI(KC_7),  SGUI(KC_8),  SGUI(KC_9),  SGUI(KC_0), 
    SGUI(KC_F1), SGUI(KC_F2), SGUI(KC_F3), SGUI(KC_F4), SGUI(KC_F5), SGUI(KC_F6), SGUI(KC_F7), SGUI(KC_F8), SGUI(KC_F9), SGUI(KC_F10), 
    _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
                               _______, _______,       _______, _______
                     ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _NAV, _SYM, _MEDIA);
  state = update_tri_layer_state(state, _NUM, _FUN, _BSPWM);
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_achordion(keycode, record)) { return false; }

  return true;
}

void matrix_scan_user(void) {
  achordion_task();
}
