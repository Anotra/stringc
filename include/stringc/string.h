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

#ifndef STRINGC_STRING_H
#define STRINGC_STRING_H

#ifdef __cplusplus
#include <cstring>
#include <cstdbool>
#include <cinttypes>
extern "C" {
#else
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#endif

#include "export.h"

STRINGC_EXPORT char *  strduplen(const char *const src, size_t *const length);

//UTF8
STRINGC_EXPORT size_t  utf8len(const char *str, const char *end);
STRINGC_EXPORT bool    utf8validate(const char *str, const char *end, size_t *length) ;
STRINGC_EXPORT int32_t utf8decode(const char **str, const char *end, bool reset_ptr_on_fail);
STRINGC_EXPORT bool    utf8encode(char **buf, const char *end, const int32_t codepoint, size_t *utf8_size);

#ifdef __cplusplus
}
#endif

#endif//STRINGC_STRING_H

