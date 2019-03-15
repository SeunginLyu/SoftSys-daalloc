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
    if(arg_parse(argc, argv)){
        return 1;
    } else {
        num_regexes = argc - optind;
        
        if(num_regexes == 0){
            fprintf(stderr, "Error: At least one regex required\n");
            return 1;
        }
        
        regexes = (Regex **) malloc(sizeof(Regex*) * num_regexes);
        
        for(int index = 0; index < num_regexes; index++){
            regexes[index] = make_regex(argv[index + optind], REG_EXTENDED | REG_NOSUB);
        }
    }

    printf("Regexes:\n");
    for(int i = 0; i < num_regexes; i++){
        if(regexec(regexes[i], "hello world", 0, NULL, 0)) {
            printf("regex number %d matches hello world\n", i);
        }
    }
    // Run these against the stdin
    return 0;
}
