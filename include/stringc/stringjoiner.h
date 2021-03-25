#ifndef STRINGC_STRINGJOINER_H
#define STRINGC_STRINGJOINER_H

#include <stdbool.h>

typedef struct stringjoiner stringjoiner;

stringjoiner * stringjoiner_create(const char *prefix, const char *delimiter, const char *suffix, const char *empty);
void           stringjoiner_destroy(stringjoiner *sj);
void           stringjoiner_reset(stringjoiner *sj);

/**
 * this pointer should be discarded after any changes made to the stringjoiner
 * @return internal string
 */
const char *   stringjoiner_string(stringjoiner *sj);
char *         stringjoiner_to_string(stringjoiner *sj);

bool           stringjoiner_add(stringjoiner *sj, const char *string);
bool           stringjoiner_addf(stringjoiner *sj, const char *format, ...);

#endif//STRINGC_STRINGJOINER_H