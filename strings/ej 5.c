/*5. Una empresa de alquiler de autos tiene una flota de 30 autos de alta gama, identificados por su número de
patente, cargado en la memoria principal en un vector de 30 posiciones. Al comenzar el procesamiento de
los alquileres, se ingresa la fecha y la cotización del dólar de ese día. A continuación, se ingresan los siguientes
datos correspondiente a cada alquiler realizado en el día:
• Patente del auto (alfanumérico, de 6 caracteres)
• Cantidad de días de alquiler (entero, mayor que 0)
• Precio diario del alquiles en dólares (real, mayor que 0)
Para finalizar la carga del día, se ingresa una patente de auto igual a “FINDIA”
Determinar e informar:
a. El porcentaje de autos alquilados durante el día.
b. Realizar el informe con el formato siguiente: */

#include <stdio.h>
#include <string.h>
#define TAM 30

int main(){
    int dia, mes, anio;
    int dias;
    float precio, dolar;
    int autos[TAM][7];


    return 0;
}

void procesamientoAlquileres(int *dia, int *mes, int *anio, float *dolar){
    printf("--PROCESAMIENTO DE ALQUILERES--\n");
    printf("Ingrese dia(1-31): ");
    leeyvalidaIntE2(&dia,1,31);
    printf("Ingrese mes (1-12): ");
    leeyvalidaIntE2(&mes, 1,12);
    printf("Ingrese año(2000-2026): ");
    leeyvalidaIntE2(&anio, 2000,2026);
    printf("Ingrese cotizacion del dolar: ");
    leeyvalidaFloat(&dolar, 0);
}

int cargaAlquiler(char patente[][7], int *dias, float *precio, int ce){
    int i=0;
    int pos;
    int alquilado[TAM]={0};
    char patenteAux[TAM];
    printf("--ALQUILERES DEL DIA--");
    printf("Ingrese patente del auto: ");
    leeryValidarTexto(patenteAux, 7);
    while (strcmpi(patenteAux, "FINDIA")!=0 && i<ce)
    {   
        pos=busqueda(patente, patenteAux, ce);
        while (pos!=-1 && strcmpi(patenteAux, "FINDIA")!=0)
        {
            alquilado[pos]=1;
            printf("Ingrese cantidad de dias de alquiler: ");
            leeyvalidaInt(&dias, 1);
            printf("Ingrese precio en dolares: ");
            leeyvalidaFloat(&precio, 1);
            i++;
        }
        printf("Patente no encontrada.");
        printf("Ingrese patente del auto: ");
        leeryValidarTexto(patenteAux, 7);
    }
    
    return i;
}

int busqueda(char patente[][7], char patenteaux[], int ce){
    int pos=-1, flag=0, i=0;
    while (flag==0 && i<ce)
    {
        if (strcmpi(patente[i], patenteaux)==0)
        {
            flag=1;
            pos=i;
        }
        i++;
    }
    return pos;
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

void leeryValidarTexto(char texto[], int largo){
    leerTexto(texto, largo);
    while (strlen(texto)!=3)
    {
        printf("El texto ingresado no es correcto. Reingrese: ");
        leerTexto(texto, largo);
    }
    
}

void leeyvalidaIntE2(int *dato, int min, int max){
    scanf("%d", dato);
    while (*dato<min || *dato>max)
    {
        printf("Error. Reingrese:");
        scanf("%d", dato);
    }
}

void leeyvalidaInt(int *dato, int lim){
    scanf("%d", dato);
    while (*dato<lim)
    {
        printf("Error. Reingrese:");
        scanf("%d", dato);
    }
}

void leeyvalidaFloat(float *dato, int lim){
    scanf("%f", dato);
    while (*dato<lim)
    {
        printf("Error. Reingrese:");
        scanf("%f", dato);
    }
}