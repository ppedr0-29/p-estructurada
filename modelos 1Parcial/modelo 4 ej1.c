/* Ejercicio 1 
Un local de electrodomésticos necesita un programa para actualizar el inventario y las ventas mensuales de sus artículos.
Primeramente, se ingresa la información de los productos existentes, cada uno compuesto por:
·       Código (entero)
·       Descripción (cadena de hasta 30 caracteres)
·       Precio Unitario (número real)
·       Unidades Vendidas (acumuladas hasta el mes anterior, entero)
·       Monto Total Recaudado (acumulado hasta el mes anterior, real)
Se sabe que el comercio maneja un máximo de 80 productos. La carga inicial de productos finaliza cuando se ingresa un código 0 .
A continuación, se procesan los comprobantes de venta del mes actual. Por cada venta se ingresa:
•             Código de Producto (entero)
•             Cantidad Vendida (entero)
El ingreso de las ventas del mes finaliza cuando la cantidad vendida es igual a 0. Validar los datos ingresados
Se solicita:
1. Actualización: Por cada venta procesada, buscar el producto por su código y actualizar la cantidad total de unidades vendidas y 
el importe total recaudado. (Nota: Si el código ingresado no existe, mostrar un mensaje de advertencia).
2. Listado Final: Al terminar el ingreso de ventas, emitir un informe con todos los productos registrados que contenga:
CÓDIGO: XXXXX DESCRIPCIÓN: XXXXXXXXXXXXXXXXXXXXXXXXXX | UNIDADES TOTALES: XXXX | MONTO TOTAL: $XXXXX.XX */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 80
#define LARGO 31

typedef struct
{
    int cod;
    char desc[31];
    float precioUnidad;
    int unidadesV;
    float total;
}PROD;

typedef struct
{
    int codigo;
    int cantV;
}VENTAS;

//parametrizar
int IngresoProd(PROD[], int);
PROD ingreso(PROD[], int);
void ventas(PROD[], int);
void listado(PROD[], int);
int busqueda(PROD[], int, int);
void leeyvalidaInt(int*, int);
void leeyvalidaF(float*, int);
void leerTexto(char[], int);
void leeryValidarTexto(char[], int);

int main(){
    PROD datos[TAM];
    int cantProductos;
    cantProductos=IngresoProd(datos, TAM);
    ventas(datos, cantProductos);
    listado(datos, cantProductos);
}

int IngresoProd(PROD datos[], int ce){
    PROD aux;
    int i=0;
    printf("--INVENTARIO DE PRODUCTOS--\n");
    aux=ingreso(datos, i);
    while (aux.cod!=0 && i<ce)
    {
        datos[i]=aux;
        i++;
        aux=ingreso(datos, i);
    }
    return i;
}

PROD ingreso(PROD datos[], int i){
    PROD aux;
    printf("Ingrese codigo de producto: ");
    leeyvalidaInt(&aux.cod, 0);
    if (aux.cod!=0)
    {
        while (busqueda(datos, aux.cod, i)!=-1)
        {
            printf("El codigo ya existe. Reingrese: ");
            leeyvalidaInt(&aux.cod, 0);
        }
        if (aux.cod!=0)
        {
            printf("Ingrese descripcion del producto: ");
            leeryValidarTexto(aux.desc, LARGO);
            printf("Ingrese precio por unidad: ");
            leeyvalidaF(&aux.precioUnidad, 0);
            printf("Ingrese unidades vendidas acumuladas hasta el mes anterior: ");
            leeyvalidaInt(&aux.unidadesV, 0);
            printf("Ingrese total recaudado acumulado hasta el mes anterior: ");
            leeyvalidaF(&aux.total, 0);
        }
    }
    return aux;
}

void ventas(PROD datos[], int ce){
    VENTAS info;
    int pos;
    printf("--VENTAS MES ACTUAL--\n");
    printf("Ingrese cantidad vendida: ");
    leeyvalidaInt(&info.cantV, 0);
    while (info.cantV!=0)
    {   
        printf("Ingrese codigo de producto: ");
        leeyvalidaInt(&info.codigo, 0);
        pos=busqueda(datos, info.codigo, ce);
        if (pos!=-1)
        {
            datos[pos].unidadesV+=info.cantV;
            datos[pos].total+=(float)(datos[pos].precioUnidad*info.cantV);
            printf("Venta procesada con exito.");
        }else{
            printf("El codigo no existe. ");
        }
        printf("Ingrese cantidad vendida: ");
        leeyvalidaInt(&info.cantV, 0);
    }
}

void listado(PROD datos[], int ce){
    for (int i = 0; i < ce; i++)
    {
        printf("CÓDIGO: %d DESCRIPCIÓN: %s | UNIDADES TOTALES: %d | MONTO TOTAL: $%.2f\n", datos[i].cod, datos[i].desc, datos[i].unidadesV, datos[i].total);
    }
}

int busqueda(PROD datos[], int cod, int ce){
    int pos=-1, i=0;
    while (pos==-1 && i<ce)
    {
        if (datos[i].cod==cod)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

void leeyvalidaInt(int *dato, int lim){
    scanf("%d", dato);
    while (*dato<lim)
    {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
}

void leeyvalidaF(float *dato, int lim){
    scanf("%f", dato);
    while (*dato<lim)
    {
        printf("Error. Reingrese: ");
        scanf("%f", dato);
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