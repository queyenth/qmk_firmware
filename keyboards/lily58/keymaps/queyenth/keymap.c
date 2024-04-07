#include QMK_KEYBOARD_H
#include <string.h>

#include "lib/pomodoro.h"
#include "lib/matrix_animation.h"

// From user space
#include "queyenth.h"

enum keycodes_lily {
  // pomodoro keys
  POM_ST = QQ_LAST, // start/stop
  POM_INC, // Increase time
};

void keyboard_post_init_user(void) {
  //debug_enable = true;
#ifdef POMODORO_ENABLE
  eeprom_pomodoro();
#endif
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_CANARY] = LAYOUT(
  KC_ESC,  KC_1, KC_2, KC_3,   KC_4,   KC_5,                    KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MUTE,
  KC_LBRC, KC_W, KC_L, KC_Y,   KC_P,   KC_B,                    KC_Z,   KC_F,    KC_O,    KC_U,    KC_QUOT, KC_RBRC,
  KC_LCTL, KC_C, KC_R, KC_S,   KC_T,   KC_G,                    KC_M,   KC_N,    KC_E,    KC_I,    KC_A,    KC_RCTL,
  KC_LALT, KC_Q, KC_J, KC_V,   KC_D,   KC_K,   KC_TAB, KC_ENT,  KC_X,   KC_H,    KC_SLSH, KC_COMM, KC_DOT,  KC_APP,
                       POM_ST, QK_REP, LA_NAV, KC_SPC, KC_LSFT, LA_SYM, QK_AREP, POM_INC
),
[_QWERTY] = LAYOUT(
  KC_ESC,  KC_1, KC_2, KC_3,   KC_4,   KC_5,                    KC_6,   KC_7,    KC_8,    KC_9,   KC_0,    KC_QUOT,
  KC_LBRC, KC_Q, KC_W, KC_E,   KC_R,   KC_T,                    KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,    KC_RBRC,
  KC_LCTL, KC_A, KC_S, KC_D,   KC_F,   KC_G,                    KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN, KC_RCTL,
  KC_LALT, KC_Z, KC_X, KC_C,   KC_V,   KC_B,   KC_TAB, KC_ENT,  KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_APP,
                       POM_ST, QK_REP, LA_NAV, KC_SPC, KC_LSFT, LA_SYM, QK_AREP, POM_INC
),
[_NAV] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_ESC,  KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,                   KC_MPLY, KC_CAPS, KC_INS,  KC_DEL,  KC_BSPC, _______,
  _______, OS_GUI,  OS_ALT,  OS_SFT,  OS_CTL,  KC_TAB,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,  _______,
  _______, KC_PSCR, KC_MUTE, MW_TOGG, NW_TOGG, SW_LANG, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  CW_TOGG, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
),
[_SYM] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_GRV,  KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,                   KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS, _______,
  _______, KC_EXLM, KC_PLUS, KC_MINS, KC_UNDS, KC_EQL,                    KC_AMPR, OS_CTL,  OS_SFT,  OS_ALT,  OS_GUI,  _______,
  _______, KC_AT,   KC_LT,   KC_GT,   KC_DLR,  KC_HASH, _______, _______, KC_PERC, KC_ASTR, KC_SCLN, KC_COLN, KC_PIPE, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
),
[_FN] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  _______, OS_GUI,  OS_ALT,  OS_SFT,  OS_CTL,  KC_F11,                    KC_F12,  OS_CTL,  OS_SFT,  OS_ALT,  OS_GUI,  _______,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
                             _______, _______, _______, _______, QK_BOOT, _______, _______, _______
)
};

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {

#ifdef MATRIX_HACKER_ANIMATION
  init_matrix_animation();
#endif

  return OLED_ROTATION_270;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(uint8_t);

char active_mods[5] = {0};
bool oled_task_user(void) {
  if (is_keyboard_master()) {
    if (is_caps_word_on()) {
      oled_write_ln("CAPW", false);
    } else if (is_smartlayer_on(_NUMWORD)) {
      oled_write_ln("NUMW", false);
    } else if (is_smartlayer_on(_MOUSEWORD)) {
      oled_write_ln("MOUW", false);
    } else {
      oled_write_ln(read_layer_state(get_active_layout()), false);
    }
    const uint8_t mods = get_mods();
    snprintf(active_mods, sizeof(active_mods),
	     "%c%c%c%c",
	     ((mods&MOD_MASK_GUI)   ? 'G' : '-'),
	     ((mods&MOD_MASK_ALT)   ? 'A' : '-'),
	     ((mods&MOD_MASK_SHIFT) ? 'S' : '-'),
	     ((mods&MOD_MASK_CTRL)  ? 'C' : '-')
	     );
    oled_write_ln(active_mods, false);

#ifdef POMODORO_ENABLE
    update_pomodoro(18);
#endif
      
  } else {
#ifdef MATRIX_HACKER_ANIMATION
    render_matrix_animation();
#endif
  }
  return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_user_queyenth(keycode, record)) {
    return false;
  }

#ifdef POMODORO_ENABLE
  if (!process_pomodoro(POM_ST, POM_INC, keycode, record)) {
    return false;
  }
#endif

  return true;
}
