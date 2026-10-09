/*1. Los datos de los alumnos de una comisión de Computación Transversal son:
• Número de DNI (entero)
• Nombre y Apellido (80 caracteres)
• Nota1, Nota2 (entero)
• Nota Promedio (real, calculado según Nota1 y Nota2)
a. Declarar un tipo de dato que contenga la información del alumno.
b. Con la información indicada para los alumnos. Grabar los datos en el archivo “ALUMNOS.dat”. Esta
información de grabación finaliza con DNI cero.
c. Leer los datos del archivo, mediante la Función LECTURA. */

#include <stdio.h>
#include <string.h>

typedef struct{
    int dni;
    char nya[81];
    int nota1;
    int nota2;
    float prom;
}ALU;

FILE *abrirArchivo(char[], char[]);
void LECTURA();
void leeryValidarTexto(char [], int);
void leerTexto(char [], int);
void leeyvalidaIntE2(int *, int, int);
void leeyvalidaIntE2CF(int *, int , int);
void ingreso();

int main(){
    ALU datos;
    ingreso();
    LECTURA();

    return 0;
}


void LECTURA(){
    ALU datos;
    FILE *arch;
    arch=abrirArchivo("ALUMNOS.dat", "rb");
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while(!feof(arch)){
        printf("DNI:%d de %s con notas %d y %d, y promedio de %.2f", datos.dni, datos.nya, datos.nota1, datos.nota2, datos.prom);
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);

}

void ingreso(){
    FILE *arch;
    arch=abrirArchivo("ALUMNOS.dat", "wb");
    ALU aux;
    printf("Ingrese numero de DNI: ");
    leeyvalidaIntE2CF(&aux.dni, 10000000, 99999999);
    while(aux.dni!=0){
        printf("Ingrese nombre del alumno: ");
        leeryValidarTexto(aux.nya, 81);
        printf("Ingrese nota 1: ");
        leeyvalidaIntE2(&aux.nota1, 1, 10);
        printf("Ingrese nota 2: ");
        leeyvalidaIntE2(&aux.nota2, 1, 10);

        aux.prom=(float)(aux.nota1+aux.nota2)/2;

        fwrite(&aux, sizeof(aux), 1, arch);
        printf("Ingrese numero de DNI: ");
        leeyvalidaIntE2CF(&aux.dni, 10000000, 99999999);
    }
    fclose(arch);
}


FILE *abrirArchivo(char nombre[], char tipo[]){
    FILE *arch;
    arch=fopen(nombre, tipo);
    if(arch==NULL){
        printf("Error al abrir el archivo.");
        getch();
        exit(1);
    }
    return arch;
}

void leeyvalidaIntE2(int *dato, int min, int max){
    scanf("%d", dato);
    while(*dato<min || *dato>max){
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
}

void leeyvalidaIntE2CF(int *dato, int min, int max){
    scanf("%d", dato);
    while((*dato<min || *dato>max) && *dato!=0){
        printf("Error. Reingrese:");
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
        printf("El texto ingresado no es correcto. Reingrese: ");
        leerTexto(texto, largo);
    }
}