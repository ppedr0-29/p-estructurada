/*Ejercicio 1. Se dispone del archivo binario empleados.dat con los siguientes datos por empleado:
Legajo (entero)
Nombre (50 caracteres)
Antigüedad (entero, en años)
Sueldo (float)
Turno (carácter: ‘M’ mañana, ‘T’ tarde, ’N’ noche)

Se solicita:
a) Actualizar el sueldo de los empleados del turno noche, aplicando un aumento del porcentaje ingresado por teclado. 
La actualización debe realizarse sobre el propio archivo, mientras se lee.
b) Calcular e informar, mediante funciones, la cantidad total de registros del archivo.
c) Copiar a otro archivo, veteranos.dat, el registro completo de todos los empleados con 20 años de antigüedad o más.
d) Explicar con sus propias palabras cómo es el proceso de eliminación física de un registro en un archivo binario.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int legajo;
    char nombre[51];
    int antiguedad;
    float sueldo;
    char turno;
}EMP;

void procesarArchivo();
int cantRegistros(FILE *, int);
void veterano(FILE *);
void leeyvalidaFloatE2(float *, int, int);
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarArchivo();

    return 0;
}

void procesarArchivo(){
    FILE *arch=abrirArchivo("empleados.dat", "r+b");
    EMP datos;
    int cantEmp;
    float porcentaje, incremento;
    printf("Ingrese porcentaje de incremento para los empleados TURNO-NOCHE (0-100): ");
    leeyvalidaFloatE2(&porcentaje, 0, 100);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.turno=='N')
        {
            incremento=(datos.sueldo*porcentaje)/100.0;
            datos.sueldo+=incremento;
            fseek(arch, -(long)sizeof(datos), SEEK_CUR);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    veterano(arch);
    cantEmp=cantRegistros(arch, sizeof(datos));
    printf("La cantidad de empleados es de %d\n", cantEmp);
    fclose(arch);
}

int cantRegistros(FILE *arch, int tamRegistro){
    int cant;
    fseek(arch, 0 , SEEK_END);
    cant=ftell(arch)/tamRegistro;
    return cant;
}

void veterano(FILE *arch){
    FILE *archV=abrirArchivo("veteranos.dat", "wb");
    EMP datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.antiguedad>=20)
        {
            fwrite(&datos, sizeof(datos), 1, archV);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(archV);
}

void leeyvalidaFloatE2(float *dato, int min, int max){
    scanf("%f", dato);
    while (*dato<min || *dato>max)
    {
        printf("Error. Reingrese: ");
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