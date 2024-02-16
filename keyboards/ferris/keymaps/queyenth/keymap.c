#include QMK_KEYBOARD_H
#include "lib/callum.h"
#include "keymap_russian.h"

#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)

enum keycodes {
  OS_GUI = SAFE_RANGE,
  OS_ALT,
  OS_SFT,
  OS_CTL,
  MS_AROW,
  SW_LANG
};

enum layer_number {
  _CANARY = 0,
  _QWERTY,
  _NAV,
  _SYM,
  _NUM,
};

oneshot_t oneshots[] = {
  OS_INIT(KC_LGUI, OS_GUI),
  OS_INIT(KC_LALT, OS_ALT),
  OS_INIT(KC_LSFT, OS_SFT),
  OS_INIT(KC_LCTL, OS_CTL),
};

size_t oneshot_length = sizeof(oneshots) / sizeof(oneshots[0]);

bool is_oneshot_cancel_key(uint16_t keycode) {
  switch (keycode) {
  case LA_SYM:
  case LA_NAV:
    return true;
  default:
    return false;
  }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
  switch (keycode) {
  case LA_SYM:
  case LA_NAV:
  case OS_GUI:
  case OS_ALT:
  case OS_SFT:
  case OS_CTL:
    return true;
  default:
    return false;
  }
}

const uint16_t PROGMEM scln_combo[] = {KC_QUOT, KC_A, COMBO_END};
combo_t key_combos[] = {
  COMBO(scln_combo, KC_SCLN),
};

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
    KC_ESC,  KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,   SW_LANG, KC_CAPS, KC_INS,  KC_DEL,  KC_BSPC,
    OS_GUI,  OS_ALT,  OS_SFT,  OS_CTL,  KC_TAB,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,
    KC_PSCR, KC_MUTE, QK_AREP, QK_REP,  KC_MPLY,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  CW_TOGG,
                               _______, _______,   _______, _______
                     ),
  [_SYM] = LAYOUT(
    KC_DQUO, KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,   KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_COLN,
    KC_EXLM, KC_PLUS, KC_MINS, KC_UNDS, KC_EQL,    KC_SCLN, OS_CTL,  OS_SFT,  OS_ALT,  OS_GUI,
    KC_GRV,  KC_ASTR, KC_AT,   KC_DLR,  KC_PERC,   KC_BSLS, QK_AREP, KC_AMPR, KC_HASH, KC_PIPE,
                               _______, _______,   _______, _______
                     ),
  [_NUM] = LAYOUT(
    KC_1,   KC_2,   KC_3,   KC_4,    KC_5,      KC_6,    KC_7,   KC_8,   KC_9,   KC_0,
    OS_GUI, OS_ALT, OS_SFT, OS_CTL,  KC_F11,    KC_F12,  OS_CTL, OS_SFT, OS_ALT, OS_GUI,
    KC_F1,  KC_F2,  KC_F3,  KC_F4,   KC_F5,     KC_F6,   KC_F7,  KC_F8,  KC_F9,  KC_F10,
                            _______, _______,   QK_BOOT, _______
                    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _NAV, _SYM, _NUM);
  return state;
}

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
  switch (keycode) {
  case KC_MINS:
  case KC_EQL: return MS_AROW;
  }

  return KC_TRNS;
}

enum LANG_LAYOUTS {
  LangCanary = 0,
  LangQwerty = 1,
};

uint8_t lang = LangCanary; 
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  for (size_t i = 0; i < oneshot_length; i++) {
    update_oneshot(&oneshots[i], keycode, record);
  }

  switch (keycode) {
  case MS_AROW:
    if (record->event.pressed) {
      SEND_STRING(">");
    }
    return false;
  case SW_LANG:
    if (record->event.pressed) {
      lang = (lang + 1) % 2; // always between 0-1
      switch (lang) {
      case LangCanary:
        default_layer_set(1UL << _CANARY);
        break;
      case LangQwerty:
        default_layer_set(1UL << _QWERTY);
        break;
      }
    }
    return false;
  }

  return true;
}
