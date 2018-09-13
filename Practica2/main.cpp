#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void Binario();
void toBinary(int numero);
void Gray();
void NumerosReales();
void NumerosEnteros();

int main(int argc, char** argv) {
	int val,ban=0;
	char res;
	cout << "Elige una de las siguientes opciones" << endl;
	
	while(true){
		cout << "1.- Poblacion binaria" << endl <<"2.- Gray" << endl << "3.- Numeros Reales" << endl << "4.- Numeros Enteros" << endl;
		cin >> val;
		if(val == 1){
			Binario();
		}else if(val == 2){
			Gray();
		}else if(val == 3){
			NumerosReales();
		}else if(val == 4){
			NumerosEnteros();
		}else{
			cout << "Por favor elige una opcion correctar" << endl;
		}
		cout << "Quieres hacer otra opcion? s/n" << endl;
		cin >> res;
		if(res=='n'){
			break;
		}
	}
	
	
	
	return 0;
}

void Binario(){
	srand(time(NULL));
	int lelo ;
	int popu[10];
	cout << "Poblacion binaria" << endl;
	cout << "||";
	for(int i=0;i<10;i++){
		lelo = rand() % 2 ;
		popu[i] = lelo;
		cout << popu[i] << "||";
	}
	 cout << endl;
	
}

void toBinary(int numero){
	int dividendo, resto, divisor = 2,cont = 1,j=9;
	int binario[10];
	for(int i=0;i<10;i++){
		binario[i] = 0;
	}
	dividendo = numero;
	while(dividendo >= divisor){
	resto = dividendo % 2;
	if(resto == 1)
		binario[j] = 1; 
	else
	   binario[j] = 0; 
	   dividendo = dividendo/divisor; 
	   cont++;
	   j--;
	}
	if(dividendo == 1)
	   binario[j] = 1; 
	else
	   binario[j] = 0;
	for(int i=0;i<10;i++){
		cout << binario[i] << "||";
	}
	cout << endl;
}
void Gray(){
	srand(time(NULL));
	int lelo ;
	int grey ;
    lelo = rand() % 1024 + 1 ;
	grey = lelo ^ (lelo >> 1);
	cout << "Numero antes de grey: " << lelo << endl;
	toBinary(lelo);
	cout << "Numero despues de grey: " << grey << endl;
	toBinary(grey);
}

void NumerosReales(){
	srand(time(NULL));
	float lelo ;
	float popu[10];
	for(int i=0;i<10;i++){
		popu[i] = 0.0;
	}
	cout << "Poblacion numeros reales" << endl;
	cout << "||";
	for(int i=0;i<10;i++){
		lelo = ((rand() % 5000 + 1)/(float)100);
		popu[i] = lelo;
		cout << popu[i] << "||";
	}
	 cout << endl;
}

void NumerosEnteros(){
	srand(time(NULL));
	float lelo ;
	float popu[10];
	for(int i=0;i<10;i++){
		popu[i] = 0.0;
	}
	cout << "Poblacion numeros reales" << endl;
	cout << "||";
	for(int i=0;i<10;i++){
		lelo = (rand() % 500 + 1);
		popu[i] = lelo;
		cout << popu[i] << "||";
	}
	 cout << endl;
}
