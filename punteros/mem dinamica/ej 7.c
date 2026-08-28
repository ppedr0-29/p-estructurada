/*7. Desarrolle un programa que solicite el ingreso de un numero entero, que indica a su vez cuantos números
enteros ingresara el usuario. Crear en memoria dinámica el vector para almacenar el tamaño exacto de los
datos y leer los enteros que serán guardados en el vector “dinámico”. Informar el promedio de los datos
ingresados. */

#include <stdio.h>
#include <stdlib.h>

int main(){

    int *v, cant;
    int acum =0; 
    
    printf("Ingrese numero entero para el tamanio del vector: ");
    scanf("%d", &cant);
    
    v=(int*)malloc(cant*sizeof(int));

    if(v==NULL){
        printf("\n ERROR, programa finalizado.");
        exit(1);
    }

    for (int i = 0; i < cant; i++)
    {
        printf("Ingrese valor en la posicion %d:", i+1);
        scanf("%d", v+i);
        acum+=*(v+i);
    }
    
    float promedio = (float) acum/cant;
    
    printf("El promedio es %.2f", promedio);

    free(v);
    return 0;
}