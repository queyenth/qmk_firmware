#include QMK_KEYBOARD_H
#include <stdio.h>
#include "quantum.h"

#define L_BASE 0 // 00000000
#define L_NAV (1 << 1) // 00000010
#define L_SYM (1 << 2) // 00000100
#define L_NUM (1 << 3) // 00001000
#define L_RGB (1 << 4) // 00010000
#define L_NUMPAD (1 << 5) // 00100000

#define L_TRI_NUM (L_SYM | L_NAV | L_NUM) // 00001110

char layer_state_str[8];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_BASE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Base");
    break;
  case L_NAV:
    snprintf(layer_state_str, sizeof(layer_state_str), "Nav");
    break;
  case L_SYM:
    snprintf(layer_state_str, sizeof(layer_state_str), "Sym");
    break;
  case L_NUM:
  case L_TRI_NUM:
    snprintf(layer_state_str, sizeof(layer_state_str), "Num");
    break;
  case L_RGB:
    snprintf(layer_state_str, sizeof(layer_state_str), "RGB");
    break;
  case L_RGB:
    snprintf(layer_state_str, sizeof(layer_state_str), "Npad");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "%u", layer_state);
  }

  return layer_state_str;
}
