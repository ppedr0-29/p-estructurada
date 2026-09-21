/*Ej 3. Cargar un vector de 10 números enteros con valores aleatorios de hasta 3 cifras (números entre 100 y 999).

Se solicita:

Realizar una función llamada buscarPunteroAlMinimo que reciba el vector y su tamaño, y retorne un puntero 
al menor valor encontrado en el vector.
En la función principal (main), mostrar el valor mínimo accediendo exclusivamente a través del puntero devuelto, 
y calcular la posición (índice) en la que se encuentra dentro del vector utilizando aritmética de punteros. El menor es único .*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 10

int *buscarPunteroAlMinimo(int*, int);

int main(){
    int v[TAM];
    int *pv=v;
    int *posmenor;
    srand(time(NULL));
    for (int i = 0; i < TAM; i++)
    {
        *(pv+i)=rand()%900+100;
    }
    
    posmenor=buscarPunteroAlMinimo(pv, TAM);
    printf("El menor valor es %d y se encuentra en la posicion %d", *(posmenor), (posmenor-pv));

    return 0;
}

int *buscarPunteroAlMinimo(int *pv, int ce){
    int min=*pv, *pr=pv;
    for (int i = 0; i < ce; i++)
    {
        if (*(pv+i)<min)
        {
            min=*(pv+i);
            pr=pv+i;
        }
    }
    return pr;
}