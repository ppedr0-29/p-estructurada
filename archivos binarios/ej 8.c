/*8. Se dispone de un archivo que contiene información de los vuelos realizados por las distintas aerolíneas a
lo largo del mes. El archivo se denomina Vuelos.dat y guarda los registros con la siguiente estructura:
• Código Aerolínea (alfanumérico de 10 caracteres máximo)
• Día (entero)
• Número de Vuelo (entero)
• Costo del pasaje (real)
• Pasajeros (inicialmente en el archivo viene en 0)
Luego se dispone de un segundo archivo llamado Pasajeros.dat que incluye la información de los viajeros
del mes para la aerolínea con código “Aero1”, el archivo contiene los siguientes campos:
• DNI (entero)
• Número de Vuelo (entero)
Se desea realizar un programa que actualice la cantidad de pasajeros de la aerolínea con código “Aero1”
con la información de los pasajeros que realizaron los viajes. Tenga en cuenta que los números de vuelo se
repiten entre las distintas aerolíneas. */

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char cod[11];
    int dia;
    int numVuelo;
    float costo;
    int pasajeros;
}VUELOS;

typedef struct
{
    int dni;
    int numVuelo;
}PASAJEROS;

void procesarArchivo();
long busqueda(FILE *, int, VUELOS *);
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarArchivo();

    return 0;
}

void procesarArchivo(){
    FILE *arch=abrirArchivo("VUELOS.dat", "r+b");
    FILE *archP=abrirArchivo("PASAJEROS.dat", "rb");
    VUELOS datos;
    PASAJEROS info;
    VUELOS *pdatos=&datos;
    long pos;

    fread(&info, sizeof(info), 1, archP);
    while (!feof(archP))
    {
        pos=busqueda(arch, info.numVuelo, pdatos);
        if (pos!=-1)
        {
            datos.pasajeros++;
            fseek(arch, pos*sizeof(datos), SEEK_SET);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        }
        fread(&info, sizeof(info), 1, archP);
    }
    fclose(arch);
    fclose(archP);
}

long busqueda(FILE *arch, int numero, VUELOS *pdatos){
    VUELOS datos;
    long pos=-1;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && pos==-1)
    {
        if (datos.numVuelo==numero && strcmpi(datos.cod, "Aero1")==0)
        {
            pos=ftell(arch)/sizeof(datos)-1;
            *pdatos=datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}

FILE *abrirArchivo(char nombre[], char tipo[]){
    FILE *arch;
    arch=fopen(nombre, tipo);
    if (arch==NULL){
        printf("Error.");
        getch();
        exit(1);
    }
    return arch;
}