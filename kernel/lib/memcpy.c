#include <stddef.h>
#include <stdint.h>

 __attribute__((__weak__))
void memcpy(void *dest_, const void *src_, uint32_t len)
{
  uint8_t *dest = dest_;
  const uint8_t *src = src_;
  for(; len != 0; len--) *dest++ = *src++;
}
