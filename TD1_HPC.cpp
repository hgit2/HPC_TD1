#include <iostream>
#include <vector>
#include <random>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

double Frand(double fMin, double fMax){
		// génère un nombre aléatoire entre fmin et fmax
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void Randomfill(double* tab, int size){
	// remplit un tableau tab de taille size avec des doubles aléatoires (suivant une loi uniforme)

	for(int i=0; i<size; ++i){
		double number = Frand(0., 2.); 
		tab[i]=number;
	}
}

void Affichetab(double* tab, int size){
	// affiche le contenu du tableau tab de taille size
	cout << "Affichage du tableau : " <<endl;
	for(int i=0; i<size; ++i){
		cout << tab[i] << endl;
	} 
}

double* Addtab(double* tab1, int size1, double* tab2, int size2){
	// additionne 2 tableaux de taille respectives size1 et size2
	double* tab3;
	tab3= new double[size1*sizeof(double)]; 
	if(size1==size2){
		for(int i=0; i<size1; ++i){
			tab3[i]=tab1[i]+tab2[i];
		}
		return tab3;
	}
	else{
		cout << "ATTENTION : les tableaux n'ont pas la même taille" << endl;
		return tab3;
	}
}

double Sumtab(double* tab, int size){
	// renvoit la somme des cases du tableau tab de taille size
	double S=0; //initialisation de la somme 
	for(int i=0; i<size; ++i){
		S=S+tab[i];
	}
	return S;
}



int main(int argc, char** argv){

cout << "hello world" << endl;

/* avec un vector
vector<double> vect1(3,2.0);
vect1.push_back(1.);
cout << "vect1=" << vect1[3] << endl;*/

// avec un tableau
int size=atoi(argv[1]); // donne la taille du tableau

// Q1 et Q2
double* tab1; // creation du tableau tab1
tab1 = new double[size*sizeof(double)];
Randomfill(tab1, size);
Affichetab(tab1, size);


// Q3
double* tab2; // creation du tableau tab2
tab2 = new double[size*sizeof(double)];
Randomfill(tab2, size);
Affichetab(tab2, size);

double* tab3 = Addtab(tab1, size, tab2, size);
Affichetab(tab3, size);

//Q4
double sum1 = Sumtab(tab1, size);
cout << "tab1 : " << endl;
Affichetab(tab1, size);
cout << "Somme des cases de tab1 = " << sum1 << endl;

// DELETES
delete tab1;
delete tab2;
delete tab3;

return 0;
}
