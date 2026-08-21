/*1. Crear una variable entera y un puntero a dicha variable
Asignar el valor 10 a la variable mediante el puntero
Mostrar:
a) la dirección de la variable
b) la dirección del puntero
c) el contenido de la variable
d) el contenido de la variable accediendo mediante el puntero
e) el contenido del puntero */

#include <stdio.h>
#include <stdlib.h>

int main (){

    int entero;
    int *pentero=&entero;
    *pentero=10;
    
    printf("La direccion de la variable es: %p\n", &entero);
    printf("La direccion del puntero es : %p\n", &pentero);
    printf("El contenido de la variable es : %d\n", entero);
    printf("El contenido de la variable mediante el puntero es: %d\n", *pentero);
    printf("El contenido del puntero es : %p\n", pentero);

    return 0;
}