#include <iostream>
#include <stdlib.h>
#define COLUMNAS 4
#define FILAS 5
#define INF 999999

using namespace std;
int* vigilanciaBasica(int* solucion, int filaActual);
void vigilanciaAvanzada(int* camaraEnColumna, int fila);
bool valido(int* solucion, int filaActual);
void mostrarSolucion(int* sol);

int main()
{
    int* solucion = (int*)malloc(FILAS*sizeof(int));
    int* mejorsolucion = (int*)malloc(FILAS*sizeof(int));
    for(int i=0;i<FILAS;i++)
        solucion[i]=0;

    //vigilanciaBasica(solucion,0);
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

void vigilanciaAvanzada(int* camaraEnColumna, int fila)
{
    int columna=0;

    if(fila==FILAS){
        mostrarSolucion(camaraEnColumna);
        return;
    }

    //repetir mientras la columna no sea válida y el número de columnas no se haya superado
    while (!valido(camaraEnColumna,fila))
    {
        cout<<" ESTO "<<camaraEnColumna[fila]<<endl;
        camaraEnColumna[fila]++;
    }
    if(camaraEnColumna[fila]>=COLUMNAS) camaraEnColumna[fila]=-1;//Si se pasa de columnas no se puede colocar en esta fila una camara
    vigilanciaAvanzada(camaraEnColumna,fila+1);

    //backtrack
    camaraEnColumna[fila]=0;
    
    /* OPCIÓN FOR
    for (int col = 0; col < COLUMNAS; col++)
    {
        camaraEnColumna[fila]=col;
        //Termina la recursividad cuando no debería porque comprueba todas las columnas, ninguna es valida y entonces no llama más a la función
        //Necesito que siga hacindo llamada aunque pase por todas las columnas sin éxito
        if(valido(camaraEnColumna,fila)){
            vigilanciaAvanzada(camaraEnColumna,fila+1);
        }else
        {
            camaraEnColumna[fila]=-1;
        }
    } 
    */

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
            cout << "  ("<< sol[z] <<","<<z<<")";
        }cout<<endl;
}
