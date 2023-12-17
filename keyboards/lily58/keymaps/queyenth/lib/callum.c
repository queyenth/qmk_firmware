#include "callum.h"

void update_oneshot(
    oneshot_t *oneshot,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == oneshot->trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (oneshot->state == os_up_unqueued) {
                register_code(oneshot->mod);
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
                unregister_code(oneshot->mod);
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
                unregister_code(oneshot->mod);
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (oneshot->state) {
                case os_down_unused:
                    oneshot->state = os_down_used;
                    break;
                case os_up_queued:
                    oneshot->state = os_up_unqueued;
                    unregister_code(oneshot->mod);
                    break;
                default:
                    break;
                }
            }
        }
    }
}
