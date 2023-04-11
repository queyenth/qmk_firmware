#include QMK_KEYBOARD_H

enum layer_names {
  _COL,
  _QWE,
  _PUNCT
  //_NAV
};

/****************************************************************************************************
*
* Keymap: Default Layer in Qwerty
*
* ,-------------------------------------------------------------------------------------------------------------------.
* | Esc    |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F8  |  F9  |  F10 |  F12 | PSCR | SLCK | PAUS |  FN0 |  BOOT  |
* |--------+------+------+------+------+------+---------------------------+------+------+------+------+------+--------|
* | =+     |  1!  |  2@  |  3#  |  4$  |  5%  |                           |  6^  |  7&  |  8*  |  9(  |  0)  | -_     |
* |--------+------+------+------+------+------|                           +------+------+------+------+------+--------|
* | Tab    |   Q  |   W  |   E  |   R  |   T  |                           |   Y  |   U  |   I  |   O  |   P  | \|     |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* | Caps   |   A  |   S  |   D  |   F  |   G  |                           |   H  |   J  |   K  |   L  |  ;:  | '"     |
* |--------+------+------+------+------+------|                           |------+------+------+------+------+--------|
* | Shift  |   Z  |   X  |   C  |   V  |   B  |                           |   N  |   M  |  ,.  |  .>  |  /?  | Shift  |
* `--------+------+------+------+------+-------                           `------+------+------+------+------+--------'
*          | `~   | INS  | Left | Right|                                         | Up   | Down |  [{  |  ]}  |
*          `---------------------------'                                         `---------------------------'
*                                        ,-------------.         ,-------------.
*                                        | Ctrl | Alt  |         | Gui  | Ctrl |
*                                 ,------|------|------|         |------+------+------.
*                                 |      |      | Home |         | PgUp |      |      |
*                                 | BkSp | Del  |------|         |------|Return| Space|
*                                 |      |      | End  |         | PgDn |      |      |
*                                 `--------------------'         `--------------------'
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_COL] = LAYOUT(
           KC_ESC, KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8,
           KC_MINS, KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,
           KC_TAB,  KC_W   ,KC_L   ,KC_Y   ,KC_P   ,KC_B   ,
           LCTL_T(KC_ESC),  KC_C   ,KC_R   ,KC_S   ,KC_T   ,KC_G   ,
           SC_LSPO, KC_Q   ,KC_J   ,KC_V   ,KC_D   ,KC_K   ,
                   KC_GRV ,KC_INS ,KC_LEFT,KC_RGHT,
           LCTL_T(KC_CAPS),TG(_QWE),
           MO(_PUNCT),
           LCTL_T(KC_BSPC),LALT_T(KC_DEL) ,KC_LGUI ,
    KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_MUTE ,KC_VOLD  ,KC_VOLU, KC_MPLY, QK_BOOT,
	KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_EQL,
	KC_Z   ,KC_F   ,KC_O   ,KC_U   ,KC_QUOT,KC_BSLS,
	KC_M   ,KC_N   ,KC_E   ,KC_I   ,KC_A,   KC_SCLN,
	KC_X   ,KC_H   ,KC_SLSH,KC_COMM,KC_DOT,SC_RSPC,
		KC_UP  ,KC_DOWN,KC_LBRC,KC_RBRC,
           KC_RGUI,KC_RCTL,
           MO(_PUNCT),
           KC_RGUI,LALT_T(KC_ENTER),RCTL_T(KC_SPC)
                ),
[_QWE] = LAYOUT(
           KC_ESC, KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8,
           KC_EQL, KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,
           KC_TAB, KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,
           LCTL_T(KC_ESC), KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,
           SC_LSPO,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,
                   KC_GRV ,KC_INS ,KC_LEFT,KC_RGHT,
           LCTL_T(KC_CAPS),TG(_QWE),
           MO(_PUNCT),
           LCTL_T(KC_BSPC),LALT_T(KC_DEL) ,KC_LGUI ,
    KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_MUTE ,KC_VOLD  ,KC_VOLU, KC_MPLY, QK_BOOT,
	KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_MINS,
	KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_BSLS,
	KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,
           KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,SC_RSPC,
		KC_UP  ,KC_DOWN,KC_LBRC,KC_RBRC,
           KC_RGUI,KC_RCTL,
           MO(_PUNCT),
           KC_RGUI,LALT_T(KC_ENTER) ,RCTL_T(KC_SPC)
                ),
[_PUNCT] = LAYOUT(
           KC_NO, KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO  ,KC_NO,
           KC_NO, KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
           KC_NO, KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,
           KC_NO, KC_LPRN   ,KC_LBRC   ,KC_LCBR   ,KC_LT   ,KC_EQL   ,
           KC_NO, KC_RPRN   ,KC_RBRC   ,KC_RCBR   ,KC_GT   ,KC_NO   ,
           KC_NO , KC_NO   ,KC_NO,KC_NO,
                                 KC_NO,KC_NO,
                                       KC_NO,
                           KC_NO,KC_NO,KC_NO,
    KC_NO  ,KC_NO ,KC_NO ,KC_NO ,KC_NO ,KC_NO  ,KC_NO, KC_NO, KC_NO,
	KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO,
	KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO   ,KC_NO,
	KC_LEFT   ,KC_DOWN   ,KC_UP   ,KC_RGHT   ,KC_NO,   KC_NO,
           KC_NO   ,KC_NO   ,KC_NO,KC_NO ,KC_NO,KC_NO,
		KC_NO  ,KC_NO,KC_NO,KC_NO,
           KC_NO,KC_NO,
           KC_NO,
           KC_NO,KC_NO ,KC_NO
    )
};
