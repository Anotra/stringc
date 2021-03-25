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

struct stringjoiner {
  stringbuilder *sb;
  char *prefix;
  char *delimiter;
  char *suffix;
  char *empty;
  char *suffix_or_empty_added;
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
      (suffix ? strlen(suffix) + 1 : 0) + (empty ? strlen(empty) + 1 : 0));
  if (sj) {
    char *p = sj->strings;
    if (prefix)    p = strpcpy(sj->prefix = p, prefix);
    if (delimiter) p = strpcpy(sj->delimiter = p, delimiter);
    if (suffix)    p = strpcpy(sj->suffix = p, suffix);
    if (empty)     p = strpcpy(sj->empty = p, empty);
    if ((sj->sb = stringbuilder_create()))
      return sj;
    free(sj);
  }
  return NULL;
}

void
stringjoiner_destroy(stringjoiner *sj) {
  stringbuilder_destroy(sj->sb);
  free(sj);
}

void
stringjoiner_reset(stringjoiner *sj) {
  sj->count = 0;
  sj->suffix_or_empty_added = NULL;
  stringbuilder_reset(sj->sb);
}

const char *
stringjoiner_string(stringjoiner *sj) {
  if (!sj->suffix_or_empty_added && (sj->suffix_or_empty_added = sj->count ? sj->suffix : sj->empty))
    stringbuilder_append(sj->sb, sj->suffix_or_empty_added);
  return stringbuilder_string(sj->sb);
}

char *
stringjoiner_to_string(stringjoiner *sj) {
  stringjoiner_string(sj);
  return stringbuilder_to_string(sj->sb);
}

bool
stringjoiner_add(stringjoiner *sj, const char *string) {
  if (sj->suffix_or_empty_added) {
    stringbuilder_set_length(sj->sb, stringbuilder_length(sj->sb) - strlen(sj->suffix_or_empty_added));
    sj->suffix_or_empty_added = NULL;
  }
  const size_t length = stringbuilder_length(sj->sb);
  char *str_to_add = sj->count ? sj->delimiter : sj->prefix;
  if (str_to_add && !stringbuilder_append(sj->sb, str_to_add))
    goto fail;
  if (stringbuilder_append(sj->sb, string)) {
    sj->count++;
    return true;
  }

  fail:
  stringbuilder_set_length(sj->sb, length);
  return false;
}

bool
stringjoiner_addf(stringjoiner *sj, const char *format, ...) {
  va_list args;
  char buffer[65536];
  va_start(args, format);
  int printed = vsnprintf(buffer, sizeof buffer - 1, format, args);
  va_end(args);
  if (printed < 0) {
    return false;
  } else if ((size_t)printed < sizeof buffer - 1) {
    buffer[printed] = '\0';
    return stringjoiner_add(sj, buffer);
  } else {
    char *string = malloc((printed + 10) * sizeof *string);
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