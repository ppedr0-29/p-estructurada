/*2. Una empresa que vende neumáticos desea realizar un programa para actualizar el total de ventas del mes de
sus productos. Para ello primeramente se ingresan la información de los productos formados por:
• Código (5 caracteres).
• Precio (real).
• Descripción (30 caracteres).
• Cantidad de unidades vendidas (al mes anterior, entero).
• Importe Total Vendido (al mes anterior, real).
Se sabe que la empresa no vende más de 50 productos. El ingreso de la carga de productos finaliza con un
producto con descripción “FIN”.
Luego ingresan las ventas del mes:
• Código de Producto (5 caracteres).
• Cantidad pedida.
El ingreso de datos de las ventas finaliza con una cantidad igual a 0. Se solicita:
a. Actualizar la información de los productos con las ventas realizadas en el mes.
b. Al finalizar, mostrar el listado de productos actualizado, informando:
DESCRIPCION CANTIDAD UNIDADES IMPORTE TOTAL
            VENDIDAS          VENDIDO
XXXXXXX XXXX $XXXXX,XX */

#include <stdio.h>
#include <string.h>
#define TAM 50

typedef struct
{
    char cod[6];
    float precio;
    char desc[31];
    int cantV;
    float imp;
}PRODUCTOS;

int ingresoProductos(PRODUCTOS [], int );
PRODUCTOS ingreso(PRODUCTOS [], int );
void cargaVentas(PRODUCTOS [], int );
void listado(PRODUCTOS [], int );
int busqueda(PRODUCTOS [], int , char []);
void leeyvalidaIntCF(int *, int );
void leeyvalidaInt(int *, int );
void leeyvalidaF(float *, int );
void leerTexto(char [], int );
void leeryValidarTexto(char [], int );

int main (){
    PRODUCTOS datos[TAM];
    int cantProductos= ingresoProductos(datos, TAM);
    cargaVentas(datos, cantProductos);
    listado(datos, cantProductos);
    return 0;
}

void listado(PRODUCTOS datos[], int ce){
    printf("\n%-31s  %-22s  %20s    ", "DESCRIPCION", "CANT.UNIDADES VENDIDAS", "IMPORTE TOTAL VENDIDO");
    for (int i = 0; i < ce; i++)
    {   
        printf("\n%-31s  %-22d  $%20.2f\n ", datos[i].desc, datos[i].cantV, datos[i].imp);
    }
    
}

void cargaVentas(PRODUCTOS datos[], int ce){
    PRODUCTOS aux;
    int pos;
    printf("--VENTAS DEL MES--\n");
    printf("Ingrese cantidad vendida(0 para cortar): ");
    leeyvalidaIntCF(&aux.cantV, 0);
    while (aux.cantV!=0)
    {
        printf("Ingrese codigo de producto: ");
        leeryValidarTexto(aux.cod, 6);
        pos=busqueda(datos, ce, aux.cod);
        if (pos!=-1)
        {
            datos[pos].cantV+=aux.cantV;
            datos[pos].imp+= (float)(aux.cantV*datos[pos].precio);
            printf("Producto actualizado.\n");
        }else{
            printf("Codigo no encontrado. ");
        }
        printf("Ingrese cantidad vendida(0 para cortar): ");
        leeyvalidaIntCF(&aux.cantV, 0);
    }
    printf("--VENTAS FINALIZADO--\n");
}

int ingresoProductos(PRODUCTOS datos[], int ce){
    int i=0;
    PRODUCTOS aux;
    printf("--INFORMACION DE LOS PRODUCTOS--\n");
    aux = ingreso(datos, i);
    while (strcmpi(aux.desc, "FIN")!=0 && i<ce)
    {
        datos[i] = aux;
        i++;
        aux = ingreso(datos, i);
    }
    printf("INGRESO FINALIZADO\n");
    return i;
}

PRODUCTOS ingreso(PRODUCTOS datos[], int i){
    PRODUCTOS aux;
    printf("Ingrese descripcion del producto: ");
    leeryValidarTexto(aux.desc, 31);
    if (strcmpi(aux.desc, "FIN")!=0)
    {
        printf("Ingrese codigo de producto: ");
        leeryValidarTexto(aux.cod, 6);
        while (busqueda(datos, i, aux.cod)!=-1)
        {
            printf("El codigo ya fue ingresado. Reingrese: ");
            leeryValidarTexto(aux.cod, 6);
        }
        printf("Ingrese precio del neumatico %s:", aux.cod);
        leeyvalidaF(&aux.precio, 1);
        printf("Ingrese cantidad de unidades vendidas el mes pasado: ");
        leeyvalidaInt(&aux.cantV, 0);
        printf("Ingrese importe total vendido el mes anterior: ");
        leeyvalidaF(&aux.imp, 0);
    }
    return aux;
}

void leeyvalidaIntCF(int *dato, int lim){
    scanf("%d", dato);
    while (*dato<lim && *dato!=0)
    {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
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

int busqueda(PRODUCTOS datos[], int cant, char cod[]){
    int pos=-1, i=0;
    while (pos==-1 && i<cant)
    {
        if (strcmpi(datos[i].cod, cod)==0)
        {
            pos=i;
        }
        i++;
    }
    return pos;
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