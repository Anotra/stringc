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

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define STRINGC_BASE64_PRIVATE
#include "stringc/base64.h"

struct base64 {
  uint8_t characters[128];
  uint8_t decode_table[256];
  uint8_t padding[128];
};

static const base64 default_base64_characters = {
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=",
  {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3E, 0xFF, 0xFF, 0xFF, 0x3F, 
    0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 
    0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 
    0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  }, {0}
};

base64 *
base64init(base64 *digits, const char *characters) {
  memset(digits, 0, sizeof *digits);
  memset(digits->decode_table, 0xFF, sizeof digits->decode_table);
  const size_t len = characters ? strlen(characters) : 0;
  switch (len) {
    case 65: digits->characters[64] = characters[64]; //fallthru
    case 64: memcpy(digits->characters, characters, 64);
      break;
    case  3: digits->characters[64] = characters[2]; //fallthru
    case  2: digits->characters[63] = characters[1];
             digits->characters[62] = characters[0];
      break;
    case  1: digits->characters[64] = characters[0];
      break;
    case  0: memcpy(digits, &default_base64_characters, sizeof *digits);
      break;
    default: return NULL;
  }
  for (int i = 0; i <= 64; i++)
    if (!digits->characters[i])
      digits->characters[i] = default_base64_characters.characters[i];
  for (int i = 0; i < 64; i++)
    digits->decode_table[digits->characters[i]] = i;
  return digits;
}

base64 *
base64create(const char *characters) {
  base64 *digits = malloc(sizeof *digits);
  if (digits) {
    base64 *ret = base64init(digits, characters);
    if (!ret) {
      free(digits);
      return NULL;
    }
  }
  return digits;
}

static size_t
base64encodelen(size_t len) {
  return (len / 3 + !!(len % 3)) * 4;
}

static size_t
base64decodelen(size_t len) {
  return (len / 4 + !!(len % 4)) * 3;
}

char *
base64encode_ex(const base64 *digits, char *out, size_t out_size, size_t *out_len, const void *in_buf, size_t in_size) {
  const uint8_t *base64characters = digits->characters;
  const uint8_t *in = in_buf;
  const int free_ret_on_fail = !out;
  if (!out) {
    out_size = base64encodelen(in_size);
    if (!(out = malloc(out_size)))
      return NULL;
  }
  char *ret = out;
  uint32_t bits;
  for (; in_size >= 3 && out_size >= 4; in_size -= 3, out_size -= 4) {
    bits  = *in++ << 16;
    bits |= *in++ <<  8;
    bits |= *in++;
    *out++ = base64characters[(bits >> 18) & 0x3F];
    *out++ = base64characters[(bits >> 12) & 0x3F];
    *out++ = base64characters[(bits >>  6) & 0x3F];
    *out++ = base64characters[ bits        & 0x3F];
  }
  if (in_size) {
    bits = 0;
    int bytes_used = 0;
    for (int i = 0; i < 3; i++) {
      bits <<= 8;
      if (in_size) {
        in_size--;
        bits |= *in++;
        bytes_used++;
      }
    }
    for (int i=18; i >= 0; i -= 6) {
      if (out_size--) {
        *out++ = bytes_used-- >= 0 ? base64characters[(bits >> i) & 0x3F] : base64characters[64];
      } else {
        if (free_ret_on_fail) //THIS SHOULD NEVER HAPPEN
          free(out);
        return NULL;
      }
    }
  }
  if (out_len) *out_len = out - ret;
  return ret;
}

static void
base64decode_fast(const base64 *digits, uint8_t **out, size_t *out_size, uint8_t **in, size_t *in_size) {
  const uint8_t *base64decode_table = digits->decode_table;
  while (*in_size >= 12 && *out_size >= 9) {
    uint8_t error = 0;
    for (int i = 0; i < 3; i++) {
      uint32_t bits = 0;
      for (int i = 18; i >= 0; i -= 6) {
        uint8_t val = base64decode_table[*(*in)++];
        error      |= val;
        bits       |= val  << i;
      }
      *(*out)++     = bits >> 16;
      *(*out)++     = bits >>  8;
      *(*out)++     = bits;
    }
    if (error == 0xFF) {
      (*in)        -= 12;
      (*out)       -=  9;
      return;
    } else {
      (*in_size)   -= 12;
      (*out_size)  -=  9;
    }
  }
}

