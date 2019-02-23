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

std::vector<double> resultados; 
std::vector<int> porcen; 
std::atomic<bool> flag_th{true};
std::vector<int> finish;

struct parametros {
		int UT;
		int hilo;
	};

// Funcion que calcula pi con Serie de Taylor

void *calcularPi(void *P){		//UT: Unidad de trabajo
	struct parametros *arg = (struct parametros *) P;
	int count=abs(50*(arg->UT));
	double sum = 0;
	double total;
	int i=0;

	while(finish[arg->hilo]==0){
		// Expresion para el calculo segun serie de Taylor
		if(flag_th){
			if (i & 0x1){	// Evalua  si el numero es impar
				sum += -1.0/(2*i+1);
			}
			else{			// Evalua si el numero es par
				sum += 1.0/(2*i+1);
			}
			total= sum*4;
			i=i+1;
			float itr = (int)i;
			float countd= (int)countd;
			resultados[arg->hilo]=total;
			porcen[arg->hilo]= round(((itr)/count)*100);
			if(i==count) finish[arg->hilo]=1;
		}
	}
	 pthread_exit(NULL);
	}


void *imprimir(void *hil){
	int *hilos= (int *)hil;
	char ch;
	int varmenu=1;
	int varmenu1=1;
	initscr();			//Start curses mode 		
	cbreak();	
	keypad(stdscr, TRUE);
	scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);	
	noecho();
	printw("Press o to pause and option");
	refresh();
	while(varmenu1==1){
		if (getch() =='o'){	
			flag_th=false;

			while(varmenu==1){
					mvprintw(1,0,"Press s to exit or press p to play");
					ch=getch();
					if(ch=='s') {
						varmenu1=0;
						varmenu=0;
						for (int i = 0; i < *hilos; ++i){
							finish[i]=1;
						}
					
					}
					else if(ch=='p'){ 
						varmenu=0;
						flag_th = true;
					}
				}
			}
			varmenu=1;
			mvprintw(1,0,"\n");
			refresh();

		for (int i = 2; i < *hilos+2; ++i)
		{
			mvprintw(i,0,"El valor de PI es:%.*f para el hilo %d estado de tarea:%d%c",resultados[i-2],15,i-1,porcen[i-2],'%');
			refresh();
			//sleep(1);
		}
	}
	endwin();
	

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

	pthread_t threads[hilos];
	pthread_t imp; 	// Vector de las variables tipo thread (Array de hilos)
	int UT[hilos];				// Array de unidades de trabajo por cada hilo.
	struct parametros P[hilos];
	resultados.reserve(hilos);
	porcen.reserve(hilos);
	finish.reserve(hilos);

	// Ciclo que guarda los UT de cada hilo
	for (int i = 0; i < hilos; ++i){

		std:: cout<< "Ingrese la cantidad de unidades de trabajo para el hilo "<<i+1<<":"; //cantidad de unidades de trabajo
		std:: cin >> UT[i];		//se va guardando la UT de cada hilo en el array UT[]
		std:: cout << "\n";
		
	}

	pthread_create(&imp,NULL,imprimir,(void *)&hilos);



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
	pthread_join(imp,NULL);




	return 0;
}