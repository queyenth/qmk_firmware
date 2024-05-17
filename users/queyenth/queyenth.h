#pragma once

#include QMK_KEYBOARD_H
#include "callum.h"
#include "keymap_russian.h"

#define LA_SYM MO(_SYM)
#define LA_NAV MO(_NAV)

enum layer_number {
  _CANARY = 0,
  _YAKO,
  _QWERTY,
  _NAV,
  _SYM,
  _FN
};

typedef enum {
  _NUMWORD = 0,
  _MOUSEWORD
} smart_layer_number;

enum keycodes {
  OS_GUI = SAFE_RANGE,
  OS_ALT,
  OS_SFT,
  OS_CTL,
  SW_LANG,
  NW_TOGG,
  MW_TOGG,
  QQ_LAST
};

typedef struct {
  uint16_t key;
  uint16_t sub;
} smartlayer_sub_t; // 4 bytes per sub. Find something better.

uint8_t get_active_layout(void);
bool is_smartlayer_on(smart_layer_number smart_layer);
bool process_record_user_queyenth(uint16_t keycode, keyrecord_t *record);
