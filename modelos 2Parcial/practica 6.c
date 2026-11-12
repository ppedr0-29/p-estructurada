/*Ejercicio 1.
Se tiene un archivo binario que registra el estado de diferentes productos en un almacén, con el siguiente diseño de registro:
ID Producto (entero)
Descripción (40 caracteres máximo)
Ubicación (char ’N’: Norte, ‘S’: Sur, ‘E’: Este, ‘O’: Oeste)
Cantidad Disponible (entero)

Se ha detectado que los productos ubicados en la zona ‘O’ (Oeste) del depósito deben ser reabastecidos. 
A estos productos se les debe incrementar la Cantidad Disponible en 100 unidades.
a) Realizar un programa en “C” que permita modificar directamente sobre el archivo las cantidades 
disponibles de los productos de la ubicación.

b) Explicar con sus palabras los pasos necesarios para proceder al borrado físico de los registros, 
ubicados en la zona ‘E’ (Este).*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void procesarArchivo();
FILE *abrirArchivo(char [], char []);

typedef struct
{
    int id;
    char desc[41];
    char ubi;
    int cantD;
}PROD;

int main(){
    procesarArchivo();

    return 0;
}

void procesarArchivo(){
    FILE *arch=abrirArchivo("Almacen.dat", "r+b");
    PROD datos;
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.ubi=='O')
        {
            datos.cantD+=100;
            fseek(arch, -(long)sizeof(datos), SEEK_CUR);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);
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