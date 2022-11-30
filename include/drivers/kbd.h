#include "config/kbdmap.h"

#ifndef _KEYBOARD_DRIVER_H_
#define _KEYBOARD_DRIVER_H_

#define KBD_CBK_MAX      8
#define CAPS_LOCK        1
#define CAPS_UNLOCK      0
#define KEY_STATE_DOWN   1
#define KEY_STATE_UP     0

extern int shift_state;
extern int ctrl_state;
extern int alt_state;
extern int caps_lock_state;

#define key_caps_lock()     (caps_lock_state == CAPS_LOCK)
#define key_alt_down()      (alt_state == KEY_STATE_DOWN)
#define key_ctrl_down()     (ctrl_state == KEY_STATE_DOWN)
#define key_shift_down()    (shift_state == KEY_STATE_DOWN)

typedef struct kbd_event {
    char key;
    int state;
    int key_no;
} kbd_event;

int register_kbd_cbk(void (*cbk_func)(kbd_event));
void unregister_kbd_cbk(int cbk_id);

int get_cbk_cnt();
void print_cbk_table();
void invoke_kbd_cbk(kbd_event);

void handle_kbd_irq(void);

#endif /* !_KEYBOARD_DRIVER_H_ */