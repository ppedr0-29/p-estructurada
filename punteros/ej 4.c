/*4. Hacer un programa que cargue un vector de 10 enteros y lo muestre usando una función para cargar y otra
mostrar sin utilizar subíndices. */

#include <stdio.h>

void cargarVector(int *, int);
void mostrarVector(int *, int);

int main (){
    int v[10];
    int *pv=v;

    cargarVector(pv, 10);
    mostrarVector(pv, 10);

    return 0;
}

void cargarVector(int *pv, int ce){
    for (int i = 0; i < ce; i++)
    {
        printf("Ingrese un numero para la posicion %d: ", i+1);
        scanf("%d", (pv+i));
    }
}

void mostrarVector(int *pv, int ce){
    for (int i = 0; i < ce; i++)
    {
        printf("El valor es %d en la posicion %d\n", *(pv+i), i+1);
    }
    
}