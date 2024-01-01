#include "yako.h"

bool update_yako(yako_subs_t *yako, uint16_t keycode, keyrecord_t *record, bool should_sub) {
    static uint16_t registered_keycode = KC_NO;

    if (registered_keycode != KC_NO) {
      unregister_code16(registered_keycode);
      registered_keycode = KC_NO;
    }

    if (keycode == yako->keycode) {
      if (record->event.pressed) {
        if (should_sub) {
          registered_keycode = yako->yako;
        } else {
          registered_keycode = yako->def;
        }
        register_code16(registered_keycode);
      }

      return false;
    }

    return true;
}
