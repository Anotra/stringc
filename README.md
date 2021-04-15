# stringc

### [stringc/string.h](https://github.com/Anotra/stringc/blob/main/include/stringc/string.h)
```c
  size_t len;
  char *dup = strduplen("Hello World!, Привет мир!", &len);
  size_t len8;
  bool is_valid_utf8 = utf8validate(dup, NULL, &len8);
  printf("%zu, %zu\nutf8_valid: %s, len=%zu\n", len, utf8len(dup, NULL), is_valid_utf8 ? "t" : "f", len8); 
  free(dup);
```
#### base64 encoding/decoding
```c
  const char *string = "Hello World!!";
  char encoded[64], decoded[64];
  size_t encoded_len, decoded_len;
  base64encodes(encoded, sizeof encoded, &encoded_len, string, 0);
  base64decodes(decoded, sizeof decoded, &decoded_len, encoded, 0);
  printf(
    "%s\n%s\n%s\n"
    "String Length: %zu\nEncoding Length: %zu\nsuccess: %c\n", 
    string, encoded, decoded,
    decoded_len, encoded_len, strcmp(string, decoded) == 0 ? 'T' : 'F'
  );
```
Output
```
  Hello World!!
  SGVsbG8gV29ybGQhIQ==
  Hello World!!
  String Length: 13
  Encoding Length: 20
  success: T
```
### [stringc/stringbuilder.h](https://github.com/Anotra/stringc/blob/main/include/stringc/stringbuilder.h)
```c
  stringbuilder *sb = stringbuilder_create();
  stringbuilder_append(sb, "Hello World!");
  stringbuilder_insert(sb, 0, "HELLO WORLD!\n");
  printf("%s", stringbuilder_string(sb));
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
