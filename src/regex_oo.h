#include <regex.h>

typedef regex_t Regex;

Regex *make_regex(char *pattern, int flags);
int regex_match(Regex *regex, char *s);
void regex_free(Regex *regex);
void find_track_regex(char pattern[]);
