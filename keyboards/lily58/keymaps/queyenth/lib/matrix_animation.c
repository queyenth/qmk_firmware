#ifdef OLED_ENABLE
#ifdef MATRIX_HACKER_ANIMATION
#include "matrix_animation.h"

matrix_start_pos_t matrix_code[] = {
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
  {0, 0, 0, 0},
};
uint32_t matrix_code_timer = 0;

const uint8_t matrix_get_random(uint8_t min, uint8_t max) {
#if defined(__AVR_ATmega32U4__)
  uint8_t ran = (TCNT0 + TCNT1 + TCNT3 + TCNT4);
#else
  uint8_t ran = rand();
#endif

  return ((ran%max)+min);
}

const char matrix_get_random_char(void) {
  return (char)matrix_get_random(33, 93);
}

void init_matrix_animation(void) {
  // TODO: right now I don't care if it starts at the same position.
  for (size_t i = 0; i < 5; i++) {
    matrix_code[i].col = i;
    matrix_code[i].len = q_get_random(3, oled_max_lines()>>1);
    matrix_code[i].line = q_get_random(0, oled_max_lines()-matrix_code[i].len-1);
  }

  matrix_code_timer = timer_read32();
}

void render_matrix_animation(void) {
  if (timer_elapsed32(matrix_code_timer) >= MATRIX_HACKER_ANIMATION_EVERY) {
    matrix_code_timer = timer_read32();
    for (size_t i = 0; i < 5; i++) {
      // First of all draw the char and decrease the len.
      if (matrix_code[i].index >= matrix_code[i].len) {
	// Start clearing up.
	uint8_t line = matrix_code[i].line + matrix_code[i].index - matrix_code[i].len;
	if (line >= oled_max_lines()) {
	  line = oled_max_lines() - 1;
	}
	oled_set_cursor(matrix_code[i].col, line);
	oled_write_char(' ', false);
	matrix_code[i].len--;
	if (matrix_code[i].len == 0) {
	  matrix_code[i].len = q_get_random(3, 6);
	  matrix_code[i].line = q_get_random(0, oled_max_lines()-matrix_code[i].len-1);
	  matrix_code[i].index = 0;
	}
      }
      else {
	uint8_t line = matrix_code[i].line + matrix_code[i].index;
	if (line >= oled_max_lines()) {
	  line = oled_max_lines() - 1;
	}
	oled_set_cursor(matrix_code[i].col, line);
	oled_write_char(q_get_random_char(), false);
	matrix_code[i].index++;
      }
    }
  }
}

#endif
#endif
