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
    int dia, mes, anio, cantAlq;
    int dias [TAM];
    float precio [TAM], dolar, porcentaje;
    char autos[TAM][7] = {
    "AA111A","AA222B","AA333C","AA444D","AA555E",
    "AA666F","AA777G","AA888H","AA999I","AB111J",
    "AB222K","AB333L","AB444M","AB555N","AB666O",
    "AB777P","AB888Q","AB999R","AC111S","AC222T",
    "AC333U","AC444V","AC555W","AC666X","AC777Y",
    "AC888Z","AC999A","AD111B","AD222C","AD333D"
    };
    cantAlq=cargaAlquiler(autos, dias, precio, TAM);
    porcentaje= (float)(cantAlq/TAM)*100;
    printf("El porcentaje de autos alquilados es %.2f%", porcentaje);



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
    printf("--ALQUILERES DEL DIA--\n");
    printf("Ingrese patente del auto: ");
    leeryValidarTexto(patenteAux, 7);
    while (strcmpi(patenteAux, "FINDIA")!=0 && i<ce){   
        pos=busqueda(patente, patenteAux, ce);
        if(pos!=-1)
        {
            alquilado[pos]=1;
            printf("Ingrese cantidad de dias de alquiler: ");
            leeyvalidaInt(&dias[pos], 1);
            printf("Ingrese precio en dolares: ");
            leeyvalidaFloat(&precio[pos], 1);
            i++;
            printf("Ingrese patente del auto: ");
        }else{
            printf("Patente no encontrada. Reingrese: ");
        }
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