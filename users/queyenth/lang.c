#include QMK_KEYBOARD_H
#include "lang.h"

uint8_t lang = 0; // index of langConfig

void switch_input_lang_next(const lang_config_t *langConfig, const size_t langCount)
{
  lang = (lang + 1) % langCount;
  default_layer_set(1UL << langConfig[lang].layout);
}

void switch_input_lag(const lang_config_t *langConfig, const size_t langCount, const uint8_t new_lang)
{
  lang = new_lang;
  if (lang >= langCount) {
    lang = langCount-1;
  }
  default_layer_set(1UL << langConfig[lang].layout);
}

