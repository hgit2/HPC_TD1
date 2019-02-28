#include <iostream>
#include <vector>
#include <random>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

double frand(double fMin, double fMax){
		// génère un nombre aléatoire entre fmin et fmax
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void randomfill(double* tab, int size){
	// remplit un tableau tab de taille size avec des doubles aléatoires (suivant une loi uniforme)

	for(int i=0; i<size; ++i){
		double number = frand(0., 2.); 
		tab[i]=number;
	}
}

void affichetab(double* tab, int size){
	// affiche le contenu du tableau tab de taille size
	cout << "affichage de tab : " <<endl;
	for(int i=0; i<size; ++i){
		cout << tab[i] << endl;
	} 
}

int main(int argc, char** argv){

cout << "hello world" << endl;

/* avec un vector
vector<double> vect1(3,2.0);
vect1.push_back(1.);
cout << "vect1=" << vect1[3] << endl;*/

// avec un tableau
int size=atoi(argv[1]); // donne la taille du tableau

double* tab;
tab = new double[size*sizeof(double)];
randomfill(tab, size);
affichetab(tab, size);
delete tab;


return 0;
}
