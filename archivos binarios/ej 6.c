/*6. Dado el archivo productos.dat con la siguiente estructura:
• Código (entero)
• Precio (float)
• Descripción (de hasta 50 caracteres)
Realizar un programa que permita eliminar productos dado su código*/

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
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarArchivo();

    return 0;
}

void procesarArchivo(){
    FILE *arch;
    FILE *archT;
    arch=abrirArchivo("PRODUCTOS.dat", "r+b");
    archT=abrirArchivo("PRODUCTOST.dat", "wb");
    PROD datos;
    PROD aux;
    int flag=0;
    printf("Ingrese el codigo del producto a eliminar: ");
    leeyvalidaInt(&aux.cod, 0);
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.cod!=aux.cod)
        {
            fwrite(&datos, sizeof(datos), 1, archT);
        }else{
            flag=1;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);
    fclose(archT);
    if (flag==1)
    {   
        remove("PRODUCTOS.dat");
        rename("PRODUCTOST.dat", "PRODUCTOS.dat");
        printf("Producto eliminado.\n");
    }else{
        printf("Codigo inexistente\n");
        remove("PRODUCTOST.dat");
    }
    }


void leeyvalidaInt(int *dato, int lim){
    scanf("%d", dato);
    while (*dato < lim)
    {
        printf("Error, reingrese codigo:");
        scanf("%d", dato);
    }
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