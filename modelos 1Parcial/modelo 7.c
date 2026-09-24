/*Ejercicio 2: Estructuras, Memoria Dinámica y Strings
Una tienda de informática necesita gestionar el inventario de sus componentes de hardware (placas de video como la RX 570, 
módulos de memoria RAM de 16GB, etc.). Cada componente se define con la siguiente estructura:
Código de Producto: Cadena de 6 caracteres con el formato estricto "PC-999" (las letras 'P' y 'C', un guion, y tres dígitos numéricos).
Descripción: Cadena de hasta 40 caracteres.
Capacidad (GB): Entero mayor a 0.
Stock Disponible: Entero.

Se solicita:
Carga Inicial: Ingresar los componentes en un arreglo de estructuras asignado dinámicamente. 
La capacidad inicial debe ser de 5 componentes. Si el arreglo se llena, su capacidad debe incrementarse dinámicamente de 5 en 5.
Validaciones de Carga: Al ingresar el Código, validar que cumpla exactamente con el formato alfanumérico estipulado y 
que no exista previamente en el inventario. La carga finaliza al ingresar el código "FIN-00".
Despacho de Hardware: Finalizada la carga, procesar los despachos del día. 
Se ingresará repetidamente el Código del componente y la Cantidad a despachar (finalizando con código "FIN-00").

Si el código existe, verificar si hay stock suficiente. Si lo hay, restar la cantidad despachada. 
Si no lo hay, mostrar un mensaje de "Stock insuficiente".

Si el código no existe, contabilizarlo como "Solicitud de producto no registrado".

Listado Final: Al terminar los despachos, emitir un informe con todos los componentes ordenado de forma descendente 
según la Capacidad (GB). Informar también el total de solicitudes de productos no registrados.

Requisitos: Implementar de forma obligatoria las funciones modulares para la validación del formato del string, 
la búsqueda secuencial y el ordenamiento por burbujeo. Gestionar y liberar correctamente la memoria dinámica.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define TXT 7
#define TXT2 41

typedef struct
{
    char cod[TXT];
    char desc[TXT2];
    int cap;
    int stockDispo;
}INVENTARIO;

INVENTARIO *INGRESO(INVENTARIO *, int *, int *);
INVENTARIO ingresoDatos(INVENTARIO *, int *);
void despachoHw(INVENTARIO *, int *);
void listadoGB(INVENTARIO *, int *);
void burbujeo(INVENTARIO *, int *);
void intercambiar(INVENTARIO *, INVENTARIO *);
int busqueda(INVENTARIO *, char [], int *);
void leeryvalidarInt(int *, int);
void leeryvalidarTextoNombre(char [], int);
void leeryvalidarTexto(char [], int);
void leerTexto(char [], int);
int leeryvalidarCod(char []);

int main(){
    INVENTARIO *datos;
    int capIni=5, cantComponentes=0;
    datos=(INVENTARIO*)malloc(capIni*sizeof(INVENTARIO));
    if (datos==NULL)
    {
        printf("Error al reservar memoria.");
        exit(1);
    }
    datos=INGRESO(datos, &capIni, &cantComponentes);
    despachoHw(datos, &cantComponentes);
    listadoGB(datos, &cantComponentes);

    free(datos);

    return 0;
}

INVENTARIO *INGRESO(INVENTARIO *datos, int *mem, int *ce){
    INVENTARIO aux;
    int i=0;
    aux=ingresoDatos(datos, &i);
    while (strcmpi(aux.cod, "FIN-00")!=0)
    {
        if (i==*mem)
        {   
            printf("Capacidad maxima alcanzada. Ampliando...\n");
            *mem+=5;
            datos=(INVENTARIO*)realloc(datos, *mem*sizeof(INVENTARIO));
            if (datos==NULL)
            {
                printf("Error al reservar memoria.");
                exit(1);
            }else{
                printf("Capacidad reservada con exito.\n");
            }
        }
        *(datos+i)=aux;
        i++;
        aux=ingresoDatos(datos, &i);
    }
    *ce=i;
    return datos;
}

INVENTARIO ingresoDatos(INVENTARIO *datos, int *ce){
    INVENTARIO aux;
    printf("Ingrese codigo del componente(Formato PC-999 o FIN-00 para terminar): ");
    leeryvalidarTexto(aux.cod, TXT);
    while (strcmpi(aux.cod, "FIN-00") != 0 && (leeryvalidarCod(aux.cod) == 0 || busqueda(datos, aux.cod, ce) != -1))
    {
        if (leeryvalidarCod(aux.cod)==0)
        {
            printf("Error de formato. Reingrese: ");
        }else{
            printf("El codigo ya existe. Reingrese: ");
        }
        leeryvalidarTexto(aux.cod, TXT);
    }
        if (strcmpi(aux.cod, "FIN-00")!=0)
        {
            printf("Ingrese descripcion del componente: ");
            leeryvalidarTextoNombre(aux.desc, TXT2);
            printf("Ingrese capacidad en GB: ");
            leeryvalidarInt(&aux.cap, 1);
            printf("Ingrese stock disponible: ");
            leeryvalidarInt(&aux.stockDispo, 0);
        }
    return aux;
}

void despachoHw(INVENTARIO *datos, int *ce){
    char cod[TXT];
    int cantD, pos, noRegistrados=0;
    
    printf("--DESPACHO DE HARDWARE--\n");
    printf("Ingrese codigo a buscar (FIN-00 para salir): ");
    leeryvalidarTexto(cod, TXT);
    while (strcmpi(cod, "FIN-00") != 0)
    {
        if (leeryvalidarCod(cod) == 0) 
        {
            printf("Error de formato. Debe ser PC-999.\n");
        }
        else
        {
            pos = busqueda(datos, cod, ce);
            if (pos != -1)
            {
                printf("Ingrese la cantidad a despachar: ");
                leeryvalidarInt(&cantD, 1);
                if ((datos+pos)->stockDispo >= cantD)
                {
                    (datos+pos)->stockDispo -= cantD;
                    printf("Despacho realizado exitosamente.\n");
                }
                else
                {
                    printf("Stock insuficiente.\n");
                }
            }
            else
            {
                printf("Componente no registrado.\n");
                noRegistrados++;
            }
        }
        printf("\nIngrese codigo a despachar (o FIN-00 para salir): ");
        leeryvalidarTexto(cod, TXT);
    }
    printf("Total de solicitudes de productos no registrados: %d\n", noRegistrados);
}

void listadoGB(INVENTARIO *datos, int *ce){
    burbujeo(datos, ce);
    printf("\n--- LISTADO DE INVENTARIO (por Capacidad, descendente) ---\n");
    printf("%-8s %-25s %10s %10s\n", "Codigo", "Descripcion", "Cap(GB)", "Stock");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < *ce; i++)
    {
        printf("%-8s %-25s %10d %10d\n",(datos+i)->cod, (datos+i)->desc, (datos+i)->cap, (datos+i)->stockDispo);
    }
}

void burbujeo(INVENTARIO *datos, int *ce){
    int cota= *ce-1;
    int desordenado=1;
    while (desordenado)
    {
        desordenado=0;
        for (int j = 0; j < cota; j++)
        {
            if ((datos+j)->cap < (datos+j+1)->cap)
            {
                intercambiar(&datos[j], &datos[j+1]);
                desordenado=j;
            }
            
        }
        cota=desordenado;
    }
}

void intercambiar(INVENTARIO *a, INVENTARIO *b){
    INVENTARIO aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

int busqueda(INVENTARIO *datos, char cod[], int *ce){
    int pos=-1, i=0;
    while (pos==-1 && i<*ce)
    {
        if (strcmpi((datos+i)->cod, cod)==0)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

void leeryvalidarInt(int *dato, int lim){
    scanf("%d", dato);
    while (*dato<lim)
    {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
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
    while(strlen(texto)!=6)
    {
        printf("Error. Reingrese: ");
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

int leeryvalidarCod(char texto[]){
    int valida=1;
    if (texto[0]!='P' || texto[1]!='C' || texto[2]!='-')
        {
            valida=0;
        }else if (isdigit(texto[3])==0)
        {
            valida=0;
        }else if (isdigit(texto[4])==0)
        {
            valida=0;
        }else if (isdigit(texto[5])==0)
        {
            valida=0;
        }
    return valida;
}
