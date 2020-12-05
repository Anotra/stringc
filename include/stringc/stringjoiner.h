#ifndef STRINGC_STRINGJOINER_H
#define STRINGC_STRINGJOINER_H

#include <stdbool.h>

typedef struct stringjoiner StringJoiner;

extern StringJoiner *
stringjoiner_create(char *prefix, char *delimiter, char *suffix, char *empty);

extern void
stringjoiner_destroy(StringJoiner *sj);

extern char *
stringjoiner_to_string(StringJoiner *sj);

extern bool
stringjoiner_add(StringJoiner *sj, char *string);

extern bool
stringjoiner_addf(StringJoiner *sj, char *format, ...);


#endif//STRINGC_STRINGJOINER_H