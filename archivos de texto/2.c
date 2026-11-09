#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


FILE *abrirArchivo(char [], char []);
void procesarArchivo();


int main()
{
    procesarArchivo();
    return 0;
}

void procesarArchivo()
{
    FILE *arch = abrirArchivo("cadenas.txt", "rt");
    char cadena[100];
    fscanf(arch,"%s", cadena);
    while(!feof(arch))
    {
        printf("%s ", cadena);
        fscanf(arch,"%s", cadena);
    }

    fclose(arch);
}

FILE *abrirArchivo(char nombre[], char tipo[])
{
    FILE *arch;
    arch = fopen(nombre, tipo);
    if(arch == NULL)
    {
        printf("ERROR ");
        getch();
        exit(1);
    }
    return arch;
}