/*Ejercicio 3. Se dispone del archivo binario ventas.dat, ordenado por sucursal, con los siguientes datos por venta:
Sucursal (entero)
Monto (float)
Número de ticket (entero)

Se solicita:
a) Mediante corte de control por sucursal, informar el promedio de monto por sucursal. 
   El cálculo del promedio debe realizarse en otra función.
b) Informar la sucursal con mayor monto de ventas en total (sumando todos los montos de cada sucursal).*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int sucursal;
    float montoTotal;
    int numTicket;
}VENTAS;

void procesarArchivo();
float promedio(float, int);
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarArchivo();

    return 0;
}

void procesarArchivo(){
    FILE *arch=abrirArchivo("ventas.dat", "rb");
    VENTAS datos;
    int sucAnterior, cantVentas, sucursalMayor;
    float promedioxSuc, montoTotxSuc, mayorTotal=-1;

    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {   
        sucAnterior=datos.sucursal;
        promedioxSuc=0;
        montoTotxSuc=0;
        cantVentas=0;
        while (!feof(arch) && sucAnterior==datos.sucursal)
        {
            montoTotxSuc+=datos.montoTotal;
            cantVentas++;
            fread(&datos, sizeof(datos), 1, arch);
        }
        
        promedioxSuc=promedio(montoTotxSuc, cantVentas);
        printf("Sucursal %d - Promedio: %.2f\n", sucAnterior, promedioxSuc);

        if (montoTotxSuc > mayorTotal)
        {
            mayorTotal=montoTotxSuc;
            sucursalMayor=sucAnterior;
        }
    }
    printf("Sucursal %d con mayor monto de ventas con %.2f\n", sucursalMayor, mayorTotal);
    fclose(arch);
}

float promedio(float monto, int cantV){
    float prom;
    prom=monto/cantV;
    return prom;
}

FILE *abrirArchivo(char nombre[], char tipo[]){
    FILE *arch=fopen(nombre, tipo);
    if(arch==NULL){
        printf("Error.");
        getch();
        exit(1);
    }
    return arch;
}