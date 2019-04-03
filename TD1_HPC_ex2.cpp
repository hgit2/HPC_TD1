#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h> // OpenMP
#include <time.h> // pour "chronométrer"
#include <string.h> // pour la comparaison de char

using namespace std;

double Frand(double fMin, double fMax){
		// génère un nombre aléatoire entre fmin et fmax
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void Randomfill(char** mat, int size1, int size2){
	// remplit une matrice de size1 lignes et size2 colonnes avec des char aléatoires (suivant une loi uniforme)

	for(int i=0; i<size1; ++i){
	    for(int j=0; j<size2; ++j){
		    int number = Frand(97,122); 
		    mat[i][j]=char(number);
		}
	}
}

void Affichemat(char** mat, int size1, int size2){
	// affiche le contenu de la une matrice mat composé de size1 lignes et size2 colonnes
	cout << "Affichage du tableau : " <<endl;
	for(int i=0; i<size1; ++i){
	    cout<< "[";
	    for(int j=0; j<size2; ++j){
		    cout << mat[i][j] << " ";
		}
		cout<< "]"<<endl;
	} 
}

/*map<char, int> Freqchar(char** mat, int size1, int size2){
	// crée un objet map, freqc, contenant la liste, sans doublons, des char présents dans mat, associés à leur fréquence d'apparition
	std::map<char, int> freqc; 
	freqc.insert ( std::pair<char,int>(mat[0][0],0) ); // initialisation
	# pragma omp parallel for 
	for(int i=0; i<size1; ++i){
		for(int j=0; j<size2; ++j){
			char letter=mat[i][j];
			bool notpresent=true; // indique si letter a déjà été rencontrée
			for (map<char,int>::iterator it=freqc.begin(); it!=freqc.end(); ++it){
				char mapletter= it->first;
				if(letter==mapletter){
					// le char a déjà été rencontré
					it->second=it->second+1; // on incrémente la fréquence d'apparition de ce char
					bool notpresent=false;
					break;
				}
			}
			if(notpresent){
				// le char n'a pas déjà été rencontré
				freqc.insert ( std::pair<char,int>(letter,1) );
			}
		}
	}
	return freqc;
}*/

map<char, int> addmap(map<char, int> map1, map<char, int> map2){
	// renvoie un objet map contenant l'addition de deux objets map, clé par clé 

	map<char, int> addmap; 
	for(int i=97; i<=122; ++i){
		addmap.insert( std::pair<char,int>(char(i),0) ); // initialisation
		addmap[i]=map1[i]+map2[i];
	}
	return addmap;
}

map<char, int> Freqchar2(char** mat, int size1, int size2){
	// crée un objet map, freqc, contenant la liste, sans doublons, des lettres de l'alphabet, associés à leur fréquence d'apparition dans la matrice tab
	
	std::map<char, int> freqc; 
	for(int i=97; i<=122; ++i){
		freqc.insert( std::pair<char,int> (char(i),0) ); // initialisation
	}
	std::map<char, int> freqcglobal; 
	for(int i=97; i<=122; ++i){
		freqcglobal.insert( std::pair<char,int> (char(i),0) ); // initialisation
	}
	# pragma omp parallel for 
	for(int i=0; i<size1; ++i){
		# pragma omp parallel for
		for(int j=0; j<size2; ++j){
			char letter=mat[i][j];
			for (map<char,int>::iterator it=freqc.begin(); it!=freqc.end(); ++it){
				char mapletter= it->first;
				if(letter==mapletter){
					// on a trouvé la lettre correspondant au char de la matrice 
					it->second=it->second+1; // on incrémente la fréquence d'apparition de ce char
					break;
				}
		freqcglobal=addmap(freqcglobal, freqc); // somme le résultat des sous-problèmes
			}
		}
	}
	return freqc;
}


int main(int argc, char** argv){

cout << "hello world" << endl;

int size1=atoi(argv[1]); // donne le nombre de lignes de la matrice
int size2=atoi(argv[2]); // donne le nombre de colonnes de la matrice
int coeur=atoi(argv[3]); // donne le nombre de coeur
omp_set_num_threads(coeur);

char** mat1; // creation de la matrice mat1
mat1 = new char*[size1];
for (int i=0; i<size1; i++){
    mat1[i] = new char[size2*sizeof(char)];
}
Randomfill(mat1, size1, size2);
Affichemat(mat1, size1, size2);

int before=(clock()*1000)/CLOCKS_PER_SEC;
map<char, int> freqmat1 = Freqchar2(mat1, size1, size2);
int after=(clock()*1000)/CLOCKS_PER_SEC;
int diff=after - before;
cout << "temps d'execution du comptage de lettres d'une matrice " << diff << endl;

cout << "liste:"<<endl;
for(map<char,int>::iterator it=freqmat1.begin(); it!=freqmat1.end(); ++it){
    cout << it->first << " => " << it->second << "\n"; 
}

// DELETES
delete mat1;

return 0;
}
