int main(int argc , char ** argv){
    if(argc < 2){
        perror("mauvais argument");
        exit(1);
    }

    vector<vector<char*>> help ;
    int add = 0 ;

    vector<char *> vec ;
    help.pushback(vec);

    for(int  i = 1 ; i < argc; i++ ){

        char* tmp = argv[i];
        if(! strcmp(tmp , "|")){
            add ++;
            vector<char *> vec2 ;
            help.pushback(vec2);
            continue;
        }
        help[add].pushback(tmp);
       
    }

    pid_t fils[add];

    int fd[2];
    fd[0] = dup(0);
    fd[1] = dup(1);

    int pip[2];
    pipe(pip);
    for(int i = 0 ; i<add ; i++){
        
        close(pip[1]);
        pipe(pip);
        
        if(i < add-1)dup2(pip[1],1);
        if(i != 0) dup2(pip[0],0);

        if(! (fils[i] = fork())){

            exevc();
        }
        
        close(pip[0]);

        dup2(fd[0],0);
        dup2(fd[1],1);
        
    }
    
    for(int i = 0 ; i< add ; i++){
        wait(NULL);
    }
}