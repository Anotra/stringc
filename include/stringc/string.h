#ifndef STRINGC_STRING_H
#define STRINGC_STRING_H

#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

extern char *
strduplen(const char *const src, size_t *length);

//UTF8
extern size_t
utf8len(const char *str, const char *end);
extern bool
utf8validate(const char *str, const char *end, size_t *length) ;
extern int32_t
utf8decode(const char **str, const char *end, bool reset_ptr_on_fail);
extern bool
utf8encode(char **buf, const char *end, const int32_t codepoint, size_t *utf8_size);

//BASE64
extern uint8_t *
base64encode(const uint8_t *in, size_t len, uint8_t *out);
extern uint8_t *
base64decode(const uint8_t *in, uint8_t *out);

#endif//STRINGC_STRING_H
