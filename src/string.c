#include <stdlib.h>

#include "stringc/string.h"

char *
strdupl(const char *const src, size_t *const size) {
  const size_t length = strlen(src);
  if (size)
    *size = length;
  char *dest = malloc(length + 1);
  if (dest)
    memcpy(dest, src, length + 1);
  return dest;
}