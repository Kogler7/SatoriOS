#include "drivers/kbd.h"
#include "types.h"

#ifndef _SATORI_KEYBOARD_INPUT_H_
#define _SATORI_KEYBOARD_INPUT_H_

extern bool kbd_input_enabled;
extern int kbd_input_cbk_id;
extern bool kbd_input_waiting;

static kbd_event kbd_tmp_event;

void kbd_input_cbk(kbd_event event);
kbd_event kbd_wait_key();
kbd_event kbd_wait_key_down();

#endif /* !_SATORI_KEYBOARD_INPUT_H_ */