/*1. Ingresar una frase de hasta 500 caracteres y contar cuántas palabras contiene dicha frase.
a. Considerar que las palabras están separadas por un único espacio.
b. Considerar que las palabras pueden estar separadas por más de un espacio consecutivo.*/

#include <stdio.h>
#include <string.h>
#define TAM 500

void leertexto(char  [], int );

int main (){
    char frase[TAM];
    int cantP=0;
    char flag=' ';
    printf("Ingresar una frase de hasta 500 caracteres: ");
    leertexto(frase, TAM);
    int i=0;
    while (frase[i]!='\0')
    {
        
        if (frase[i]!='\0' && flag==' ' && frase[i]!=' ')
        {
            cantP+=1;
        }
        flag=frase[i];
        i++;
    }
    printf("La cantidad de palabras son %d", cantP);
}

void leertexto(char texto [], int largo){
    fflush(stdin);
    fgets(texto, largo, stdin);
    int i=0;
    while (texto[i]!='\0')
    {
        if (texto[i]=='\n')
        {
            texto[i]='\0';
        }
        i++;
    }
    
}