/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* MIT License                                                                    *
*                                                                                *
* Copyright (c) 2020 Anotra                                                      *
*                                                                                *
* Permission is hereby granted, free of charge, to any person obtaining a copy   *
* of this software and associated documentation files (the "Software"), to deal  *
* in the Software without restriction, including without limitation the rights   *
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      *
* copies of the Software, and to permit persons to whom the Software is          *
* furnished to do so, subject to the following conditions:                       *
*                                                                                *
* The above copyright notice and this permission notice shall be included in all *
* copies or substantial portions of the Software.                                *
*                                                                                *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  *
* SOFTWARE.                                                                      *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <stdlib.h>
#include <errno.h>

#include "stringc/string.h"

bool
utf8validate(const char *str, const char *end, size_t *length) {
  size_t len = 0;
  bool is_valid = true;
  for (int32_t codepoint; (codepoint = utf8decode(&str, end, false));) {
    if (codepoint == -1) {
      is_valid = false;
      if (errno == ENOBUFS) break;
    } else len++;
  }
  if (length)
    *length = len;
  return is_valid;
}

size_t
utf8len(const char *str, const char *end) {
  size_t len = 0;
  if (end) {
    while (str < end && *str)
      if ((*str++ & 0xC0) != 0x80)
        len++;
  } else {
    while (*str)
      if ((*str++ & 0xC0) != 0x80)
        len++;
  }
  return len;
}

int32_t
utf8decode(const char **str, const char *end, bool reset_ptr_on_fail) {
  const char *const begin = *str;
  if (end && *str >= end) {
    if (*str == end)
      return 0;
    return errno = ENOBUFS, -1;
  }
  int32_t first = *(*str)++;
  if (first & 0x80) { //UTF-8
    if (first & 0x40) {
      int32_t codepoint = 0;
      int shifted = 0;
      for (; first & 0x40; first <<= 1, shifted++) {
        if ((**str & 0xC0) == 0x80) {
          codepoint <<= 6;
          if (end && *str >= end)
            goto fail;
          codepoint |= *(*str)++ & 0x3F;
        } else goto fail;
      }
      if (shifted < 6)
        return ((first & 0x3F) << (6 * shifted - shifted)) | codepoint;
    } else goto fail;
  } else return first;

  fail:
  if (reset_ptr_on_fail)
    *str = begin;
  return errno = EILSEQ, -1;
}

bool
utf8encode(char **buf, const char *end, const int32_t codepoint, size_t *utf8_size) {
  size_t bytes_needed = 1;
  if ((codepoint & 0x7F) == codepoint) { //ASCII
    if (utf8_size) *utf8_size = bytes_needed;
    if (!buf || (end && (*buf + bytes_needed) > end))
      return errno = ENOBUFS, false;

    //nothing to compute. insert ascii into buffer
    *(*buf)++ = codepoint;
    return true;
  } else if (codepoint < 0) {            //invalid codepoint
    if (utf8_size) *utf8_size = 0;
    return errno = EILSEQ, false;
  } else {                               //UTF8
    int32_t mask = 0, cp = 0;

    //dry run to calculate bytes needed
    for (cp = codepoint, mask = 0x3F; (mask & cp) != cp; cp >>= 6, mask >>= 1)
      bytes_needed++;

    if (utf8_size) *utf8_size = bytes_needed;
    if (!buf || (end && (*buf + bytes_needed) > end))
      return errno = ENOBUFS, false;
    
    //begin inserting utf8 chars
    char *tmp = (*buf += bytes_needed);
    for (cp = codepoint, mask = 0x3F; (mask & cp) != cp; cp >>= 6, mask >>= 1)
      //insert continuation bytes back to front
      *--tmp = 0x80 | (cp & 0x3F);
    //insert first byte
    *--tmp = (~mask << 1) | cp;
    return true;
  }
}

