#include "arch/loongarch.h"
#include "arch/ls7a.h"
#include "arch/port.h"
#include "io/stdio.h"

#pragma GCC diagnostic ignored "-Warray-bounds"

void i8042_init(void)
{
	unsigned char data;

	/* disable device */
	// WR_PORT(LS7A_I8042_COMMAND, 0xAD); // disable keyboard 0xAD=10101101
	// WR_PORT(LS7A_I8042_COMMAND, 0xA7); // disable mouse 0xA7=10100111

	/* flush */
	// data = RD_PORT(LS7A_I8042_DATA);

	/* self test */
	// WR_PORT(LS7A_I8042_COMMAND, 0xAA);
	// data = RD_PORT(LS7A_I8042_DATA);
	// printf("keyboard reponse %x\n", data);

	/* set config byte, enable device and interrupt*/
	// WR_PORT(LS7A_I8042_COMMAND, 0x20); // 0x20=00100000 准备读取控制命令
	// data = RD_PORT(LS7A_I8042_DATA);
	WR_PORT(LS7A_I8042_COMMAND, 0x60); // 0x60=01100000 准备写入控制命令
	WR_PORT(LS7A_I8042_DATA, 0x07);	   // 0x07=00000111

	/* test */
	// WR_PORT(LS7A_I8042_COMMAND, 0xAB); // 0xAB=10101011
	// data = RD_PORT(LS7A_I8042_DATA);
	// printf("test result %x\n", data);

	/* enable first port */
	// 0xAE=10101110 打开键盘接口 Command Byte的bit-4被清除
	WR_PORT(LS7A_I8042_COMMAND, 0xAE);

	/* reset device */
	// WR_PORT(LS7A_I8042_COMMAND, 0xFF);
	// data = RD_PORT(LS7A_I8042_DATA);
	// printf("reset result %x\n", data);
}

int kbd_has_data(void)
{
	unsigned char status = RD_PORT(LS7A_I8042_STATUS);
	return (status & 0x1);
}

unsigned char kbd_read_byte(void)
{
	return RD_PORT(LS7A_I8042_DATA);
}

void kbd_clear_buffer(void)
{
	// 定期清空键盘缓冲区，有助于提高键盘响应稳定性，详细原理暂不清楚
	while (kbd_has_data())
	{
		kbd_read_byte();
	}
}