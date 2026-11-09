#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

FILE *abrirArchivo(char [], char []);
void procesarArchivos();

int main()
{
    procesarArchivos();
    return 0;
}

void procesarArchivos()
{
    FILE *arch = abrirArchivo("cadenas.txt", "wt" );
    char cadena[100];

    printf("ingrese la cadena de caracteres: ");
    fscanf(stdin,"%s", cadena);
    while(strcmpi(cadena , "FINALIZAR") != 0)
    {
        fprintf(arch, "%s\n", cadena);
        printf( "ingrese la cadena de caracteres: ");
        fscanf(stdin,"%s", cadena);
    }
    fclose(arch);
}

FILE *abrirArchivo(char nombre[], char tipo[])
{
    FILE *arch;
    arch=fopen(nombre, tipo);
    if(arch == NULL)
    {
        printf("Error al abrir el archivo.");
        getch();
        exit(1);
    }
    return arch;
}