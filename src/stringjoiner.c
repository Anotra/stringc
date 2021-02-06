#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "stringc/stringjoiner.h"
#include "stringc/stringbuilder.h"

struct stringjoiner {
  char *prefix;
  char *delimiter;
  char *suffix;
  char *empty;
  StringBuilder *sb;
};

StringJoiner *
stringjoiner_create(const char *prefix, const char *delimiter, const char *suffix, const char *empty) {
  StringJoiner *sj = calloc(1, sizeof *sj);
  if (sj) {
    if ((sj->sb = stringbuilder_create())) {
      if ((prefix    && !(sj->prefix    = strdup(prefix)))
       || (delimiter && !(sj->delimiter = strdup(delimiter)))
       || (suffix    && !(sj->suffix    = strdup(suffix)))
       || (empty     && !(sj->empty     = strdup(empty)))) {
        free(sj->prefix);
        free(sj->suffix);
        free(sj->delimiter);
        free(sj->empty);
      } else {
        return sj;
      }
      stringbuilder_destroy(sj->sb);
    }
    free(sj);
  }
  return NULL;
}

void
stringjoiner_destroy(StringJoiner *sj) {
  free(sj->prefix);
  free(sj->delimiter);
  free(sj->suffix);
  free(sj->empty);
  stringbuilder_destroy(sj->sb);
  free(sj);
}

void
stringjoiner_reset(StringJoiner *sj) {
  stringbuilder_reset(sj->sb);
}

char *
stringjoiner_to_string(StringJoiner *sj) {
  const size_t len = stringbuilder_length(sj->sb);
  if (len == 0)
    return strdup(sj->empty ? sj->empty : "");
  if (sj->suffix)
    stringbuilder_append(sj->sb, sj->suffix);
  char *string = stringbuilder_to_string(sj->sb);
  stringbuilder_set_length(sj->sb, len);
  return string;
}

bool
stringjoiner_add(StringJoiner *sj, const char *string) {
  const size_t length = stringbuilder_length(sj->sb);
  char *str_to_add = (length == 0) ? sj->prefix : sj->delimiter;
  if (str_to_add && !stringbuilder_append(sj->sb, str_to_add))
    goto fail;
  if (stringbuilder_append(sj->sb, string))
    return true;

  fail:
  stringbuilder_set_length(sj->sb, length);
  return false;
}

bool
stringjoiner_addf(StringJoiner *sj, const char *format, ...) {
  va_list args;
  char buffer[65536];
  va_start(args, format);
  int printed = vsnprintf(buffer, sizeof buffer - 1, format, args);
  va_end(args);
  if (printed < sizeof buffer - 1) {
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