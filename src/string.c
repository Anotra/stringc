#include <stdlib.h>
#include <stdbool.h>

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

bool
utf8validate(const char *str, size_t *len) {
  size_t length = 0;
  bool is_valid = true;
  while (true) {
    switch (utf8next(&str)) {
      case -1: {
        is_valid = false;
      } break;
      case 0:  {
        if (len)
          *len = length;
      } return is_valid;
      default: length++;
    }
  }
}

size_t
utf8len(const char *str) {
  size_t len = 0;
  while (*str)
    if ((*str++ & 0xC0) != 0x80)
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
      return shifted > 5 ? -1 : ((first & 0x3F) << (6 * shifted - shifted)) | codepoint;
    } else return -1;
  } else return first;
}