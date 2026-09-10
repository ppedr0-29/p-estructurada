/*3. Un laboratorio dispone de una lista con sus 50 medicamentos. De cada uno conoce:
• Código del medicamento (entero, de 3 cifras).
• Precio (real).
• Stock (entero).
Se solicita:
a. Declarar un tipo de dato que contenga la información del medicamento.
b. Declarar un vector de estructura de tipo de datos creado en a.
c. Cargar en un sector de estructuras, los datos referentes a los medicamentos. Función INGRESO.
d. Consultar el precio según código del medicamento. Función BUSQUEDA_MEDI.
e. Informar los códigos de los medicamentos cuyo stock es inferior a 10 unidades. Función INFORME. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 50

typedef struct
{
    int cod;
    float precio;
    int stock;
}MEDICAMENTOS;

void INGRESO(MEDICAMENTOS info[], int ce);
void INFORME(MEDICAMENTOS info[], int ce);
void BUSQUEDA_MEDI(MEDICAMENTOS info[], int ce);
int busqueda(MEDICAMENTOS info[], int ce, int cod2);
MEDICAMENTOS ingreso();
void leeyvalidaInt(int *dato, int lim);
void leeyvalidaF(float *dato, int lim);
void leeyvalidaIntE2(int *dato, int min, int max);

int main(){
    MEDICAMENTOS info[TAM];
    INGRESO(info, TAM);
    BUSQUEDA_MEDI(info, TAM);
    INFORME(info, TAM);

    return 0;
}

void INGRESO(MEDICAMENTOS info[], int ce){
    for (int i = 0; i < ce; i++)
    {
        info[i]=ingreso();
    }
    
}

void INFORME(MEDICAMENTOS info[], int ce){
    printf("--INFORME--");
    for (int i = 0; i < ce; i++)
    {
        if (info[i].stock<10)
        {
            printf("El medicamento %d tiene stock inferior a 10.\n", info[i].cod);
        }
    }
}

void BUSQUEDA_MEDI(MEDICAMENTOS info[], int ce){
    int pos;
    int cod;
    printf("--CONSULTA DE PRECIOS--\n");
    printf("Ingrese codigo del medicamento a consultar: ");
    leeyvalidaIntE2(&cod, 100, 999);
    pos=busqueda(info, ce, cod);
    while (pos==-1)
    {
        printf("Codigo no encontrado. Reingrese:");
        leeyvalidaIntE2(&cod, 100, 999);
        pos=busqueda(info, ce, cod);
    }
    printf("El precio del medicamento %d es : $%.2f", info[pos].cod, info[pos].precio);
}

int busqueda(MEDICAMENTOS info[], int ce, int cod2){
    int pos=-1, i=0;
    while (pos==-1 && i<ce)
    {
        if (info[i].cod==cod2)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}
MEDICAMENTOS ingreso (){
    MEDICAMENTOS aux;
    printf("Ingrese codigo del medicamento: ");
    leeyvalidaIntE2(&aux.cod, 100, 999);
    printf("Ingrese precio del medicamento: ");
    leeyvalidaF(&aux.precio, 1);
    printf("Ingrese stock del medicamento: ");
    leeyvalidaInt(&aux.stock, 0);

    return aux;
}

void leeyvalidaInt(int *dato, int lim){
    scanf("%d", dato);
    while (*dato<lim)
    {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
}

void leeyvalidaF(float *dato, int lim){
    scanf("%f", dato);
    while (*dato<lim)
    {
        printf("Error. Reingrese: ");
        scanf("%f", dato);
    }
}

void leeyvalidaIntE2(int *dato, int min, int max){
    scanf("%d", dato);
    while (*dato<min || *dato>max)
    {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
}