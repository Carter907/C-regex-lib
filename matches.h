#ifndef _MATCHES_H
#define _MATCHES_H

#include <regex.h>

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

char *creg_matches(const char *const src, regoff_t *off, char *regex_string);

#endif
