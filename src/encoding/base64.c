#include <stdlib.h>
#include <ctype.h>

#define STRINGC_STRING_BASE64_PRIVATE
#include "stringc/string.h"

struct base64digits {
  uint8_t characters[128];
  uint8_t decode_table[256];
  uint8_t padding[128];
};

base64digits default_base64_characters = {
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

base64digits *
base64digits_init(base64digits *digits, const char *characters) {
  memset(digits, 0, sizeof *digits);
  memset(digits->decode_table, 0xFF, sizeof digits->decode_table);
  const size_t len = characters ? strlen(characters) : 0;
  switch (len) {
    case 65: digits->characters[64] = characters[64]; //fallthru
    case 64: memcpy(digits->characters, characters, 64);
      break;
    case  3: digits->characters[64] = characters[2]; //fallthru
    case  2: digits->characters[63] = characters[1]; //fallthru
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

base64digits *
base64digits_create(const char *characters) {
  base64digits *digits = malloc(sizeof *digits);
  if (digits) {
    base64digits *ret = base64digits_init(digits, characters);
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
base64encode_ex(const base64digits *digits, const void *in_buf, size_t in_size, char *out, size_t out_size, size_t *out_len) {
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
    bits =  *in++ << 16;
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

void *
base64decode_ex(const base64digits *digits, const char *in, size_t in_size, void *out_buf, size_t out_size, size_t *out_len) {
  const uint8_t *base64decode_table = digits->decode_table;
  const uint8_t base64_padding_character = digits->characters[64];
  uint8_t *out = out_buf;
  const int free_ret_on_fail = !out;
  if (!out) {
    out_size = base64decodelen(strlen(in));
    if (!(out = malloc(out_size)))
      return NULL;
  }
  uint8_t *ret = out;
  for (uint8_t character = 1, padding = 0; character && *in; padding = 0) {
    uint32_t bits = 0;
    for (int i = 0; i < 4;) {
      character = character ? *in++ : 0;
      uint32_t val = base64decode_table[character];
      if (val == 0xFF) {
        if (character == base64_padding_character || !character) {
          switch (i) {
            case 0:
              if (character == base64_padding_character)
                continue;
              if (!character)
                goto done;
            case 1:
              goto fail;
            default:
              bits <<= 6;
              padding++;
          }
        } else if (isspace(character)) {
          continue;
        } else goto fail;
      } else if (padding) {
        goto fail;
      } else if (in_size--) {
        bits <<= 6;
        bits |= val;
      } else goto fail;
      i++;
    }
    if (out_size >= 3u - padding) {
      out_size   -= 3u - padding;
                       *out++ = (bits >> 16);
      if (padding < 2) *out++ = (bits >>  8);
      if (padding < 1) *out++ =  bits;
    } else goto fail;
  }
  
  done:
  if (out_len) *out_len = out - ret;
  return ret;

  fail:
  if (free_ret_on_fail)
    free(ret);
  if (out_len) *out_len = 0;
  return NULL;
}

char *
base64encodes_ex(const base64digits *digits, const void *in, size_t in_size, char *out, size_t out_size, size_t *out_len) {
  if (!in_size) in_size = strlen(in);
  if (!out) {
    out_size = base64encodelen(in_size) + 1;
    if (!(out = malloc(out_size)))
      return NULL;
  } else if (!out_size) {
    return NULL;
  }
  size_t encoded_len;
  char *encoded = base64encode_ex(digits, in, in_size, out, out_size - 1, &encoded_len);
  if (encoded)
    encoded[encoded_len] = 0;
  if (out_len)
    *out_len = encoded_len;
  return encoded;
}

void *
base64decodes_ex(const base64digits *digits, const char *in, size_t in_size, void *out, size_t out_size, size_t *out_len) {
  if (!in_size) in_size = strlen(in);
  if (!out) {
    out_size = base64decodelen(in_size) + 1;
    if (!(out = malloc(out_size)))
      return NULL;
  } else if (!out_size) {
    return NULL;
  }
  size_t decoded_len;
  char *decoded = base64decode_ex(digits, in, in_size, out, out_size - 1, &decoded_len);
  if (decoded)
    decoded[decoded_len] = 0;
  if (out_len)
    *out_len = decoded_len;
  return decoded;
}

char *
base64encode(const void *in, size_t in_size, char *out, size_t out_size, size_t *out_len) {
  return base64encode_ex(&default_base64_characters, in, in_size, out, out_size, out_len);
}

void *
base64decode(const char *in, size_t in_size, void *out, size_t out_size, size_t *out_len) {
  return base64decodes_ex(&default_base64_characters, in, in_size, out, out_size, out_len);
}

char *
base64encodes(const void *in, size_t in_size, char *out, size_t out_size, size_t *out_len) {
  return base64encodes_ex(&default_base64_characters, in, in_size, out, out_size, out_len);
}

void *
base64decodes(const char *in, size_t in_size, void *out, size_t out_size, size_t *out_len) {
  return base64decodes_ex(&default_base64_characters, in, in_size, out, out_size, out_len);
}
