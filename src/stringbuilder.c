#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "stringc/stringbuilder.h"

struct stringbuilder {
  size_t length;
  size_t capacity;
  char *string;
};

StringBuilder *
stringbuilder_create() {
  StringBuilder *sb = calloc(1, sizeof *sb);
  return sb;
}

void
stringbuilder_destroy(StringBuilder *sb) {
  if (sb->string)
    free(sb->string);
  free(sb);
}

static bool
ensure_space(StringBuilder *sb, size_t space_needed) {
  if (!sb->string) {
    size_t capacity = space_needed < 64 ? 64 : space_needed;
    sb->string = malloc((capacity + 1) * sizeof *sb->string);
    if (sb->string) {
      sb->string[0] = '\0';
      sb->capacity = capacity;
      return true;
    }
    return false;
  }

  if (space_needed > sb->capacity - sb->length) {
    size_t new_capacity = sb->capacity * 2;
    if (new_capacity - sb->length < space_needed)
      new_capacity = sb->length + space_needed;
    char *new_string = realloc(sb->string, (new_capacity + 1) * sizeof *sb->string);
    if (!new_string)
      return false;
    sb->string = new_string;
    sb->capacity = new_capacity;
  }
  return true;
}

size_t
stringbuilder_length(StringBuilder *sb) {
  return sb->length;
}

bool
stringbuilder_set_length(StringBuilder *sb, size_t length) {
  if (sb->length >= length) {
    sb->length = length;
    sb->string[sb->length] = '\0';
    return true;
  }
  return false;
}

void
stringbuilder_reset(StringBuilder *sb) {
  sb->length = 0;
  if (sb->string)
    sb->string[0] = '\0';
}

bool
stringbuilder_insert(StringBuilder *sb, size_t position, char *string) {
  const size_t len = strlen(string);
  if (ensure_space(sb, len)) {
    if (position != sb->length) {
      memmove(&sb->string[position + len], &sb->string[position], (sb->length - position) * sizeof *sb->string);
    }
    memcpy(&sb->string[position], string, len * sizeof *string);
    sb->length += len;
    sb->string[sb->length] = '\0';
    return true;
  }
  return false;
}

bool
stringbuilder_append(StringBuilder *sb, char *string) {
  return stringbuilder_insert(sb, sb->length, string);
}

bool
stringbuilder_appendf(StringBuilder *sb, char *format, ...) {
  int printed = 0;
  va_list args;
  if (ensure_space(sb, 0)) {
    va_start(args, format);
    printed = vsnprintf(&sb->string[sb->length], sb->capacity - sb->length, format, args);
    va_end(args);
  } else {
    return false;
  }
  if (printed > sb->capacity - sb->length) {
    if (ensure_space(sb, printed)) {
      va_start(args, format);
      printed = vsnprintf(&sb->string[sb->length], sb->capacity - sb->length, format, args);
      va_end(args);
    } else {
      //undo append
      sb->string[sb->length] = '\0';
      return false;
    }
  }
  sb->length += printed;
  sb->string[sb->length] = '\0';
  return true;
}

bool
stringbuilder_insertf(StringBuilder *sb, size_t position, char *format, ...) {
  va_list args;
  char buffer[65536];
  va_start(args, format);
  int printed = vsnprintf(buffer, sizeof buffer - 1, format, args);
  va_end(args);
  if (printed < sizeof buffer - 1) {
    buffer[printed] = '\0';
    return stringbuilder_insert(sb, position, buffer);
  } else {
    char *string = malloc((printed + 10) * sizeof *string);
    if (string) {
      va_start(args, format);
      printed = vsnprintf(string, printed + 1, format, args);
      va_end(args);
      string[printed] = '\0';
      bool succeeded = stringbuilder_insert(sb, position, string);
      free(string);
      return succeeded;
    }
  }
  return false;
}

bool
stringbuilder_insert_sb(StringBuilder *dest, size_t position, StringBuilder *src) {
  return stringbuilder_insert(dest, position, src->string);
}

bool
stringbuilder_append_sb(StringBuilder *dest, StringBuilder *src) {
  return stringbuilder_insert_sb(dest, dest->length, src);
}

char *
stringbuilder_to_string(StringBuilder *sb) {
  char *string = malloc((sb->length + 1) *  sizeof *sb->string);
  if (string) {
    if (sb->string) {
      memcpy(string, sb->string, (sb->length + 1) *  sizeof *sb->string);
    } else {
      string[0] = '\0';
    }
  }
  return string;
}

char *
stringbuilder_string(StringBuilder *sb) {
  return sb->string;
}