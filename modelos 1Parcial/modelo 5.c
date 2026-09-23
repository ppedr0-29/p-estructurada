/*Una estación de bomberos está a cargo de apagar los fuegos en la ciudad de Morón. 
Se tiene la estructura CasasPrendidasFuego, donde se carga la localidad (una cadena de 50 caracteres como maximo), 
la dirección (una cadena de 50 caracteres como maximo y debe incluir 4 digitos al final de la cadena) y la prioridad (un entero de 1 a 10). 

Los llamados de urgencia van llegando por numero de llamado y se desconoce cuantos llamados pueden ser. 

Dado a que los llamados llegan todos uno tras otro, es imposible preparar una misión organizada llamado tras llamado

El equipo de bomberos te solicita que, tras terminar la carga de casas prendidas fuego (terminando con la dirección MORON) 

1.- Muestres las casas prendidas fuego más importantes según su orden de prioridad, así el equipo de bomberos puede dirigirse 
lo antes posible

2.- Si existen casas repetidas en una misma localidad, entonces realizar un ordenamiento por la cantidad de casas 
que existan por cada municipio y mostrar el listado*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TXT 51

typedef struct
{
    char localidad[TXT];
    char direccion[TXT];
    int prioridad;
}CasasPrendidasFuego;


int main(){
    CasasPrendidasFuego *datos=NULL;
    int capIni=1, cantCasas=0;
    datos=(CasasPrendidasFuego*)malloc(capIni*sizeof(CasasPrendidasFuego));
    if (datos==NULL)
    {
        printf("Error al resevar memoria.");
        exit(1);
    }
    
    datos=INGRESO(datos, &capIni, &cantCasas);

    return 0;
}

CasasPrendidasFuego *INGRESO(CasasPrendidasFuego *datos, int *mem, int *ce){
    CasasPrendidasFuego aux;
    int i=0;
    aux=ingreso(datos);
    while (strcmpi(aux.direccion, "MORON")!=0)
    {
        if (i==*mem)
        {
            *mem+=1;
            datos=(CasasPrendidasFuego*)realloc(datos, *mem*sizeof(CasasPrendidasFuego));
            if (datos==NULL)
            {
                printf("Error al resevar memoria.");
                exit(1);
            }
        }
        *(datos+i)=aux;
        i++;
        aux=ingreso(datos);
    }
    *ce=i;
    return datos;
}

CasasPrendidasFuego ingreso(CasasPrendidasFuego *datos){
    CasasPrendidasFuego aux;
    printf("Ingrese la direccion: ");
    leeryvalidarTexto(aux.direccion, TXT);
    while (strcmpi(aux.direccion, "MORON")!=0 && validarDireccion(aux.direccion)==0)
        {
            printf("Error. Reingrese: ");
            leeryvalidarTexto(aux.direccion, TXT);
        }
    if (strcmpi(aux.direccion, "MORON")!=0)
    {
        
        printf("Ingrese localidad: ");
        leeryvalidarTexto(aux.localidad, TXT);
        printf("Ingrese prioridad (1-10): ");
        leeyvalidaIntE2(&aux.prioridad, 1, 10);
    }
    return aux;
}

void repetidas(CasasPrendidasFuego *datos, int *ce){
    char localidades[*ce][TXT];
    int contador[*ce];
    int cantLocalidades=0;
    int pos, i;

    for (i=0; i<*ce; i++)
    {
        pos=busquedaLocalidad(localidades, cantLocalidades, (datos+i)->localidad);
        if (pos==-1)
        {
            strcpy(localidades[cantLocalidades], (datos+i)->localidad);
            contador[cantLocalidades]=1;
            cantLocalidades++;
        }
        else
        {
            contador[pos]++;
        }
    }
}

int busquedaLocalidad(char localidades[][TXT], int cantLocalidades, char loc[]){
    int pos=-1, i=0;
    while (pos==-1 && i<cantLocalidades)
    {
        if (strcmpi(localidades[i], loc)==0)
        {
            pos=i;
        }
        i++;
    }
    return pos;
}

void casasxprioridadD(CasasPrendidasFuego *datos, int *ce){
    burbujeo(datos, ce);
    for (int i = 0; i < *ce; i++)
    {
        printf("La casa %s, %s tiene orden de prioridad %d\n", (datos+i)->direccion, (datos+i)->localidad, (datos+i)->prioridad);
    }
}

void burbujeo(CasasPrendidasFuego *datos, int *ce){
    int j, cota=*ce-1;
    int desordenado=1;
    while (desordenado)
    {
        desordenado=0;
        for (j = 0; j < cota; j++)
        {
            if ((datos+j)->prioridad>(datos+j+1)->prioridad)
            {
                intercambiar(&datos[j], &datos[j+1]);
                desordenado=j;
            }
            
        }
        cota=desordenado;
    }
}

void intercambiar(CasasPrendidasFuego *a, CasasPrendidasFuego *b){
    CasasPrendidasFuego aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

void leeyvalidaIntE2(int *dato, int min, int max){
    scanf("%d", dato);
    while (*dato<min || *dato>max)
    {
        printf("Error. Reingrese prioridad: ");
        scanf("%d", dato);
    }
}

int validarDireccion(char texto[]){
    int valido=1;
    int largo=strlen(texto);
    int i=largo-4;
    if (largo<4)
    {
        valido=0;
    }
    while (valido==1 && i<largo)
    {
        if (isdigit(texto[i])==0)
        {
            valido=0;
        }
        i++;
    }
    return valido;
}

void leerTexto(char texto[], int largo){
    fflush(stdin);
    fgets(texto, largo, stdin);
    int i=0;
    while (texto[i]!='\0')
    {
        if (texto[i]=='\n')
        {
            texto[i]='\0';
        }
        i++;
    }
}

void leeryvalidarTexto(char texto[], int largo){
    leerTexto(texto, largo);
    while (strlen(texto)==0)
    {
        printf("El texto no puede ser vacio. Reingrese: ");
        leerTexto(texto, largo);
    }
}