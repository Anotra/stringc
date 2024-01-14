/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* MIT License                                                                    *
*                                                                                *
* Copyright (c) 2020 Anotra                                                      *
*                                                                                *
* Permission is hereby granted, free of charge, to any person obtaining a copy   *
* of this software and associated documentation files (the "Software"), to deal  *
* in the Software without restriction, including without limitation the rights   *
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      *
* copies of the Software, and to permit persons to whom the Software is          *
* furnished to do so, subject to the following conditions:                       *
*                                                                                *
* The above copyright notice and this permission notice shall be included in all *
* copies or substantial portions of the Software.                                *
*                                                                                *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  *
* SOFTWARE.                                                                      *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef STRINGC_BASE64_H
#define STRINGC_BASE64_H

#ifdef __cplusplus
#include <cstdlib>
#include <cinttypes>
extern "C" {
#else
#include <stdlib.h>
#include <inttypes.h>
#endif

#include "export.h"

typedef struct base64 
#ifndef STRINGC_BASE64_PRIVATE
{ const uint8_t _private[512]; }
#endif
base64;

STRINGC_EXPORT base64 * base64init(base64 *digits, const char *characters);
STRINGC_EXPORT base64 * base64create(              const char *characters);

STRINGC_EXPORT char * base64encode    (                      char *out, size_t out_size, size_t *out_len, const void *in, size_t in_size);
STRINGC_EXPORT void * base64decode    (                      void *out, size_t out_size, size_t *out_len, const char *in, size_t in_size);
STRINGC_EXPORT char * base64encodes   (                      char *out, size_t out_size, size_t *out_len, const void *in, size_t in_size);
STRINGC_EXPORT char * base64decodes   (                      void *out, size_t out_size, size_t *out_len, const char *in, size_t in_size);
STRINGC_EXPORT char * base64encode_ex (const base64 *digits, char *out, size_t out_size, size_t *out_len, const void *in, size_t in_size);
STRINGC_EXPORT void * base64decode_ex (const base64 *digits, void *out, size_t out_size, size_t *out_len, const char *in, size_t in_size);
STRINGC_EXPORT char * base64encodes_ex(const base64 *digits, char *out, size_t out_size, size_t *out_len, const void *in, size_t in_size);
STRINGC_EXPORT char * base64decodes_ex(const base64 *digits, void *out, size_t out_size, size_t *out_len, const char *in, size_t in_size);

#ifdef __cplusplus
}
#endif

#endif//STRINGC_BASE64_H

