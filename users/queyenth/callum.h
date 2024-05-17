#pragma once

#include QMK_KEYBOARD_H

#define OS_INIT(trigger, callback) {(trigger), os_up_unqueued, callback}

// Represents the four states a oneshot key can be in
typedef enum {
    os_up_unqueued,
    os_up_queued,
    os_up_done,
    os_down_unused,
    os_down_used,
} oneshot_state;

typedef struct {
  uint16_t trigger;
  oneshot_state state;
  void (*callback)(bool, uint16_t);
} oneshot_t;

// Custom oneshot mod implementation that doesn't rely on timers. If a mod is
// used while it is held it will be unregistered on keyup as normal, otherwise
// it will be queued and only released after the next non-mod keyup.
void update_oneshot(
    oneshot_t *oneshot,
    uint16_t keycode,
    keyrecord_t *record
);

// To be implemented by the consumer. Defines keys to cancel oneshot mods.
bool is_oneshot_cancel_key(uint16_t keycode);

// To be implemented by the consumer. Defines keys to ignore when determining
// whether a oneshot mod has been used. Setting this to modifiers and layer
// change keys allows stacking multiple oneshot modifiers, and carrying them
// between layers.
bool is_oneshot_ignored_key(uint16_t keycode);

// Ctrl/Alt/Gui/Shift callbacks.
void oneshot_ctrl_callback(bool status, uint16_t trigger); 
void oneshot_alt_callback(bool status, uint16_t trigger);
void oneshot_gui_callback(bool status, uint16_t trigger);
void oneshot_shift_callback(bool status, uint16_t trigger);
