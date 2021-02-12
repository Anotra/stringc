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

stringbuilder *
stringbuilder_create(void) {
  stringbuilder *sb = calloc(1, sizeof *sb);
  return sb;
}

void
stringbuilder_destroy(stringbuilder *sb) {
  free(sb->string);
  free(sb);
}

static bool
increase_size(stringbuilder *sb, size_t space_needed) {
  size_t new_capacity = 0x10;
  for (; new_capacity - 1 < space_needed; new_capacity <<= 1)
    if (!new_capacity) return false;
  void *tmp = sb->string ? realloc(sb->string, new_capacity * sizeof *sb->string) : calloc(new_capacity, sizeof *sb->string);
  if (tmp) {
    sb->capacity = new_capacity - 1;
    sb->string = tmp;
  }
  return (bool)tmp;
}

static inline bool
ensure_space(stringbuilder *sb, size_t space_needed) {
  space_needed += sb->length;
  if (sb->capacity < space_needed || !sb->string)
    return increase_size(sb, space_needed);
  return true;
}

size_t
stringbuilder_length(stringbuilder *sb) {
  return sb->length;
}

bool
stringbuilder_set_length(stringbuilder *sb, const size_t length) {
  if (sb->length >= length) {
    sb->length = length;
    sb->string[sb->length] = '\0';
    return true;
  }
  return false;
}

void
stringbuilder_reset(stringbuilder *sb) {
  sb->length = 0;
  if (sb->string)
    sb->string[0] = '\0';
}

bool
stringbuilder_delete(stringbuilder *sb, const size_t position, const size_t length) {
  if ((position + length) < sb->length) {
    if (length)
      memmove(&sb->string[position], &sb->string[position + length], (sb->length - position + 1) * sizeof *sb->string);
    sb->length -= length;
    return true;
  }
  return false;
}

bool
stringbuilder_insertl(stringbuilder *sb, const size_t position, const char *string, const size_t length) {
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

bool
stringbuilder_appendl(stringbuilder *sb, const char *string, const size_t length) {
  return stringbuilder_insertl(sb, sb->length, string, length);
}

bool
stringbuilder_insert(stringbuilder *sb, const size_t position, const char *string) {
  return stringbuilder_insertl(sb, position, string, strlen(string));
}

bool
stringbuilder_append(stringbuilder *sb, const char *string) {
  return stringbuilder_insert(sb, sb->length, string);
}

bool
stringbuilder_appendf(stringbuilder *sb, const char *format, ...) {
  int printed = 0;
  va_list args;
  if (ensure_space(sb, 0)) {
    va_start(args, format);
    printed = vsnprintf(&sb->string[sb->length], sb->capacity - sb->length, format, args);
    va_end(args);
  } else return false;
  if (printed < 0) {
    return false;
  } else if ((size_t)printed > sb->capacity - sb->length) {
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
stringbuilder_insertf(stringbuilder *sb, const size_t position, const char *format, ...) {
  va_list args;
  char buffer[65536];
  va_start(args, format);
  int printed = vsnprintf(buffer, sizeof buffer, format, args);
  va_end(args);
  if (printed < 0) {
    return false;
  } else if ((size_t)printed < sizeof buffer) {
    return stringbuilder_insertl(sb, position, buffer, printed);
  } else {
    char *string = malloc((printed + 1) * sizeof *string);
    if (string) {
      va_start(args, format);
      printed = vsnprintf(string, printed + 1, format, args);
      va_end(args);
      bool succeeded = stringbuilder_insertl(sb, position, string, printed);
      free(string);
      return succeeded;
    }
  }
  return false;
}

bool
stringbuilder_insert_sb(stringbuilder *dest, const size_t position, const stringbuilder *src) {
  return stringbuilder_insertl(dest, position, src->string, src->length);
}

bool
stringbuilder_append_sb(stringbuilder *dest, const stringbuilder *src) {
  return stringbuilder_insert_sb(dest, dest->length, src);
}

char *
stringbuilder_to_string(stringbuilder *sb) {
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
stringbuilder_string(stringbuilder *sb) {
  ensure_space(sb, 0);
  return sb->string;
}

size_t
stringbuilder_append_fgets(stringbuilder *sb, FILE *file) {
  char buf[0x800];
  char *const start = buf, *end = buf + sizeof buf;
  size_t count = 0;
  do {
    char *pos = start;
    do {
      int character = fgetc(file);
      switch (character) {
        case EOF: {
          end = NULL;
        } break;

        case '\n':
          end = NULL;
          // fallthru
        default:
          *pos++ = character;
      };
    } while (end && pos < end);
    if (pos > start)
      stringbuilder_appendl(sb, start, count += pos - start);
  } while (end);
  return count;
}