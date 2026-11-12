/*Ejercicio 2. 
Se dispone del archivo binario llamadas.dat, ordenado por cliente, con los siguientes datos por llamada:

Número de cliente (entero)
Duración en minutos (entero)
Tipo (carácter: ‘L’ local, ’N’ nacional, ‘I’ internacional)

El minuto cuesta $2 si es local, $5 si es nacional y $12 si es internacional.

Se solicita:
a) Para cada cliente, informar el total de minutos hablados y el importe a pagar. El importe de cada llamada debe calcularse en otra función.
b) Informar el cliente con el mayor importe.
c) Ingresar por teclado un importe límite e informar cuántos clientes lo superaron.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int num;
    int duracion;
    char tipo;
}LLAMADA;

void procesarCdC();
float calcularImporte(char, int);
void leeyvalidaFloat(float *, int);
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarCdC();
    return 0;
}

void procesarCdC(){
    FILE *arch=abrirArchivo("llamadas.dat", "rb");
    LLAMADA datos;
    int minutosTotales, primero=1, clienteMayorImp, clienteAnterior, cantClientes=0;
    float importe, importeTotal, importeLimite, mayorImporte;
    printf("Ingrese limite de importe: ");
    leeyvalidaFloat(&importeLimite, 0);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {   
        importeTotal=0;
        clienteAnterior=datos.num;
        minutosTotales=0;
        while (!feof(arch) && clienteAnterior==datos.num)
        {
            minutosTotales+=datos.duracion;
            importe=calcularImporte(datos.tipo, datos.duracion);
            importeTotal+=importe;
            fread(&datos, sizeof(datos), 1, arch);
        }
        printf("Cliente %d: Minutos totales %d y importe total %.2f\n", clienteAnterior, minutosTotales, importeTotal);

        if (primero==1 || importeTotal>mayorImporte)
        {
            mayorImporte=importeTotal;
            primero=0;
            clienteMayorImp=clienteAnterior;
        }
        
        if (importeTotal>importeLimite)
        {
            cantClientes++;
        }
        
    }
    printf("Cliente %d con mayor importe de %.2f\n", clienteMayorImp, mayorImporte);
    printf("Cantidad de clientes que superaron el importe limite %d", cantClientes);
    fclose(arch);
}

float calcularImporte(char tipo,int minTot){
    float importe;
    switch (tipo)
    {
    case 'L':
        importe= (float)minTot*2.0;
        break;
    case 'N':
        importe= (float)minTot*5.0;
        break;
    case 'I':
        importe= (float)minTot*12.0;
        break;
    }
    return importe;
}

void leeyvalidaFloat(float *dato, int lim){
    scanf("%f", dato);
    while (*dato<=lim)
    {
        printf("Error. Reingrese:");
        scanf("%f", dato);
    }
}

FILE *abrirArchivo(char nombre[], char tipo[]){
    FILE *arch=fopen(nombre, tipo);
    if (arch==NULL)
    {
        printf("Error.");
        getch();
        exit(1);
    }
    return arch;
}
