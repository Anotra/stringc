#ifndef STRINGC_STRINGJOINER_H
#define STRINGC_STRINGJOINER_H

#include <stdbool.h>

typedef struct stringjoiner StringJoiner;

extern StringJoiner *
stringjoiner_create(const char *prefix, const char *delimiter, const char *suffix, const char *empty);
extern void
stringjoiner_destroy(StringJoiner *sj);
extern void
stringjoiner_reset(StringJoiner *sj);

extern char *
stringjoiner_to_string(StringJoiner *sj);
extern const char *
stringjoiner_string(StringJoiner *sj);

extern bool
stringjoiner_add(StringJoiner *sj, const char *string);
extern bool
stringjoiner_addf(StringJoiner *sj, const char *format, ...);


#endif//STRINGC_STRINGJOINER_H