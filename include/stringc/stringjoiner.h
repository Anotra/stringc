#ifndef STRINGC_STRINGJOINER_H
#define STRINGC_STRINGJOINER_H

#include <stdbool.h>

typedef struct stringjoiner stringjoiner;

extern stringjoiner *
stringjoiner_create(const char *prefix, const char *delimiter, const char *suffix, const char *empty);
extern void
stringjoiner_destroy(stringjoiner *sj);
extern void
stringjoiner_reset(stringjoiner *sj);

/**
 * this pointer should be discarded after any changes made to the stringjoiner
 * @return internal string
 */
extern const char *
stringjoiner_string(stringjoiner *sj);
extern char *
stringjoiner_to_string(stringjoiner *sj);

extern bool
stringjoiner_add(stringjoiner *sj, const char *string);
extern bool
stringjoiner_addf(stringjoiner *sj, const char *format, ...);


#endif//STRINGC_STRINGJOINER_H