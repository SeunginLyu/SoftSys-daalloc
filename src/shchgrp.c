#include "shvec.h"
#include "regex_oo.h"
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
    char ** regexes;
    if(arg_parse(argc, argv)){
        return 1;
    } else {
        num_regexes = argc - optind;
        
        if(num_regexes == 0){
            fprintf(stderr, "Error: At least one regex required\n");
            return 1;
        }
        
        regexes = (char **) malloc(sizeof(char*) * num_regexes);
        
        for(int index = 0; index < num_regexes; index++){
            regexes[index] = strdup(argv[index + optind]);
        }
    }

    printf("Regexes:\n");
    for(int i = 0; i < num_regexes; i++){
        printf("%s\n", regexes[i]);
    }
    // Run these against the stdin
    return 0;
}
