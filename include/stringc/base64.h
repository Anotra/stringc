#ifndef STRINGC_BASE64_H
#define STRINGC_BASE64_H

#include <stdlib.h>
#include <inttypes.h>

typedef struct base64digits 
#ifndef STRINGC_BASE64_PRIVATE
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

#endif//STRINGC_BASE64_H