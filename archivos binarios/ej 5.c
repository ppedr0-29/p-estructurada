/*5. Se desea realizar un programa que permita actualizar la lista de precios de una empresa en forma
individual a cada uno de sus productos.
Los productos que están guardados en el archivo PRODUCTOS.dat con la siguiente estructura:
• Código (entero)
• Precio (float)
• Descripción (de hasta 50 caracteres)
Para modificar un precio se ingresa por teclado el código del producto y el nuevo precio. La modificación
de precios finaliza con un código de producto igual a 0. */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int cod;
    float precio;
    char desc[51];
}PROD;

void procesarArchivo();
void leeyvalidaInt(int *, int);
void leeyvalidaFloat(float *, int);
long busqueda(FILE *, int, PROD *);
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarArchivo();

    return 0;
}

void procesarArchivo(){
    FILE *arch;
    arch=abrirArchivo("PRODUCTOS.dat", "r+b");
    PROD datos;
    PROD aux;
    PROD *pdatos=&datos;
    long pos;
    printf("Ingrese el codigo del producto: ");
    leeyvalidaInt(&aux.cod, 0);
    while (aux.cod!=0){
        pos=busqueda(arch, aux.cod, pdatos);
        if (pos!=-1){
            printf("Ingrese nuevo precio del producto: ");
            leeyvalidaFloat(&aux.precio, 1);
            datos.precio=aux.precio;
            fseek(arch, pos*sizeof(datos), SEEK_SET);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
            printf("Ingrese el codigo del producto: ");
        }
        else{
            printf("Codigo no encontrado. Reingrese: ");
        }
        leeyvalidaInt(&aux.cod, 0);
    }
    fclose(arch);
}

void leeyvalidaInt(int *dato, int lim){
    scanf("%d", dato);
    while (*dato < lim)
    {
        printf("Error, reingrese codigo:");
        scanf("%d", dato);
    }
}

void leeyvalidaFloat(float *dato, int lim){
    scanf("%f", dato);
    while (*dato < lim){
        printf("Error, reingrese precio:");
        scanf("%f", dato);
    }
}

long busqueda(FILE *arch, int cod, PROD *pdatos){
    PROD datos;
    long pos=-1;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && pos==-1)
    {
        if (datos.cod==cod)
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