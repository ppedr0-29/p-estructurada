/*En una ferretería se cuenta con un archivo binario llamado Productos.dat que contiene los productos comercializados.
Se definió la siguiente estructura para el archivo:
codigo (entero)
descripcion (hasta 50 caracteres)
categoria (entero: 1 = Herramientas, 2 = Pinturas, 3 = Electricidad)
precio (float)
Debido a cambios en los costos de proveedores, se solicita realizar un programa en C que:
Ajuste masivo de precios: Solicite por teclado un porcentaje de aumento y el número de categoría a la cual aplicarlo. Actualice en el propio archivo Productos.dat
únicamente el precio de los productos que pertenezcan a esa categoría.
Conteo e informe: Informe por pantalla la cantidad total de registros grabados
en el archivo y cuántos productos pertenecen a la categoría actualizada.
Exportación: Genere un archivo de texto plano denominado productos_actualizados.csv con encabezados
(Codigo;Descripcion;Categoria;Precio) que contenga el catálogo
completo con los precios ya ajustados.
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

typedef struct{
    int cod;
    char desc[51];
    int cat;
    float precio;
}PROD;

void procesarArchivo();
void exportar();
int cantidadRegistros(FILE *, int);
void leeyvalidaIntE2(float *, int, int);
void leeyvalidaIntE3(int *);
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarArchivo();
    exportar();
    return 0;
}


void procesarArchivo(){
    FILE *arch=abrirArchivo("Productos.dat", "r+b");
    PROD datos;
    float porcentaje, incremento;
    int catAux, cantR, cantP=0;

    printf("Ingrese porcentaje de incremento(0-100): ");
    leeyvalidaIntE2(&porcentaje, 0, 100);
    printf("Ingrese categoria (H-P-E )a cual aplicar el incremento en numero (1-2-3): ");
    leeyvalidaIntE3(&catAux);
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch)){

        if(datos.cat==catAux){
            incremento=(datos.precio*porcentaje)/100.0;
            datos.precio+=incremento;
            cantP++;
            fseek(arch, -(long)sizeof(datos), SEEK_CUR);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    cantR=cantidadRegistros(arch, sizeof(datos));
    fclose(arch);
    printf("La cantidad de registros es %d\n", cantR);
    printf("La cantidad de productos actualizados para la categoria elegida es %d \n", cantP);
}

void exportar(){
    PROD datos;
    FILE *arch=abrirArchivo("Productos.dat", "rb");
    FILE *archExp=abrirArchivo("productos_actualizados.csv", "wt");
    fprintf(archExp, "Codigo;Descripcion;Categoria;Precio\n");
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch)){
        fprintf(archExp, "%d;%s;%d;%.2f\n", datos.cod, datos.desc, datos.cat, datos.precio);
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

void leeyvalidaIntE2(float *dato, int min, int max){
    scanf("%f", dato);
    while(*dato<min || *dato>max){
        printf("Error. Reingrese:");
        scanf("%f", dato);
    }
}

void leeyvalidaIntE3(int *dato){
    scanf("%d", dato);
    while(*dato!=1 && *dato!=2 && *dato!=3){
        printf("Error. Reingrese:");
        scanf("%d", dato);
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