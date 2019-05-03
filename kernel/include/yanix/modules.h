#pragma once

#include <stddef.h>
#include <stdint.h>

enum module_state {
  MODULE_NOT_INITIALISED,
  MODULE_PREREQS_RESOLVED,
  MODULE_INIT_RUN,
  MODULE_FINI_RUN
};

typedef struct prereq {
  const char *name;
  struct module *module;
} prereq_t;

typedef struct module {
  const char *name; 
  prereq_t *required; 
  prereq_t *load_after; 
  int (*init)(void); 
  int (*fini)(void);;

  uintptr_t state;
  uintptr_t padding[2];
} module_t;

#ifdef __APPLE__
#define run_on_startup __attribute__((__section__("__DATA,__modules"),used))
#else
#define run_on_startup __attribute__((__section__("modules"),used))
#endif
