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