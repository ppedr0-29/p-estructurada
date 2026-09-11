/*5. Se ingresan las ventas de un comercio de insumos de computación. Por cada venta se ingresa:
• Número de cliente (entero de 4 dígitos no correlativos).
• Importe (mayor a cero).
• Número de vendedor (entero de 1 a 10).
El ingreso de datos finaliza con un número de cliente 999.
Se sabe que no son más de 100 clientes, la carga de los clientes se debe realizar al inicio del programa con la
función CARGA_CLIENTE () y para cada uno se ingresa:
• Código de cliente (entero de 4 dígitos no correlativos).
• Nombre y Apellido (50 caracteres máximo).
Se solicita:
a. Determinar la cantidad de ventas realizadas por cliente.
b. La cantidad de ventas realizadas por vendedor.
c. Informar en forma ordenada por total facturado (modo descendente), el total facturado a cada
cliente, informando:
CODIGO DE CLIENTE NOMBRE Y APELLIDO TOTAL FACTURADO
X XXXXX XXXXXXXX $ XXXXXXXXX,XX */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM 100

typedef struct
{
    int cod; //numero de cliente
    char nya[51];
}CLIENTE;

typedef struct
{
    int cod; //numero de cliente
    float importe;
    int numVendedor;
}VENTAS;


int main(){
    CLIENTE datos[TAM];
    VENTAS *info;
    int capacidadInicial=5;
    info= (VENTAS *)malloc(capacidadInicial *sizeof(VENTAS));
    if (info==NULL)
    {
        printf("Error al reservar memoria.");
        exit(1);
    }
    

    return 0;
}

int ingresoClientes(CLIENTE datos[], int ce){
    int i;
    for (i = 0; i < ce; i++)
    {
        datos[i]=ingreso(datos, i);
    }
    return i;
}

CLIENTE ingreso(CLIENTE datos[], int i){
    CLIENTE aux;
    printf("Ingrese el numero de cliente: ");
    leeyvalidaIntE2(&aux.cod, 1000, 9999);
    while (busqueda(datos, i , aux.cod)!=-1)
    {
        printf("Cliente ya ingresado. Reingrese: ");
        leeyvalidaIntE2(&aux.cod, 1000, 9999);
    }
    printf("Ingrese nombre y apellido del cliente: ");
    leeryValidarTexto(aux.nya, 51);

    return aux;
}

int busqueda(CLIENTE datos[], int ce, int cod){
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

void leeyvalidaF(float *dato, int lim){
    scanf("%f", dato);
    while (*dato<lim)
    {
        printf("Error. Reingrese: ");
        scanf("%f", dato);
    }
}

void leeyvalidaIntE2(int *dato, int min, int max){
    scanf("%d", dato);
    while (*dato<min || *dato>max)
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
