#ifndef STRINGC_STRINGBUILDER_H
#define STRINGC_STRINGBUILDER_H

#include <stdbool.h>

typedef struct stringbuilder StringBuilder;

extern StringBuilder *
stringbuilder_create();

extern void
stringbuilder_destroy(StringBuilder *sb);

extern char *
stringbuilder_string(StringBuilder *sb);

extern char *
stringbuilder_to_string(StringBuilder *sb);

extern size_t
stringbuilder_length(StringBuilder *sb);

extern bool
stringbuilder_set_length(StringBuilder *sb, size_t length);

extern void
stringbuilder_reset(StringBuilder *sb);

extern bool
stringbuilder_insert(StringBuilder *sb, size_t position, char *string);

extern bool
stringbuilder_insertf(StringBuilder *sb, size_t position, char *format, ...);

extern bool
stringbuilder_insert_sb(StringBuilder *dest, size_t position, StringBuilder *src);

extern bool
stringbuilder_append(StringBuilder *sb, char *string);

extern bool
stringbuilder_appendf(StringBuilder *sb, char *format, ...);

extern bool
stringbuilder_append_sb(StringBuilder *dest, StringBuilder *src);


#endif//STRINGC_STRINGBUILDER_H