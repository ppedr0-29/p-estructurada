/*Ejercicio 2. Se dispone del archivo binario examenes.dat, ordenado por curso, con los siguientes datos por examen rendido:

Curso (entero)
Legajo del alumno (entero)
Nota (float, de 0 a 10)

Se solicita:
a) Para cada curso, informar la cantidad de exámenes rendidos y el promedio de notas. El cálculo del promedio debe hacerse en otra función.
b) Informar el curso con el mejor promedio.
c) Generar un archivo binario resumen.dat con un registro por curso, que contenga el número de curso y su promedio.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int curso;
    int legajo;
    float nota;
}EXAMENES;

typedef struct
{
    int curso;
    float promedio;
}RESUMEN;

void procesarCdC();
float promedio(float, int);
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarCdC();

    return 0;
}

void procesarCdC(){
    FILE *arch=abrirArchivo("examenes.dat", "rb");
    FILE *archR=abrirArchivo("resumen.dat", "wb");
    EXAMENES datos;
    RESUMEN info;
    int cantExamenes, primero=1, mejorCurso, cursoAnterior;
    float promedioNotas, notasTotales,mejorPromedio;
    
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {   
        cursoAnterior=datos.curso;
        cantExamenes=0;
        notasTotales=0;
        while (!feof(arch) && cursoAnterior==datos.curso)
        {
            cantExamenes++;
            notasTotales+=datos.nota;
            fread(&datos, sizeof(datos), 1, arch);
        }
        promedioNotas=promedio(notasTotales, cantExamenes);
        printf("Curso %d : Examenes rendidos - %d y Promedio de notas - %.2f\n", cursoAnterior, cantExamenes, promedioNotas);
        info.curso=cursoAnterior;
        info.promedio=promedioNotas;
        fwrite(&info, sizeof(info), 1, archR);
        if (primero==1 || promedioNotas>mejorPromedio)
        {
            mejorPromedio=promedioNotas;
            mejorCurso=cursoAnterior;
            primero=0;
        }
    }
    printf("Curso %d con mejor promedio de %.2f\n", mejorCurso, mejorPromedio);
    fclose(arch);
    fclose(archR);
}

float promedio(float notas,int cant){
    float prom;
    prom=notas/cant;
    return prom;
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