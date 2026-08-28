/*8. Se debe realizar un programa para ingresar los DNI de los asistentes a un evento. Se cargan todos los DNI
hasta que se recibe un DNI igual 0. Al finalizar mostrar el listado de todos los DNI ingresados. Los datos deben
almacenarse en un vector en memoria dinámica al no saber la cantidad comenzar con un vector de 5
elementos y si es necesario y el vector se llena ir aumentando la capacidad del vector de 5 en 5. */

/*--PSEUDOCODIGO--
int *vDni, cant=5
aux;
malloc
int i=0;
printf(Ingreso)
aux=leeryvalida
while(aux!=0){
    i++;
    if(i=cant){
        cant+=5;
        print(Ampliando)
        realloc
        print(Ampliado)
    }
    printf(Ingreso)
    aux=leeryvalida
}

mostrar();

free
*/

#include <stdio.h>
#include <stdlib.h>

void mostrarDNI(int *v, int);
void leeyvalidaE2CF(int *dato, int, int, int);

int main(){
    int *vDni, cant=5, i=0;
    
    vDni=(int*)malloc(cant*sizeof(int));
    
    if(vDni==NULL){
        printf("\n ERROR, programa finalizado.");
        exit(1);
    }
    
    printf("\n Ingrese el DNI deseado:");
    leeyvalidaE2CF(vDni+i, 10000000, 99999999, 0); 
    while (*(vDni+i)!=0)
    {
        i++;
        if (i==cant)
        {   
            cant+=5;
            printf("Ampliando capacidad a %d", cant);
            vDni=(int*)realloc(vDni,cant*sizeof(int));
            if (vDni==NULL)
            {
                printf("Error al ampliar memoria.");
                exit(1);
            }
        }
        printf("\n Ingrese el DNI deseado:");
        leeyvalidaE2CF(vDni+i, 10000000, 99999999, 0); 
    }
    
    mostrarDNI(vDni, i);
    free(vDni);
    
    return 0;
}

void mostrarDNI(int *v, int ce){
    for (int i = 0; i < ce; i++)
    {
        printf("DNI Invitado %d: %d\n", i+1, *(v+i));
    }
}

void leeyvalidaE2CF(int *dato, int min, int max, int cf){
    scanf("%d", dato);
    while ((*dato<min || *dato>max) && *dato!=cf)
    {
        printf("Error. Reingrese:");
        scanf("%d", dato);
    }

}