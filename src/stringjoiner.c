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
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "stringc/stringjoiner.h"
#include "stringc/stringbuilder.h"
#include "stringbuilder.h"

struct stringjoiner {
  stringbuilder sb;
  struct {
    char  *string;
    size_t length;
  } prefix, delimiter, suffix,
    empty, suffix_or_empty_added;
  size_t count;
  char strings[];
};

static char *
strpcpy(char *dest, const char *src) {
  size_t len = strlen(src) + 1;
  memcpy(dest, src, len * sizeof *src);
  return dest + len;
}

stringjoiner *
stringjoiner_create(const char *prefix, const char *delimiter, const char *suffix, const char *empty) {
  stringjoiner *sj = calloc(1, sizeof *sj + 
      (prefix ? strlen(prefix) + 1 : 0) + (delimiter ? strlen(delimiter) + 1 : 0) +
      (suffix ? strlen(suffix) + 1 : 0) + (empty     ? strlen(empty)     + 1 : 0));
  if (sj) {
    char *p = sj->strings;
    if (prefix)    sj->prefix.length    = strlen(prefix),    p = strpcpy(sj->prefix.string = p,    prefix);
    if (delimiter) sj->delimiter.length = strlen(delimiter), p = strpcpy(sj->delimiter.string = p, delimiter);
    if (suffix)    sj->suffix.length    = strlen(suffix),    p = strpcpy(sj->suffix.string = p,    suffix);
    if (empty)     sj->empty.length     = strlen(empty),     p = strpcpy(sj->empty.string = p,     empty);
    return sj;
  }
  return NULL;
}

void
stringjoiner_destroy(stringjoiner *sj) {
  stringbuilder_destroy(&sj->sb);
  free(sj);
}

static char * //this just looks cool
stringjoiner_set_suffix_or_empty_added(stringjoiner *sj, char *string) {
  return sj->suffix_or_empty_added.length = string ? strlen(string) : 0,
         sj->suffix_or_empty_added.string = string; }

void
stringjoiner_reset(stringjoiner *sj) {
  sj->count = 0;
  stringjoiner_set_suffix_or_empty_added(sj, NULL);
  stringbuilder_reset(&sj->sb);
}

size_t
stringjoiner_length(stringjoiner *sj) {
  return stringbuilder_length(&sj->sb) + 
    (sj->suffix_or_empty_added.string ? 0 : sj->count ? sj->suffix.length : sj->empty.length);
}

const char *
stringjoiner_string(stringjoiner *sj) {
  if (!sj->suffix_or_empty_added.string
   && stringjoiner_set_suffix_or_empty_added(sj, sj->count ? sj->suffix.string : sj->empty.string))
    stringbuilder_append(&sj->sb, sj->suffix_or_empty_added.string);
  return stringbuilder_string(&sj->sb);
}

char *
stringjoiner_to_string(stringjoiner *sj) {
  stringjoiner_string(sj);
  return stringbuilder_to_string(&sj->sb);
}

bool
stringjoiner_add(stringjoiner *sj, const char *string) {
  if (sj->suffix_or_empty_added.string) {
    stringbuilder_set_length(&sj->sb, stringbuilder_length(&sj->sb) - sj->suffix_or_empty_added.length);
    stringjoiner_set_suffix_or_empty_added(sj, NULL);
  }
  const size_t length = stringbuilder_length(&sj->sb);
  char *str_to_add = sj->count ? sj->delimiter.string : sj->prefix.string;
  if (str_to_add && !stringbuilder_append(&sj->sb, str_to_add))
    goto fail;
  if (stringbuilder_append(&sj->sb, string)) {
    sj->count++;
    return true;
  }

  fail:
  stringbuilder_set_length(&sj->sb, length);
  return false;
}

bool
stringjoiner_addf(stringjoiner *sj, const char *format, ...) {
  va_list args;
  char buffer[0x2000];
  va_start(args, format);
  int printed = vsnprintf(buffer, sizeof buffer, format, args);
  va_end(args);
  if (printed < 0) {
    return false;
  } else if ((size_t)printed < sizeof buffer) {
    buffer[printed] = '\0';
    return stringjoiner_add(sj, buffer);
  } else {
    char *string = malloc((printed + 1) * sizeof *string);
    if (string) {
      va_start(args, format);
      printed = vsnprintf(string, printed + 1, format, args);
      va_end(args);
      string[printed] = '\0';
      bool succeeded = stringjoiner_add(sj, string);
      free(string);
      return succeeded;
    }
  }
  return false;
}