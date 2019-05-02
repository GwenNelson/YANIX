#include <yanix/kprintf.h>
#include <yanix/x86/portio.h>
#include <yanix/pmm.h>
#include <yanix/memlayout.h>

#define QEMU_EXIT_SUCCESS 0x00
#define QEMU_EXIT_FAILED  0x01
#define QEMU_EXIT_PORT    0x501

#define TEST(desc,f) kprintf("Testing: %s \t",desc); if(f()==0) { passed_tests++; kprintf("PASS\n");} else { failed_tests++; kprintf("FAIL\n");}; total_tests++;

#define ASSERT(desc,cond) if(! (cond)) { kprintf("Assert %s (%s) failed\t",desc, #cond); return 1;}

int test_page_alloc_free() {
	size_t starting_free_mem = get_free_mem();
	uintptr_t p = alloc_page();
	ASSERT("alloc_page() reduces free memory",get_free_mem() < starting_free_mem);
	ASSERT("alloc_page() reduces free memory by 1 page", get_free_mem() == starting_free_mem-PAGESIZE);
	free_page(p);
	ASSERT("free_page() actually frees a page", get_free_mem()==starting_free_mem);
	return 0;
}

void run_tests() {
	int passed_tests = 0;
	int failed_tests = 0;
	int total_tests  = 0;

	TEST("Simple physical page alloc/free", test_page_alloc_free);

	kprintf("Ran %d tests, %d passed, %d failed\n", total_tests, passed_tests, failed_tests);

	if(failed_tests > 0) {
		outb(QEMU_EXIT_PORT,QEMU_EXIT_FAILED);
	} else { 
		outb(QEMU_EXIT_PORT,QEMU_EXIT_SUCCESS);;
	}

}
