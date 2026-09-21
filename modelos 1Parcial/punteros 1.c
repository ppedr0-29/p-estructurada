/*Ej 1. Realizar un programa en “C” que contenga una función llamada registrarMedicion que permita cargar por teclado los datos 
de un reporte meteorológico:
Número de estación meteorológica (entero).
Temperatura registrada en °C (flotante).
Categoría del clima: 'S' para soleado, 'N' para nublado, 'L' para lluvioso (carácter).
La función no debe retornar ningún valor. Las tres variables deben estar declaradas en el main, 
ser modificadas dentro de la función y ser mostradas en la pantalla únicamente desde el main.*/

#include <stdio.h>

void registrarMedicion(int *, float *, char *);

int main(){
    int num;
    float temp;
    char cat;
    registrarMedicion(&num, &temp, &cat);
    printf("El numero de estacion es %d\n", num);
    printf("La temperatura es %.2f°C\n", temp);
    printf("La categoria es %c\n", cat);

    return 0;
}

void registrarMedicion(int *num, float *temp, char *cat){

    printf("Ingrese numero de estacion meteorologica: ");
    scanf("%d", num);
    printf("Ingrese temperatura registrada en °C: ");
    scanf("%f", temp);
    printf("Ingrese categoria del clima (S-N-L): ");
    scanf(" %c", cat);
}