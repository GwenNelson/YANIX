#include <stdio.h>
#include <stdlib.h>
#include <yanix/kprintf.h>

void _putchar(char character) {
	putchar(character);
}

void plat_init() {
	kprintf("YANIX\n");
}
