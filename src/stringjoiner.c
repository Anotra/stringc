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
stringjoiner_create(char *prefix, char *delimiter, char *suffix, char *empty) {
  StringJoiner *sj = calloc(1, sizeof *sj);
  if (sj) {
    if (sj->sb = stringbuilder_create()) {
      sj->prefix = prefix ? strdup(prefix) : NULL;
      sj->delimiter = delimiter ? strdup(delimiter) : NULL;
      sj->suffix = suffix ? strdup(suffix) : NULL;
      sj->empty = empty ? strdup(empty) : NULL;
      return sj;
    }
    free(sj);
  }
  return NULL;
}

void
stringjoiner_destroy(StringJoiner *sj) {
  if (sj->prefix)
    free(sj->prefix);
  if (sj->delimiter)
    free(sj->delimiter);
  if (sj->suffix)
    free(sj->suffix);
  if (sj->empty)
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
stringjoiner_add(StringJoiner *sj, char *string) {
  const size_t len = stringbuilder_length(sj->sb);
  bool fail = false;
  if (len == 0) {
    if (sj->prefix)
      fail |= !stringbuilder_append(sj->sb, sj->prefix);
    fail |= !stringbuilder_append(sj->sb, string);
  } else {
    if (sj->delimiter)
      fail |= !stringbuilder_append(sj->sb, sj->delimiter);
    fail |= !stringbuilder_append(sj->sb, string);
  }
  if (fail)
    stringbuilder_set_length(sj->sb, len);
  return !fail;
}

bool
stringjoiner_addf(StringJoiner *sj, char *format, ...) {
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