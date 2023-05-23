#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lily58.h"

#define L_BASE 0 // 00000000
#define L_NAV (1 << 1) // 00000010
#define L_NUM (1 << 2) // 00000100
#define L_SYM (1 << 3) // 00001000
#define L_FUN (1 << 4) // 00010000
#define L_MEDIA (L_NAV | L_SYM) // 00001010
#define L_BSPWM (L_NUM | L_FUN) // 00010100

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_BASE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Default");
    break;
  case L_NAV:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Nav");
    break;
  case L_NUM:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Number");
    break;
  case L_SYM:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Symbol");
    break;
  case L_FUN:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Function");
    break;
  case L_MEDIA:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Media");
    break;
  case L_BSPWM:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: BSPWM");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%u", layer_state);
  }

  return layer_state_str;
}
