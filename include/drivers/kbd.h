#include "config/kbdmap.h"

#ifndef _DEV_KBD_H_
#define _DEV_KBD_H_

#define KBD_CBK_MAX      8
#define CAPS_LOCK        1
#define CAPS_UNLOCK      0
#define KEY_STATE_DOWN   1
#define KEY_STATE_UP     0

extern unsigned int keymap[512];
extern char kbd_US[128];
extern char kbd_US_shift[128];

extern int shift_state;
extern int ctrl_state;
extern int alt_state;
extern int caps_lock_state;

int register_kbd_cbk(void (*cbk_func)(char, int));
void unregister_kbd_cbk(int cbk_id);

int get_cbk_cnt();
void print_cbk_table();
void invoke_kbd_cbk(char key, int state);

void handle_kbd_irq(void);

#endif /* !_DEV_KBD_H_ */