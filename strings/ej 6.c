/*6. Realizar el juego del ahorcado. Primero se debe ingresar la palabra a adivinar de hasta 10 caracteres. Luego
se muestra por cada letra un guion bajo para que el jugador sepa la cantidad de letras a adivinar. Se irá
ingresando una a una las letras y si estas se encuentran en la palabra las deberá ir mostrando en el lugar
correspondiente. Por cada letra que no se encuentre en la palabra perderá una vida. El jugador dispondrá de
5 vidas para intentar ganar el juego.
Complemento:
• Ir completando el dibujo del muñeco del ahorcado cada vez que se comete un error. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 11

void juego(char []);
void busqueda(char [], char  [],char , int , int *, int *);
void leerTexto(char [], int );
void leeryValidarTexto(char [], int );
void munieco(int );

int main(){
    char palabra[TAM];
    printf("Ingrese la palabra a adivinar (10 letras maximo): ");
    leeryValidarTexto(palabra, TAM);
    juego(palabra);

    return 0;
}

void juego(char palabra[]){
    char adivinado[TAM], letra;
    int vidas=5, gano=0, errores=0;
    int largo=strlen(palabra);

    for(int i=0; i<largo; i++){
        adivinado[i]='_';
    }
    adivinado[largo]='\0';
    while(vidas>0 && gano==0){
        for(int i=0; i<largo; i++){
            printf("%c ", adivinado[i]);
        }
        munieco(errores);
        printf("Ingrese una letra: ");
        fflush(stdin);
        scanf("%c", &letra);
        busqueda(palabra, adivinado, letra, largo, &vidas, &errores);
        gano=1;
        for(int i=0; i<largo; i++){
            if(adivinado[i]=='_'){
                gano=0;
            }
        }

    }
    if(gano==0){
        munieco(errores);
        printf("Perdiste, la palabra era %s", palabra);
    }
    else{
        printf("Felicitaciones! La palabra era %s", adivinado);
    }
}

void busqueda(char palabra[], char adivinado [],char letra, int largo, int *vida, int *errores){
    int acum=0;
    for(int i=0; i<largo; i++){
        if(palabra[i]==letra){
            adivinado[i]=letra;
            acum++;
        }
    }
    if(acum==0){
        *vida-=1;
        *errores+=1;
        printf("La letra %c no se encuentra en la palabra.", letra);
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
    while (strlen(texto) < 1 || strlen (texto)>10 )
    {
        printf("El texto ingresado no es correcto. Reingrese: ");
        leerTexto(texto, largo);
    }

}

void munieco(int errores){
    switch(errores){
        case 0:
            printf(" ");
        break;
        case 1:
            printf("\nO\n");
        break;
        case 2:
            printf("\nO\n");
            printf("|\n");
        break;
        case 3:
            printf("\nO\n");
            printf("|\\ \n");
        break;
        case 4:
            printf("\nO\n");
            printf(" /|\\ \n");
        break;
        case 5:
            printf("\nO\n");
            printf(" /|\\ \n");
            printf(" /  \n");
        break;
        case 6:
            printf("\nO\n");
            printf(" /|\\ \n");
            printf(" / \\ \n");
        break;
    }
}