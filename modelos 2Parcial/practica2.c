/*La librería "Ateneo Universitario" almacena la lista de libros en el archivo binario Libros.dat utilizando la siguiente estructura:
codigo (entero)
titulo (hasta 50 caracteres)
precio (float)
Para incentivar las ventas o ajustar márgenes, la librería requiere un programa en C que realice lo siguiente:
Ajuste condicional de precios: Solicite un valor límite de precio y un porcentaje de ajuste. 
Si el libro tiene un precio inferior al limiteingresado, se le aplicará un incremento. 
Si supera o iguala dicho valor, el precio no se modificará. 
La actualización debe realizarse sobre el archivo Libros.dat.
Informar la cantidad total de libros registrados utilizando cálculo directo sobre la longitud total del archivo 
binario con las funciones vistas en el curso
Exportación en formato CSV: Generar el archivo libros_actualizados.csv con los títulos de las columnas (Codigo,Titulo,Precio) 
separado por comas.
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

typedef struct
{
    int cod;
    char titulo[51];
    float precio;
}LIB;

void procesarArchivo();
void exportar();
int cantidadRegistros(FILE *, int);
void leeyvalidaFloatE2(float *, int, int);
void leeyvalidaFloat(float *, int);
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarArchivo();
    exportar();

    return 0;
}

void procesarArchivo(){
    FILE *arch=abrirArchivo("Libros.dat", "r+b");
    float limite, porcentaje, incremento;
    int cantLib;
    LIB datos;
    printf("Ingrese un limite de precio: ");
    leeyvalidaFloat(&limite, 0);
    printf("Ingrese porcentaje de incremento(0-100): ");
    leeyvalidaFloatE2(&porcentaje, 0, 100);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.precio<limite)
        {
            incremento=(datos.precio*porcentaje)/100.0;
            datos.precio+=incremento;
            fseek(arch, -(long)sizeof(datos), SEEK_CUR);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    cantLib=cantidadRegistros(arch, sizeof(datos));
    printf("La cantidad de libros es de %d\n", cantLib);
    fclose(arch);
}

void exportar(){
    LIB datos;
    FILE *arch=abrirArchivo("Libros.dat", "rb");
    FILE *archExp=abrirArchivo("libros_actualizados.csv", "wt");
    fprintf(archExp, "Codigo,Titulo,Precio\n");
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch)){
        fprintf(archExp, "%d,%s,%.2f\n", datos.cod, datos.titulo, datos.precio);
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);
    fclose(archExp);
}

int cantidadRegistros(FILE *arch, int tam){
    int cant;
    fseek(arch, 0, SEEK_END);
    cant=ftell(arch)/tam;
    return cant;
}

void leeyvalidaFloatE2(float *dato, int min, int max){
    scanf("%f", dato);
    while(*dato<min || *dato>max){
        printf("Error. Reingrese:");
        scanf("%f", dato);
    }
}

void leeyvalidaFloat(float *dato, int lim){
    scanf("%f", dato);
    while(*dato<=lim){
        printf("Error. Reingrese:");
        scanf("%f", dato);
    }
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