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

extern bool
stringbuilder_insertl(StringBuilder *sb, size_t position, size_t length, char *string) {
  if (ensure_space(sb, length)) {
    if (position > sb->length) {
      return false;
    } else if (position < sb->length) {
      memmove(&sb->string[position + length], &sb->string[position], (sb->length - position) * sizeof *sb->string);
    }
    memcpy(&sb->string[position], string, length * sizeof *string);
    sb->length += length;
    sb->string[sb->length] = '\0';
    return true;
  }
  return false;
}

extern bool
stringbuilder_appendl(StringBuilder *sb, char *string, size_t length) {
  return stringbuilder_insertl(sb, sb->length, length, string);
}

bool
stringbuilder_insert(StringBuilder *sb, size_t position, char *string) {
  return stringbuilder_insertl(sb, position, strlen(string), string);
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
  int printed = vsnprintf(buffer, sizeof buffer, format, args);
  va_end(args);
  if (printed < sizeof buffer) {
    return stringbuilder_insertl(sb, position, printed, buffer);
  } else {
    char *string = malloc((printed + 1) * sizeof *string);
    if (string) {
      va_start(args, format);
      printed = vsnprintf(string, printed + 1, format, args);
      va_end(args);
      bool succeeded = stringbuilder_insertl(sb, position, printed, string);
      free(string);
      return succeeded;
    }
  }
  return false;
}

bool
stringbuilder_insert_sb(StringBuilder *dest, size_t position, StringBuilder *src) {
  return stringbuilder_insertl(dest, position, src->length, src->string);
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

const char *
stringbuilder_string(StringBuilder *sb) {
  return sb->string;
}