/* "Object Oriented" Regex
 * Inspired by code written by Allen Downey for Exercises in C
 * https://github.com/AllenDowney/ExercisesInC/tree/master/exercises/ex05
 */
#include <regex_oo.h>
#include <stdlib.h>

#define MAX_FILENAME 255
#define MAX_FILECOUNT 255
#define BUFSIZE 1000

typedef regex_t Regex;

/* Returns a new Regex that matches the given pattern.
*
* pattern: string regex
* flags: flags passed to regcomp
* returns: new Regex
*/
Regex *make_regex(char *pattern, int flags) {
    regex_t *regex = malloc(sizeof(regex_t)); // Not using shvalloc because regex_t
    int ret;
    ret = regcomp(regex, pattern, flags);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    return regex;
}

/* Checks whether a regex matches a string.
*
* regex: Regex pointer
* s: string
* returns: 1 if there's a match, 0 otherwise
*/
int regex_match(Regex *regex, char *s) {
    int ret = regexec(regex, s, 0, NULL, 0);
    if (!ret) {
        return 1;
    } else{
        return 0;
    }
}

/* Frees a Regex.
*
* regex: Regex pointer
*/
void regex_free(Regex *regex) {
    free(regex);
}


/* Finds all tracks that match the given pattern.
*
* Prints track number and title.
*/
void find_track_regex(char pattern[]) {
    int i;

    Regex *regex = make_regex(pattern, REG_EXTENDED | REG_NOSUB);

    for (i=0; i<NUM_TRACKS; i++) {
        if (regex_match(regex, tracks[i])) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }

    regex_free(regex);
}
