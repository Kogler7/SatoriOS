#include "drivers/kbdmap.h"

//#define KBD_BUF_SIZE 2048
#define KBD_CALLBACK_TABLE 32
enum{
    KEY_PUSH = 1,
    KEY_RELEASE = 0
};
enum{
    CAPS_UPER = 1,
    CAPS_LOWER = 0
};

//typedef void (*kbd_callback_table)(char*)[KBD_CALLBACK_TABLE];

int kbd_event_register(void *f_entry);
int kbd_event_invoke(char issue_c, int key_state, int kbd_n);
unsigned char kbd_irq();

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