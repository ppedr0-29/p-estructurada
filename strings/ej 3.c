/*3. Ingresar nombre y DNI de los alumnos de un curso. Como máximo el curso puede tener 50 alumnos. La carga
finaliza con un alumno de nombre FIN. Luego de cargar los alumnos se pide:
a. Ingresar nombres de a uno en uno y buscarlos. Si el nombre está en el curso mostrar su DNI y sino
informar que no está. Seguir ingresando nombres hasta que se ingrese un nombre igual a
NOBUSCARMAS.
b. Mostrar el listado de alumnos ordenado alfabéticamente de menor a mayor. */

#include <stdio.h>
#include <string.h>
#define TAM 50

int ingreso(char nombres[][TAM], int dni[], int ce);
void mostrarDNI(int dni[], char nombre[][TAM], int ce);
int busqueda(char nombreB[], char nombre[][TAM], int ce);
void mostrarListado(char nombre[][TAM], int dni[], int ce);
void burbujeo(char V[][TAM], int dni[], int ce);
void leerTexto(char texto[], int largo);
void leeryValidarTexto(char texto[], int largo);
void leeyvalidaE2(int *dato, int min, int max);

int main(){
    char nombres[TAM][TAM];
    int dni[50];
    int cantAlu;
    cantAlu=ingreso(nombres, dni, TAM);
    printf("--BUSQUEDA DE ALUMNO--");
    mostrarDNI(dni, nombres, cantAlu);
    mostrarListado(nombres, dni, cantAlu);

    return 0;
}

void mostrarListado(char nombre[][TAM], int dni[], int ce){
    burbujeo(nombre, dni, ce);
    for (int i = 0; i < ce; i++)
    {
            printf("%s - %d", nombre[i], dni[i]);
        
    }
}

void burbujeo(char V[][TAM], int dni[], int ce){
    char AUX[TAM];
    int auxDni;
    int j, cota = ce - 1;
    int desordenado = 1;

    while (desordenado)
    {
        desordenado = 0;
        for (j = 0; j < cota; j++)
        {
            if (strcmpi(V[j], V[j + 1]) > 0)
            {
                strcpy(AUX, V[j]);
                strcpy(V[j], V[j + 1]);
                strcpy(V[j + 1], AUX);
                auxDni=dni[j];
                dni[j]=dni[j+1];
                dni[j+1]=auxDni;
                desordenado = j;
            }
        }
        cota = desordenado;
    }
}

void mostrarDNI(int dni[], char nombre[][TAM], int ce){
    int pos=-1;
    char nombreB[TAM];
    printf("Ingrese el nombre del alumno a buscar: ");
    leeryValidarTexto(nombreB, TAM);
    while (strcmpi(nombreB, "NOBUSCARMAS")!=0)
    {
        pos=busqueda(nombreB, nombre, ce);
        if (pos==-1)
        {
            printf("El nombre no esta.");
        }else{
            printf("DNI %d, perteneciente a %s\n", dni[pos], nombreB);
        }
        printf("Ingrese el nombre del alumno a buscar: ");
        leeryValidarTexto(nombreB, TAM);
    }
}

int busqueda(char nombreB[], char nombre[][TAM],int ce){
    int pos=-1, flag=0, i=0;
    while (flag==0 && i<ce)
    {
        if (strcmpi(nombreB, nombre[i])==0)
        {
            flag=1;
            pos=i;
        }
        i++;
    }
    return pos;
}

int ingreso(char nombres[][TAM], int dni[], int ce){
    char nombreAux[TAM];
    int i=0;
    printf("Ingrese nombre del alumno: ");
    leeryValidarTexto(nombreAux, TAM);
    while (strcmpi(nombreAux, "FIN")!=0 && i<ce)
    {
        printf("Ingrese el DNI del alumno: ");
        leeyvalidaE2(&dni[i], 10000000, 99999999);
        strcpy(nombres[i], nombreAux);
        i++;
        printf("Ingrese nombre del alumno: ");
        leeryValidarTexto(nombreAux, TAM);
    }
    
    return i;
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
        printf("El texto no puede ser vacio. Reingrese: ");
        leerTexto(texto, largo);
    }
    
}

void leeyvalidaE2(int *dato,int min, int max){
    scanf("%d", dato);
    while (*dato<min || *dato>max)
    {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
}