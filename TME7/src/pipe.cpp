#include <cstddef>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <sys/wait.h>

using namespace std;

void help(char ** args , int v1){
    execv(args[v1] , &(args[v1]));
    exit(0);
}

int main(int argc , char ** argv){
    if(argc < 2){
        perror("mauvais argument");
        exit(1);
    }

    int add = 1 ;
    vector<int> v1;
    v1.push_back(1);
    for(int i = 1 ; i< argc ; i++){
        char*tmp = argv[i]; 
        if(strcmp(tmp , "|")==0){
            add++;
            *(argv+i) = NULL;
            v1.push_back(i+1);
        }
    }

    pid_t fils[add];
    int fd[2];
    fd[0] = dup(0);
    fd[1] = dup(1);

    int pi[2];
    pipe(pi);
    
    for(int i = 0 ; i<add ; i++){
        if(i > 0){
            dup2(pi[0],0);
            close(pi[0]);
            pipe(pi);
        }
          
        if(i < add-1)dup2(pi[1],1);
        close(pi[1]);
 

        if(! (fils[i] = fork())){
            help(argv , v1[i]);
            exit(0);
        }     

        dup2(fd[0],0);
        dup2(fd[1],1);
        
    }

    for(int i = 0 ; i< add ; i++){
        wait(&fils[i]);
    }

}