#include QMK_KEYBOARD_H
#include <stdio.h>
#include "quantum.h"

#define L_CANARY 0 // 00000000
#define L_QWERTY 1 // 00000010
#define L_NAV (1 << 2) // 00000100
#define L_SYM (1 << 3) // 00001000
#define L_FN (1 << 4) // 00010000

#define L_TRI_FN (L_SYM | L_NAV | L_FN) // 00011100

char layer_state_str[8];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_CANARY:
    snprintf(layer_state_str, sizeof(layer_state_str), "CNRY");
    break;
  case L_NAV:
    snprintf(layer_state_str, sizeof(layer_state_str), "NAV");
    break;
  case L_SYM:
    snprintf(layer_state_str, sizeof(layer_state_str), "SYM");
    break;
  case L_FN:
  case L_TRI_FN:
    snprintf(layer_state_str, sizeof(layer_state_str), "FN");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "%u", layer_state);
  }

  return layer_state_str;
}
