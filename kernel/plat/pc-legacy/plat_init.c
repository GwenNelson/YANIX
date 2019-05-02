#include <yanix/plat/pc-legacy/serial.h>
#include <yanix/kprintf.h>

void _putchar(char character) {
	write_serial(SERIAL_PORT_COM1,character);
}

void plat_init() {
	init_serial(SERIAL_PORT_COM1);
	init_pic();
	kprintf("YANIX\n");
}
