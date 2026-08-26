/*5. Al programa anterior agregarle una función que reciba la dirección de inicio del vector y un número a buscar
y retorne un puntero al dato encontrado o NULL sino lo encuentra. En el main agregar un proceso de
búsqueda que se repita hasta ingresar un número negativo o cero a buscar. Si se lo encontró se debe indicar
en qué posición del vector estaba (calcular dicha posición utilizando la dirección retornada) */

#include <stdio.h>

void cargarVector(int *, int);
void mostrarVector(int *, int);
int *busqueda(int *, int , int );

int main (){
    int v[10];
    int *pv=v;
    int numBusqueda, posencontrada;
    int *pos;
    cargarVector(pv, 10);
    mostrarVector(pv, 10);
    printf("Ingrese el numero a buscar(>=0 corta): ");
    scanf("%d", &numBusqueda);
    while (numBusqueda>0)
    {
        pos=busqueda(pv, numBusqueda, 10);
        if (pos==NULL)
        {
            printf("No se encontro. Reingrese:");
        }else{
            posencontrada=pos-pv;
            printf("Se encontraba en la posicion %d", posencontrada);
            printf("Ingrese el numero a buscar(>=0 corta): ");
        }
        scanf("%d", &numBusqueda);
    }
    printf("El programa finalizo.");

    return 0;
}

void cargarVector(int *pv, int ce){
    for (int i = 0; i < ce; i++)
    {
        printf("Ingrese un numero para la posicion %d: ", i+1);
        scanf("%d", (pv+i));
    }
}

void mostrarVector(int *pv, int ce){
    for (int i = 0; i < ce; i++)
    {
        printf("El valor es %d en la posicion %d\n", *(pv+i), i+1);
    }
    
}

int *busqueda(int *pv, int num, int ce){
    int i=0, pos=-1, *pr=NULL;
    while (pos==-1 && i<ce)
    {
        if (*(pv+i)==num)
        {
            pos=i;
            pr=pv+pos;
        }else{
            i++;
        }
    }
    return pr;
}