/*Una inmobiliaria gestiona las visitas agendadas a propiedades en alquiler. 
Por cada visita se carga: 
Código de propiedad (formato alfanumérico "AAA-000", tres letras, un guion, tres números), 
Nombre del interesado (cadena) y 
Estado de la visita (carácter: 'P' Pendiente, 'C' Concretada, 'A' Anulada).
Los datos se cargan en un vector de estructuras hasta que se ingresa como código de propiedad "FIN".
Al ingresar un código, se debe validar el formato (las tres letras y el guion en la posición correcta, los tres dígitos finales).
Finalizada la carga, se solicita:
a) Informar la cantidad de visitas en cada estado ('P', 'C', 'A').
b) Listar únicamente las visitas Pendientes, ordenadas alfabéticamente por nombre del interesado (con burbujeo).
c) Implementar una función de búsqueda que, dado un código de propiedad ingresado por teclado, informe el nombre del interesado 
y el estado de esa visita (o un mensaje si no existe).*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define TXT 8

typedef struct 
{
    char codigo[TXT];
    char nombre[21];
    char estado;
}VISITA;

VISITA *INGRESO(VISITA *, int *, int *);
VISITA ingreso(VISITA *, int *);
void mensajeVisita(VISITA *, int *);
void listadoPendientes(VISITA *, int *);
void burbujeo(VISITA *, int *);
void intercambio(VISITA *, VISITA *);
void informarEstado(VISITA *, int *);
void leeryvalidarC(char *);
int busqueda(VISITA *, char [], int *);
void leeryvalidarTextoNombre(char [], int);
void leeryvalidarTexto(char [], int);
void leerTexto(char [], int);
int leeryvalidarCod(char [], int);

int main()
{
    VISITA *datos=NULL;
    int capInicial=10, cantVisitas=0;
    datos=(VISITA*)malloc(capInicial*sizeof(VISITA));
    if (datos==NULL)
    {
        printf("Error al reservar memoria.");
        exit(1);
    }
    datos=INGRESO(datos, &cantVisitas, &capInicial);
    informarEstado(datos, &cantVisitas);
    listadoPendientes(datos, &cantVisitas);
    mensajeVisita(datos, &cantVisitas);

    free(datos);

    return 0;
}

VISITA *INGRESO(VISITA *datos, int *ce, int *mem){
    VISITA aux;
    int i=0;
    aux=ingreso(datos, &i);
    while (strcmpi(aux.codigo, "FIN")!=0)
    {
        if (i==*mem)
        {
            *mem+=10;
            datos=(VISITA*)realloc(datos, *mem*sizeof(VISITA));
            if (datos==NULL)
            {
                printf("Error al reservar memoria.");
                exit(1);
            }
        }
        *(datos+i)=aux;
        i++;
        aux=ingreso(datos, &i);
    }
    *ce=i;
    return datos;
}

VISITA ingreso(VISITA *datos, int *ce)
{
    VISITA aux;
    printf("Ingrese el codigo (AAA-000): ");
    leeryvalidarTexto(aux.codigo, TXT);
    while (strcmpi(aux.codigo, "FIN")!=0 && (leeryvalidarCod(aux.codigo, TXT)==0 || busqueda(datos, aux.codigo, ce)!=-1))
    {
        if (leeryvalidarCod(aux.codigo, TXT)==0)
        {
            printf("Error de formato. Reingrese: ");
        }
        else
        {
            printf("El codigo ya fue ingresado. Reingrese: ");
        }
        leeryvalidarTexto(aux.codigo, TXT);
    }
        if (strcmpi(aux.codigo, "FIN")!=0)
        {
        printf("Ingrese nombre del interesado: ");
        leeryvalidarTextoNombre(aux.nombre, 21);
        printf("Ingrese el estado (P-C-A): ");
        leeryvalidarC(&aux.estado);
    }   
    return aux;
}

void mensajeVisita(VISITA *datos, int *ce)
{
    char cod[TXT];
    int pos;
    printf("--BUSQUEDA INTERESADO--\n");
    printf("Ingrese el codigo: ");
    leeryvalidarTexto(cod, TXT);
    while (leeryvalidarCod(cod, TXT)==0)
    {
        printf("Error de formato. Reingrese: ");
        leeryvalidarTexto(cod, TXT);
    }
    pos=busqueda(datos, cod, ce);
    if (pos!=-1)
    {
        printf("El nombre del interesado es %s y su visita se encuentra en estado %c\n", (datos+pos)->nombre, (datos+pos)->estado);
    }else{
        printf("El codigo no existe.");
    }
}

void listadoPendientes(VISITA *datos, int *ce)
{
    burbujeo(datos, ce);
    int acum=0;
    for (int i = 0; i < *ce; i++)
    {
        if ((datos+i)->estado=='P')
        {
            printf("Visita pendiente del interesado %s\n", (datos+i)->nombre);
            acum++;
        }
        
    }
    if (acum==0)
    {
        printf("No hay visitas pendientes.");
    }
}

void burbujeo(VISITA *datos, int *ce){
    int cota = *ce-1;
    int desordenado=1;
    while (desordenado)
    {
        desordenado=0;
        for (int j = 0; j < cota; j++)
        {
            if (strcmpi((datos+j)->nombre, (datos+j+1)->nombre)>0)
            {
                intercambio(&datos[j], &datos[j+1]);
                desordenado=j;
            }
        }
        cota=desordenado;
    }   
}

void intercambio(VISITA *a, VISITA *b){
    VISITA aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

void informarEstado(VISITA *datos, int *ce){
    int cantP=0, cantC=0, cantA=0;
    for (int i = 0; i < *ce; i++)
    {
        switch ((datos+i)->estado)
        {
        case 'P':
            cantP++;
            break;
        case 'C':
            cantC++;
            break;
        case 'A':
            cantA++;
            break;
        }
    }
    printf("La cantidad de visitas en P(Pendientes) fueron %d\n", cantP);
    printf("La cantidad de visitas en C(Concretadas) fueron %d\n", cantC);
    printf("La cantidad de visitas en A(Anulados) fueron %d\n", cantA);
}

void leeryvalidarC(char *dato){
    scanf(" %c", dato);
    *dato=toupper(*dato);
    while (*dato!='P' && *dato!='C' && *dato!='A')
    {
        printf("Error. Reingrese estado: ");
        scanf(" %c", dato);
        *dato=toupper(*dato);
    }
}

int busqueda(VISITA *datos, char cod[], int *ce){
    int pos=-1, i=0;
    while (pos==-1 && i<*ce)
    {
        if (strcmpi((datos+i)->codigo, cod)==0)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

void leeryvalidarTextoNombre(char texto[], int largo)
{
    leerTexto(texto, largo);
    while(strlen(texto)==0)
    {
        printf("Error. Reingrese");
        leerTexto(texto, largo);
    }
}

void leeryvalidarTexto(char texto[], int largo)
{
    leerTexto(texto, largo);
    while(strlen(texto)!=7 && strlen(texto)!=3)
    {
        printf("Error. Reingrese");
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

int leeryvalidarCod(char texto[], int ce){
    int valida=1, i=0;
    while (valida==1 && i<ce)
    {
        if (i<=2)
        {
            if (isalpha(texto[i])==0)
            {
                valida=0;
            }
        }else if (i==3)
        {
            if (texto[i]!='-')
            {
                valida=0;
            }
        }else if (i>3)
        {
            if (isdigit(texto[i])==0)
            {
                valida=0;
            }
        }
        i++;
    }
    return valida;
}
