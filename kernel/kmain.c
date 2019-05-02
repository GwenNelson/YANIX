#include <yanix/plat_init.h>
#include <yanix/arch_init.h>
#include <yanix/bootinfo.h>
#include <yanix/kprintf.h>
#include <yanix/pmm.h>

void run_tests() __attribute__((__weak__));
void run_tests() {
}

void kmain(yanix_bootinfo_t bootinfo) {
	arch_init();
	plat_init();
	kprintf("kmain: cmdline=%s\n", bootinfo.cmdline);
	kprintf("kmain: mem_pool at 0x%p, %dkb\n", bootinfo.mem_pool, bootinfo.mem_pool_size/1024);
	init_pmm(bootinfo.mem_pool, bootinfo.mem_pool_size);
	kprintf("kmain: %dkb free\n", get_free_mem()/1024);
	run_tests();
}
