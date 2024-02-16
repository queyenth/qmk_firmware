#include QMK_KEYBOARD_H
#include <string.h>
#include "raw_hid.h"
#include "lib/callum.h"

#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)
#define LA_RGB MO(_RGB)
#define LA_NUM TG(_NUMPAD)

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
  _RGB,
  _NUMPAD
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
  case LA_RGB:
  case LA_NUM:
    return true;
  default:
    return false;
  }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
  switch (keycode) {
  case LA_SYM:
  case LA_NAV:
  case LA_RGB:
  case LA_NUM:
  case OS_GUI:
  case OS_ALT:
  case OS_SFT:
  case OS_CTL:
    return true;
  default:
    return false;
  }
}

#ifdef RGBLIGHT_LAYERS
const rgblight_segment_t PROGMEM sym_layer[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                       {6, 3, HSV_GREEN}
                                                                       );
const rgblight_segment_t PROGMEM nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                       {0, 3, HSV_CYAN}
                                                                       );
const rgblight_segment_t PROGMEM num_layer[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                       {6, 3, HSV_RED},
                                                                       {0, 3, HSV_RED}
                                                                       );

const rgblight_segment_t PROGMEM numpad_layer[] = RGBLIGHT_LAYER_SEGMENTS(
                                                                          {6, 3, HSV_CYAN},
                                                                          {0, 3, HSV_CYAN}
                                                                          );

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
                                                                            sym_layer,
                                                                            nav_layer,
                                                                            num_layer,
                                                                            numpad_layer
                                                                            );
#endif

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_LAYERS
  rgblight_layers = rgb_layers;
#endif
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* CANARY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Tab |   W  |   L  |   Y  |   P  |   B  |                    |   Z  |   F  |   O  |   U  |   '  | bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Ctrl |   C  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   A  |   ;  |
 * |------+------+------+------+------+------|  rep  |    | arep  |------+------+------+------+------+------|
 * |  Alt |   Q  |   J  |   V  |   D  |   K  |-------|    |-------|   X  |   H  |   /  |   ,  |   .  |  ent |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |  gui |  NUM |  NAV | /Space  /       \ Shift\  | SYM  | RGB  |  gui |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_CANARY] = LAYOUT(
  KC_ESC,  KC_1, KC_2, KC_3,    KC_4,    KC_5,                    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_DEL,
  KC_TAB,  KC_W, KC_L, KC_Y,    KC_P,    KC_B,                    KC_Z,    KC_F,   KC_O,    KC_U,    KC_QUOT, KC_BSPC,
  KC_LCTL, KC_C, KC_R, KC_S,    KC_T,    KC_G,                    KC_M,    KC_N,   KC_E,    KC_I,    KC_A,    KC_SCLN,
  KC_LALT, KC_Q, KC_J, KC_V,    KC_D,    KC_K,   QK_REP, QK_AREP, KC_X,    KC_H,   KC_SLSH, KC_COMM, KC_DOT,  KC_ENT,
                       KC_LGUI, LA_NUM,  LA_NAV, KC_SPC, KC_LSFT, LA_SYM,  LA_RGB, KC_RGUI
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
 * |      |   "  |   [  |   {  |   (  |   ~  |                    |   ^  |   )  |   }  |   ]  |   :  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   +  |   -  |   _  |   =  |-------.    ,-------|   ;  |  CTL |  SFT |  ALT |  GUI |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |   `  |   *  |   @  |   $  |   %  |-------|    |-------|   \  | arep |   &  |   #  |   |  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_SYM] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_DQUO, KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,                   KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_COLN, _______,
  _______, KC_EXLM, KC_PLUS, KC_MINS, KC_UNDS, KC_EQL,                    KC_SCLN, OS_CTL,  OS_SFT,  OS_ALT,  OS_GUI,  _______,
  _______, KC_GRV,  KC_ASTR, KC_AT,   KC_DLR,  KC_PERC, _______, _______, KC_BSLS, QK_AREP, KC_AMPR, KC_HASH, KC_PIPE, _______,
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
                ),
[_RGB] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, RGB_SAD, RGB_SAI, RGB_HUD, RGB_HUI,                   _______, _______, _______, _______, _______, _______,
  _______, _______, RGB_VAD, RGB_VAI, RGB_MOD, RGB_TOG,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
                ),
