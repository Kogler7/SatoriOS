#include "trap/loongarch.h"
#include "trap/ls7a.h"
#include "satio/printf.h"

#pragma GCC diagnostic ignored "-Warray-bounds"

void i8042_init(void)
{
  unsigned char data;

  /* disable device */
  *(volatile unsigned char*)(LS7A_I8042_COMMAND) = 0xAD;
  *(volatile unsigned char*)(LS7A_I8042_COMMAND) = 0xA7;
  /* flush */
  data = *(volatile unsigned char*)(LS7A_I8042_DATA);
  /* self test */
  *(volatile unsigned char*)(LS7A_I8042_COMMAND) = 0xAA;
  data = *(volatile unsigned char*)(LS7A_I8042_DATA);
  printf("keyboard response %x\n\r", data);

  /* set config byte, enable device and interrupt*/
  *(volatile unsigned char*)(LS7A_I8042_COMMAND) = 0x20;
  data = *(volatile unsigned char*)(LS7A_I8042_DATA);
  *(volatile unsigned char*)(LS7A_I8042_COMMAND) = 0x60;
  *(volatile unsigned char*)(LS7A_I8042_DATA) = 0x07;

  /* test */
  *(volatile unsigned char*)(LS7A_I8042_COMMAND) = 0xAB;
  data = *(volatile unsigned char*)(LS7A_I8042_DATA);
  printf("test result %x\n\r", data);

  /* enable first port */
  *(volatile unsigned char*)(LS7A_I8042_COMMAND) = 0xAE;

  /* reset device */
  *(volatile unsigned char*)(LS7A_I8042_DATA) = 0xFF;
  data = *(volatile unsigned char*)(LS7A_I8042_DATA);
  printf("reset result %x\n\r", data);
}

int kbd_has_data(void)
{
    unsigned char status = *(volatile unsigned char*)(LS7A_I8042_STATUS); 
    return (status & 0x1);
}

unsigned char kbd_read_byte(void)
{
    return *(volatile unsigned char*)(LS7A_I8042_DATA);
}
