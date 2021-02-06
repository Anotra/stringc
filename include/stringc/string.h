#ifndef STRINGC_STRING_H
#define STRINGC_STRING_H

#include <string.h>
#include <inttypes.h>

extern char *
strdupl(const char *const src, size_t *length);

extern size_t
utf8_strlen(const uint8_t *str);
extern size_t
utf8_strlen_fast(const uint8_t *str);
extern int32_t
utf8_next(const uint8_t **str);

#endif//STRINGC_STRING_H