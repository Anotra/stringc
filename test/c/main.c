#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "testing.h"

#define TEST_FEATURE(name)\
  do {\
    if (0 == strcmp(#name, argv[1])) {\
      return test_ ## name();\
    }\
  } while (0)

int main(int argc, char *argv[]) {
  if (argc != 2)
    return 1;
  TEST_FEATURE(stringbuilder);
  TEST_FEATURE(stringjoiner);
  TEST_FEATURE(utf8);
  TEST_FEATURE(base64);
}
