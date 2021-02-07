# stringc

#### [String](https://github.com/Anotra/stringc/blob/main/include/stringc/string.h)
```c
  size_t len;
  char *dup = strduplen("Hello World!, Привет мир!", &len);
  size_t len8;
  bool is_valid_utf8 = utf8validate(dup, &len8);
  printf("%zu, %zu\nutf8_valid: %s, len=%zu\n", len, utf8len(dup), is_valid_utf8 ? "t" : "f", len8); 
  free(dup);
```

#### [StringBuilder](https://github.com/Anotra/stringc/blob/main/include/stringc/stringbuilder.h)
```c
  StringBuilder *sb = stringbuilder_create();
  stringbuilder_append(sb, "Hello World!");
  stringbuilder_insert(sb, 0, "HELLO WORLD!\n");
  printf("%s", stringbuilder_string(sb));
  stringbuilder_destroy(sb);
```

#### [StringJoiner](https://github.com/Anotra/stringc/blob/main/include/stringc/stringjoiner.h)
```c
  StringJoiner *sj = stringjoiner_create("[", ", ", "]", "[]");
  for (int i=0; i<100; i++)
    stringjoiner_addf(sj, "Item #%i", i);
  char *result = stringjoiner_to_string(sj);
  printf("%s\n", result);
  free(result);
  stringjoiner_destroy(sj);
```
