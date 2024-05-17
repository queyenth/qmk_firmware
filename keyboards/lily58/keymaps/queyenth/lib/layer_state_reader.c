#include QMK_KEYBOARD_H
#include <stdio.h>
#include "quantum.h"

#define L_CANARY 0
#define L_NAV (1 << 3)
#define L_SYM (1 << 4)
#define L_FN (1 << 5)

#define L_TRI_FN (L_SYM | L_NAV | L_FN)

char layer_state_str[5];

const char *read_layer_state(uint8_t active_layer) {
  switch (layer_state)
  {
  case L_CANARY:
    if (active_layer == 0) {
      snprintf(layer_state_str, sizeof(layer_state_str), "CNRY");
    } else if (active_layer == 1) {
      snprintf(layer_state_str, sizeof(layer_state_str), "YAKO");
    } else if (active_layer == 2) {
      snprintf(layer_state_str, sizeof(layer_state_str), "QWRT");
    }
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
