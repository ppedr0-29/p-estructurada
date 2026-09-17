/*Una clínica veterinaria requiere un programa en C para gestionar su inventario. 
El sistema debe reservar memoria dinámica inicialmente para 40 artículos. 
De cada producto se registra la siguiente información:
Código: Formato alfanumérico "XXX/000" (tres letras, una barra y tres números).
Nombre completo: Cadena de caracteres.
Tipo: Carácter validado ('A' Alimentos, 'V' Vacunas, 'C' Cuidados).
Inventario: Cantidad en stock (número real).
Luego de preparar el sistema, se comenzarán a registrar las compras de reposición. 
Por cada compra se ingresará el Código del artículo y la Cantidad comprada (validar que sea un real mayor a 0). 
El ingreso de compras finalizará al introducir el código "FFF/000".
Durante este proceso de compras, se debe contemplar lo siguiente:
Si el código ya existe en el arreglo, se debe actualizar su inventario sumando la cantidad comprada.
Si el código no existe, se debe dar de alta como un artículo nuevo, solicitando al usuario el nombre y el tipo, 
y redimensionando la memoria del arreglo para agregarlo.
Al finalizar el programa, se debe informar por pantalla:
La cantidad total acumulada en el inventario por cada Tipo de artículo.
La cantidad exacta de artículos nuevos que fueron añadidos al catálogo original.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
    char codigo[8];
    char nombre[31];
    char tipo;
    float cantStock;
}INVENTARIO;

typedef struct
{
    char cod[8];
    float cantComprada;
}COMPRAS;

INVENTARIO* ingresoCompras(INVENTARIO *, int *, int *);
INVENTARIO* INGRESO(INVENTARIO *, int *, int *);
INVENTARIO ingreso(INVENTARIO *, int *);
void informe(INVENTARIO *, int *);
int busqueda(INVENTARIO *, char [], int *);
void leeyvalidaF(float *, int);
void leeyvalchar(char *);
int valCod(char [], int);
void leerTexto(char [], int);
void leeryValidarTexto(char [], int);

int main(){
    INVENTARIO *datos;
    COMPRAS info;
    int capInicial=40;
    int cantVec=0;
    datos=(INVENTARIO*)malloc(capInicial*sizeof(INVENTARIO));
    if (datos==NULL)
    {
        printf("Error.");
        exit(1);
    }
    datos=INGRESO(datos, &capInicial, &cantVec);
    datos = ingresoCompras(datos, &cantVec, &capInicial);
    informe(datos, &cantVec);
    return 0;
}

INVENTARIO *ingresoCompras(INVENTARIO *datos, int *ce, int *mem){
    COMPRAS info;
    int pos;
    printf("--ACTUALIZACION DE INVENTARIO--\n");
    printf("Ingrese codigo de producto: ");
    leeryValidarTexto(info.cod, 8);
    while (valCod(info.cod, 8)==1 && strcmpi(info.cod, "FFF/000")!=0){
        pos=busqueda(datos, info.cod, ce);
        printf("Ingrese cantidad comprada: ");
            leeyvalidaF(&info.cantComprada, 1);
        if (pos!=-1)
        {
            (datos+pos)->cantStock+=info.cantComprada;
        }else{
                printf("Producto nuevo detectado.\n");
            if (*ce == *mem) {
                *mem += 10; 
                datos = (INVENTARIO*)realloc(datos, *mem * sizeof(INVENTARIO));
                if (datos == NULL) {
                    printf("Error al reservar memoria.");
                    exit(1);
                }
            }
            strcpy((datos+*ce)->codigo, info.cod); 
            printf("Ingrese nombre completo: ");
            leeryValidarTexto((datos+*ce)->nombre, 31);
            printf("Ingrese tipo A-V-C: ");
            leeyvalchar(&(datos+*ce)->tipo);
            (datos+*ce)->cantStock = info.cantComprada;
            (*ce)++; 
        }
        printf("Ingrese codigo de producto (FFF/000 para salir): ");
    leeryValidarTexto(info.cod, 8);
    while (valCod(info.cod, 8) == 0)
    {
        printf("Error de formato. Reingrese: ");
        leeryValidarTexto(info.cod, 8);
    }
    }
    return datos;
}

INVENTARIO *INGRESO(INVENTARIO *datos, int *mem, int *cant){
    int i;
    printf("--CARGA DE INVENTARIO--\n");
    for (i = 0; i < *mem; i++)
    {
        *(datos+i)=ingreso(datos, &i);
    }
    *cant=i;
    return datos;
}

INVENTARIO ingreso(INVENTARIO *datos, int *ce){
    INVENTARIO aux;
    printf("Ingrese el codigo(XXX/000):");
    leeryValidarTexto(aux.codigo, 8);
    while (valCod(aux.codigo, 8)==0 || busqueda(datos, aux.codigo, ce)!=-1)
    {
        printf("Error. Reingrese: ");
        leeryValidarTexto(aux.codigo, 8);
    }
        printf("Ingrese nombre completo");
        leeryValidarTexto(aux.nombre, 31);
        printf("Ingrese tipo A-V-C: ");
        leeyvalchar(&aux.tipo);
        printf("Ingrese cantidad en stock: ");
        leeyvalidaF(&aux.cantStock, 0);
    return aux;
}

void informe(INVENTARIO *datos, int *ce){
    float stockA=0, stockV=0, stockC=0;
    int nuevo= *ce-40;
    for (int i = 0; i < *ce; i++)
    {
        switch ((datos+i)->tipo)
        {
        case 'A':
            stockA+=(datos+i)->cantStock;
            break;
        case 'V':
            stockV+=(datos+i)->cantStock;
            break;
        case 'C':
            stockC+=(datos+i)->cantStock;
            break;
        default:
            break;
        }
    }
    printf("La cantidad para el tipo A es %.2f\n", stockA);
    printf("La cantidad para el tipo V es %.2f\n", stockV);
    printf("La cantidad para el tipo C es %.2f\n", stockC);
    printf("La cantidad de articulos nuevos fueron %d", nuevo);
}

int busqueda(INVENTARIO *datos, char cod[], int *ce){
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

void leeyvalidaF(float *dato, int lim){
    scanf("%f", dato);
    while (*dato<lim)
    {   
        printf("Error. Reingrese: ");
        scanf("%f", dato);
    }
    
}

void leeyvalchar(char *dato){
    fflush(stdin);
    scanf("%c", dato);
    *dato=toupper(*dato);
    while (*dato!='A' && *dato!='V' && *dato!='C')
    {
        printf("Error. Reingrese: ");
        fflush(stdin);
        scanf("%c", dato);
        *dato=toupper(*dato);
    }
}

int valCod(char dato[], int ce){
    int valido=1, i=0;
    while (valido==1 && i<ce-1)
    {
        if (i<=2)
        {
            if (isalpha(dato[i])==0)
            {
                valido=0;
            }
            
        }else if(i==3){
            if (dato[i]!='/')
            {
                valido=0;
            }
            
        }else if(i>3){
            if (isdigit(dato[i])==0)
            {
                valido=0;
            }
        }
        i++;
    }
    return valido;
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
    while (strlen(texto)!=largo-1)
    {
        printf("Error. Reingrese: ");
        leerTexto(texto, largo);
    }
}