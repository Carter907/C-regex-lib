#include "matches.h"
#include <string.h>

char *creg_matches(const char *const src, regoff_t *off, char *regex_string) {

  regex_t regex;
  regmatch_t pmatch[1];
  regoff_t len;

  if (regcomp(&regex, regex_string, REG_NEWLINE | REG_EXTENDED))
    return NULL; // will update error handling later

  if (regexec(&regex, src, ARRAY_SIZE(pmatch), pmatch, 0)) {
    return NULL;
  }

  *off = pmatch[0].rm_so len = pmatch[0].rm_eo - pmatch[0].rm_so;

  regfree(&regex);

  return strndup(src + off, (size_t)len);
}
