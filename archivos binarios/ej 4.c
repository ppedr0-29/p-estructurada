/*4. Realizar un programa que permite actualizar una lista de precios en forma masiva, ingresando un
porcentaje de incremento. El archivo se llama PRECIOS.dat y fue generado utilizando la siguiente
estructura:
• Código (entero)
• Precio (float)
• Descripción (de hasta 50 caracteres) */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

typedef struct
{
    int cod;
    float precio;
    char desc[51];
}Precios;

FILE *abrirArchivo(char[], char[]);
void leeyvalidaInt(int *, int);

int main(){
    Precios datos;
    float incremento;
    int porcentaje;
    FILE *arch;
    arch=abrirArchivo("PRECIOS.dat", "r+b");
    
    printf("Ingrese porcentaje de incremento:");
    leeyvalidaInt(&porcentaje, 0);

    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        incremento=(porcentaje*datos.precio)/100.0;
        datos.precio+=incremento;
        fseek(arch, -(long)sizeof(datos), SEEK_CUR);
        fwrite(&datos, sizeof(datos), 1, arch);
        fflush(arch);
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);

    return 0;
}

void leeyvalidaInt(int *dato, int lim){
    scanf("%d", dato);
    while (*dato < lim)
    {
        printf("Error, reingrese porcentaje:");
        scanf("%d", dato);
    }
}

FILE *abrirArchivo(char nombre[], char tipo[]){
    FILE *arch;
    arch=fopen(nombre, tipo);
    if (arch==NULL)
    {
        printf("Error.");
        getch();
        exit(1);
    }
    return arch;
}

