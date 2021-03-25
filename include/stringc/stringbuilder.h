#ifndef STRINGC_STRINGBUILDER_H
#define STRINGC_STRINGBUILDER_H

#include <stdio.h>
#include <stdbool.h>

typedef struct stringbuilder stringbuilder;

stringbuilder *stringbuilder_create(void);
void           stringbuilder_destroy(stringbuilder *sb);

/**
 * this pointer should be discarded after any changes made to the stringbuilder
 * @return internal string
 */
const char * stringbuilder_string(stringbuilder *sb);
char *       stringbuilder_to_string(stringbuilder *sb);

void         stringbuilder_set_max_capacity(stringbuilder *sb, size_t capacity);
size_t       stringbuilder_max_capacity(stringbuilder *sb);
size_t       stringbuilder_length(stringbuilder *sb);
bool         stringbuilder_set_length(stringbuilder *sb, const size_t length);
void         stringbuilder_reset(stringbuilder *sb);
bool         stringbuilder_delete(stringbuilder *sb, const size_t position, const size_t length);
bool         stringbuilder_insert(stringbuilder *sb, const size_t position, const char *string);
bool         stringbuilder_insertl(stringbuilder *sb, const size_t position, const char *string, const size_t length);
bool         stringbuilder_insertf(stringbuilder *sb, const size_t position, const char *format, ...);
bool         stringbuilder_insert_sb(stringbuilder *dest, const size_t position, const stringbuilder *src);
bool         stringbuilder_append(stringbuilder *sb, const char *string);
bool         stringbuilder_appendl(stringbuilder *sb, const char *string, const size_t length);
bool         stringbuilder_appendf(stringbuilder *sb, const char *format, ...);
bool         stringbuilder_append_sb(stringbuilder *dest, const stringbuilder *src);
size_t       stringbuilder_append_fgets(stringbuilder *sb, FILE *file);

#endif//STRINGC_STRINGBUILDER_H