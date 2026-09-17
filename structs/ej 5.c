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
X XXXXX XXXXXXXX $ XXXXXXXXX,XX*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM 100
#define COD_MIN 1000
#define COD_MAX 9999
#define COD_FIN 999
#define NYA_LEN 51

typedef struct
{
    int cod;
    char nya[NYA_LEN];
} CLIENTE;

void ingresoClientes(CLIENTE[], int);
CLIENTE ingreso(CLIENTE[], int);
int busqueda(CLIENTE[], int, int);
int IngresoVentas(CLIENTE[], int, int[], float[], int[]);
void ordenarPorFacturado(CLIENTE[], float[], int);
void listado(CLIENTE[], float[], int);
void mostrarVentasPorCliente(CLIENTE[], int[], int);
void mostrarVentasPorVendedor(int[], int);
int leeyvalidaInt(int);
int leeyvalidaIntE2(int, int);
int leeyvalidaIntE2CF(int, int, int);
float leeyvalidaF(float);
int leerTexto(char[], int);
int leeryValidarTexto(char[], int);

int main()
{
    CLIENTE datos[TAM];
    int cantVentasCliente[TAM] = {0};
    float totalFacturado[TAM] = {0};
    int ventasVendedor[10] = {0};
    int cantVentas;

    ingresoClientes(datos, TAM);
    cantVentas = IngresoVentas(datos, TAM, cantVentasCliente, totalFacturado, ventasVendedor);

    mostrarVentasPorCliente(datos, cantVentasCliente, TAM);
    mostrarVentasPorVendedor(ventasVendedor, 10);

    ordenarPorFacturado(datos, totalFacturado, TAM);
    listado(datos, totalFacturado, TAM);

    return 0;
}

void ingresoClientes(CLIENTE datos[], int ce)
{
    int i;

    for (i = 0; i < ce; i++)
    {
        datos[i] = ingreso(datos, i);
    }
}

CLIENTE ingreso(CLIENTE datos[], int i)
{
    CLIENTE aux;

    printf("Ingrese el numero de cliente: ");
    aux.cod = leeyvalidaIntE2(COD_MIN, COD_MAX);
    while (busqueda(datos, i, aux.cod) != -1)
    {
        printf("Cliente ya ingresado. Reingrese: ");
        aux.cod = leeyvalidaIntE2(COD_MIN, COD_MAX);
    }
    printf("Ingrese nombre y apellido del cliente: ");
    leeryValidarTexto(aux.nya, NYA_LEN);

    return aux;
}

int busqueda(CLIENTE datos[], int ce, int cod)
{
    int pos = -1, i = 0;

    while (pos == -1 && i < ce)
    {
        if (datos[i].cod == cod)
        {
            pos = i;
        }
        i++;
    }
    return pos;
}

int IngresoVentas(CLIENTE datos[], int ce, int cantVentasCliente[], float totalFacturado[], int ventasVendedor[])
{
    int cod, pos, vendedor, cant = 0;
    float importe;

    printf("--INGRESO VENTAS--\n");
    printf("Ingrese codigo de cliente (999 para terminar): ");
    cod = leeyvalidaIntE2CF(COD_MIN, COD_MAX, COD_FIN);
    while (cod != COD_FIN)
    {
        pos = busqueda(datos, ce, cod);
        if (pos != -1)
        {
            printf("Ingrese importe: ");
            importe = leeyvalidaF(1);
            printf("Ingrese numero de vendedor (1-10): ");
            vendedor = leeyvalidaIntE2(1, 10);

            cantVentasCliente[pos]++;
            totalFacturado[pos] += importe;
            ventasVendedor[vendedor - 1]++;
            cant++;
        }
        else
        {
            printf("El cliente no existe.\n");
        }
        printf("Ingrese codigo de cliente (999 para terminar): ");
        cod = leeyvalidaIntE2CF(COD_MIN, COD_MAX, COD_FIN);
    }
    return cant;
}

void ordenarPorFacturado(CLIENTE datos[], float totalFacturado[], int ce)
{
    int i, j;
    CLIENTE auxCliente;
    float auxFacturado;

    for (i = 0; i < ce - 1; i++)
    {
        for (j = 0; j < ce - 1 - i; j++)
        {
            if (totalFacturado[j] < totalFacturado[j + 1])
            {
                auxFacturado = totalFacturado[j];
                totalFacturado[j] = totalFacturado[j + 1];
                totalFacturado[j + 1] = auxFacturado;

                auxCliente = datos[j];
                datos[j] = datos[j + 1];
                datos[j + 1] = auxCliente;
            }
        }
    }
}

void listado(CLIENTE datos[], float totalFacturado[], int ce)
{
    int i;

    printf("%-10s%-30s%-20s\n", "CODIGO", "NOMBRE Y APELLIDO", "TOTAL FACTURADO");
    for (i = 0; i < ce; i++)
    {
        printf("%-10d%-30s$ %-18.2f\n", datos[i].cod, datos[i].nya, totalFacturado[i]);
    }
}

void mostrarVentasPorCliente(CLIENTE datos[], int cantVentasCliente[], int ce)
{
    int i;

    for (i = 0; i < ce; i++)
    {
        printf("%d ventas al cliente %d\n", cantVentasCliente[i], datos[i].cod);
    }
}

void mostrarVentasPorVendedor(int ventasVendedor[], int cant)
{
    int i;

    for (i = 0; i < cant; i++)
    {
        printf("%d ventas del vendedor %d\n", ventasVendedor[i], i + 1);
    }
}

int leeyvalidaInt(int lim)
{
    int dato;

    scanf("%d", &dato);
    while (dato < lim)
    {
        printf("Error. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}

int leeyvalidaIntE2(int min, int max)
{
    int dato;

    scanf("%d", &dato);
    while (dato < min || dato > max)
    {
        printf("Error. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}

int leeyvalidaIntE2CF(int min, int max, int cf)
{
    int dato;

    scanf("%d", &dato);
    while ((dato < min || dato > max) && dato != cf)
    {
        printf("Error. Reingrese: ");
        scanf("%d", &dato);
    }
    return dato;
}

float leeyvalidaF(float lim)
{
    float dato;

    scanf("%f", &dato);
    while (dato < lim)
    {
        printf("Error. Reingrese: ");
        scanf("%f", &dato);
    }
    return dato;
}

int leerTexto(char texto[], int largo)
{
    int i = 0;

    fflush(stdin);
    fgets(texto, largo, stdin);
    while (texto[i] != '\0')
    {
        if (texto[i] == '\n')
        {
            texto[i] = '\0';
        }
        else
        {
            i++;
        }
    }
    return i;
}

int leeryValidarTexto(char texto[], int largo)
{
    int len;

    len = leerTexto(texto, largo);
    while (len == 0)
    {
        printf("Error. Reingrese: ");
        len = leerTexto(texto, largo);
    }
    return len;
}