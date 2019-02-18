#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>

using namespace std;

int main(){

    srand(time(NULL));

    int posiciones[100];

    string letras [10][10] = {{"AAAA"}, {"CCC"}, {"FFFF"}, {"NNNNN"}};

    random_shuffle(posiciones, posiciones + 100);

    for(int fila = 0; fila < 10; fila++){
        for(int columna = 0; columna < 10; columna++)
            letras [fila][columna] = posiciones[100];

    }

    for(int f = 0; f < 10; f++){
        for(int c = 0; c < 10; c++)
            cout << letras[f][c];

        cout << endl;
    }

    return 0;

}