#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std; 

int main(){
    pid_t p , f1 , f2;
    p = getpid();
    int fds[2];
    if(pipe(fds)){
        perror("pipe");
        exit(1);
    }   


    if(! (f1 = fork())){
        f1 = getpid();
        close(fds[1]);
        read(fds[0],&f2,sizeof(pid_t));
        close(fds[0]);
        cout << "f1 " << p << " " << f1 << " " << f2 << endl;
        exit(0);
    }

    close(fds[0]);

    if(! (f2 = fork())){
        f2 = getpid();
        close(fds[1]);
        cout << "f2 " << p << " " << f1 << " " << f2 << endl;
        exit(0);
    }

    if(write(fds[1], &f2 , sizeof(pid_t)) != sizeof(pid_t)){
        perror("pipe");
        exit(1);
    }
    close(fds[1]);
    cout<< "principal "  << p << " " << f1 << " " << f2 << endl;
    wait(NULL);
    wait(NULL);
    return 0;
}