#ifndef STRINGC_STRING_H
#define STRINGC_STRING_H

#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

char *  strduplen(const char *const src, size_t *length);

//UTF8
size_t  utf8len(const char *str, const char *end);
bool    utf8validate(const char *str, const char *end, size_t *length) ;
int32_t utf8decode(const char **str, const char *end, bool reset_ptr_on_fail);
bool    utf8encode(char **buf, const char *end, const int32_t codepoint, size_t *utf8_size);


#endif//STRINGC_STRING_H