static bool
base64decode_tolerant(const base64 *digits, uint8_t **out, size_t *out_size, uint8_t **in, size_t *in_size) {
  const uint8_t *base64decode_table = digits->decode_table;
  const uint8_t base64_padding_character = digits->characters[64];
  for (uint8_t padding = 0; *in_size; padding = 0) {
    uint32_t bits = 0;
    int i = 4;
    while (i > 0 && *in_size) {
      (*in_size)--;
      uint8_t character = *(*in)++;
      uint8_t val = base64decode_table[character];
      if (val == 0xFF) {
        if (!character) {
          return false;
        } else if (character == base64_padding_character) {
          switch (i) {
            case 4:   continue;
            case 3:   return false;
            default:  bits <<= 6;
                      padding++;
                      i--;
                      continue;
          }
        } else if (isspace(character)) {
          continue;
        } else return false;
      } else if (padding) {
         return false;
      } else {
        bits <<= 6;
        bits |= val;
        i--;
        continue;
      }
    }
    switch (i) {
      case 4:  continue;
      case 3:  return false;
      case 2:  //fallthru
      case 1:  bits <<= i * 6;
               padding += i;
               //fallthru
      case 0: if (*out_size >= 3u - padding) {
                  *out_size -= 3u - padding;
                                 *(*out)++ = (bits >> 16);
                if (padding < 2) *(*out)++ = (bits >>  8);
                if (padding < 1) *(*out)++ =  bits;
              } else return false;
    }
  }
  return true;
}

void *
base64decode_ex(const base64 *digits, void *out_buf, size_t out_size, size_t *out_len, const char *in, size_t in_size) {
  uint8_t *out = out_buf;
  const int free_ret_on_fail = !out;
  if (!in_size)
    in_size = strlen(in);
  if (!out) {
    out_size = base64decodelen(strlen(in));
    if (!(out = malloc(out_size)))
      return NULL;
  }
  uint8_t *const ret = out;
  base64decode_fast(digits, &out, &out_size, (uint8_t **)&in, &in_size);
  base64decode_tolerant(digits, &out, &out_size, (uint8_t **)&in, &in_size);
  if (in_size) {
    if (free_ret_on_fail)
      free(ret);
    if (out_len) *out_len = 0;
    return NULL;
  } else {
    if (out_len) *out_len = out - ret;
    //TODO: realloc
    return ret;
  }
}

char *
base64encodes_ex(const base64 *digits, char *out, size_t out_size, size_t *out_len, const void *in, size_t in_size) {
  if (!in_size) in_size = strlen(in);
  if (!out) {
    out_size = base64encodelen(in_size) + 1;
    if (!(out = malloc(out_size)))
      return NULL;
  } else if (!out_size) {
    return NULL;
  }
  size_t encoded_len;
  char *encoded = base64encode_ex(digits, out, out_size - 1, &encoded_len, in, in_size);
  if (encoded)
    encoded[encoded_len] = 0;
  if (out_len)
    *out_len = encoded_len;
  return encoded;
}

char *
base64decodes_ex(const base64 *digits, void *out, size_t out_size, size_t *out_len, const char *in, size_t in_size) {
  if (!in_size) in_size = strlen(in);
  if (!out) {
    out_size = base64decodelen(in_size) + 1;
    if (!(out = malloc(out_size)))
      return NULL;
  } else if (!out_size) {
    return NULL;
  }
  size_t decoded_len;
  char *decoded = base64decode_ex(digits, out, out_size - 1, &decoded_len, in, in_size);
  if (decoded)
    decoded[decoded_len] = 0;
  if (out_len)
    *out_len = decoded_len;
  //TODO: realloc
  return decoded;
}

char *
base64encode(char *out, size_t out_size, size_t *out_len, const void *in, size_t in_size) {
  return base64encode_ex(&default_base64_characters, out, out_size, out_len, in, in_size);
}

void *
base64decode(void *out, size_t out_size, size_t *out_len, const char *in, size_t in_size) {
  return base64decode_ex(&default_base64_characters, out, out_size, out_len, in, in_size);
}

char *
base64encodes(char *out, size_t out_size, size_t *out_len, const void *in, size_t in_size) {
  return base64encodes_ex(&default_base64_characters, out, out_size, out_len, in, in_size);
}

char *
base64decodes(void *out, size_t out_size, size_t *out_len, const char *in, size_t in_size) {
  return base64decodes_ex(&default_base64_characters, out, out_size, out_len, in, in_size);
}
