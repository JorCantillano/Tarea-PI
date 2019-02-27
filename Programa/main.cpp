/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Tecnologico de Costa Rica
Taller de Sistemas Embebidos
Tarea 1

Integrantes:

Jordan Cantillano 
Leonardo Castro Vindas
Steven Jimenez

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <atomic>
#include <iomanip>
#include <string.h>
#include <pthread.h>
#include <ncurses.h>
#include <vector>
#include <math.h>

// Declaracion de variables globales

std::vector<double> resultados; 							// vector global donde se guardan los valores de pi.
std::vector<int> porcen; 									// vector global donde se guardan los porcentajes de cada hilo.
std::atomic<bool> flag_th{true};
std::vector<int> finish;


// Struct donde se guardan los parametros UT e hilo para poder ser utilizados por Calcular PI.
struct parametros {		
		int UT;
		int hilo;
	};

//--------------------------------------------------------------------------

// Funcion que calcula pi con Serie de Taylor
void *calcularPi(void *P){		
	struct parametros *arg = (struct parametros *) P;		// arg es un puntero del struct parametros.
	int count=abs(50*(arg->UT));							// Conversion de void a int.
	double sum = 0;
	double total;
	int i=0;

	// Expresion para el calculo segun serie de Taylor
	while(finish[arg->hilo]==0){
		if(flag_th){
			if (i & 0x1){									// Evalua si el numero es impar
				sum += -1.0/(2*i+1);
			}
			else{											// Evalua si el numero es par
				sum += 1.0/(2*i+1);
			}
			total= sum*4;									//Funcion calcula pi/4 por eso se multiplica por 4.
			i=i+1;
			float itr = (int)i;
			float countd= (int)countd;
			resultados[arg->hilo]=total;					// Se guarda el termino calculado en el vector global.
			porcen[arg->hilo]= round(((itr)/count)*100); 	// Se guarda el porcentaje calculado en el vector global.		
			if(i==count) finish[arg->hilo]=1;
		}
	}
	 pthread_exit(NULL);
	}

// --------------------------------------------------------------------------

//Funcion que imprime los resultados utilizando la libreria ncurses.
void *imprimir(void *hil){
	int *hilos= (int *)hil;
	char ch;
	int varmenu=1;
	int varmenu1=1;
	initscr();												// Inicio de Ncurses		
	cbreak();	
	keypad(stdscr, TRUE);									// 
	scrollok(stdscr, TRUE);									//
    nodelay(stdscr, TRUE);									//
	noecho();
	printw("Presione o para detener y elegir una opcion");
	refresh();
	while(varmenu1==1){										
		if (getch() =='o'){									// Si se presiona "o" se detiene el programa.
			flag_th=false;

			while(varmenu==1){
					mvprintw(1,0,"Presione s para salir o p para continuar");
					ch=getch();
					if(ch=='s') {							// Si se presiona "s" es sistema termina
						varmenu1=0;
						varmenu=0;
						for (int i = 0; i < *hilos; ++i){
							finish[i]=1;
						}
					
					}
					else if(ch=='p'){ 						// Si se presiona p el sistema vuelve a ejecutar desde donde se pausó.
						varmenu=0;
						flag_th = true;
					}
				}
			}
			varmenu=1;
			mvprintw(1,0,"\n");
			refresh();

		for (int i = 2; i < *hilos+2; ++i)					// Impresion de los resultados 
		{
			mvprintw(i,0,"El valor de PI es:%.*f para el hilo %d Estado de tarea:%d%c" ,resultados[i-2],15,i-1,porcen[i-2],'%');
			refresh();
			//sleep(1);
		}
	}
	endwin();
	
}

//--------------------------------------------------------------------


// %%%%%%%%%%%%%%%%%%%%%%___Main___%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

int main(){

	int hilos; 												// variable que almacena la cantidad de hilos
	int rc;		
    std:: cout << "\n";
	std:: cout << "\n";
	std:: cout << "******************************************************************";
	std:: cout << "\n";
	std:: cout << "Calculo de pi en varios THREADS con diferentes unidades de trabajo";
	std:: cout << "\n";
	std:: cout << "\n";
	std:: cout<< "Ingrese la cantidad de Hilos de trabajo: "; 	
	std:: cin >> hilos;										// variable donde se guarda el # de hilos
	std:: cout << "\n";
	std:: cout << "----------------------Unidades de Trabajo--------------------------";
	std:: cout << "\n";
	std:: cout << "\n";

	pthread_t threads[hilos];								// vector de las variables tipo thread (Array de hilos)
	pthread_t imp; 											
	int UT[hilos];											// array de unidades de trabajo por cada hilo.
	struct parametros P[hilos];								// creacion del struct P.
	resultados.reserve(hilos);
	porcen.reserve(hilos);
	finish.reserve(hilos);

	// Ciclo que guarda los UT de cada hilo
	for (int i = 0; i < hilos; ++i){

		std:: cout<< "Ingrese la cantidad de unidades de trabajo para el hilo "<<i+1<<":"; //cantidad de unidades de trabajo
		std:: cin >> UT[i];									// Se va guardando la UT de cada hilo en el array UT[]
		std:: cout << "\n";
		
	}

	//Creacion del hilo que se encarga de imprimir los resultados.
	pthread_create(&imp,NULL,imprimir,(void *)&hilos);


	//Ciclo Asignador de parametros
	for (int i = 0; i < hilos; ++i) 
	{
		P[i].UT= UT[i];										// Unidad de Trabajo.
		P[i].hilo= i;									  	// Identificador de hilo.
	}

	// Ciclo creador de hilos
	for (int i = 0; i < hilos; ++i)
	{
		rc = pthread_create(&threads[i], NULL, calcularPi,(void *)&P[i]); 
 
      if (rc) {
         std:: cout << "Error:unable to create thread," << rc << "\n";
         exit(-1);
		}
	}


	// Ciclo de inicio de hilos
	for (int i = 0; i < hilos; ++i)
	{
	pthread_join(threads[i],NULL);					// Acciona los hilos de calculos.
	}
	pthread_join(imp,NULL);							// Acciona el hilo de imprimir.



	return 0;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%____END____%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%