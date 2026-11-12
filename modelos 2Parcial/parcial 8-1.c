/*Ejercicio 1. El club “Los Andes” tiene el archivo binario socios.dat con los siguientes datos por socio:
Número de socio (entero)
Nombre (hasta 40 caracteres)
Categoría (carácter: ‘B’ básico, ‘P’ premium)
Cuotas adeudadas (entero)
Deuda (float)

Se solicita:
a) Ingresar por teclado un porcentaje de recargo (entre 1 y 50) y aplicarlo a la deuda de los socios con más de 2 cuotas adeudadas. 
La modificación debe hacerse sobre el propio archivo, mientras se lee.
b) Ingresar por teclado un número de socio que acaba de pagar. Si existe en el archivo, poner en 0 sus cuotas adeudadas y su deuda, 
directamente sobre el archivo. Si no existe, informarlo.
c) Generar el archivo de texto morosos.csv, separado por ‘;’, con encabezado (Socio;Nombre;Deuda), 
que contenga solo los socios cuya deuda sea mayor a 0.
d) Informar, mediante una función, la cantidad total de registros de socios.dat.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int numSocio;
    char nombre[41];
    char cat;
    int cuotasAdeudada;
    float deuda;
}SOCIO;

void exportar();
void procesarPago();
long busqueda(FILE *, int, SOCIO *);
void procesarIncremento();
int contarRegistros(FILE *, int);
void leeyvalidaFloatE2(float *, int, int);
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarIncremento();
    procesarPago();
    exportar();
    return 0;
}

void exportar(){
    FILE *arch=abrirArchivo("socios.dat", "rb");
    FILE *archNuevo=abrirArchivo("morosos.csv", "wt");
    SOCIO datos;
    fprintf(archNuevo, "Socio;Nombre;Deuda\n");
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {   
        if (datos.deuda>0)
        {
            fprintf(archNuevo, "%d;%s;%.2f\n", datos.numSocio, datos.nombre, datos.deuda);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);
    fclose(archNuevo);
}

void procesarPago(){
    FILE *arch=abrirArchivo("socios.dat", "r+b");
    SOCIO datos, *pdatos=&datos;
    int numAux;
    long pos;
    printf("Ingresar numero de socio que acaba de pagar:");
    scanf("%d", &numAux);
    pos=busqueda(arch, numAux, pdatos);
    if (pos!=-1)
    {
        datos.cuotasAdeudada=0;
        datos.deuda=0;
        fseek(arch, pos*sizeof(datos), SEEK_SET);
        fwrite(&datos, sizeof(datos), 1, arch);
        fflush(arch);
    }else{
        printf("El socio %d no existe.\n", numAux);
    }
    fclose(arch);
}

long busqueda(FILE *arch, int num, SOCIO *pdatos){
    long pos=-1;
    SOCIO datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && pos==-1)
    {
        if (datos.numSocio==num)
        {
            pos=ftell(arch)/sizeof(datos)-1;
            *pdatos=datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}


void procesarIncremento(){
    FILE *arch=abrirArchivo("socios.dat", "r+b");
    SOCIO datos;
    float porcentaje, incremento;
    int cantR;

    printf("Ingrese porcentaje de recargo(1-50):");
    leeyvalidaFloatE2(&porcentaje, 1, 50);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.cuotasAdeudada>2)
        {
            incremento=(datos.deuda*porcentaje)/100.0;
            datos.deuda+=incremento;
            fseek(arch, -(long)sizeof(datos), SEEK_CUR);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    cantR=contarRegistros(arch, sizeof(datos));
    printf("La cantidad de socios es %d\n", cantR);
    fclose(arch);
}

int contarRegistros(FILE *arch, int tam){
    int cant;
    fseek(arch, 0, SEEK_END);
    cant=ftell(arch)/tam;
    return cant;
}

void leeyvalidaFloatE2(float *dato, int min, int max){
    scanf("%f", dato);
    while (*dato<min || *dato>max)
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