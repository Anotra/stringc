# stringc

### [stringc/string.h](https://github.com/Anotra/stringc/blob/main/include/stringc/string.h)
```c
  size_t len;
  char *dup = strduplen("Hello World!, Привет мир!", &len);
  size_t len8;
  bool is_valid_utf8 = utf8validate(dup, &len8);
  printf("%zu, %zu\nutf8_valid: %s, len=%zu\n", len, utf8len(dup), is_valid_utf8 ? "t" : "f", len8); 
  free(dup);
```

### [stringc/stringbuilder.h](https://github.com/Anotra/stringc/blob/main/include/stringc/stringbuilder.h)
```c
  stringbuilder *sb = stringbuilder_create();
  stringbuilder_append(sb, "Hello World!");
  stringbuilder_insert(sb, 0, "HELLO WORLD!\n");
  printf("%s", stringbuilder_string(sb));
  stringbuilder_destroy(sb);
```
#### read line from file into stringbuilder
```c
  stringbuilder *sb = stringbuilder_create();
  for (size_t count; (count = stringbuilder_append_fgets(sb, stdin)); stringbuilder_reset(sb))
    printf("%zu> %s", count, stringbuilder_string(sb));
  stringbuilder_destroy(sb);
```
### [stringc/stringjoiner.h](https://github.com/Anotra/stringc/blob/main/include/stringc/stringjoiner.h)
```c
  stringjoiner *sj = stringjoiner_create("[", ", ", "]", "[]");
  for (int i=0; i<100; i++)
    stringjoiner_addf(sj, "Item #%i", i);
  printf("%s\n", stringjoiner_string(sj));
  stringjoiner_destroy(sj);
```
