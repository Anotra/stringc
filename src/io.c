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

#include <string.h>

#include "stringc/io.h"

int
fgets_line(char **line, size_t *capacity, size_t max_capacity, FILE *stream) {
  //TODO: implement max_capacity
  if (!*line && !(*line = malloc(*capacity = 64)))
    return *capacity = 0, -1;
  (*line)[0] = 0;
  char *position = *line;
  while (1) {
    (*line)[*capacity - 1] = 1;
    (*line)[*capacity - 2] = 0;
    if (fgets(position, *line + *capacity - position, stream)) {
      if ((*line)[*capacity - 1] == 0
       && (*line)[*capacity - 2] != '\n') {
        size_t new_capacity = *capacity * 2;
        char *tmp = realloc(*line, new_capacity);
        if (tmp) {
          position = tmp + *capacity - 1;
          *line = tmp;
          *capacity = new_capacity;
        } else return -1;
      } else goto success;
    } else if (position != *line) {
      if (feof(stream))
        goto success;
      return -1;
    } else return 0;
  }
  success:
  return 1;
}