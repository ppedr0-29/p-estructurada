/*3. Realizar una función que permita ingresar por teclado un valor entero, un flotante y un carácter. La función
no debe retornar ningún valor. Las variables se declaran y se muestran en el programa principal. */

#include <stdio.h>

void ingresoDatos(int *, float *, char *);

int main (){
    int entero;
    float flotante;
    char caractere;
    
    ingresoDatos(&entero, &flotante, &caractere);

    printf("\nEl numero entero ingresado es: %d", entero);
    printf("\nEl numero flotante ingresado es: %f", flotante);
    printf("\nEl caractere ingresado es: %c", caractere);

    return 0;
    
}

void ingresoDatos(int *pe, float *pf, char *pc){

    printf("Ingrese el numero entero:");
    scanf("%d", pe);
    printf("\nIngrese el numero float:");
    scanf("%f", pf);
    fflush(stdin);
    printf("\nIngrese el caracter:");
    scanf("%c", pc);
}
