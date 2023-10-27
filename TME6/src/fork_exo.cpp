#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	int j = N , i = 1 ;
	int nb = 0;

	for (; i<=N && j==N && fork()==0 ; i++ ) {
		nb = 0 ;
		std::cout << "pid: " << getpid() << " pere:" << getppid() << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				j=0;
				nb=0;
				std::cout <<  "pid: " << getpid() << " pere:" << getppid() <<  " k:j " << k << ":" << j << std::endl;
			} else { nb++ ;}
		}
	}

	if(j && i < N)nb++;

	for(int p = 0 ; p < nb ; p++){
		if(wait(NULL) == -1) std::cout<<"trop de wait "<<getpid() << std::endl;
	}
	
	
	return 0;
}
