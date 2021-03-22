#ifndef STRINGC_STRING_H
#define STRINGC_STRING_H

#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

extern char *
strduplen(const char *const src, size_t *length);

//UTF8
size_t  utf8len(const char *str, const char *end);
bool    utf8validate(const char *str, const char *end, size_t *length) ;
int32_t utf8decode(const char **str, const char *end, bool reset_ptr_on_fail);
bool    utf8encode(char **buf, const char *end, const int32_t codepoint, size_t *utf8_size);

//BASE64
typedef struct base64digits 
#ifndef STRINGC_STRING_BASE64_PRIVATE
{ const uint8_t _private[512]; }
#endif
base64digits;

base64digits * base64digits_init(base64digits *digits, const char *characters);
base64digits * base64digits_create(                    const char *characters);

char * base64encode    (                            const void *in, size_t in_size, char *out, size_t out_size, size_t *out_len);
void * base64decode    (                            const char *in, size_t in_size, void *out, size_t out_size, size_t *out_len);
char * base64encodes   (                            const void *in, size_t in_size, char *out, size_t out_size, size_t *out_len);
void * base64decodes   (                            const char *in, size_t in_size, void *out, size_t out_size, size_t *out_len);
char * base64encode_ex (const base64digits *digits, const void *in, size_t in_size, char *out, size_t out_size, size_t *out_len);
void * base64decode_ex (const base64digits *digits, const char *in, size_t in_size, void *out, size_t out_size, size_t *out_len);
char * base64encodes_ex(const base64digits *digits, const void *in, size_t in_size, char *out, size_t out_size, size_t *out_len);
void * base64decodes_ex(const base64digits *digits, const char *in, size_t in_size, void *out, size_t out_size, size_t *out_len);

#endif//STRINGC_STRING_H
