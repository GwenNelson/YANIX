#include <stdbool.h>
#include <yanix/pmm.h>
#include <yanix/kprintf.h>

size_t pages_free = 0;

uint32_t pages_bmap[MAX_PAGES/32];

bool test_page(uintptr_t page_no) {
     return pages_bmap[page_no / 32] & (1 << (page_no % 32));
}

void set_page(uint32_t page_no) {
     pages_bmap[page_no/32] |= 1 << (page_no%32);
     pages_free -= 1;
}

void unset_page(uint32_t page_no) {
     pages_bmap[page_no/32] &= ~(1 << (page_no%32));
     pages_free++;
}

void init_pmm(uintptr_t mem_pool_start, size_t mem_pool_size) {
	__builtin_memset(&pages_bmap,1,sizeof(pages_bmap));
	for(uintptr_t i=mem_pool_start; i<mem_pool_start+(mem_pool_size-PAGESIZE); i+=PAGESIZE) {
		unset_page(i/PAGESIZE);
	}
}

size_t get_free_mem() {
	return pages_free*PAGESIZE;
}

uintptr_t alloc_page() {
	for(uintptr_t i=0; i<MAX_PAGES; i++) {
		if(!test_page(i)) {
			set_page(i);
			return i*PAGESIZE;
		}
	}
	return 0;
}

void free_page(uintptr_t p) {
	unset_page(p/PAGESIZE);
}
