#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "rsleep.h"

int pv =  3;

static void hand(int){
    
    pv--;
    std::cout << getpid() <<" pv restant: "<<pv<< std::endl;
   
}

void attaque(pid_t adversaire){
    struct sigaction sa;
    sa.sa_handler = &hand ;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT,&sa,NULL);
    
    if(kill(adversaire , SIGINT)){
        std::cout << getpid() <<" gagne" << std::endl;
        exit(1); 
    };
    randsleep();
}

void defense(){
    struct sigaction sa;
    sa.sa_handler = SIG_IGN ;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT,&sa,NULL);

    randsleep();
}

void combat(pid_t adversaire){
   
    while(pv){
        defense();
        attaque(adversaire);
    }

    std::cout<< getpid() << " perdu " << std::endl;

}

int main(){
    struct sigaction sa;
    sa.sa_handler = SIG_IGN ;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT,&sa,NULL);
    
    pid_t luke;
    luke = fork();

    if(luke == -1 )return 1;

    if(luke){ //fils
        pid_t vador = getppid();

        combat(vador);

        return 0;
    }else{ //pere

        combat(luke);
        wait(NULL);
    }

    return 0;
}