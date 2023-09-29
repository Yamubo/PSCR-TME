#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <cstring>

using namespace std;

int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	//std::vector<string> vec;
	
	std::vector< std::pair<string , int>* > vec;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		
		/*
		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0){
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
			
		}
		*/

		int t = 0;
		size_t tmp = vec.size() ;
		for(size_t i = 0 ; i<tmp ; i++ ){
			if(word == vec[i] -> first){
				vec[i] -> second ++;
				t= 1 ; break;

			}
			
		}

		if(!t){
			vec.push_back(new pair(word,1));
			nombre_lu++;
		}
			
		
	}
	input.close();

	size_t tmp = vec.size() ;
		for(size_t i = 0 ; i<tmp ; i++ ){
			string tt = vec[i] -> first;
			if(tt == "war" ||tt ==  "peace" ||tt ==  "toto")
			cout << "mot : "<< vec[i] -> first << " nb: " << vec[i] -> second << endl;

		}
			



	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
    return 0;
}

/*
Ex1 
il y a 566193 mots

Ex2 
dont 20333 mots différents

Ex4
la compléxité de cette méthode est mauvaise, les tables de hachage ou dictionnaires
seraient plus adapté. 
*/
