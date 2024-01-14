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

#ifndef STRINGC_STRINGJOINER_H
#define STRINGC_STRINGJOINER_H

#ifdef __cplusplus
#include <cstdbool>
extern "C" {
#else
#include <stdbool.h>
#endif

#include "export.h"

typedef struct stringjoiner stringjoiner;

STRINGC_EXPORT stringjoiner * stringjoiner_create(const char *prefix, const char *delimiter, const char *suffix, const char *empty);
STRINGC_EXPORT void           stringjoiner_destroy(stringjoiner *sj);
STRINGC_EXPORT void           stringjoiner_reset(stringjoiner *sj);

STRINGC_EXPORT size_t         stringjoiner_length(stringjoiner *sj);

/**
 * this pointer should be discarded after any changes made to the stringjoiner
 * @return internal string
 */
STRINGC_EXPORT const char *   stringjoiner_string(stringjoiner *sj);
STRINGC_EXPORT char *         stringjoiner_to_string(stringjoiner *sj);

STRINGC_EXPORT bool           stringjoiner_add(stringjoiner *sj, const char *string);
STRINGC_EXPORT bool           stringjoiner_addf(stringjoiner *sj, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif//STRINGC_STRINGJOINER_H

