#include "trap/ls7a.h"

void ls7a_i8042_init(void)
{
    unsigned char data;

    /* disable device */
    *(volatile unsigned char *)(LS7A_I8042_COMMAND) = 0xAD;
    *(volatile unsigned char *)(LS7A_I8042_COMMAND) = 0xA7;
    /* flush */
    data = *(volatile unsigned char *)(LS7A_I8042_DATA);
    /* self test */
    *(volatile unsigned char *)(LS7A_I8042_COMMAND) = 0xAA;
    data = *(volatile unsigned char *)(LS7A_I8042_DATA);
    printf("kbd: keyboard response %x\n\r", data);

    /* set config byte, enable device and interrupt*/
    *(volatile unsigned char *)(LS7A_I8042_COMMAND) = 0x20;
    data = *(volatile unsigned char *)(LS7A_I8042_DATA);
    *(volatile unsigned char *)(LS7A_I8042_COMMAND) = 0x60;
    *(volatile unsigned char *)(LS7A_I8042_DATA) = 0x07;

    /* test */
    *(volatile unsigned char *)(LS7A_I8042_COMMAND) = 0xAB;
    data = *(volatile unsigned char *)(LS7A_I8042_DATA);
    printf("kbd: test result %x\n\r", data);

    /* enable first port */
    *(volatile unsigned char *)(LS7A_I8042_COMMAND) = 0xAE;

    /* reset device */
    *(volatile unsigned char *)(LS7A_I8042_DATA) = 0xFF;
    data = *(volatile unsigned char *)(LS7A_I8042_DATA);
    printf("kbd: reset result %x\n\r", data);
}