/*Ejercicio 2: Un centro odontológico administra la agenda de turnos para un día determinado. 
Cada turno se representa mediante una estructura con los siguientes datos:

DNI del Paciente (entero).
Nombre del Paciente (cadena de hasta 50 caracteres).
Estado del Turno (entero: 1 para "Pendiente", 2 para "Atendido", 3 para "Cancelado").

Se deben ingresar los datos de los turnos en un vector de estructuras asignado dinámicamente en memoria.
El arreglo debe comenzar con una capacidad inicial de 10 turnos.
Cada vez que el arreglo se llene, su capacidad debe aumentarse dinámicamente de 10 en 10.
Al ingresar el DNI se debe validar que el paciente no tenga ya un turno asignado en el vector. La carga finaliza con DNI = 0.

Finalizada la carga, se ingresará una secuencia de DNI de pacientes que van llegando a la recepción, terminando con DNI = 0.
Si el DNI existe, se debe cambiar el estado del turno a 2: "Atendido".
Si el DNI no existe, se lo contabilizará como "Paciente No Registrado".
Informar:
a) La cantidad total de pacientes que asistieron, pero no tenían turno.
b) El listado completo de la agenda ordenado de forma ascendente por DNI, mostrando DNI, Nombre y estado.
Implementar al menos dos funciones: Una para la búsqueda del DNI en el vector de estructuras, y otra para el ordenamiento.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TXT 51
typedef struct
{
    int dni;
    char nombre[TXT];
    int estado;
}AGENDA;

AGENDA* INGRESO(AGENDA*, int*, int*);
AGENDA ingreso(AGENDA*, int*);
void listado(AGENDA*, int*);
void recepcion(AGENDA*, int*);
void burbujeo(AGENDA*, int*);
int busqueda(AGENDA*, int, int*);
void leeyvalidarEstado(int*);
void leerTexto(char[], int);
void leeryValidarTexto(char[], int);
void leeyvalidarIntE2CF(int*, int, int, int);

int main(){
    AGENDA *datos;
    int capacidadIni=10;
    int cantVec=0;
    datos=(AGENDA*)malloc(capacidadIni*sizeof(AGENDA));
    if (datos==NULL)
    {
        printf("Error.");
        exit(1);
    }

    datos=INGRESO(datos, &capacidadIni, &cantVec);
    recepcion(datos, &cantVec);
    listado(datos, &cantVec);

    free(datos);

    return 0;
}

AGENDA *INGRESO(AGENDA *datos, int *mem, int *ce){
    AGENDA aux;
    int i=0;
    aux=ingreso(datos, ce);
    while (aux.dni!=0)
    {
        if (i==*mem)
        {
            *mem+=10;
            datos=(AGENDA*)realloc(datos, *mem*sizeof(AGENDA));
            if (datos==NULL)
            {
                printf("Error.");
                exit(1);
            }
        }
        *(datos+i)=aux;
        i++;
        aux=ingreso(datos, ce);
    }
    *ce=i;
    return datos;
}

AGENDA ingreso(AGENDA *datos, int *ce){
    AGENDA aux;
    printf("Ingrese DNI del paciente: ");
    leeyvalidarIntE2CF(&aux.dni, 10000000, 99999999,0);
    if (aux.dni!=0)
    {
        while (busqueda(datos, aux.dni, ce)!=-1)
        {
            printf("El DNI ya fue ingresado");
            leeyvalidarIntE2CF(&aux.dni, 10000000, 99999999,0);
        }
        if (aux.dni!=0)
        {
            printf("Ingrese nombre del paciente: ");
            leeryValidarTexto(aux.nombre, TXT);
            printf("Ingrese estado del turno: ");
            leeyvalidarEstado(&aux.estado);
        }
    }
    return aux;
}

void listado(AGENDA *datos, int *ce){
    burbujeo(datos, ce);
    printf("-LISTADO DE TURNOS-\n");
    printf("%8s %-30s %-6s\n", "DNI", "NOMBRE", "ESTADO");
    for (int i = 0; i < *ce; i++)
    {
        printf("%8d %-30s %-6d\n", (datos+i)->dni, (datos+i)->nombre, (datos+i)->estado);
    }
    
}

void recepcion(AGENDA *datos, int *ce){
    AGENDA recepcion;
    int pos, noregistado=0;;
    printf("--SALA DE RECEPCION--\n");
    printf("Ingrese DNI del paciente: ");
    leeyvalidarIntE2CF(&recepcion.dni, 10000000, 99999999, 0);
    while (recepcion.dni!=0)
    {
        pos=busqueda(datos, recepcion.dni, ce);
        if (pos!=-1)
        {
            (datos+pos)->estado=2;
        }else{
            noregistado++;
        }
        printf("Ingrese DNI del paciente: ");
        leeyvalidarIntE2CF(&recepcion.dni, 10000000, 99999999, 0);
    }
    printf("La cantidad de pacientes que asistieron pero no tenian turno son %d", noregistado);
}

void burbujeo(AGENDA *datos, int *ce){
    AGENDA aux;
    int j, cota= *ce-1;
    int desordenado=1;
    while (desordenado)
    {
        desordenado=0;
        for (j=0; j<cota; j++)
        {
            if ((datos+j)->dni > (datos+j+1)->dni)
            {
                aux=*(datos+j);
                *(datos+j)=*(datos+j+1);
                *(datos+j+1)=aux;
                desordenado=j;
            }
        }
        cota=desordenado;
    }
}

int busqueda(AGENDA *datos, int cod, int *ce){
    int pos=-1, i=0;
    while (pos==-1 && i<*ce)
    {
        if ((datos+i)->dni==cod)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

void leeyvalidarEstado(int *dato){
    scanf("%d", dato);
    while (*dato!=1 && *dato!=2 && *dato!=3)
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

void leeyvalidarIntE2CF(int *dato, int min, int max, int cf){
    scanf("%d", dato);
    while ((*dato<min || *dato>max) && *dato!=cf)
    {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
}