[_NUMPAD] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
  _______, _______, KC_7,    KC_8,    KC_9,    _______,                       _______, _______, _______, _______, _______, _______,
  _______, _______, KC_4,    KC_5,    KC_6,    _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, KC_1,    KC_2,    KC_3,    _______,     _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______,     _______, _______, _______, _______, _______
                )
};

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _NAV, _SYM, _NUM);
#ifdef RGBLIGHT_LAYERS
  rgblight_set_layer_state(0, layer_state_cmp(state, _SYM));
  rgblight_set_layer_state(1, layer_state_cmp(state, _NAV));
  rgblight_set_layer_state(2, layer_state_cmp(state, _NUM));
  rgblight_set_layer_state(3, layer_state_cmp(state, _NUMPAD));
#endif
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

typedef struct {
  uint8_t col;
  uint8_t line;
  uint8_t len;
  uint8_t index;
} matrix_start_pos_t;

matrix_start_pos_t matrix_code[] = {
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
};

uint32_t matrix_code_timer = 0;

const uint8_t q_get_random(uint8_t min, uint8_t max) {
#if defined(__AVR_ATmega32U4__)
  uint8_t ran = (TCNT0 + TCNT1 + TCNT3 + TCNT4);
#else
  uint8_t ran = rand();
#endif

  return ((ran%max)+min);
}

const char q_get_random_char(void) {
  return (char)q_get_random(33, 93);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  // TODO: right now I don't care if it starts at the same position.
  for (size_t i = 0; i < 5; i++) {
    matrix_code[i].col = i;
    matrix_code[i].len = q_get_random(3, oled_max_lines()>>1);
    matrix_code[i].line = q_get_random(0, oled_max_lines()-matrix_code[i].len-1);
  }

  matrix_code_timer = timer_read32();

  //if (!is_keyboard_master())
  //  return OLED_ROTATION_180;  // flips the display 180 degrees if offhand

  return OLED_ROTATION_270;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
const char *read_rgb_info(void);

void render_rabbit(void) {
  static const char PROGMEM raw_logo[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,248,  4,  4,  4,248,  4,  4,  4,248,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0, 15,  8,  8,  8, 15,  8,200, 16, 32, 64,128,  0,  0,  0,  0,  0,128,128,128, 96, 16,  8,  4,  4, 66, 34, 34, 33, 65,134,  8, 16, 16, 32, 32, 32, 32, 32,224, 32, 16,  8,  6,  1,  0,  0,  0, 15, 16, 16, 23, 24, 32, 64,128,128,128,128,128,160,144,152,247, 16, 16,254,128,128,152,150,225,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224, 16,  8,196,242, 50,  2,  2,  2,  2,  2,  6, 58,194, 58,250,250,250,250,250,244,232, 16,224,  0,  0,  0,  0,  0,  0,  0,  0,  7,  8, 16, 32, 64, 64, 64, 64, 64, 64, 64,112, 78, 81, 94, 95, 95, 95, 95, 95, 47, 23,  8,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
  };
  oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

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
      oled_write_ln(read_layer_state(), false);
      oled_write_ln("RGB", false);
      oled_write_ln(read_rgb_info(), false);
      render_rabbit();
#ifdef RAW_ENABLE
    }
#endif
  } else {
    if (timer_elapsed32(matrix_code_timer) >= 200) { // 5 fps
      matrix_code_timer = timer_read32();
      for (size_t i = 0; i < 5; i++) {
        // First of all draw the char and decrease the len.
        if (matrix_code[i].index >= matrix_code[i].len) {
          // Start clearing up.
          uint8_t line = matrix_code[i].line + matrix_code[i].index - matrix_code[i].len;
          if (line >= oled_max_lines()) {
            line = oled_max_lines() - 1;
          }
          oled_set_cursor(matrix_code[i].col, line);
          oled_write_char(' ', false);
          matrix_code[i].len--;
          if (matrix_code[i].len == 0) {
            matrix_code[i].len = q_get_random(3, 6);
            matrix_code[i].line = q_get_random(0, oled_max_lines()-matrix_code[i].len-1);
            matrix_code[i].index = 0;
          }
        }
        else {
          uint8_t line = matrix_code[i].line + matrix_code[i].index;
          if (line >= oled_max_lines()) {
            line = oled_max_lines() - 1;
          }
          oled_set_cursor(matrix_code[i].col, line);
          oled_write_char(q_get_random_char(), false);
          matrix_code[i].index++;
        }
      }
    }
    //oled_write(read_logo(), false);
  }

  return false;
}
#endif // OLED_ENABLE

uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
  switch (keycode) {
  case KC_MINS:
  case KC_EQL: return MS_AROW;
  }

  return KC_TRNS;
}

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
  }

  return true;
}
