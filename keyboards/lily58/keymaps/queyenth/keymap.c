#include QMK_KEYBOARD_H
#include <string.h>
#include "raw_hid.h"
#include "lib/callum.h"

#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)

enum keycodes {
  OS_GUI = SAFE_RANGE,
  OS_ALT,
  OS_SFT,
  OS_CTL,
  MS_AROW,
};

enum layer_number {
  _CANARY = 0,
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* CANARY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   W  |   L  |   Y  |   P  |   B  |                    |   Z  |   F  |   O  |   U  |   ;  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   C  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   A  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |   Q  |   J  |   V  |   D  |   K  |-------|    |-------|   X  |   H  |   /  |   ,  |   .  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |  NAV | /Space  /       \ Shift\  | SYM  |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_CANARY] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_W,    KC_L,    KC_Y,    KC_P,    KC_B,                     KC_Z,    KC_F,    KC_O,    KC_U,    KC_SCLN, XXXXXXX,
  XXXXXXX, KC_C,    KC_R,    KC_S,    KC_T,    KC_G,                     KC_M,    KC_N,    KC_E,    KC_I,    KC_A,    XXXXXXX,
  XXXXXXX, KC_Q,    KC_J,    KC_V,    KC_D,    KC_K,   XXXXXXX, XXXXXXX, KC_X,    KC_H,    KC_SLSH, KC_COMM, KC_DOT,  XXXXXXX,
                             XXXXXXX, XXXXXXX, LA_NAV, KC_SPC,  KC_LSFT, LA_SYM,  XXXXXXX, XXXXXXX
),
/* NAV
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  Esc | back |  fwd | voldn| volup|                    |      | caps |insert| del  | bspc |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  GUI |  ALT |  SFT |  CTL |  Tab |-------.    ,-------| Left | Down |  Up  | Right| Enter|
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      | prsc | mute |altrep|  rep | play |-------|    |-------| Home | PgDn | PgUp | End  | word |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_NAV] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_ESC,  KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU,                   _______, KC_CAPS, KC_INS,  KC_DEL,  KC_BSPC, _______,
  _______, OS_GUI,  OS_ALT,  OS_SFT,  OS_CTL,  KC_TAB,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,  _______,
  _______, KC_PSCR, KC_MUTE, QK_AREP, QK_REP,  KC_MPLY, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  CW_TOGG, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
),
/* SYM
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   <  |   [  |   {  |   (  |   ~  |                    |   ^  |   )  |   }  |   ]  |   `  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   >  |   +  |   -  |   =  |   _  |-------.    ,-------|   '  |  CTL |  SFT |  ALT |  GUI |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |   !  |   *  |   @  |   $  |   %  |-------|    |-------|  ->  |   \  |   &  |   #  |   |  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_SYM] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_LT,   KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,                   KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV,  _______,
  _______, KC_GT,   KC_PLUS, KC_MINS, KC_EQL,  KC_UNDS,                   KC_QUOT, OS_CTL,  OS_SFT,  OS_ALT,  OS_GUI,  _______,
  _______, KC_EXLM, KC_ASTR, KC_AT,   KC_DLR,  KC_PERC, _______, _______, MS_AROW, KC_BSLS, KC_AMPR, KC_HASH, KC_PIPE, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
),
/* NUM
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  GUI |  ALT |  SFT |  CTL |  F11 |-------.    ,-------|  F12 |  CTL |  SFT |  ALT |  GUI |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |-------|    |-------|  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_NUM] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  _______, OS_GUI,  OS_ALT,  OS_SFT,  OS_CTL,  KC_F11,                    KC_F12,  OS_CTL,  OS_SFT,  OS_ALT,  OS_GUI,  _______,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
                             _______, _______, _______, _______, QK_BOOT, _______, _______, _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _NAV, _SYM, _NUM);
  return state;
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

#ifdef RAW_ENABLE
uint32_t hid_timer = 0;
char hid_msgs[4][20] = {'\0'}; // 4 rows, max lenght is 19, cause of
                               // null terminator (ill be back)

void raw_hid_receive(unsigned char *data, uint8_t lenght) {
  if (strcmp((char *)data, "0clear") == 0) {
    hid_timer = 0;
    for (int i = 0; i < 4; i++) {
      memset(hid_msgs[i], '\0', sizeof(hid_msgs[i]));
    }
  } else {
    hid_timer = timer_read32();
    strncpy(hid_msgs[data[0]], (char *)data+1, 19);
    hid_msgs[data[0]][19] = '\0';
  }
}
#endif // RAW_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
#ifdef RAW_ENABLE
    if (hid_timer != 0 && timer_elapsed32(hid_timer) < HID_DATA_TIMEOUT) {
      oled_write_ln(hid_msgs[0], false);
      oled_write_ln(hid_msgs[1], false);
      oled_write_ln(hid_msgs[2], false);
      oled_write_ln(hid_msgs[3], false);
    } else {
#endif
      // If you want to change the display of OLED, you need to change here
      oled_write_ln(read_layer_state(), false);
      oled_write_ln(read_keylog(), false);
      oled_write_ln(read_keylogs(), false);
      //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
      //oled_write_ln(read_host_led_state(), false);
      //oled_write_ln(read_timelog(), false);
#ifdef RAW_ENABLE
    }
#endif
  } else {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
  if (record->event.pressed) {
    set_keylog(keycode, record);
    // set_timelog();
  }
#endif

  for (size_t i = 0; i < oneshot_length; i++) {
    update_oneshot(&oneshots[i], keycode, record);
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
  }

  return true;
}
