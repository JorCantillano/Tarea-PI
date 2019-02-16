#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <pthread.h>


// Funcion que calcula pi con Serie de Taylor

void *calcularPi(void *UT){		//UT: Unidad de trabajo
	int *UTnum = (int *) UT;
	int count=50*(*UTnum);
	double sum = 0;
	double total;

	
	// Expresion para el calculo segun serie de Taylor
	for (int i = 0; i < count; ++i){
		if (i & 0x1)	// Evalua  si el numero es impar
		{
			sum += -1.0/(2*i+1);
		}
		else{			// Evalua si el numero es par
			sum += 1.0/(2*i+1);
		}

	}
	total= sum*4;
	std:: cout<<"El valor de PI es:"<<std::setprecision(15)<<total<<"\n";
}


int main(){

	int hilos; 	// variable que almacena la cantidad de hilos
	int rc;		//
    std:: cout << "\n";
	std:: cout << "\n";
	std:: cout << "Calculo de pi en varios THREADS con diferentes unidades de trabajo";
	std:: cout << "\n";
	std:: cout<< "Ingrese la cantidad de Hilos de trabajo:"; 	// Pedir al usuario la cantidad de hilos
	std:: cin >> hilos;			// Variable donde se guarda el # de hilos
	std:: cout << "\n";

	pthread_t threads[hilos]; 	// Vector de las variables tipo thread (Array de hilos)
	int UT[hilos];				// Array de unidades de trabajo por cada hilo.

	// Ciclo que guarda los UT de cada hilo
	for (int i = 0; i < hilos; ++i){

		std:: cout<< "Ingrese la cantidad de unidades de trabajo:"; //cantidad de unidades de trabajo
		std:: cin >> UT[i];		//se va guardando la UT de cada hilo en el array UT[]
		std:: cout << "\n";
		
	}

	// Ciclo creador de hilos
	for (int i = 0; i < hilos; ++i)
	{
		rc = pthread_create(&threads[i], NULL, calcularPi,(void *)&UT[i]); //pthread argumentos (puntero hilos, Null, funcion, parametros para funcion)
 
      if (rc) {
         std:: cout << "Error:unable to create thread," << rc << "\n";
         exit(-1);
		}
	}

	// Ciclo de inicio de hilos
	for (int i = 0; i < hilos; ++i)
	{
	pthread_join(threads[i],NULL);		//pthread_join Argumentos (hilos, status)
	}


	
	return 0;
}
