/* shchgrp
 *
 * SHitty
 * CHained
 * GReP
 * 
 * Filter text with multiple regexes. It's an over-engineered way to chain a few
 * regexes together. 
 * 
 * Written by Seungin Lyu, Adam Novotny, Matthew Beaudouin-Lafon
 */

#include "shvec.h"
#include "regexlib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <argp.h>

int arg_parse(int argc, char* argv[]){
    // parse arguments
    char ch;
    while((ch = getopt(argc, argv, "")) != EOF){
        switch (ch){
            default:
                fprintf(stderr, "Error: Unknow Flag");
                return 1;
        }
    }
    return 0;
}
int main(int argc, char *argv[]){
    int num_regexes = 0;

    Regex ** regexes;
    int * matches;
    int * matches_i;


    // Setup regexes and shvectors to hold matching strings
    if(arg_parse(argc, argv)){
        return 1;
    } else {
        num_regexes = argc - optind;
        
        if(num_regexes == 0){
            fprintf(stderr, "Error: At least one regex required\n");
            return 1;
        }
        
        // Allocate them
        regexes = (Regex **) malloc(sizeof(Regex*) * num_regexes);
        matches = malloc(sizeof(int) * num_regexes);
        matches_i = malloc(sizeof(int) * num_regexes);

        // Initialize them
        for(int index = 0; index < num_regexes; index++){
            regexes[index] = make_regex(argv[index + optind], REG_EXTENDED | REG_NOSUB);
            matches[index] = shvec_create();
            matches_i[index] = 0;
        }
    }


    // Find matches
    char in_buf[100];
    while(fgets(in_buf, 100, stdin) != NULL) {                      // Read stdin line-by-line
        for(int i = 0; i < num_regexes; i++){                       // Test each regex on the line
            int match = regexec(regexes[i], in_buf, 0, NULL, 0);
            if(match == 0) {                                        // If match, append the line to matches
                for(int x = 0; in_buf[x] != '\0'; x++){
                    shvec_set(matches[i], matches_i[i], (int)in_buf[x]);
                    matches_i[i]++;
                }
                shvec_set(matches[i], matches_i[i], '\0');          // End the shvector with a \0
            }
        }   
    }
    
    // Print matches
    for(int i = 0; i < num_regexes; i++){
        if(i!= 0) printf("\n");
        printf("Matches to regex (%s):\n", argv[i + optind]);
        for(int x = 0; x < shvec_get_size(i); x++){
            printf("%c", shvec_get(matches[i], x));
        }
    }

    return 0;
}
