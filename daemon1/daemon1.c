#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <shrd_log.h>

int action_flag = 1;

void sigHandler(int sig);

int main(int argc, char *argv[]){

    struct sigaction action;

    action.sa_handler = sigHandler;    
    sigfillset(&action.sa_mask);    
    action.sa_flags = SA_RESTART;

    sigaction(SIGTERM, &action, NULL);    
    sigaction(SIGUSR1, &action, NULL);    
    sigaction(SIGHUP, &action, NULL);

    open_log();

    while(action_flag == 1){
        log_write(argv[0], INFO, "im working");
        sleep(2);
    }
    return 0;

}

void sigHandler(int sig){
    if (sig == SIGTERM){
        printf("Daemon terminated\n");
        close_log();
    exit(0);
    }
    else if (sig == SIGHUP){
        printf("HUP is used to reload any config files\n");
    }
    else if(sig == SIGUSR1){
        action_flag = 0;
    }
}
