/*1. Ingresar una frase de hasta 500 caracteres y contar cuántas palabras contiene dicha frase.
a. Considerar que las palabras están separadas por un único espacio.
b. Considerar que las palabras pueden estar separadas por más de un espacio consecutivo.*/

#include <stdio.h>
#include <string.h>
#define TAM 500

int main (){
    char frase[TAM];
    int cantP=0;
    printf("Ingresar una frase de hasta 500 caracteres: ");
    leertexto(frase, TAM);
    for (int i = 0; i < TAM; i++)
    {
        
    }
    
}

void leertexto(char texto [], int largo){
    fflush(stdin);
    fgets(texto, largo, stdin);
    int i=0;
    while (texto[i]!='\0')
    {
        if (texto[i]=='\n')
        {
            texto[i]='\n';
        }
        i++;
    }
    
}