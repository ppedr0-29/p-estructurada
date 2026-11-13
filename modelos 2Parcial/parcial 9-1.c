/* Un supermercado almacena su información de productos en un archivo binario llamado "inventario.dat".

Cada registro del archivo tiene el siguiente formato:
-Codigo (int)
-Nombre (char[40])
-Stock (int)
-Precio (float)
-Rubro (char) 'A'= Alimentos, 'B'= Bebidas, 'L'= Limpieza

El archivo ya existe y contiene información cargada previamente. Se pide:
a) Modificar el archivo en el mismo lugar, aplicando el siguiente aumento según el rubro:
    Rubro A -> aumento del 8%
    Rubro B -> sin aumento
    Rubro L -> aumento del 3%
b) Crear un nuevo archivo binario que contenga solo los productos cuyo stock sea menor o igual a 15 unidades. 
Este archivo debe contener el mismo tipo de registro.
c) Informar la cantidad total de registros del archivo original utilizando las funciones vistas en el curso. 
No se permite ir leyendo para contarlos.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int cod;
    char nombre[41];
    int stock;
    float precio;
    char rubro;
}STOCK;

void procesarArchivo();
void nuevoArchivo();
int cantRegistros(FILE *, int);
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarArchivo();
    nuevoArchivo();

    return 0;
}

void procesarArchivo(){
    STOCK datos;
    float procentaje, incremento;
    int cantR;
    FILE *arch=abrirArchivo("inventario.dat", "r+b");
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {   
        procentaje=0;
        if (datos.rubro=='A')
        {   
            procentaje=8.0;
        }else if (datos.rubro=='L')
        {
            procentaje=3.0;
        }
        if (procentaje>0)
        {
            incremento=(datos.precio*procentaje)/100.0;
            datos.precio+=incremento;
            fseek(arch, -(long)sizeof(datos), SEEK_CUR);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    cantR=cantRegistros(arch, sizeof(datos));
    printf("Cantidad de registros: %d\n", cantR);
    fclose(arch);
}

void nuevoArchivo(){
    FILE *arch=abrirArchivo("inventario.dat", "rb");
    FILE *archN=abrirArchivo("pocostock.dat", "wb");
    STOCK datos;
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.stock<=15)
        {
            fwrite(&datos, sizeof(datos), 1, archN);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);
    fclose(archN);
}

int cantRegistros(FILE *arch, int tam){
    int cant;
    fseek(arch, 0, SEEK_END);
    cant=ftell(arch)/tam;
    return cant;
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