/*9. Crear una función que defina en memoria dinámica un vector de 10 elementos cargados de forma aleatoria
con números de 2 cifras, la función debe mostrar los datos generados en forma ordenada de mayor a menor.
Desde el main invocar la función 5 veces para visualizar 5 vectores distintos.*/

#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
#define TAM 10

void mostrarV(int *, int );
void burbujeoMam (int *v, int);
void cargarVec(int );

int main(){

    srand(time(NULL));
    
    for (int i = 0; i < 5; i++)
    {   
        printf("\n--- Vector %d ---\n", i+1);
        cargarVec(TAM);
    }
    return 0;
}


void cargarVec(int tam){
    
    int *v;

    v=(int*)malloc(tam*sizeof(int));

    if(v==NULL){
        printf("\n ERROR, programa finalizado.");
        exit(1);
    }
    for (int i = 0; i < tam; i++)
    {
        *(v+i)=rand()%90+10;
    }
    burbujeoMam(v, tam);
    mostrarV(v, tam);

    free(v);
}

void mostrarV(int *v, int tam){
    for (int i = 0; i < tam; i++)
    {
        printf("%d\t", *(v+i));
    }
    
}

void burbujeoMam (int *v, int ce)
{
    int AUX, j, cota = ce - 1;
    int desordenado = 1;

    while (desordenado)
    {
        desordenado = 0;
        for (j = 0; j < cota; j++)
        {
            if (*(v+j) < *(v+(j+1)))
            {
                AUX = *(v+j);
                *(v+j) = *(v+(j+1));
                *(v+(j+1)) = AUX;
                desordenado = j;
            }
        }
        cota = desordenado;
    }
}