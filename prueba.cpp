#include <iostream>
#include <stdlib.h>
#define COLUMNAS 4
#define FILAS 5
#define INF 999999

using namespace std;
int* vigilanciaBasica(int* solucion, int filaActual);
bool vigilanciaAvanzada(int* camaraEnColumna, int fila);
bool valido(int* solucion, int filaActual);
void mostrarSolucion(int* sol);

int main()
{
    int* solucion = (int*)malloc(FILAS*sizeof(int));
    int* mejorsolucion = (int*)malloc(FILAS*sizeof(int));
    for(int i=0;i<FILAS;i++)
        solucion[i]=0;

    //vigilanciaBasica(solucion,0);
    cout << "(COLUMNA,FILA) MAX("<<COLUMNAS-1<<","<<FILAS-1<<")"<<endl;
    vigilanciaAvanzada(solucion,0);
//    for(int z=0;z<FILAS; z++){
//            if(solucion[z]>-1)
//                cout << "  ("<< z <<","<<solucion[z]<<")";
//    }
    cout<<endl<<" DONE"<<endl;

    return 0;
}

int* vigilanciaBasica(int* solucion, int filaActual)
{
    //El valor filaActual representa las columnas
    //Ya se han llenado las columnas y no se puede seguir
    if (filaActual > FILAS){
        return 0;
    }

    bool resuelto = false;
    solucion[filaActual] = -1;

    while(!resuelto)
    {
        //filaActual -> fila
        //solucion[filaActual] -> columna
        solucion[filaActual]++;

        if (valido(solucion,solucion[filaActual])){
            if (filaActual < FILAS){
                if(solucion[filaActual]>=COLUMNAS) solucion[filaActual]=-1;
                //cout<<" SOLUCION "<<filaActual<<": "<<solucion[filaActual]<<endl;
                resuelto = vigilanciaBasica(solucion, filaActual+1);
            }
            else{
//                for(int z=0;z<COLUMNAS; z++){
//                    cout << "  ("<< z <<","<<solucion[z]<<")";
//                }
                resuelto = true;
                return solucion;
            }
        }
    }
}

bool vigilanciaAvanzada(int* camaraEnColumna, int fila)
{
    /* base case: If all queens are placed
    then return true */
    if (fila == FILAS) {
        mostrarSolucion(camaraEnColumna);
        return true;
    }
 
    /* comprobar en la fila actual cada columna */
    bool res = false;
    for (int col = 0; col <= COLUMNAS; col++) {
        /*si es una posición valida, se guarda en el array solución y llama a la función recursiva*/
        camaraEnColumna[fila]=col;
        if (valido(camaraEnColumna,fila)&&col<COLUMNAS) {
 
            // Si se puede colocar una camara res = true
            res = vigilanciaAvanzada(camaraEnColumna, fila + 1);
 
            camaraEnColumna[fila] = 0; //BACKTRACK
        }else //En caso de comprobar todas las columnas y que ninguna sea valida, no llamaría a la función recursiva
              // y terminaría sin llegar a la solución, para evitar esto esta el siguiente if
        if(col == COLUMNAS){//TO DO Al hacer backtacking, si no se encuentra una coluna válida se elimina la que ya había, eso MAL
            //Se marca con -1 para indicar que en esta fila no hay sitio y se llama a la función para la siguiente
            camaraEnColumna[fila]=-1;
            res = vigilanciaAvanzada(camaraEnColumna, fila + 1);
            camaraEnColumna[fila] = 0; //BACKTRACK
        }
    }
 
    /* If queen can not be place in any row in
        this column col then return false */
    return res;
}



bool valido(int* solucion, int filaActual){
    bool valido = true;
    int i;

    //recorrer filas asignadas hasta ahora
    //comparar la columnas asignadas solucion[i], con la última solucion[filaActual]
    for(i=0;i<filaActual;i++){
        //misma columna no es valida
        if(solucion[i]==solucion[filaActual])
        {
            valido = false;
        }
        //misma diagonal no es valida
        if (abs(solucion[i]-solucion[filaActual])==abs(i-filaActual))
        {
            valido = false;
        }    
    }
    return valido;
}

void mostrarSolucion(int* sol){
        for(int z=0;z<FILAS; z++){
            if (sol[z]>-1) cout << "  ("<< sol[z] <<","<<z<<")";
        }cout<<endl;
}
