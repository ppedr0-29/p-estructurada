/*6. Cargar un vector de enteros con números aleatorios de 3 cifras máximo.
Realizar una función que retorne un puntero al mayor valor del vector.
Mostrar el máximo valor mediante el puntero y la posición en la cual se encuentra.*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define TAM 10

void leeyvalidaE2(int *);
int *mayor(int *, int );

int main(){
    int v[TAM];
    int *pv=v;
    srand(time(NULL));
    for (int i = 0; i < TAM; i++)
    {
        *(pv+i)=rand()%900+100;
    }
    
    int *posmax=mayor(pv, TAM);
    printf("El maximo valor es %d y se encuentra en la posicion %d", *(posmax), (posmax-pv));

    return 0;
}

int *mayor(int *pv, int ce){
    int max=*pv, *pr=pv; //apunta a la primera direccion de memoria del vector;
    for (int i = 0; i < ce; i++)
    {
        if (*(pv+i)>max)
        {
            max=*(pv+i);
            pr=pv+i; //puntero que apunta a la direccion de memoria del vector
        }
        
    }
    return pr;
}

void leeyvalidaE2(int *dato){
    scanf("%d", dato);
    while (*dato<100 || *dato>999)
    {
        printf("Error. Reingrese:");
        scanf("%d", dato);
    }
}