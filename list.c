#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


static char default_list_name[] = "Default list & stuff";


int main(int argc, char *argv[]) {


    printf("Number of arguments: %i\n", argc);
    for(int i=0;i<argc;i++){
        printf("argv[%i]: %s\n", i, argv[i]);
    }

    if(2 > argc) {
        printf("\tPring help\n");
        fprintf(stderr, "\a"); /* Beep! */
        return 0;
    }

    if(strcmp(argv[1], "add") && strcmp(argv[1], "help")) {
        fprintf(stderr, "\tUnrecognized command.\n\tSee todo help for more information\n");
        fprintf(stderr,"\a"); /* Beep! */
        return 1;
    }
    
    return 0;
}