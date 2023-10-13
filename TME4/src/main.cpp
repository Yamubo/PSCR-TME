#include "Banque.h"
#include <random>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#include <iostream>

using namespace std;
using namespace pr;

void boucle(Banque & b , int val){
	srand(time(NULL));

	int i , j ; //indices de comptes rdm
	int m ; //montant rdm
	//int spl ;
	
	for(int tmp = 0 ; tmp < 1000; tmp ++){
		i = rand() % 10 ;
		do{
			j = rand() % 10 ;
		}while(i == j );
	


		m = rand() % 99 + 1 ; 
		//spl = rand() % 20 / 10 ;

		b.transfert (i,j, m);
		//std::cout << "transfert entre " << i << " et " << j << " thread nb "  << val <<std::endl;
		//sleep(spl);
	}

	if(	! b.comptabiliser(400)){
	std::cout <<  "thread nb " << val << std::endl;
	}
	
	
}

const int NB_THREAD = 10;
int main () {
	vector<thread> threads;
	// TODO : creer des threads qui font ce qui est demandé
	Banque b(20,20);
	for(int i = 0 ; i < NB_THREAD ; i ++){
		//std::cout << "creation threads " << i << std::endl;
		threads.emplace_back(boucle, ref(b) , i );
	}



	for (auto & t : threads) {
		t.join();
	}


		b.comptabiliser(400);
	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
