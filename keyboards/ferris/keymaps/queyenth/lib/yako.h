#pragma once

#include QMK_KEYBOARD_H

typedef struct {
  uint16_t keycode;
  uint16_t def;
  uint16_t yako;
} yako_subs_t;

bool update_yako(
    yako_subs_t *yako,
    uint16_t keycode,
    keyrecord_t *record,
    bool should_sub
);
