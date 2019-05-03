#include <yanix/plat_init.h>
#include <yanix/arch_init.h>
#include <yanix/bootinfo.h>
#include <yanix/kprintf.h>
#include <yanix/pmm.h>
#include <yanix/modules.h>

#ifdef __APPLE__
extern module_t __start_modules __asm("section$start$__DATA$__modules");
extern module_t __stop_modules  __asm("section$end$__DATA$__modules");
#else
extern module_t __start_modules, __stop_modules;
#endif

static void earlypanic(const char *msg, const char *msg2);
static module_t *find_module(const char *name);
static void resolve_module(module_t *m);
static void init_module(module_t *m);
static void fini_module(module_t *m);
static void log_status(int status, const char *name, const char *text);

void run_tests() __attribute__((__weak__));
void run_tests() {
}

static void resolve_module(module_t *m) {
  if (m->state >= MODULE_PREREQS_RESOLVED)
    return;

  for (prereq_t *p = m->required; p != NULL && p->name != NULL; ++p)
    p->module = find_module(p->name);

  for (prereq_t *p = m->load_after; p != NULL && p->name != NULL; ++p)
    p->module = find_module(p->name);

  m->state = MODULE_PREREQS_RESOLVED;
}

static void init_module(module_t *m) {
  if (m->state >= MODULE_INIT_RUN)
    return;
  m->state = MODULE_INIT_RUN;

  if (m->required)
    for (prereq_t *p = m->required; p != NULL && p->name != NULL; ++p) {
      if (!p->module)
        earlypanic("Module not found: ", p->name);
      else
        init_module(p->module);
    }

  if (m->load_after)
    for (prereq_t *p = m->load_after; p != NULL && p->name != NULL; ++p) {
      if (p->module)
        init_module(p->module);
    }

  if (m->init) {
    int ok = m->init();
    log_status(ok, m->name, "Started");
  }
}

static void fini_module(module_t *m) {
  if (m->state != MODULE_INIT_RUN)
    return;
  m->state = MODULE_FINI_RUN;

  if (m->required)
    for (prereq_t *p = m->required; p != NULL && p->name != NULL; ++p) {
      if (!p->module)
        earlypanic("Module not found: ", p->name);
      else
        fini_module(p->module);
    }

  if (m->load_after)
    for (prereq_t *p = m->load_after; p != NULL && p->name != NULL; ++p) {
      if (p->module)
        fini_module(p->module);
    }

  if (m->fini) {
    int ok = m->fini();
    log_status(ok, m->name, "Stopped");
  }
}


static module_t *find_module(const char *name) {
  for (module_t *i = &__start_modules, *e = &__stop_modules; i < e; ++i) {
    if (!strcmp(name, i->name)) return i;
  }
  return NULL;
}

static void log_status(int status, const char *name, const char *text) {
  kprintf("[");
  if (status == 0)
    kprintf("\033[32m OK \033[0m");
  else
    kprintf("\033[31mFAIL\033[0m");
  kprintf("] %s %s\n",text,name);
}

static void earlypanic(const char *msg, const char *msg2) {
	kprintf("PANIC! %s %s\n", msg, msg2);
	for(;;);
}

void init_modules() {
  for (module_t *m = &__start_modules, *e = &__stop_modules; m < e; ++m)
    m->state = MODULE_NOT_INITIALISED;

  for (module_t *m = &__start_modules, *e = &__stop_modules; m < e; ++m)
    resolve_module(m);

    for (module_t *m = &__start_modules, *e = &__stop_modules; m < e; ++m)
      init_module(m);

}

void kmain(yanix_bootinfo_t bootinfo) {
	arch_init();
	plat_init();
	kprintf("kmain: cmdline=%s\n", bootinfo.cmdline);
	kprintf("kmain: mem_pool at 0x%p, %dkb\n", bootinfo.mem_pool, bootinfo.mem_pool_size/1024);
//	init_pmm(bootinfo.mem_pool, bootinfo.mem_pool_size);
//	kprintf("kmain: %dkb free\n", get_free_mem()/1024);
	init_modules();
	run_tests();
}
