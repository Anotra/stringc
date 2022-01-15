
#include <stdio.h>
#include <stringc/string.h>

#include "testing.h"

int test_utf8() {
  char buf[64];
  for (int i=1; i<10000000; i++) {
    char *enc = buf;
    const char *dec = buf;
    utf8encode(&enc, 0, i % 3984, 0);
    utf8encode(&enc, 0, i % 437, 0);
    utf8encode(&enc, 0, i * 3, 0);
    utf8encode(&enc, 0, i, 0);
    if (utf8decode(&dec, 0, 0) != i % 3984
     || utf8decode(&dec, 0, 0) != i % 437
     || utf8decode(&dec, 0, 0) != i * 3
     || utf8decode(&dec, 0, 0) != i)
      return printf("utf8 enc/dec %i\n", i), 1;
  }
  return 0;
}
