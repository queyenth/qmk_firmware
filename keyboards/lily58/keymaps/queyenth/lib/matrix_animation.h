#pragma once
#ifdef OLED_ENABLE
#ifdef MATRIX_HACKER_ANIMATION

#ifndef MATRIX_HACKER_ANIMATION_FPS
#define MATRIX_HACKER_ANIMATION_FPS 5
#endif

#define MATRIX_HACKER_ANIMATION_EVERY (1000 / (MATRIX_HACKER_ANIMATION_FPS))

typedef struct {
  uint8_t col;
  uint8_t line;
  uint8_t len;
  uint8_t index;
} matrix_start_pos_t;

void init_matrix_animation(void);
void render_matrix_animation(void);

#endif
#endif
