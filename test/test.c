#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stringc/stringbuilder.h"
#include "stringc/stringjoiner.h"

int main() {
  StringBuilder *sb = stringbuilder_create();
  for (int i=0; i<10; i++)
    stringbuilder_appendf(sb, "%s", "Hello World!\n");
  for (int i=0; i<10; i++)
    stringbuilder_insertf(sb, 13, "%s", "Hello!!!\n");
    
  StringBuilder *sb2 = stringbuilder_create();
  stringbuilder_append(sb2, "---SB2---\n");
    
  stringbuilder_insert_sb(sb, 13, sb2);
  stringbuilder_append(sb2, "---SB2 --- ..... ---\n");
  stringbuilder_insert_sb(sb, 0, sb2);
  stringbuilder_append_sb(sb, sb2);
  stringbuilder_reset(sb2);
  stringbuilder_appendf(sb2, "Hello from StringBuilder %i!\n", 2);
  stringbuilder_append_sb(sb, sb2);
  stringbuilder_appendl(sb, "TRUNCATED STRING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", 17);
  printf("%s\n\n", stringbuilder_string(sb));
  stringbuilder_destroy(sb);
  stringbuilder_destroy(sb2);


  StringJoiner *sj = stringjoiner_create("StringJoiner:\n[\n  ", ",\n  ", "\n]", "[]");
  stringjoiner_add(sj, "\"Hello!\"");
  stringjoiner_add(sj, "\"Hello!\"");
  stringjoiner_addf(sj, "\"Hello %i!\"", 123);
  char *sj_result = stringjoiner_to_string(sj);
  printf("%s\n", sj_result);
  free(sj_result);
  stringjoiner_destroy(sj);

  sj = stringjoiner_create(NULL, ", ", NULL, "[]");
  for (int i=0; i<10; i++)
    stringjoiner_addf(sj, i > 3 ? "%i" : "", i);
  sj_result = stringjoiner_to_string(sj);
  printf("%s\n", sj_result);
  free(sj_result);

  stringjoiner_reset(sj);
  for (int i=5; i<10; i++)
    stringjoiner_addf(sj, "%i", i);
  sj_result = stringjoiner_to_string(sj);
  printf("%s\n", sj_result);
  free(sj_result);
  stringjoiner_destroy(sj);
}