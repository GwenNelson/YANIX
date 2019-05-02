#include <yanix/plat/raspi2/uart.h>
#include <yanix/kprintf.h>

void _putchar(char character) {
	uart_putc(character);
}

void plat_init() {
	uart_init();
	kprintf("YANIX\n");
}
