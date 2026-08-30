/*2. Ingresar dos Strings, uno con el nombre y el otro con el apellido de una persona. Utilizando las funciones de
la biblioteca string.h generar un tercer string formado por: NOMBRE, APELLIDO (nombre coma espacio y
apellido) y mostrarlo */

#include <stdio.h>
#include <string.h>
#define TAM 50

void leerTexto(char [], int );
void leeryValidarTexto(char [], int );

int main(){
    char nombre[TAM];
    char apellido[TAM];
    char completo[TAM+TAM];
    printf("Ingresar nombre: ");
    leeryValidarTexto(nombre, TAM);
    printf("Ingresar apellido: ");
    leeryValidarTexto(apellido, TAM);
    strcpy(completo, nombre);
    strcat(completo, ", ");
    strcat(completo, apellido);
    printf("El nombre y apellido es: %s", completo);

    return 0;
}

void leerTexto(char texto[], int largo){
    int i=0;
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
        printf("El texto no puede ser vacio. Reingrese: ");
        leerTexto(texto, largo);
    }
    
}