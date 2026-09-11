/*4. Se sabe que como máximo en una comisión de Elementos de Programación hay 80 alumnos. De cada alumno
se conoce:
• Número de DNI (entero).
• Apellido y Nombre (80 caracteres).
• Nota1, Nota2 (entero).
• Nota Promedio (real, calculado según Nota1 y Nota2).
Se solicita:
a. Declarar un tipo de dato que contenga la información del alumno.
b. Declarar un vector de estructuras del tipo de dato creado en el punto a.
c. Cargar en un vector de estructuras, los datos referentes a los alumnos de la comisión, esta
información termina con DNI igual al 0. Función INGRESO.
d. Indicar cuántos alumnos aprobaron (ambos parciales con nota >= 4 y cuántos reprobaron la materia.
Función RESULTADO.
e. Informar los datos de los alumnos de (DNI – Apellido y Nombre – Nota Promedio) de los alumnos.
PROMOCIONADOS (ambas notas >= 7). Función INFORME_PROMO. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 80
#define TXT 81

typedef struct
{
    int dni;
    char ayn[TXT];
    int nota1;
    int nota2;
    float promedio;
}ALUMNOS;

void INFORME_PROMO(ALUMNOS[], int);
void RESULTADO(ALUMNOS[], int);
int INGRESO(ALUMNOS[], int);
int busqueda(ALUMNOS[], int, int);
ALUMNOS ingreso(ALUMNOS[], int);
void leeyvalidaF(float*, int);
void leeyvalidaIntE2(int*, int, int);
void leeyvalidaIntE2CF(int*, int, int, int);
void leerTexto(char[], int);
void leeryValidarTexto(char[], int);

int main(){
    ALUMNOS datos[TAM];
    int cantAlu=INGRESO(datos, TAM);
    RESULTADO(datos, cantAlu);
    INFORME_PROMO(datos, cantAlu);
    return 0;
}

void INFORME_PROMO(ALUMNOS datos[], int ce){
    for (int i = 0; i < ce; i++)
    {
        if (datos[i].nota1>=7 && datos[i].nota2>=7)
        {
            printf("El alumno %s con DNI:%d promociono con %.2f\n", datos[i].ayn, datos[i].dni, datos[i].promedio);
        }
        
    }
    
}

void RESULTADO(ALUMNOS datos[], int ce){
    int acumA=0, acumR=0;
    for (int i = 0; i < ce; i++)
    {
        if (datos[i].nota1 >=4 && datos[i].nota2>=4)
        {
            acumA++;
        }else{
            acumR++;
        }
        
    }
    printf("Los alumnos aprobados son %d\n", acumA);
    printf("Los alumnos reprobados son %d\n", acumR);
}

int INGRESO(ALUMNOS datos[], int ce){
    ALUMNOS aux;
    int i=0;
    printf("--INGRESO ALUMNOS--\n");
    aux=ingreso(datos, i);
    while (aux.dni!=0 && i<ce)
    {
        datos[i]=aux;
        i++;
        aux=ingreso(datos, i);
    }
    return i;
}

int busqueda(ALUMNOS datos[], int ce, int dni){
    int pos=-1, i=0;
    while (pos==-1 && i<ce)
    {
        if (datos[i].dni==dni)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

ALUMNOS ingreso(ALUMNOS datos[], int i){
    ALUMNOS aux;
    printf("Ingrese dni del alumno: ");
    leeyvalidaIntE2CF(&aux.dni, 10000000, 99999999, 0);
    while (busqueda(datos, i, aux.dni)!=-1)
    {   
        printf("El dni ya fue ingresado. Reingrese: ");
        leeyvalidaIntE2CF(&aux.dni, 10000000, 99999999, 0);
    }
    if (aux.dni!=0)
        {   
            printf("Ingrese apellido y nombre del alumno: ");
            leeryValidarTexto(aux.ayn, TXT);
            printf("Ingrese nota 1: ");
            leeyvalidaIntE2(&aux.nota1, 1, 10);
            printf("Ingrese nota 2: ");
            leeyvalidaIntE2(&aux.nota2, 1, 10);
            aux.promedio=(float)(aux.nota1+aux.nota2)/2;
    }
    return aux;
}



void leeyvalidaF(float *dato, int lim){
    scanf("%f", dato);
    while (*dato<lim)
    {
        printf("Error. Reingrese: ");
        scanf("%f", dato);
    }
}

void leeyvalidaIntE2(int *dato, int min, int max){
    scanf("%d", dato);
    while (*dato<min || *dato>max)
    {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
}

void leeyvalidaIntE2CF(int *dato, int min, int max, int cf){
    scanf("%d", dato);
    while ((*dato<min || *dato>max) && *dato!=cf)
    {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
}

void leerTexto(char texto[], int largo){
    int i=0;
    fflush(stdin);
    fgets(texto, largo, stdin);
    while (texto[i]!='\0')
    {
        if (texto[i]=='\n')
        {
            texto[i]='\0';
        }
        i++;
    }

}

void leeryValidarTexto(char texto[], int largo){
    leerTexto(texto, largo);
    while (strlen(texto)==0)
    {
        printf("Error. Reingrese: ");
        leerTexto(texto, largo);
    }

}