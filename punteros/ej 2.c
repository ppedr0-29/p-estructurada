/*2. Definir dos números enteros y dos punteros a dichos números. Accediendo mediante los punteros sumar
ambos números y mostrar el resultado por pantalla.*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    
    int entero1=10;
    int entero2=20;
    int *p1=&entero1;
    int *p2=&entero2;
    int resultado;

    resultado= *p1+*p2;

    printf("El resultado es: %d", resultado);
    
    return 0;
}
