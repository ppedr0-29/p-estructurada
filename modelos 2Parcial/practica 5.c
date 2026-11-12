/*Se tiene un archivo binario que registra los sueldos de los empleados de una empresa
Con el siguiente diseño de registro
Legajo( int)
Nombre(45)
Antigüedad (en años int)
Sueldo básico (float)
Area( char 'A': administración, 'P': producción, 'C' comercial)
Realizar un programa en C que permita modificar directamente sobre el archivo (llamado sueldos.dat)los sueldos básicos de
los empleados según la siguiente escala de antigüedad
Mayor a 10 años 5%
Mayor a 20 años 6%
Una vez actualizado se debe generar un nuevo archivo, que solo contenga a los empleados del área administrativa
e informar la cantidad de registros de dicho archivo, utilizando las funciones vistas en el curso.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int legajo;
    char nombre[46];
    int antiguedad;
    float sueldoBasico;
    char area;
}EMP;

void procesarArchivo();
void nuevoArchivo();
int contarRegistros(FILE *, int);
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarArchivo();
    nuevoArchivo();

    return 0;
}

void procesarArchivo(){
    EMP datos;
    FILE *arch=abrirArchivo("sueldos.dat", "r+b");
    float incremento, porcentaje10=5.0, porcentaje20=6.0;

    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.antiguedad>20)
        {
            incremento=(porcentaje20*datos.sueldoBasico)/100.0;
            datos.sueldoBasico+=incremento;
            fseek(arch, -(long)sizeof(datos), SEEK_CUR);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        }else if (datos.antiguedad>10 && datos.antiguedad<=20)
        {
            incremento=(porcentaje10*datos.sueldoBasico)/100.0;
            datos.sueldoBasico+=incremento;
            fseek(arch, -(long)sizeof(datos), SEEK_CUR);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);
}

void nuevoArchivo(){
    FILE *arch=abrirArchivo("sueldos.dat", "rb");
    FILE *archA=abrirArchivo("administrativos.dat", "w+b");
    EMP datos;
    int cantR;
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.area=='A')
        {
            fwrite(&datos, sizeof(datos), 1, archA);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    cantR=contarRegistros(archA, sizeof(datos));
    printf("La cantidad de registros es %d\n", cantR);
    fclose(arch);
    fclose(archA);
}

int contarRegistros(FILE *arch, int tam){
    int cant;
    fseek(arch, 0, SEEK_END);
    cant=ftell(arch)/tam;
    return cant;
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