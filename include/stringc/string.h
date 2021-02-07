#ifndef STRINGC_STRING_H
#define STRINGC_STRING_H

#include <string.h>
#include <inttypes.h>

extern char *
strdupl(const char *const src, size_t *length);

extern size_t
utf8len(const char *str);
extern size_t
utf8len_fast(const char *str);
extern int32_t
utf8next(const char **str);

#endif//STRINGC_STRING_H