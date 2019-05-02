#include <yanix/x86/gdt.h>
#include <yanix/x86/idt.h>

void arch_init() {
	init_gdt();
	init_idt();
}
