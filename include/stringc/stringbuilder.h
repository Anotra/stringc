#ifndef STRINGC_STRINGBUILDER_H
#define STRINGC_STRINGBUILDER_H

#include <stdbool.h>

typedef struct stringbuilder stringbuilder;

extern stringbuilder *
stringbuilder_create();
extern void
stringbuilder_destroy(stringbuilder *sb);

/**
 * this pointer should be discarded after any changes made to the stringbuilder
 * @return internal string
 */
extern const char *
stringbuilder_string(stringbuilder *sb);
extern char *
stringbuilder_to_string(stringbuilder *sb);

extern size_t
stringbuilder_length(stringbuilder *sb);
extern bool
stringbuilder_set_length(stringbuilder *sb, const size_t length);
extern void
stringbuilder_reset(stringbuilder *sb);

extern bool
stringbuilder_delete(stringbuilder *sb, const size_t position, const size_t length);

extern bool
stringbuilder_insert(stringbuilder *sb, const size_t position, const char *string);
extern bool
stringbuilder_insertl(stringbuilder *sb, const size_t position, const char *string, const size_t length);
extern bool
stringbuilder_insertf(stringbuilder *sb, const size_t position, const char *format, ...);
extern bool
stringbuilder_insert_sb(stringbuilder *dest, const size_t position, const stringbuilder *src);
extern bool
stringbuilder_append(stringbuilder *sb, const char *string);
extern bool
stringbuilder_appendl(stringbuilder *sb, const char *string, const size_t length);
extern bool
stringbuilder_appendf(stringbuilder *sb, const char *format, ...);
extern bool
stringbuilder_append_sb(stringbuilder *dest, const stringbuilder *src);


#endif//STRINGC_STRINGBUILDER_H