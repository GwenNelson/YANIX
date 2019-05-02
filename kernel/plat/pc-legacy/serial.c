#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <yanix/x86/portio.h>

void init_serial(uint16_t port) {
	outb(port + 1, 0x00); // disable IRQ
	outb(port + 3, 0x80); // setup baud rate to 38400
	outb(port + 0, 0x03);
	outb(port + 1, 0x00);
	outb(port + 3, 0x03); // setup 8N1
	outb(port + 2, 0xC7); // enable FIFO
	outb(port + 4, 0x0B); // re-enable IRQ and set RTS/DSR
}

bool serial_received(uint16_t port) {
	if(inb(port + 5) & 1) return true;
	return false;
}

char read_serial(uint16_t port) {
	while(serial_received(port) == 0);
	return inb(port);
}

bool serial_transmit_empty(uint16_t port) {
	if(inb(port + 5) & 0x20) return true;
	return false;
}

void write_serial(uint16_t port, char c) {
	while(!serial_transmit_empty(port));
	outb(port,c);
}
