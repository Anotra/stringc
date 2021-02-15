#include <stdlib.h>

#include "stringc/string.h"

bool
utf8validate(const char *str, size_t *length) {
  size_t len = 0;
  bool is_valid = true;
  for (int32_t codepoint; (codepoint = utf8decode(&str));) {
    if (codepoint == -1) is_valid = false;
    else len++;
  }
  if (length)
    *length = len;
  return is_valid;
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
utf8decode(const char **str) {
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

bool
utf8encode(char **buf, char *end, const int32_t codepoint, size_t *utf8_size) {
  size_t bytes_needed = 1;
  if ((codepoint & 0x7F) == codepoint) { //is ascii
    if (utf8_size) *utf8_size = bytes_needed;
    if (!buf || (end && (*buf + bytes_needed) > end))
      return false;
    //nothing to compute. insert ascii into buffer
    *(*buf)++ = codepoint;
    return true;
  } else if (codepoint < 0) {            //invalid codepoint
    if (utf8_size) *utf8_size = 0;
    return false;
  } else {                               //UTF8
    int32_t mask = 0, cp = 0;

    //dry run to calculate bytes needed
    for (cp = codepoint, mask = 0x3F; (mask & cp) != cp; cp >>= 6, mask >>= 1)
      bytes_needed++;

    if (utf8_size) *utf8_size = bytes_needed;
    if (!buf || (end && (*buf + bytes_needed) > end))
      return false;
    
    //begin inserting utf8 chars
    *buf += bytes_needed;
    for (cp = codepoint, mask = 0x3F; (mask & cp) != cp; cp >>= 6, mask >>= 1)
      //insert continuation bytes back to front
      *(--*buf) = 0x80 | (cp & 0x3F);
    //insert first byte
    *(--*buf) = (~mask << 1) | cp;
    *buf += bytes_needed;
    return true;
  }
}