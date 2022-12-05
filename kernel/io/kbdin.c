#include "io/kbdin.h"
#include "gcc.h"

bool kbd_input_enabled = false;
int kbd_input_cbk_id = -1;
bool kbd_input_waiting = false;

void kbd_input_cbk(kbd_event event)
{
    if (kbd_input_enabled)
    {
        kbd_tmp_event = event;
        kbd_input_waiting = false;
    }
}

static inline void kbd_input_enable()
{
    if (!kbd_input_enabled)
    {
        kbd_input_cbk_id = register_kbd_cbk(kbd_input_cbk);
        if (kbd_input_cbk_id != -1)
            kbd_input_enabled = true;
    }
}

static inline void kbd_input_disable()
{
    if (kbd_input_enabled)
    {
        unregister_kbd_cbk(kbd_input_cbk_id);
        kbd_input_cbk_id = -1;
        kbd_input_enabled = false;
    }
}

kbd_event kbd_wait_key()
{
    kbd_input_enable();
    kbd_input_waiting = true;
    while (kbd_input_waiting)
        nop();
    kbd_input_disable();
    return kbd_tmp_event;
}

kbd_event kbd_wait_key_down()
{
    kbd_event event;
    do
    {
        event = kbd_wait_key();
    } while (event.state != KEY_STATE_DOWN);
    return event;
}