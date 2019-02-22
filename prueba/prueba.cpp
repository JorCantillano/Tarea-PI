#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <math.h>
#include <iomanip>
#include <string.h>
#include <pthread.h>
#include <ncurses.h>
#include <vector>

std::vector<double> resultados; 

struct parametros {
		int UT;
		int hilo;
	};

// Funcion que calcula pi con Serie de Taylor
int calcularPi2 (void )

void *calcularPi(void *P){		//UT: Unidad de trabajo
	struct parametros *arg = (struct parametros *) P;
	int count=50*(arg->UT);
	double sum = 0;
	double total;


	double PI= calcularPi2(UT)
	// Expresion para el calculo segun serie de Taylor
	for (int i = 0; i < count; ++i){
		if (i & 0x1)	// Evalua  si el numero es impar
		{
			sum += -1.0/(2*i+1);
		}
		else{			// Evalua si el numero es par
			sum += 1.0/(2*i+1);
		}
	total= sum*4;
	resultados[arg->hilo]=total;
	mvprintw(arg->hilo,0,"El valor de PI es:%f para el hilo %d",total,arg->hilo);
	refresh();
	}
	//std:: cout<<"El valor de PI es:"<<std::setprecision(15)<<total<<" del hilo:"<<arg->hilo<<"\n";
	}


int main(){

	int hilos; 	// variable que almacena la cantidad de hilos
	int rc;		//
	int ch;
    std:: cout << "\n";
	std:: cout << "\n";
	std:: cout << "Calculo de pi en varios THREADS con diferentes unidades de trabajo";
	std:: cout << "\n";
	std:: cout<< "Ingrese la cantidad de Hilos de trabajo:"; 	// Pedir al usuario la cantidad de hilos
	std:: cin >> hilos;			// Variable donde se guarda el # de hilos
	std:: cout << "\n";

	pthread_t threads[hilos]; 	// Vector de las variables tipo thread (Array de hilos)
	int UT[hilos];				// Array de unidades de trabajo por cada hilo.
	struct parametros P[hilos];
	resultados.reserve(hilos);

	// Ciclo que guarda los UT de cada hilo
	for (int i = 0; i < hilos; ++i){

		std:: cout<< "Ingrese la cantidad de unidades de trabajo para el hilo "<<i<<":"; //cantidad de unidades de trabajo
		std:: cin >> UT[i];		//se va guardando la UT de cada hilo en el array UT[]
		std:: cout << "\n";
		
	}
	for (int i = 0; i < hilos; ++i) //Ciclo Asignador de parametros
	{
		P[i].UT= UT[i];
		P[i].hilo= i;
	}
	// Ciclo creador de hilos
	for (int i = 0; i < hilos; ++i)
	{
		rc = pthread_create(&threads[i], NULL, calcularPi,(void *)&P[i]); //pthread argumentos (puntero hilos, Null, funcion, parametros para funcion)
 
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

	initscr();			//Start curses mode 		
	cbreak();	
	keypad(stdscr, TRUE);	
	noecho();
	printw("Press F6 to exit");
	refresh();
	while(true){

		/*for (int i = 0; i < hilos; ++i)
		{
			mvprintw(i,0,"El valor de PI es:%f para el hilo %d",resultados[i],i);
		}*/
		if ((ch = getch()) == KEY_F(6))
			{	
				endwin();
				break;
			}
		refresh();
	}


	/*for (int i = 0; i < hilos; ++i)
	{
	std:: cout<<"El valor de PI es:"<<std::setprecision(15)<<resultados[i]<<" del hilo:"<<i<<"\n";
	}
	std::cin>>ch;*/




	return 0;
}
