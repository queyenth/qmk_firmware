#pragma once
#ifdef OLED_ENABLE
#ifdef POMODORO_ENABLE

#include QMK_KEYBOARD_H

#define POMODORO_MINUTE 60000
#define POMODORO_WORK (pomodoroWork * POMODORO_MINUTE)
#define POMODORO_REST (pomodoroRest * POMODORO_MINUTE)

#define POMODORO_NUMBER_FONT_WIDTH 3 // in pixels
#define POMODORO_NUMBER_FONT_HEIGHT 8 // in pixels

#ifndef POMODORO_MIN_WORK
#define POMODORO_MIN_WORK 5
#endif

#ifndef POMODORO_MAX_WORK
#define POMODORO_MAX_WORK 120
#endif

#ifndef POMODORO_STEP_WORK
#define POMODORO_STEP_WORK 5
#endif

#ifndef POMODORO_MIN_REST
#define POMODORO_MIN_REST 5
#endif

#ifndef POMODORO_MAX_REST
#define POMODORO_MAX_REST 60
#endif

#ifndef POMODORO_STEP_REST
#define POMODORO_STEP_REST 5
#endif

#ifndef POMODORO_SESSIONS
#define POMODORO_SESSIONS 4
#endif

#ifndef POMODORO_WORK_UPDATE_CLOCK
#define POMODORO_WORK_UPDATE_CLOCK 5000 // (POMODORO_WORK / POMODORO_STEPS)
#endif

#ifndef POMODORO_REST_UPDATE_CLOCK
#define POMODORO_REST_UPDATE_CLOCK 5000 // (POMODORO_REST / POMODORO_STEPS)
#endif

#ifndef POMODORO_UPDATE_TIMER
#define POMODORO_UPDATE_TIMER 2000 // Every 2 seconds.
#endif

typedef enum {
  stopped,
  work,
  rest
} pomodoro_state;

typedef union {
  uint32_t raw;
  struct {
    uint8_t work :8;
    uint8_t rest :8;
  };
} pomodoro_config_t;

void eeprom_pomodoro(void);
void update_pomodoro(void);
bool process_pomodoro(uint16_t startKeycode, uint16_t incKeycode, uint16_t keycode, keyrecord_t *record);

#endif // POMODORO_ENABLE
#endif // OLED_ENABLE
