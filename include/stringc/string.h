#ifndef STRINGC_STRING_H
#define STRINGC_STRING_H

#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

extern char *
strduplen(const char *const src, size_t *length);

extern size_t
utf8len(const char *str);
extern bool
utf8validate(const char *str, size_t *length) ;
extern int32_t
utf8decode(const char **str);
extern bool
utf8encode(char **buf, char *end, const int32_t codepoint, size_t *utf8_size);

#endif//STRINGC_STRING_H