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
utf8_strlen(const uint8_t *str) {
  size_t len = 0;
  while (true) {
    switch (utf8_next(&str)) {
      case -1: {
        return -1;
      } break;
      case 0: {
        return len;
      } break;
      default: len++;
    }
  }
}

size_t
utf8_strlen_fast(const uint8_t *str) {
  size_t len = 0;
  for (; *str; str++)
    if ((*str & 0xC0) != 0x80)
      len++;
  return len;
}

int32_t
utf8_next(const uint8_t **str) {
  int32_t first = *(*str)++;
  if (first) {
    if (first & 0x80) { //UTF-8
      if (first & 0x40) {
        int32_t codepoint = 0;
        int shifted = 0;
        for (; first & 0x40; first <<= 1, shifted++) {
          const uint32_t next = *(*str)++;
          if ((next & 0xC0) == 0x80) {
            codepoint <<= 6;
            codepoint |= next & 0x3F;
          } else { //expected a continuation byte or null byte
            if ((next & 0xC0) == 0xC0 /* first sequence of utf8 */ || next == '\0');
              *str--;
            return -1;
          }
        }
        return ((first & 0x3F) << 6 * shifted - shifted) | codepoint;
      } else { //unexpected a continuation byte
        return -1;
      }
    } else { //ASCII
      return first;
    }
  }
}