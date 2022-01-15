#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stringc/stringbuilder.h>

#include "testing.h"

int test_stringbuilder() {
  int result = 0;
  const char *hello_world = "Hello World!";
  stringbuilder *sb = stringbuilder_create();
  stringbuilder_set_max_capacity(sb, 16);
  if (!stringbuilder_append(sb, hello_world))
    puts("append hello_world"), result = 1;
  if (stringbuilder_append(sb, hello_world))
    puts("append hello_world 2"), result = 1;
  if (strcmp(stringbuilder_string(sb), hello_world) != 0)
    puts("cmp hello_world"), result = 1;
  stringbuilder_set_max_capacity(sb, SIZE_MAX);
  if (stringbuilder_max_capacity(sb) != SIZE_MAX)
    puts("check max_capacity"), result = 1;
  
  for (int i=0; i < 20; i+=2)
    stringbuilder_insertf(sb, i, "%i", i);
  if (strcmp(stringbuilder_string(sb), "0H2e4l6l8o1012141618 World!") != 0) 
    puts("cmp 0H2e4l6l8o1012141618 World!"), result = 1;
  
  stringbuilder_reset(sb);
  stringbuilder_append(sb, hello_world);
  if (stringbuilder_length(sb) != strlen(hello_world))
    puts("check length"), result = 1;
  if (strcmp(stringbuilder_string(sb), hello_world) != 0)
    puts("cmp hello_world 2"), result = 1;
  

  stringbuilder_destroy(sb);

  return result;
}
