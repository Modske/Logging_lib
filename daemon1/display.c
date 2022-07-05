#include <stdio.h>
#include <stdlib.h>
#include <shrd_log.h>

void print_help(char *prog_name);

int main(int argc, char *argv[]){

    if(argc > 2){
        print_help(argv[0]);
        return 1;
    }

    open_log();
    display_log(argv[1]);
    close_log();

    return 0;
}

void print_help(char *prog_name){
    printf("Program usage:\n");
    printf("%s (optional)[program name] \n", prog_name);
}