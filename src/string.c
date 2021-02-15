#include <stdlib.h>

#include "stringc/string.h"

char *
strduplen(const char *const src, size_t *const lengthp) {
  const size_t length = strlen(src);
  if (lengthp)
    *lengthp = length;
  void *dest = malloc((length + 1) * sizeof *src);
  if (dest)
    memcpy(dest, src, (length + 1) * sizeof *src);
  return dest;
}

