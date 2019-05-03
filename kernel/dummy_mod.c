#include <yanix/modules.h>
#include <yanix/kprintf.h>

int dummy_init() {
	kprintf("dummy: dummy module loaded!\n");
	return 0;
}

static prereq_t prereqs[] = { {NULL,NULL} };

static module_t x run_on_startup = {
  .name = "dummy",
  .required = prereqs,
  .load_after = NULL,
  .init = &dummy_init,
  .fini = NULL
};

