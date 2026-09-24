/*Ejercicio 1: Manejo de Texto y Punteros
Una empresa de logística requiere un programa para validar los Códigos de Rastreo de sus paquetes. 
El formato válido consta estrictamente de 8 caracteres:
Los primeros 2 son alfabéticos (indican el país de origen).
Los siguientes 5 son numéricos (código de paquete).
El último es 1 carácter alfabético (indica la zona de entrega).
(Ejemplo válido: AR12345Z)

Realizar una función validarRastreo() que reciba como parámetro el string correspondiente al código y retorne 1 si es válido, 
o 0 en caso de no serlo. La función debe terminar la validación ante la primera inconsistencia detectada.
Condición obligatoria: 
Resolver esta función utilizando exclusivamente aritmética de punteros (no se permite el uso de subíndices [] dentro de esta función).*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validarRastreo(char *, int );
void leerTexto(char [], int );
void leeryvalidarTexto(char [], int );

int main(){
    char cod[9];
    int valido;
    printf("Ingrese codigo de rastreo(AA00000A):");
    leeryvalidarTexto(cod, 9);
    valido=validarRastreo(cod, 8);
    if (valido==1)
    {
        printf("Codigo valido.\n");
    }else{
        printf("Codigo invalido.\n");
    }
}

int validarRastreo(char *cod, int tam){
    int valido=1, i=0;
    while (valido==1 && i<tam)
    {
        if (i<2)
        {
            if (isalpha(*(cod+i))==0)
            {
                valido=0;
            }else{
                *(cod+i)=toupper(*(cod+i));
            }
        }else if (i>=2 && i<=6)
        {
            if (isdigit(*(cod+i))==0)
            {
                valido=0;
            }
        }else if (i>6)
        {
            if (isalpha(*(cod+i))==0)
            {
                valido=0;
            }else{
                *(cod+i)=toupper(*(cod+i));
            }
        }
        i++;
    }
    return valido;
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

void leeryvalidarTexto(char texto[], int largo)
{
    leerTexto(texto, largo);
    while(strlen(texto)!=8)
    {
        printf("Error, reingrese: ");
        leerTexto(texto, largo);
    }
}
