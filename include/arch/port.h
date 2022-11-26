#ifndef _ARCH_PORT_H_
#define _ARCH_PORT_H_

#define IO_PORT(port)           *(volatile unsigned char *)(port)
#define RD_PORT(port)           IO_PORT(port)
#define WR_PORT(port, val)      IO_PORT(port) = (val)

#define IO_PORT_L(port)         *(volatile unsigned long *)(port)
#define RD_PORT_L(port)         IO_PORT_L(port)
#define WR_PORT_L(port, val)    IO_PORT_L(port) = (val)

#endif /* !_ARCH_PORT_H_ */