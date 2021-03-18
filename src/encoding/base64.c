#include <stdlib.h>

#include "stringc/string.h"

static size_t
base64encodelen(size_t len) {
  return (len / 3 + !!(len % 3)) * 4;
}

static size_t
base64decodelen(size_t len) {
  return (len / 4 + !!(len % 4)) * 3;
}

static const uint8_t *base64_characters = (uint8_t *) "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static uint8_t *
base64encode_ex(const uint8_t *characters, const uint8_t *in, size_t len, uint8_t *out) {
  if (!out && !(out = malloc(base64encodelen(len) + 1))) return NULL;
  uint8_t *ret = out;
  if (!characters) characters = base64_characters;
  uint32_t bits;
  while (len >= 3) {
    bits = *in++;
    bits <<= 8;
    bits |= *in++;
    bits <<= 8;
    bits |= *in++;
    *out++ = characters[(bits >> 18) & 0x3F];
    *out++ = characters[(bits >> 12) & 0x3F];
    *out++ = characters[(bits >> 6) & 0x3F];
    *out++ = characters[bits & 0x3F];
    len -= 3;
  }
  if (len) {
      bits = 0;
      int bytes_used = 0;
      for (int i = 0; i < 3; i++) {
        bits <<= 8;
        if (len) {
          len--;
          bits |= *in++;
          bytes_used++;
        }
      }
      for (int i=18; i >= 0; i -= 6)
        *out++ = bytes_used-- >= 0 ? characters[(bits >> i) & 0x3F] : '=';
  }
  *out = 0;
  return ret;
}

static uint8_t *
base64decode_ex(const uint8_t *characters, const uint8_t *in, uint8_t *out) {
  uint8_t decode[256];
  int free_ret_on_fail = !out;
  if (!out && !(out = malloc(base64decodelen(strlen((char *)in)) + 1))) return NULL;
  uint8_t *ret = out;
  if (!characters) characters = base64_characters;
  memset(decode, 0xFF, sizeof decode);
  decode[0] = 0;
  for (int i = 0; i < 64; i++)
    decode[characters[i]] = i;
  for (uint8_t c = 1, padding = 0; c; padding = 0) {
    uint32_t bits = 0;
    for (int i = 0; i < 4; i++) {
      c = c ? *in++ : 0;
      int32_t b = decode[c];
      bits <<= 6;
      if (c == '=') {
        if (i < 2)
          goto fail;
        padding++;
      } else if (b == 0xFF) {
        goto fail;
      } else {
        bits |= b;
      }
    }
    *out++ = (bits >> 16) & 0xFF;
    if (padding < 2) *out++ = (bits >> 8) & 0xFF;
    if (padding < 1) *out++ = bits & 0xFF;
  }
  *out = 0;
  return ret;

  fail:
  if (free_ret_on_fail)
    free(ret);
  return NULL;
}

uint8_t *
base64encode(const uint8_t *in, size_t len, uint8_t *out) {
  return base64encode_ex(NULL, in, len, out);
}

uint8_t *
base64decode(const uint8_t *in, uint8_t *out) {
  return base64decode_ex(NULL, in, out);
}