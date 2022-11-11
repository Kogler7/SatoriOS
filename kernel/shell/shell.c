#include"shell.h"
#include"util.h"
#include"satio/printf.h"
#include"satio/serial.h"
#include"driver/kbd.h"

char input_buff[SHELL_BUFFER_SIZE];

int wait_for_input()
{
    // int i = 0;
    // while (1)
    // {
    //     char c = serial_recv_byte();
    //     if (c == '\b')
    //     {
    //         if (i > 0)
    //         {
    //             i--;
    //             printf("\b \b");
    //         }
    //     }
    //     else if (c == '\r')
    //     {
    //         printf("\n\r");
    //         input_buff[i] = 0;
    //         return i;
    //     }
    //     else
    //     {
    //         input_buff[i] = c;
    //         i++;
    //         printf("%c", c);
    //     }
    // }
}

// void handle_kbd_irq()
// {
//     char c = kbd_getc();
//     printf("%c", c);
// }

void kbd_getchar(char c, int s)
{
    printf("%c %d", c, s);
}

void entry_shell(){
    printf("Entering Shell...\n\r");
    // while(1){
    //     printf(">> ");
    //     int len = wait_for_input();
    //     printf("input: %s\n\r", input_buff);
    // }
    register_kbd_cbk(kbd_getchar);
    while (1)
    {
        memset(input_buff, 0, sizeof(input_buff));
        puts("SatoriOS $ ");
        printf("SatoriOS $ %d",1);
        break;
    }
    printf("Exiting Shell...\n\r");
}