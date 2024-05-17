#include "queyenth.h"

static oneshot_t oneshots[] = {
  OS_INIT(OS_GUI, oneshot_gui_callback),
  OS_INIT(OS_ALT, oneshot_alt_callback),
  OS_INIT(OS_SFT, oneshot_shift_callback),
  OS_INIT(OS_CTL, oneshot_ctrl_callback),
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

static const smartlayer_sub_t NUMWORD_TABLE[] = {
  {KC_C, KC_1},
  {KC_R, KC_2},
  {KC_S, KC_3},
  {KC_T, KC_4},
  {KC_G, KC_5},
  {KC_M, KC_6},
  {KC_N, KC_7},
  {KC_E, KC_8},
  {KC_I, KC_9},
  {KC_A, KC_0},
};
static const size_t numwordLength = sizeof(NUMWORD_TABLE) / sizeof(NUMWORD_TABLE[0]);

static const smartlayer_sub_t MOUSEWORD_TABLE[] = {
  {KC_M, KC_MS_L},
  {KC_N, KC_MS_D},
  {KC_E, KC_MS_U},
  {KC_I, KC_MS_R},
  {KC_F, KC_BTN1},
  {KC_O, KC_BTN2},
  {KC_U, KC_BTN3},
  {KC_H, KC_WH_D},
  {KC_SLSH, KC_WH_U},
};
static const size_t mousewordLength = sizeof(MOUSEWORD_TABLE) / sizeof(MOUSEWORD_TABLE[0]);

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _NAV, _SYM, _FN);
  return state;
}

static uint8_t layoutCount = _QWERTY+1;
static uint8_t layoutActive = _CANARY;

uint8_t get_active_layout(void)
{
  return layoutActive;
}

static bool numwordStatus = false;
static bool mousewordStatus = false;

bool is_smartlayer_on(smart_layer_number smart_layer)
{
  switch (smart_layer) {
  case _NUMWORD:
    return numwordStatus;
  case _MOUSEWORD:
    return mousewordStatus;
  }

  return false;
}

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods)
{
  switch (keycode) {
  case KC_MINS:
  case KC_EQL: return KC_GT;
  }

  return KC_TRNS;
}

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

  const uint8_t mods = get_mods();
  // if emx status active, then do stuff.
  const bool isShiftedAndCanary = layoutActive == _CANARY && (mods & MOD_MASK_SHIFT);
  switch (keycode) {
  case SW_LANG:
    if (record->event.pressed) {
      layoutActive= (layoutActive + 1) % layoutCount;
      default_layer_set(1UL << layoutActive);
    }
    return false;
  case KC_COMM:
    if (isShiftedAndCanary && record->event.pressed) {
      registered_keycode = KC_SCLN;
    }
    break;
  case KC_DOT:
    if (isShiftedAndCanary && record->event.pressed) {
      registered_keycode = KC_COLN;
    }
    break;
  case KC_LT:
    if (isShiftedAndCanary && record->event.pressed) {
      registered_keycode = KC_GT;
    }
    break;
  case NW_TOGG:
    if (record->event.pressed) {
      numwordStatus = !numwordStatus;
    }
    return false;
  case MW_TOGG:
    if (record->event.pressed) {
      mousewordStatus = !mousewordStatus;
    }
    return false;
  }

  if (record->event.pressed && numwordStatus) {
    bool found = false;
    for (size_t i = 0; i < numwordLength; i++) {
      if (keycode == NUMWORD_TABLE[i].key) {
	registered_keycode = NUMWORD_TABLE[i].sub;
	found = true;
	break;
      }
    }

    numwordStatus = found;
  }

  if (record->event.pressed && mousewordStatus) {
    bool found = false;
    for (size_t i = 0; i < mousewordLength; i++) {
      if (keycode == MOUSEWORD_TABLE[i].key) {
	registered_keycode = MOUSEWORD_TABLE[i].sub;
	found = true;
	break;
      }
    }

    mousewordStatus = found;
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
