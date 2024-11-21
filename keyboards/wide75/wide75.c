#include "wide75.h"
#include "print.h"

void board_init(void) {
    usbpd_init();
}

#ifdef OLED_ENABLE

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }
    oled_invert(true);
    oled_write_ln("#################", false);
    oled_write_ln("#################", false);
    oled_write_ln("#################", false);
    oled_write_ln("#################", false);
    return true;
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
  return true;
}
