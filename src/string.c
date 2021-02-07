#include <stdlib.h>
#include <stdbool.h>

#include "stringc/string.h"

char *
strdupl(const char *const src, size_t *const lengthp) {
  const size_t length = strlen(src);
  if (lengthp)
    *lengthp = length;
  void *dest = malloc((length + 1) * sizeof *src);
  if (dest)
    memcpy(dest, src, (length + 1) * sizeof *src);
  return dest;
}

size_t
utf8len(const char *str) {
  size_t len = 0;
  while (true) {
    switch (utf8next(&str)) {
      case -1: return -1;
      case 0:  return len;
      default: len++;
    }
  }
}

size_t
utf8len_fast(const char *str) {
  size_t len = 0;
  for (; *str; str++)
    if ((*str & 0xC0) != 0x80)
      len++;
  return len;
}

int32_t
utf8next(const char **str) {
  int32_t first = *(*str)++;
  if (first & 0x80) { //UTF-8
    if (first & 0x40) {
      int32_t codepoint = 0;
      int shifted = 0;
      for (; first & 0x40; first <<= 1, shifted++) {
        if ((**str & 0xC0) == 0x80) {
          codepoint <<= 6;
          codepoint |= *(*str)++ & 0x3F;
        } else return -1;
      }
      return ((first & 0x3F) << (6 * shifted - shifted)) | codepoint;
    } else return -1;
  } else return first;
}