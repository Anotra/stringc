#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stringc/stringjoiner.h>

int main() {
  int result = 0;
  stringjoiner *sj = stringjoiner_create("[ ", ", ", " ]", "[]");
  if (strcmp(stringjoiner_string(sj), "[]") != 0)
    puts("cmp []"), result = 1;
  
  stringjoiner_add(sj, "Hello World!");
  if (strcmp(stringjoiner_string(sj), "[ Hello World! ]") != 0)
    puts("cmp [ Hello World! ]"), result = 1;
  stringjoiner_addf(sj, "%s", "Hello World!");
  if (strcmp(stringjoiner_string(sj), "[ Hello World!, Hello World! ]") != 0)
    puts("cmp [ Hello World!, Hello World! ]"), result = 1;

  stringjoiner_reset(sj);
  if (strcmp(stringjoiner_string(sj), "[]") != 0)
    puts("cmp [] 2"), result = 1;
  
  for (int i = 0; i < 10; i++)
    stringjoiner_addf(sj, "%i", i);
  
  if (strcmp(stringjoiner_string(sj), "[ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ]") != 0)
    puts("cmp [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ]"), result = 1;
  
  stringjoiner_destroy(sj);

  sj = stringjoiner_create("[", 0, "]", "[]");
  for (size_t i = 1; i < 10; i++) {
    stringjoiner_addf(sj, "%zu", i);
    if (i % 3 && stringjoiner_length(sj) != 2 + i)
      puts("length check"), result = 1;
  }
  stringjoiner_reset(sj);
  if (stringjoiner_length(sj) != 2)
    puts("empty length check"), result = 1;

  stringjoiner_destroy(sj);
  return result;
}

