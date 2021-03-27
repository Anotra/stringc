#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stringc/stringjoiner.h>

int main() {
  stringjoiner *sj = stringjoiner_create("[ ", ", ", " ]", "[]");
  if (strcmp(stringjoiner_string(sj), "[]") != 0)
    return 1;
  
  stringjoiner_add(sj, "Hello World!");
  if (strcmp(stringjoiner_string(sj), "[ Hello World! ]") != 0)
    return 1;
  stringjoiner_addf(sj, "%s", "Hello World!");
  if (strcmp(stringjoiner_string(sj), "[ Hello World!, Hello World! ]") != 0)
    return 1;

  stringjoiner_reset(sj);
  if (strcmp(stringjoiner_string(sj), "[]") != 0)
    return 1;
  
  for (int i = 0; i < 10; i++)
    stringjoiner_addf(sj, "%i", i);
  
  if (strcmp(stringjoiner_string(sj), "[ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ]") != 0)
    return 1;
  
  stringjoiner_destroy(sj);

  sj = stringjoiner_create("[", 0, "]", "[]");
  for (size_t i = 1; i < 10; i++) {
    stringjoiner_addf(sj, "%zu", i);
    if (i % 3 && stringjoiner_length(sj) != 2 + i)
      return 1;
  }
  stringjoiner_reset(sj);
  if (stringjoiner_length(sj) != 2)
    return 1;

  stringjoiner_destroy(sj);
}