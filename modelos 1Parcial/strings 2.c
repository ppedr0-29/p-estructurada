/*2) Un palíndromo es una palabra o frase cuyas letras se leen de la misma manera de izquierda a derecha que de derecha a izquierda 
(por ejemplo: ANA, NEUQUEN, RECONOCER, OSO)

Se solicita realizar un programa en C que permita el ingreso continuo de palabras por teclado. 
El ingreso finaliza cuando el usuario escribe la palabra "FIN" (en mayúsculas).

Desarrollar una función esPalindromo que retorne 1 si la palabra es palíndromo o 0 si no lo es.
La función debe ser independiente de mayúsculas y minúsculas (tratar 'A' y 'a' como iguales)
Para cada ingreso (excepto "FIN"), mostrar si la palabra es o no un palíndromo*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TXT 21

int esPalindromo(char []);
void leerTexto(char [], int );
void leeryvalidarTexto(char [], int );

int main(){
    char texto[TXT];
    int esPali;
    printf("--PALINDROMO--\n");
    printf("Ingrese palabra o frase(FIN para terminar): ");
    leeryvalidarTexto(texto, TXT);
    while (strcmp(texto, "FIN")!=0)
    {   
        esPali=esPalindromo(texto);
        if (esPali==1)
        {
            printf("%s es palindromo.\n", texto);
        }else{
            printf("%s no es palindromo.\n", texto);
        }
        printf("Ingrese palabra o frase(FIN para terminar): ");
        leeryvalidarTexto(texto, TXT);
    }
    return 0;
}

int esPalindromo(char texto[]){
    int esPali=1;
    int inicio=0;
    int fin= strlen(texto)-1;
    while (inicio<fin && esPali==1)
    {
        while(texto[inicio]==' ' && inicio<fin)
        {
            inicio++;
        }
        while(texto[fin]==' ' && inicio<fin)
        {
            fin--;
        }
        if(toupper(texto[inicio])!=toupper(texto[fin])){
            esPali=0;
        }
    inicio++;
    fin--;
    }
    return esPali;
}

void leeryvalidarTexto(char texto[], int largo)
{
    leerTexto(texto, largo);
    while(strlen(texto)==0)
    {
        printf("Error. Reingrese: ");
        leerTexto(texto, largo);
    }
}

void leerTexto(char texto[], int largo)
{
    int i=0;
    fflush(stdin);
    fgets(texto, largo, stdin);
    while(texto[i]!='\0')
    {
        if(texto[i]=='\n')
        {
            texto[i]='\0';
        }
        i++;
    }
}

