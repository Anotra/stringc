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

#ifndef STRINGC_STRINGBUILDER_H
#define STRINGC_STRINGBUILDER_H


#ifdef __cplusplus
#include <cstdio>
#include <cstdbool>
extern "C" {
#else
#include <stdio.h>
#include <stdbool.h>
#endif

#include "export.h"

typedef struct stringbuilder stringbuilder;

STRINGC_EXPORT stringbuilder *stringbuilder_create(void);
STRINGC_EXPORT void           stringbuilder_destroy(stringbuilder *sb);

/**
 * this pointer should be discarded after any changes made to the stringbuilder
 * @return internal string
 */
STRINGC_EXPORT const char * stringbuilder_string(stringbuilder *sb);
STRINGC_EXPORT char *       stringbuilder_to_string(stringbuilder *sb);

STRINGC_EXPORT void         stringbuilder_set_max_capacity(stringbuilder *sb, size_t capacity);
STRINGC_EXPORT size_t       stringbuilder_max_capacity(stringbuilder *sb);
STRINGC_EXPORT size_t       stringbuilder_length(stringbuilder *sb);
STRINGC_EXPORT bool         stringbuilder_set_length(stringbuilder *sb, const size_t length);
STRINGC_EXPORT void         stringbuilder_reset(stringbuilder *sb);
STRINGC_EXPORT bool         stringbuilder_delete(stringbuilder *sb, const size_t position, const size_t length);
STRINGC_EXPORT bool         stringbuilder_insert(stringbuilder *sb, const size_t position, const char *string);
STRINGC_EXPORT bool         stringbuilder_insertl(stringbuilder *sb, const size_t position, const char *string, const size_t length);
STRINGC_EXPORT bool         stringbuilder_insertf(stringbuilder *sb, const size_t position, const char *format, ...);
STRINGC_EXPORT bool         stringbuilder_insert_sb(stringbuilder *dest, const size_t position, const stringbuilder *src);
STRINGC_EXPORT bool         stringbuilder_append(stringbuilder *sb, const char *string);
STRINGC_EXPORT bool         stringbuilder_appendl(stringbuilder *sb, const char *string, const size_t length);
STRINGC_EXPORT bool         stringbuilder_appendf(stringbuilder *sb, const char *format, ...);
STRINGC_EXPORT bool         stringbuilder_append_sb(stringbuilder *dest, const stringbuilder *src);

#ifdef __cplusplus
}
#endif

#endif//STRINGC_STRINGBUILDER_H

