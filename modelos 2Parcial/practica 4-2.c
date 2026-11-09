/*Ejercicio 2. 
Realizar una función que reciba la base y la altura de un rectángulo y, mediante punteros, devuelva su área y su diagonal. 
La función no debe utilizar return para devolver los resultados. 
Mostrar los resultados en el programa principal.*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void leeyvalidaFloat(float *, int);
void calculo(float, float, float *, float *);

int main(){
    float base, altura, area, diagonal;
    printf("Ingrese base del rectangulo:");
    leeyvalidaFloat(&base, 0);
    printf("Ingrese altura del rectangulo:");
    leeyvalidaFloat(&altura, 0);
    calculo(base, altura, &area, &diagonal);
    printf("Area: %.2f\n", area);
    printf("Diagonal: %.2f\n", diagonal);

    return 0;
}

void leeyvalidaFloat(float *dato, int min){
    scanf("%f", dato);
    while (*dato<=min)
    {
        printf("Error. Reingrese: ");
        scanf("%f", dato);
    }
}

void calculo(float base, float altura, float *area, float *diagonal){
    *area=base*altura;
    *diagonal=sqrt(base*base + altura*altura);
}