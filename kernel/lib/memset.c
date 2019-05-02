#include <stddef.h>
#include <stdint.h>

void* memset(void *b, int c, size_t len) {
      uint8_t* buf = (uint8_t*)b;
      size_t i=0;
      for(i=0; i<len; i++) buf[i] = c;
      return b;
}

