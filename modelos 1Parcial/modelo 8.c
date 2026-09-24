/*Definir un registro que almacene los datos de un empleado:   
Legajo (cadena con formato estricto XX/00).
Nombre.
Proyecto (carácter 'S', 'I' o 'H').
Horas (entero mayor a 0).
2. Carga Inicial:
Cargar un vector con exactamente 20 empleados de forma validada y asegurando que no existan legajos duplicados.
3. Actualización y Altas:Permitir el ingreso continuo de legajos hasta leer la condición de corte "FF/00".
Si el legajo existe: Solicitar una cantidad de horas y sumarlas al total de ese empleado.
Si no existe: Darlo de alta en el vector como empleado nuevo, solicitando y validando el resto de su información.
4. Reporte Final:Al finalizar el ciclo de actualización, informar:
La sumatoria total de horas trabajadas por cada uno de los proyectos ('S', 'I', 'H').
La cantidad de empleados nuevos que fueron dados de alta.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define TAM 5
#define TXT 6

typedef struct
{
    char legajo[TXT];
    char nombre[31];
    char proyecto;
    int horas;
}EMPLEADO;

EMPLEADO *actualizacion(EMPLEADO *, int *, int *, int *);
void informe(EMPLEADO *, int *, int *);
EMPLEADO *ingresoDatos(EMPLEADO *, int *, int);
EMPLEADO ingreso(EMPLEADO *, int);
int busqueda(EMPLEADO *, char [], int);
void leeyvalidaInt(int *, int);
void valChar(char *);
int valCod(char [], int);
void leerTexto(char [], int);
void leeryValidarNombre(char [], int);
void leeryValidarCod(char [], int);

int main(){
    EMPLEADO *datos=NULL;
    int capIni=TAM, cantEmpleados=0, nuevo=0;
    datos=(EMPLEADO*)malloc(capIni*sizeof(EMPLEADO));
    if (datos==NULL)
    {
        printf("Error.");
        exit(1);
    }
    datos=ingresoDatos(datos, &cantEmpleados, capIni);
    datos=actualizacion(datos, &capIni, &cantEmpleados, &nuevo);
    informe(datos, &cantEmpleados, &nuevo);

    free(datos);
    return 0;
}

EMPLEADO *actualizacion(EMPLEADO *datos, int *mem, int *ce, int *nuevo){
    EMPLEADO aux;
    EMPLEADO *auxR;
    int pos;
    printf("--ACTUALIZACION Y ALTAS--\n");
    printf("Ingrese codigo de legajo(FF/00 para terminar): ");
    leeryValidarCod(aux.legajo, TXT);
    while (valCod(aux.legajo, 5)==1 && strcmpi(aux.legajo, "FF/00")!=0)
    {
        pos=busqueda(datos, aux.legajo, *ce);
        if (pos!=-1)
        {
            printf("Ingrese cantidad de horas a actualizar: ");
            leeyvalidaInt(&aux.horas, 1);
            (datos+pos)->horas += aux.horas;
            printf("Horas actualizadas.\n");
        }else{
            if (*ce==*mem)
            {
                (*mem)++;
                auxR=(EMPLEADO*)realloc(datos, *mem*sizeof(EMPLEADO));
                if (auxR!=NULL)
                {   
                    printf("Agregando al empleado...\n");
                    datos=auxR;
                }else{
                    printf("No pudo reservarse memoria.\n");
                    exit(1);
                }
                
            }
            strcpy((datos+*ce)->legajo, aux.legajo);
            printf("Ingrese nombre del empleado: ");
            leeryValidarNombre(aux.nombre, 31);
            printf("Ingrese proyecto: ");
            valChar(&(datos+*ce)->proyecto);
            printf("Ingrese horas del empleado: ");
            leeyvalidaInt(&(datos+*ce)->horas, 1);
            (*nuevo)++;
            (*ce)++;
        }
        printf("Ingrese codigo de legajo(FF/00 para terminar): ");
        leeryValidarCod(aux.legajo, TXT);
        while (valCod(aux.legajo, 5) == 0)
        {
            printf("Error de formato. Reingrese: ");
            leeryValidarCod(aux.legajo, TXT);
        }
    }
    return datos;
}

void informe(EMPLEADO *datos, int *ce, int *nuevo){
    int cantS=0, cantI=0, cantH=0;
    for (int i = 0; i < *ce; i++)
    {
        switch ((datos+i)->proyecto)
        {
        case 'S':
            cantS+=(datos+i)->horas;
            break;
        case 'I':
            cantI+=(datos+i)->horas;
            break;
        case 'H':
            cantH+=(datos+i)->horas;
            break;
        default:
            break;
        }
    }
    printf("La cantidad para el proyecto S es %d\n", cantS);
    printf("La cantidad para el proyecto I es %d\n", cantI);
    printf("La cantidad para el proyecto H es %d\n", cantH);
    printf("La cantidad de empleados nuevos fueron %d", *nuevo);
}

EMPLEADO *ingresoDatos(EMPLEADO *datos, int *ce, int mem){
    int i;
    printf("--REGISTRO EMPLEADOS--\n");
    for (i = 0; i < mem; i++)
    {
        *(datos+i)=ingreso(datos, i);
    }
    *ce=i;
    return datos;
}

EMPLEADO ingreso(EMPLEADO *datos, int ce){
    EMPLEADO aux;
    printf("Ingrese codigo de legajo(XX/00): ");
    leeryValidarCod(aux.legajo, TXT);
    while (valCod(aux.legajo, 5)==0 || busqueda(datos, aux.legajo, ce)!=-1)
    {
        printf("Error, el codigo ya existe o el formato es invalido. Reingrese: ");
        leeryValidarCod(aux.legajo, TXT);
    }
    printf("Ingrese nombre del empleado: ");
    leeryValidarNombre(aux.nombre, 31);
    printf("Ingrese proyecto (S-I-H):");
    valChar(&aux.proyecto);
    printf("Ingrese horas del empleado: ");
    leeyvalidaInt(&aux.horas, 1);
    return aux;
}

int busqueda(EMPLEADO *datos, char dato[], int ce){
    int pos=-1, i=0;
    while (pos==-1 && i<ce)
    {
        if (strcmpi((datos+i)->legajo, dato)==0) pos=i;
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

void valChar(char *dato){
    scanf(" %c", dato);
    *dato=toupper(*dato);
    while (*dato!='S' && *dato!='I' && *dato!='H')
    {
        printf("Error. Reingrese el proyecto: ");
        scanf(" %c", dato);
        *dato=toupper(*dato);
    }
}

int valCod(char texto[], int ce){
    int valido=1, i=0;
    while (valido==1 && i<ce)
    {
        if (i<2)
        {
            if (isalpha(texto[i])==0)
            {
                valido=0;
            }else{
                texto[i]=toupper(texto[i]);
            }
        }else if(i==2){
            if (texto[i]!='/')
            {
                valido=0;
            }
        }else if(i>2){
            if (isdigit(texto[i])==0)
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

void leeryValidarNombre(char texto[], int largo){
    leerTexto(texto, largo);
    while (strlen(texto)==0)
    {
        printf("Error. Reingrese: ");
        leerTexto(texto, largo);
    }
}

void leeryValidarCod(char texto[], int largo){
    leerTexto(texto, largo);
    while (strlen(texto)!=5)
    {
        printf("Error. Reingrese: ");
        leerTexto(texto, largo);
    }
}