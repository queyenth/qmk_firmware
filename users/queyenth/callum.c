#include "callum.h"

void oneshot_ctrl_callback(bool status, uint16_t trigger) {
  if (status) {
    register_code(KC_LCTL);
  } else {
    unregister_code(KC_LCTL);
  }
}

void oneshot_alt_callback(bool status, uint16_t trigger) {
  if (status) {
    register_code(KC_LALT);
  } else {
    unregister_code(KC_LALT);
  }
}

void oneshot_gui_callback(bool status, uint16_t trigger) {
  if (status) {
    register_code(KC_LGUI);
  } else {
    unregister_code(KC_LGUI);
  }
}

void oneshot_shift_callback(bool status, uint16_t trigger) {
  if (status) {
    register_code(KC_LSFT);
  } else {
    unregister_code(KC_LSFT);
  }
}

void update_oneshot(
    oneshot_t *oneshot,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == oneshot->trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (oneshot->state == os_up_unqueued) {
              oneshot->callback(true, oneshot->trigger);
	      //register_code(oneshot->mod);
            }
            oneshot->state = os_down_unused;
        } else {
            // Trigger keyup
            switch (oneshot->state) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                oneshot->state = os_up_queued;
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                oneshot->state = os_up_unqueued;
                oneshot->callback(false, oneshot->trigger);
                //unregister_code(oneshot->mod);
                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && oneshot->state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                oneshot->state = os_up_unqueued;
                oneshot->callback(false, oneshot->trigger);
                //unregister_code(oneshot->mod);
            }
	    // If it's not oneshot cancel key and oneshot state is
	    // os_up_queued, then we need to let the key process and
	    // remember that for next key we should disable the
	    // oneshot mod, otherwise it can be triggered for next key
	    // if we roll (e.g. Oneshot shift then qwerty in roll
	    // could result in QWErty instead of Qwerty)
	    if (!is_oneshot_ignored_key(keycode)) {
	      if (oneshot->state == os_up_done) {
	        oneshot->state = os_up_unqueued;
                oneshot->callback(false, oneshot->trigger);
	        //unregister_code(oneshot->mod);
	      }
	      else if (oneshot->state == os_up_queued) {
		oneshot->state = os_up_done;
	      }
	    }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (oneshot->state) {
                case os_down_unused:
                    oneshot->state = os_down_used;
                    break;
		case os_up_done:
                case os_up_queued:
                    oneshot->state = os_up_unqueued;
                    oneshot->callback(false, oneshot->trigger);
                    //unregister_code(oneshot->mod);
                    break;
                default:
                    break;
                }
            }
        }
    }
}
