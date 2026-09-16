/*Una editorial desea gestionar su sistema de stock de libros. Para ello necesita manejar la siguiente información:
Por cada libro:
Código ISBN (entero de 8 dígitos)
Título (50 caracteres máximo)
Autor (40 caracteres máximo)
Cantidad de unidades en stock (entero)
La carga inicial de productos finaliza cuando se ingresa ISBN = 0.

Gestión de memoria:
a) Debido a que no se conoce la cantidad total de libros, se debe asignar un arreglo dinámico en memoria.
b) El arreglo debe comenzar con una capacidad inicial de 10 elementos.
c) Cada vez que el arreglo se llene, su capacidad debe aumentarse dinámicamente de 10 en 10.

Al finalizar el mes, se ingresan las ventas con los siguientes datos:
Código ISBN del libro
Cantidad vendida
Se pide hacer un programa que permita ingresar los datos de los libros considerando que se finaliza la carga cuando se ingresa el ISBN 0.
Luego, permitir ingresar las ventas considerando que no se van a ingresar más ventas cuando se ingrese el ISBN 0.
Se debe:
a. Actualizar el stock de cada libro con las ventas realizadas en el mes.
b. Al finalizar, mostrar el listado actualizado, informando:
ISBN              TITULO               AUTOR                STOCK ACTUALIZADO
99999999 XXXXXXXXXXXXXXXXXXXX XXXXXXXXXXXXXXXXXXXX        9999*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int codigo;
    char titulo[51];
    char autor[41];
    int cantStock;
}LIBRO;

typedef struct
{
    int cod;
    int cantV;
}VENTAS;

LIBRO* INGRESO(LIBRO *, int *, int *);
LIBRO ingreso(LIBRO *, int *);
void ventas(LIBRO *, int *);
int busqueda(LIBRO *, int , int *);
void listado(LIBRO *, int *);
void leeyvalidaInt(int *, int );
void leeyvalidaIntE2CF(int *, int , int , int );
void leerTexto(char [], int );
void leeryValidarTexto(char [], int );

int main(){
    LIBRO *datos;
    int capInicial=10;
    int cantLibros=0;
    datos=(LIBRO*)malloc(capInicial*sizeof(LIBRO));
    if (datos==NULL)
    {
        printf("Error al reservar memoria.");
        exit(1);
    }
    datos= INGRESO(datos, &capInicial, &cantLibros);
    ventas(datos, &cantLibros);
    listado(datos, &cantLibros);

    free(datos);

    return 0;
}

void listado(LIBRO *datos, int *ce){
    printf("%8s %-20s %-20s %17s\n", "ISBN", "TITULO", "AUTOR", "STOCK ACTUALIZADO");
    for (int i = 0; i < *ce; i++)
    {
        printf("%8d %-20s %-20s %17d\n", (datos+i)->codigo, (datos+i)->titulo, (datos+i)->autor ,(datos+i)->cantStock);
    }
}

void ventas(LIBRO *datos,int *ce){
    VENTAS info;
    int pos;
    printf("--ACTUALIZACION STOCK--\n");
    printf("Ingrese codigo ISBN: ");
    leeyvalidaIntE2CF(&info.cod, 10000000, 99999999, 0);
    while (info.cod!=0)
    {
        pos=busqueda(datos, info.cod, ce);
        if (pos!=-1)
        {   
            printf("Ingrese cantidad vendida: ");
            leeyvalidaInt(&info.cantV, 1);
            if ((datos+pos)->cantStock>=info.cantV)
            {
                (datos+pos)->cantStock-=info.cantV;
            }else{
                printf("La cantidad vendida supera el stock. ");
            }
        }else{
            printf("El codigo no existe. ");
        }
        printf("Ingrese codigo ISBN: ");
        leeyvalidaIntE2CF(&info.cod, 10000000, 99999999, 0);
    }
    printf("--Actualizacion finalizada.--\n");
}

int busqueda(LIBRO *datos, int cod, int *ce){
    int pos=-1, i=0;
    while (pos==-1 && i<*ce)
    {
        if ((datos+i)->codigo==cod)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

LIBRO* INGRESO(LIBRO *datos, int *mem, int *cantL){
    LIBRO aux;
    int i=0;
    printf("--INGRESO LIBROS--\n");
    aux=ingreso(datos, &i);
    while (aux.codigo!=0)
    {
        if(i==*mem){
            *mem+=10;
            datos=(LIBRO*)realloc(datos, *mem*sizeof(LIBRO));
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
    *cantL=i;
    return datos;
}

LIBRO ingreso(LIBRO *datos, int *ce){
    LIBRO aux;
    printf("Ingrese codigo ISBN: ");
    leeyvalidaIntE2CF(&aux.codigo, 10000000, 99999999, 0);
    if (aux.codigo!=0)
    {
        while (busqueda(datos, aux.codigo, ce)!=-1)
        {
            printf("Codigo ya ingresado. Reingrese: ");
            leeyvalidaIntE2CF(&aux.codigo, 10000000, 99999999, 0);
        }
        printf("Ingrese titulo del libro: ");
        leeryValidarTexto(aux.titulo, 51);
        printf("Ingrese autor del libro: ");
        leeryValidarTexto(aux.autor, 41);
        printf("Ingrese cantidad de stock: ");
        leeyvalidaInt(&aux.cantStock, 0);
    }
    return aux;
}

void leeyvalidaInt(int *dato, int lim){
    scanf("%d", dato);
    while (*dato<lim)
    {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
}

void leeyvalidaIntE2CF(int *dato, int min, int max, int cf){
    scanf("%d", dato);
    while ((*dato<min || *dato>max) && *dato!=cf)
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