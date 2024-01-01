#include QMK_KEYBOARD_H
#include "lib/callum.h"
#include "keymap_russian.h"
#include "lib/yako.h"

#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)
#define LA_MOU MO(_MOUSE)

enum keycodes {
  OS_GUI = SAFE_RANGE,
  OS_ALT,
  OS_SFT,
  OS_CTL,
  MS_AROW,
  SW_LANG,
  // Cause for yako it should be something different.
  MY_LBRC,
  MY_LCBR,
  MY_QUOT,
};

enum layer_number {
  _CANARY = 0,
  _YAKO, // in case there's no yako kbd layout set up on machine
  _NAV,
  _SYM,
  _NUM,
  _MOUSE,
};

oneshot_t oneshots[] = {
  OS_INIT(KC_LGUI, OS_GUI),
  OS_INIT(KC_LALT, OS_ALT),
  OS_INIT(KC_LSFT, OS_SFT),
  OS_INIT(KC_LCTL, OS_CTL),
};

yako_subs_t yakos[] = {
  {MY_LBRC, KC_LBRC, KC_SLSH},
  {MY_LCBR, KC_LCBR, KC_QUES},
};

size_t oneshot_length = sizeof(oneshots) / sizeof(oneshots[0]);
size_t yakos_length = sizeof(yakos) / sizeof(yakos[0]);

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

const uint16_t PROGMEM esc_combo[] = {KC_W, KC_C, COMBO_END};
const uint16_t PROGMEM bspc_combo[] = {KC_QUOT, KC_A, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_P, KC_T, COMBO_END};
const uint16_t PROGMEM mouse_layer_combo[] = {LA_NAV, KC_SPC, COMBO_END};
combo_t key_combos[] = {
  COMBO(esc_combo, KC_ESC),
  COMBO(bspc_combo, KC_BSPC),
  COMBO(tab_combo, KC_TAB),
  COMBO(mouse_layer_combo, LA_MOU),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_CANARY] = LAYOUT(
    KC_W, KC_L, KC_Y, KC_P,   KC_B,     KC_Z,    KC_F, KC_O,    KC_U,    KC_SCLN,
    KC_C, KC_R, KC_S, KC_T,   KC_G,     KC_M,    KC_N, KC_E,    KC_I,    KC_A,
    KC_Q, KC_J, KC_V, KC_D,   KC_K,     KC_X,    KC_H, KC_SLSH, KC_COMM, KC_DOT,
                      LA_NAV, KC_SPC,   KC_LSFT, LA_SYM
                     ),
  [_YAKO] = LAYOUT(
    RU_ZHE, RU_HA, RU_ER, RU_BE,  RU_TSE,   RU_SHCH, RU_GHE, RU_A,    RU_YERU, RU_EF,
    RU_ES,  RU_TE, RU_EN, RU_VE,  RU_EM,    RU_YA,   RU_KA,  RU_O,    RU_I,    RU_IE,
    RU_SHA, RU_ZE, RU_EL, RU_DE,  RU_CHE,   RU_SHTI, RU_PE,  RU_SOFT, RU_U,    RU_YU,
                          LA_NAV, KC_SPC,   KC_LSFT, LA_SYM
                     ),
  [_NAV] = LAYOUT(
    KC_ESC,  KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,   SW_LANG, KC_CAPS, KC_INS,  KC_DEL,  KC_BSPC,
    OS_GUI,  OS_ALT,  OS_SFT,  OS_CTL,  KC_TAB,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,
    KC_PSCR, KC_MUTE, QK_AREP, QK_REP,  KC_MPLY,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  CW_TOGG,
                               _______, _______,   _______, _______
                     ),
  [_SYM] = LAYOUT(
    KC_LT,   MY_LBRC, MY_LCBR, KC_LPRN, KC_TILD,   KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV,
    KC_GT,   KC_PLUS, KC_MINS, KC_EQL,  KC_UNDS,   KC_QUOT, OS_CTL,  OS_SFT,  OS_ALT,  OS_GUI,
    KC_EXLM, KC_ASTR, KC_AT,   KC_DLR,  KC_PERC,   MS_AROW, KC_BSLS, KC_AMPR, KC_HASH, KC_PIPE,
                               _______, _______,   _______, _______
                     ),
  [_NUM] = LAYOUT(
    KC_1,   KC_2,   KC_3,   KC_4,    KC_5,      KC_6,    KC_7,   KC_8,   KC_9,   KC_0,
    OS_GUI, OS_ALT, OS_SFT, OS_CTL,  KC_F11,    KC_F12,  OS_CTL, OS_SFT, OS_ALT, OS_GUI,
    KC_F1,  KC_F2,  KC_F3,  KC_F4,   KC_F5,     KC_F6,   KC_F7,  KC_F8,  KC_F9,  KC_F10,
                            _______, _______,   QK_BOOT, _______
                    ),
  [_MOUSE] = LAYOUT(
    _______, _______, _______, _______, _______,   _______, KC_BTN1, KC_BTN3, KC_BTN2, KC_WBAK,
    OS_GUI,  OS_ALT,  OS_SFT,  OS_CTL,  _______,   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WFWD,
    _______, _______, _______, _______, _______,   KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______,
                               _______, _______,   _______, _______
                    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _NAV, _SYM, _NUM);
  return state;
}

bool canary_active = true; 
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  for (size_t i = 0; i < oneshot_length; i++) {
    update_oneshot(&oneshots[i], keycode, record);
  }

  for (size_t i = 0; i < yakos_length; i++) {
    if (!update_yako(&yakos[i], keycode, record, !canary_active)) {
      return false;
    }
  }

  switch (keycode) {
  case MS_AROW:
    if (record->event.pressed) {
      const uint8_t mods = get_mods();

      if (mods & MOD_MASK_SHIFT) {
        unregister_mods(MOD_MASK_SHIFT);
        SEND_STRING("=>");
        set_mods(mods);
      } else {
        SEND_STRING("->");
      }
    }
    return false;
  case SW_LANG:
    if (record->event.pressed) {
      if (canary_active) {
        default_layer_set(1UL << _YAKO);
      } else {
        default_layer_set(1UL << _CANARY);
      }
      canary_active = !canary_active;
    }
    return false;
  }

  return true;
}
