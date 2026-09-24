/*Se solicita realizar un programa en C para validar el formato de las patentes registradas en un sistema de tránsito. 
El programa debe permitir el ingreso continuo de patentes por teclado hasta que se ingrese la palabra "FIN" (en mayúsculas) 
como condición de fin.
Una patente se considera válida si responde estrictamente a uno de los dos formatos vigentes:
Formato Tradicional: 3 letras seguidas de 3 números (Ejemplo: AAA999).
Formato Mercosur: 2 letras, 3 números y 2 letras(Ejemplo: AA999AA)*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TAM 8

int validarF7(char patente[], int ce);
int validarF6(char patente[], int ce);
void leerTexto(char texto[], int largo);
void leeryValidarTexto(char texto[], int largo);

int main(){
    int valida=0;
    char patente[TAM];
    printf("Ingrese la patente: ");
    leeryValidarTexto(patente, TAM);
    while (strcmpi(patente, "FIN")!=0)
    {   
        if (strlen(patente)==6)
        {
            valida = validarF6(patente, 6);
        }
        else if (strlen(patente)==7){
            valida = validarF7(patente, 7);
        }else{
            valida=0;
        }
        if (valida == 1){
            printf("Patente Valida.\n");
        }
        else 
        {
            printf("Patente Invalida.\n");
        }
        printf("Ingrese la patente: ");
        leeryValidarTexto(patente, TAM);
    }
}

int validarF7(char patente[], int ce){
    int valido=1, i=0;
    while (valido==1 && i<ce)
    {
        if (i<=1){
            if (isalpha(patente[i])==0){
                valido=0;
            }else{
                patente[i]=toupper(patente[i]);
            }
        }else if(i>=2 && i<=4){
            if (isdigit(patente[i])==0){
                valido=0;
            }
        }else if (i>4)
        {
            if (isalpha(patente[i])==0){
                valido=0;
            }else{
                patente[i]=toupper(patente[i]);
            }
        }
        i++;
    }
    return valido;
}

int validarF6(char patente[], int ce){
    int valido=1, i=0;
    while (valido==1 && i<ce)
    {
        if (i<=2){
            if (isalpha(patente[i])==0){
                valido=0;
            }
            else{
                patente[i]=toupper(patente[i]);
            }
        }else if(i>2){
            if (isdigit(patente[i])==0)
            {
                valido=0;
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

void leeryValidarTexto(char texto[], int largo){
    leerTexto(texto, largo);
    while ((strlen(texto)!=6 && strlen(texto)!=7) && strlen(texto)!=3)
    {
        printf("Error. Reingrese: ");
        leerTexto(texto, largo);
    }
}