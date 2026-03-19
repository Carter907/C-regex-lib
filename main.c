#define _XOPEN_SOURCE 700

#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))
#define MATCH_CAP (16)

char **match_regex(const char *regex_string, const char *input_string,
                   size_t *num_matches) {

  regex_t regex;
  regmatch_t pmatch[1];
  regoff_t off, len;

  const char *s = input_string;
  size_t matches_cap = MATCH_CAP;

  char **matches = malloc(sizeof(char *) * MATCH_CAP);

  if (regcomp(&regex, regex_string, REG_NEWLINE | REG_EXTENDED))
    return NULL; // will update error handling later

  for (size_t matches_size = 0;; matches_size++) {

    if (regexec(&regex, s, ARRAY_SIZE(pmatch), pmatch, 0)) {
      *num_matches = matches_size; // set the number of matches before returning
      break;
    }

    off =
        pmatch[0].rm_so +
        (int)(s -
              input_string); // off represents start of match (relative to s) +
                             // the relative distance between start and input
    len = pmatch[0].rm_eo - pmatch[0].rm_so;

    if (matches_size == matches_cap) {

      char **ptr = realloc(matches, sizeof(char *) * matches_cap * 2);
      matches_cap *= 2;

      if (ptr == NULL) {
        perror("realloc()");
        return NULL;
      }
      matches = ptr; // update matches ptr
    }

    matches[matches_size] = strndup(input_string + off, (size_t)len);

    s += pmatch[0].rm_eo; // move string ptr past this match
  }

	regfree(&regex);

  return matches;
}

int main(void) {
  const char *const input_string =
      "1) John Driverhacker;\n2) John Doe;\n3) John Foo;\n";
  const char *const regex_string = "John.*o";
  size_t num_matches = 0;

  char **matches = match_regex(regex_string, input_string, &num_matches);

  if (!matches) {

    puts("Found no matches"
         "exiting...");
    exit(EXIT_SUCCESS);
  }

  puts("Found matches:");
  for (size_t i = 0; i < num_matches; i++) {
    printf("- %s\n", matches[i]);
    free(matches[i]);
  }
  free(matches);

  exit(EXIT_SUCCESS);
}
