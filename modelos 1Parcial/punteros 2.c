/*Ej 2. Un taller mecánico necesita un programa para ordenar y mostrar la lista de sus 3 reparaciones del día de menor a mayor costo.

Se solicita en el programa principal (main) Declarar el arreglo, cargar las 3 reparaciones (Código, Descripción y Costo), 
llamar a la función de ordenamiento y mostrar el listado final ordenado.
Escribir una función de tipo void llamada intercambiar que reciba los punteros a dos estructuras de tipo Reparacion 
e intercambie sus valores utilizando una variable auxiliar.
Implementar una función que reciba el arreglo de reparaciones y ordene los elementos en forma ascendente según el costo,
haciendo uso obligatorio de la función intercambiar. -*/

#include <stdio.h>
#include <string.h>
#define TAM 3

typedef struct
{
    int cod;
    char desc[31];
    float costo;
}REPARACIONES;

void burbujeo(REPARACIONES[], int);
void intercambiar(REPARACIONES*, REPARACIONES*);
void leeyValidaFloat(float*, int);
void leerTexto(char[], int);
void leeyValidarTexto(char[], int);

int main(){
    REPARACIONES datos[TAM];
    for (int i = 0; i < TAM; i++)
    {
        printf("Reparacion %d\n", i+1);
        printf("Ingrese codigo: ");
        scanf("%d", &datos[i].cod);
        printf("Ingrese descripcion: ");
        leeyValidarTexto(datos[i].desc, 31);
        printf("Ingrese costo: ");
        leeyValidaFloat(&datos[i].costo, 0);
    }
    
    burbujeo(datos, TAM);
}

void burbujeo(REPARACIONES datos[], int ce){
    int j, cota=ce-1;
    int desordenado=1;
    while (desordenado)
    {
        desordenado=0;
        for (int j = 0; j < cota; j++)
        {
            if (datos[j].costo > datos[j+1].costo)
            {
                intercambiar(&datos[j], &datos[j+1]);
                desordenado=j;
            }
            
        }
        cota=desordenado;
    }
    
}

void intercambiar(REPARACIONES *a, REPARACIONES *b){
    REPARACIONES aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

void leeyValidaFloat(float *dato, int min)
{
    scanf("%f", dato);

    while(*dato<min)
    {
        printf("\n Error, reingrese: ");
        scanf("%f", dato);   
    }
}

void leerTexto(char texto[], int largo){
    int i=0;
    fflush(stdin);
    fgets(texto, largo, stdin);
    while (texto[i]!='\0')
    {
        if (texto[i]=='\n')
        {
            texto[i]='\0';
        }
        i++;
    }
}

void leeyValidarTexto(char texto[], int largo)
{
    leerTexto(texto, largo);
    while(strlen(texto)==0)
    {
        printf("\n Error, reingrese: ");
        leerTexto(texto, largo);
    }
}
