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
extern char *
base64encode(const void *in, size_t len, char *out, size_t *out_len);
extern void *
base64decode(const char *in, void *out, size_t *out_len);
extern char *
base64encodes(const void *in, char *out, size_t *out_len);
extern void *
base64decodes(const char *in, void *out, size_t *out_len);


//BASE16
extern char *
base16encode(const void *in, size_t len, char *out, size_t *out_len);
extern void *
base16decode(const char *in, void *out, size_t *out_len);

#endif//STRINGC_STRING_H
