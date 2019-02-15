#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <pthread.h>

void *calcularPi(void *UT){
	//UT: Unidad de trabajo
	int *UTnum = (int *) UT;
	int count=50*(*UTnum);
	double sum = 0;
	double total;

	for (int i = 0; i < count; ++i){
		if (i & 0x1)  // Evalua  si el nummero es impar
		{
			sum += -1.0/(2*i+1);
		}
		else{          // Evalua si el numero es par
			sum += 1.0/(2*i+1);
		}

	}
	total= sum*4;
	std:: cout<<"El valor de PI es:"<<std::setprecision(15)<<total<<"\n";
}

int main(){

	int hilos; //cantidad de hilos a asignar
	int rc;

	std:: cout<< "Ingrese la cantidad de Hilos de trabajo:"; //Pedir al usuario la camtidad
	std:: cin >> hilos;
	std:: cout << "\n";

	pthread_t threads[hilos]; // Vector de las variables tipo thread
	int UT[hilos];

	for (int i = 0; i < hilos; ++i){

		std:: cout<< "Ingrese la cantidad de unidades de trabajo:"; //cantidad de unidadades de trabajo al usuario
		std:: cin >> UT[i];
		std:: cout << "\n";
		
	}

	for (int i = 0; i < hilos; ++i)
	{
		rc = pthread_create(&threads[i], NULL, calcularPi,(void *)&UT[i]);
 
      if (rc) {
         std:: cout << "Error:unable to create thread," << rc << "\n";
         exit(-1);
		}
	}

	for (int i = 0; i < hilos; ++i)
	{
	pthread_join(threads[i],NULL);
	}


	
	return 0;
}
