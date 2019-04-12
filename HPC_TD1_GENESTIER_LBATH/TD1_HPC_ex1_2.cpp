#include <iostream>
#include <vector>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h> // OpenMP
#include <time.h> // pour "chronométrer"
#include <fstream> // pour les fichiers

using namespace std;

double Frand(double fMin, double fMax){
		// génère un nombre aléatoire entre fmin et fmax
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void Randomfill(double** mat, int size1, int size2){
	// remplit une matrice de size1 lignes et size2 colonnes avec des doubles aléatoires (suivant une loi uniforme)

	for(int i=0; i<size1; ++i){
	    for(int j=0; j<size2; ++j){
		    double number = Frand(0., 2.); 
		    mat[i][j]=number;
		}
	}
}

void Affichemat(double** mat, int size1, int size2){
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


double** Addtab(double** mat1, int size1, int size2, double** mat2, int size3, int size4){
	// additionne 2 matrices de taille respectives size1 lignes et size2 colonnes et size3 lignes et size4 colonnes
	double** mat3; // tableau qui contiendra la somme terme à terme de mat1 et mat2
	mat3 = new double*[size1];
    for (int i=0; i<size1; i++){
        mat3[i] = new double[size2*sizeof(double)];
    }
	if(size1==size2 and size3==size4){
		# pragma omp parallel for shared(mat3) 
		for(int i=0; i<size1; ++i){
		    for (int j=0; j<size2; ++j){
			    mat3[i][j]=mat1[i][j]+mat2[i][j];
			}
		}
		return mat3;
	}
	else{
		cout << "ATTENTION : les matrices n'ont pas la même taille" << endl;
		return mat3;
	}
}


double Summat(double** mat, int size1, int size2){
	// renvoit la somme des cases de la matrice mat de taille size1 x size2
	double S=0; //initialisation de la somme 
	//# pragma omp parallel for shared(S) 
	# pragma omp parallel for reduction(+:S)
	for(int i=0; i<size1; ++i){
	    for (int j=0; j<size2; ++j){
		    S=S+mat[i][j];
		}
	}
	return S;
}


double** Matprod(double** mat, int size1, int size2, double a){
	// Multiplication de la matrice de doubles mat de taille size1 x size2 par un scalaire double a
	double** matm; // tableau qui contiendra la multiplication des termes de tab par a
	matm = new double*[size1];
    for (int i=0; i<size1; i++){
        matm[i] = new double[size2*sizeof(double)];
    }
	# pragma omp parallel for shared(matm) 
	for(int i=0; i<size1; ++i){
	    for (int j=0; j<size2; ++j){
		    matm[i][j]=mat[i][j]*a;
		}
	}
	return matm;
}

void Testfort(){
	/* Passage à l'échelle forte pour les fonctions Addtab, Summat, Matprod (pour 1, 2, 4 coeurs et 3 tailles de matrices carrées).
		Création de fichiers de sortie contenant les résultats.*/

	// Création des fichiers de sortie 
	ofstream myfile1;
	myfile1.open("fort_addmat.txt");
	ofstream myfile2;
	myfile2.open("fort_summat.txt");
	ofstream myfile3;
	myfile3.open("fort_matprod.txt");

	// Titres des colones
	myfile1 << "nb_coeurs \t tps_execution \t taille_vecteur \t moy" <<"\n";
	myfile2 << "nb_coeurs \t tps_execution \t taille_vecteur \t moy" <<"\n";
	myfile3 << "nb_coeurs \t tps_execution \t taille_vecteur \t moy" <<"\n";

	for(int size1=50; size1<=5000; size1=size1*10){
		cout << "in size" << endl;
		for( int coeur=1; coeur<=4; coeur=coeur*2){
			cout<< "in coeur" << endl;
			// moyennes des temps d'execution pour les trois fonctions
			int timeaddtab=0;
			int timesummat=0;
			int timematprod=0;

			int diff1;
			int diff2;
			int diff3;

			int k=0;
			while(k<4){
				omp_set_num_threads(coeur);

				// creation de la matrice mat1
				double** mat1; 
				mat1 = new double*[size1];
				for (int i=0; i<size1; i++){
    				mat1[i] = new double[size1*sizeof(double)];
				}	
				Randomfill(mat1, size1, size1);
				// creation de la matrice mat2
				double** mat2; 
				mat2 = new double*[size1];
				for (int i=0; i<size1; i++){
    				mat2[i] = new double[size1*sizeof(double)];
				}
				Randomfill(mat2, size1, size1);

				cout<< "finished fill"<<endl;

				int before1=(clock()*1000)/CLOCKS_PER_SEC;
				double** mat3 = Addtab(mat1, size1, size1, mat2, size1, size1); // somme de mat1 et de mat2
				int after1=(clock()*1000)/CLOCKS_PER_SEC;
				int diff1=after1 - before1; // temps d'execution de la somme de deux matrices
				timeaddtab=timeaddtab+diff1; 
				cout<<"timetab"<<timeaddtab<<endl;

				int before2=(clock()*1000)/CLOCKS_PER_SEC;
				double sum1 = Summat(mat1, size1, size1); // somme des éléments de mat1
				int after2=(clock()*1000)/CLOCKS_PER_SEC;
				int diff2=after2 - before2; // temps d'execution de la somme des éléments d'une matrice 
				timesummat=timesummat+diff2;

				int before3=(clock()*1000)/CLOCKS_PER_SEC;
				double** matm1=Matprod(mat1, size1, size1, 2); // multiplication des éléments de mat1 par 2
				int after3=(clock()*1000)/CLOCKS_PER_SEC;
				int diff3=after3 - before3; // temps d'execution de la multiplication des éléments d'une matrice par un scalaire
				timematprod=timematprod+diff3;

				// DELETES
				for (int i=0; i<size1; i++){
					delete[] mat1[i];
				}
				delete[] mat1;
				for (int i=0; i<size1; i++){
					delete[] mat2[i];
				}
				delete[] mat2;
				for (int i=0; i<size1; i++){
					delete[] mat3[i];
				}
				delete[] mat3;
				for (int i=0; i<size1; i++){
					delete[] matm1[i];
				}
				delete[] matm1;

				++k;
			}
		// moyennes des temps d'exécution
		timeaddtab=timeaddtab/4;
		timematprod=timematprod/4;
		timesummat=timesummat/4;

		// remplissage des fichiers
		cout << size1 << endl;
		myfile1 << coeur <<" \t "<< diff1 <<" \t "<< size1 << " \t "  << timeaddtab <<"\n";
		myfile2 << coeur <<" \t "<< diff2 <<" \t "<< size1 << " \t " << timesummat <<"\n";
		myfile3 << coeur <<" \t "<< diff3 <<" \t "<< size1 << " \t " << timematprod <<"\n";
		}
	}

	// fermer les fichiers
	myfile1.close();
	myfile2.close();
	myfile3.close();	
}


void Testfaible(){
	/* Passage à l'échelle faible pour les fonctions Addtab, Summat, Matprod (pour 1, 2, 4 coeurs et 3 tailles de matrices carrées).
		 Création de fichiers de sortie contenant les résultats.*/

	// Création des fichiers de sortie 
	ofstream myfile4;
	myfile4.open("faible_addmat.txt");
	ofstream myfile5;
	myfile5.open("faible_summat.txt");
	ofstream myfile6;
	myfile6.open("faible_matprod.txt");

	// Titres des colones
	myfile4 << "nb_coeurs \t tps_execution \t taille_vecteur \t moy" <<"\n";
	myfile5 << "nb_coeurs \t tps_execution \t taille_vecteur \t moy" <<"\n";
	myfile6 << "nb_coeurs \t tps_execution \t taille_vecteur \t moy" <<"\n";

		int size=1000;
		for( int coeur=1; coeur<=4; coeur=coeur*2){
			cout<< "in coeur" << endl;
			int size1=size*coeur;
			// moyennes des temps d'execution pour les trois fonctions
			int timeaddtab=0;
			int timesummat=0;
			int timematprod=0;

			int diff1;
			int diff2;
			int diff3;

			int k=0;
			while(k<4){
				omp_set_num_threads(coeur);

				// creation de la matrice mat1
				double** mat1; 
				mat1 = new double*[size1];
				for (int i=0; i<size1; i++){
    				mat1[i] = new double[size1*sizeof(double)];
				}	
				Randomfill(mat1, size1, size1);
				// creation de la matrice mat2
				double** mat2; 
				mat2 = new double*[size1];
				for (int i=0; i<size1; i++){
    				mat2[i] = new double[size1*sizeof(double)];
				}
				Randomfill(mat2, size1, size1);

				cout<< "finished fill"<<endl;

				int before1=(clock()*1000)/CLOCKS_PER_SEC;
				double** mat3 = Addtab(mat1, size1, size1, mat2, size1, size1); // somme de mat1 et de mat2
				int after1=(clock()*1000)/CLOCKS_PER_SEC;
				int diff1=after1 - before1; // temps d'execution de la somme de deux matrices
				timeaddtab=timeaddtab+diff1; 
				cout<<"timetab"<<timeaddtab<<endl;

				int before2=(clock()*1000)/CLOCKS_PER_SEC;
				double sum1 = Summat(mat1, size1, size1); // somme des éléments de mat1
				int after2=(clock()*1000)/CLOCKS_PER_SEC;
				int diff2=after2 - before2; // temps d'execution de la somme des éléments d'une matrice 
				timesummat=timesummat+diff2;

				int before3=(clock()*1000)/CLOCKS_PER_SEC;
				double** matm1=Matprod(mat1, size1, size1, 2); // multiplication des éléments de mat1 par 2
				int after3=(clock()*1000)/CLOCKS_PER_SEC;
				int diff3=after3 - before3; // temps d'execution de la multiplication des éléments d'une matrice par un scalaire
				timematprod=timematprod+diff3;

				// DELETES
				for (int i=0; i<size1; i++){
					delete[] mat1[i];
				}
				delete[] mat1;
				for (int i=0; i<size1; i++){
					delete[] mat2[i];
				}
				delete[] mat2;
				for (int i=0; i<size1; i++){
					delete[] mat3[i];
				}
				delete[] mat3;
				for (int i=0; i<size1; i++){
					delete[] matm1[i];
				}
				delete[] matm1;

				++k;
			}
		// moyennes des temps d'exécution
		timeaddtab=timeaddtab/4;
		timematprod=timematprod/4;
		timesummat=timesummat/4;

		// remplissage des fichiers
		cout << size1 << endl;
		myfile4 << coeur <<" \t "<< diff1 <<" \t "<< size1 << " \t "  << timeaddtab <<"\n";
		myfile5 << coeur <<" \t "<< diff2 <<" \t "<< size1 << " \t " << timesummat <<"\n";
		myfile6 << coeur <<" \t "<< diff3 <<" \t "<< size1 << " \t " << timematprod <<"\n";
		
	}

	// fermer les fichiers
	myfile4.close();
	myfile5.close();
	myfile6.close();	
}


int main(int argc, char** argv){

int size1=atoi(argv[1]); // donne le nombre de lignes de la matrice
int size2=atoi(argv[2]); // donne le nombre de colonnes de la matrice
int coeur=atoi(argv[3]); //Q5 : donne le nombre de coeur
omp_set_num_threads(coeur);


// Q1 et Q2
double** mat1; // creation de la matrice mat1
mat1 = new double*[size1];
for (int i=0; i<size1; i++){
    mat1[i] = new double[size2*sizeof(double)];
}
Randomfill(mat1, size1, size2);
//Affichemat(mat1, size1, size2);

//Q3
double** mat2; // creation de la matrice mat2
mat2 = new double*[size1];
for (int i=0; i<size1; i++){
    mat2[i] = new double[size2*sizeof(double)];
}
Randomfill(mat2, size1, size2);
//Affichemat(mat2, size1, size2);


int before1=(clock()*1000)/CLOCKS_PER_SEC;
double** mat3 = Addtab(mat1, size1, size2, mat2, size1, size2); // somme de tab1 et de tab2
int after1=(clock()*1000)/CLOCKS_PER_SEC;
int diff1=after1 - before1;
cout << "temps d'execution de la somme de deux matrices " << diff1 << endl;
// affichage de tab3
//Affichemat(mat3, size1, size2); 

//Q4
int before2=(clock()*1000)/CLOCKS_PER_SEC;
double sum1 = Summat(mat1, size1, size2); // somme des éléments de tab1
int after2=(clock()*1000)/CLOCKS_PER_SEC;
int diff2=after2 - before2;
cout << "temps d'execution de la somme des éléments d'une matrice " << diff2 << endl;
// affichage de sum1
//cout << "mat1 : " << endl;
//Affichemat(mat1, size1, size2);
//cout << "Somme des cases de mat1 = " << sum1 << endl;

//Q8
int before3=(clock()*1000)/CLOCKS_PER_SEC;
double** matm1=Matprod(mat1, size1, size2, 2); // multiplication des éléments de tab1 par 2
int after3=(clock()*1000)/CLOCKS_PER_SEC;
int diff3=after3 - before3;
cout << "temps d'execution de la multiplication des éléments d'une matrice par un scalaire " << diff3 << endl;
// affichage de tabm1
//cout << "mat1 : " << endl;
//Affichemat(mat1, size1, size2);
//cout << "Produit des cases de mat1 avec 2 = " << endl;
//Affichemat(matm1, size1, size2);

// DELETES
for (int i=0; i<size1; i++){
	delete[] mat1[i];
}
delete[] mat1;
for (int i=0; i<size1; i++){
	delete[] mat2[i];
}
delete[] mat2;
for (int i=0; i<size1; i++){
	delete[] mat3[i];
}
delete[] mat3;
for (int i=0; i<size1; i++){
	delete[] matm1[i];
}
delete[] matm1;

// Tests pour différentes conditions (nombre de coeurs et taille des matrices variable)
//Testfort(); // passage à l'échelle forte
//Testfaible(); // passage à l'échelle faible

return 0;
}


