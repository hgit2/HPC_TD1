#include <iostream>
#include <vector>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h> // OpenMP
#include <time.h> // pour "chronométrer"

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
	double* tab3; // tableau qui contiendra la somme terme à terme de tab1 et tab2
	tab3= new double[size1*sizeof(double)]; 
	if(size1==size2){
		# pragma omp parallel for shared(tab3) 
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
	//# pragma omp parallel for shared(S) 
	# pragma omp parallel for reduction(+:S)
	for(int i=0; i<size; ++i){
		S=S+tab[i];
	}
	return S;
}

double* Vectprod(double* tab, int size, double a){
	// Multiplication du tableau de double tab de taille size par un scalaire double a
	double* tabm; // tableau qui contiendra la multiplication des termes de tab par a
	tabm = new double[size*sizeof(double)]; 
	# pragma omp parallel for shared(tabm) 
	for(int i=0; i<size; ++i){
		tabm[i]=tab[i]*a;
	}
	return tabm;
}

int main(int argc, char** argv){

cout << "hello world" << endl;

// avec un tableau
int size=atoi(argv[1]); // donne la taille du tableau
int coeur=atoi(argv[2]); //Q5 : donne le nombre de coeur
omp_set_num_threads(coeur);

// Q1 et Q2
double* tab1; // creation du tableau tab1
tab1 = new double[size*sizeof(double)];
Randomfill(tab1, size);
//Affichetab(tab1, size);


// Q3
double* tab2; // creation du tableau tab2
tab2 = new double[size*sizeof(double)];
Randomfill(tab2, size);
//Affichetab(tab2, size);

int before1=(clock()*1000)/CLOCKS_PER_SEC;
double* tab3 = Addtab(tab1, size, tab2, size); // somme de tab1 et de tab2
int after1=(clock()*1000)/CLOCKS_PER_SEC;
int diff1=after1 - before1;
cout << "temps d'execution de la somme de deux vecteurs " << diff1 << endl;
// affichage de tab3
//Affichetab(tab3, size); 


//Q4
int before2=(clock()*1000)/CLOCKS_PER_SEC;
double sum1 = Sumtab(tab1, size); // somme des éléments de tab1
int after2=(clock()*1000)/CLOCKS_PER_SEC;
int diff2=after2 - before2;
cout << "temps d'execution de la somme des éléments d'un vecteur " << diff2 << endl;
// affichage de sum1
/*cout << "tab1 : " << endl;
Affichetab(tab1, size);
cout << "Somme des cases de tab1 = " << sum1 << endl;*/

//Q8
int before3=(clock()*1000)/CLOCKS_PER_SEC;
double* tabm1=Vectprod(tab1, size, 2); // multiplication des éléments de tab1 par 2
int after3=(clock()*1000)/CLOCKS_PER_SEC;
int diff3=after3 - before3;
cout << "temps d'execution de la multiplication des éléments d'un vecteur par un scalaire " << diff3 << endl;
// affichage de tabm1
/*cout << "tab1 : " << endl;
Affichetab(tab1, size);
cout << "Produit des cases de tab1 avec 2 = " << endl;
Affichetab(tabm1, size);*/

// DELETES
delete[] tab1;
delete[] tab2;
delete[] tab3;
delete[] tabm1;

return 0;
}
