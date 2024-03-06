#pragma once

typedef struct {
  uint8_t layout;
  char lang[2];
} lang_config_t;

void switch_input_lang_next(const lang_config_t *langConfig, const size_t langCount);
void switch_input_lang(const lang_config_t *langConfig, const size_t langCount, uint8_t new_lang);
