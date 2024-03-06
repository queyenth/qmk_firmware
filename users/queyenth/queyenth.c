#include "queyenth.h"

static oneshot_t oneshots[] = {
  OS_INIT(KC_LGUI, OS_GUI),
  OS_INIT(KC_LALT, OS_ALT),
  OS_INIT(KC_LSFT, OS_SFT),
  OS_INIT(KC_LCTL, OS_CTL),
};
static const size_t oneshot_length = sizeof(oneshots) / sizeof(oneshots[0]);

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

static const numword_t NUMWORD_TABLE[] = {
  {KC_F, KC_7},
  {KC_O, KC_8},
  {KC_U, KC_9},
  {KC_N, KC_4},
  {KC_E, KC_5},
  {KC_I, KC_6},
  {KC_H, KC_1},
  {KC_UNDS, KC_2},
  {KC_COMM, KC_3},
  {KC_X, KC_0},
  {KC_G, KC_EQL},
  {KC_S, KC_MINS},
  {KC_R, KC_PLUS},
  {KC_D, KC_DLR},
  {KC_K, KC_PERC},
  {KC_W, KC_SLSH},
  {KC_Z, KC_LT},
  {KC_M, KC_GT},
};
static const size_t numwordLength = sizeof(NUMWORD_TABLE) / sizeof(NUMWORD_TABLE[0]);

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _NAV, _SYM, _FN);
  return state;
}

static uint8_t langCount = _QWERTY+1;
static uint8_t lang = _CANARY;
static bool numwordStatus = false;

bool process_record_user_queyenth(uint16_t keycode, keyrecord_t *record)
{
   
  static uint16_t registered_keycode = KC_NO;

  if (registered_keycode != KC_NO) {
    unregister_code16(registered_keycode);
    registered_keycode = KC_NO;
  }
  
  for (size_t i = 0; i < oneshot_length; i++) {
    update_oneshot(&oneshots[i], keycode, record);
  }

  if (record->event.pressed && numwordStatus) {
    bool found = false;
    for (size_t i = 0; i < numwordLength; i++) {
      if (keycode == NUMWORD_TABLE[i].key) {
	registered_keycode = NUMWORD_TABLE[i].num;
	found = true;
	break;
      }
    }

    if (!found) {
      numwordStatus = false;
    }
  }

  const uint8_t mods = get_mods();
  const bool isShifted = mods & MOD_MASK_SHIFT;
  switch (keycode) {
  case SW_LANG:
    if (record->event.pressed) {
      lang = (lang + 1) % langCount;
      default_layer_set(1UL << lang);
      //switch_input_lang_next(langConfig, langConfigCount);
    }
    return false;
  case NW_TOGG:
    if (record->event.pressed) {
      numwordStatus = !numwordStatus;
    }
    return false;
  case KC_DOT:
    if (isShifted && record->event.pressed) {
      registered_keycode = KC_COLN;
    }
    break;
  case KC_COMM:
    if (isShifted && record->event.pressed) {
      registered_keycode = KC_SCLN;
    }
    break;
  case KC_UNDS:
    if (isShifted && record->event.pressed) {
      registered_keycode = KC_SLSH;
    }
    break;
  }

  if (registered_keycode != KC_NO) {
    if (IS_QK_MODS(registered_keycode) && (QK_MODS_GET_MODS(registered_keycode) & MOD_LSFT) != 0) {
      register_code16(registered_keycode);
    } else {
      unregister_mods(MOD_MASK_SHIFT);
      register_code16(registered_keycode);
      set_mods(mods);
    }
    return false;
  }

  return true;
}
