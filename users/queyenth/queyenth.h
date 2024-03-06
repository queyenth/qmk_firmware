#pragma once

#include QMK_KEYBOARD_H
#include "callum.h"

#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)

#ifdef RAW_ENABLE
enum raw_hid_funcs {
  RAW_HID_ONESHOT_SEND = 0,
  RAW_HID_LAYOUT_RECV,
};
#endif

enum layer_number {
  _CANARY = 0,
  _QWERTY,
  _NAV,
  _SYM,
  _FN,
};

enum keycodes {
  OS_GUI = SAFE_RANGE,
  OS_ALT,
  OS_SFT,
  OS_CTL,
  SW_LANG,
  NW_TOGG,
  QQ_LAST
};

typedef struct {
  uint16_t key;
  uint16_t num;
} numword_t; // 2 bytes per sub. Find something better. Maybe just save diff between two keys in an int16_t or something

bool process_record_user_queyenth(uint16_t keycode, keyrecord_t *record);
