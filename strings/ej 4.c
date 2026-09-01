/*4. Se ingresan código y precio unitario de los productos que vende un negocio. No se sabe la cantidad exacta de
productos, pero sí se sabe que son menos de 50. El código es alfanumérico de 3 caracteres y la carga de los
datos de productos termina con un código igual al “FIN”. Luego se registran las ventas del día y por cada venta
se ingresa el código de producto y cantidad de unidades vendidas terminando con una cantidad igual a 0. Se
solicita:
a. Calcular la recaudación total del día y el producto del cual se vendió menor cantidad de unidades.
b. Mostrar el listado de productos con su precio ordenado en forma alfabética por código de producto. */

#include <stdio.h>
#include <string.h>
#define TAM 50
#define TXT 4  

int main(){
    char cod[TAM][TXT];
    float precios[TAM];
    int cantProd=0;
    cantProd=cargaProductos(precios, cod);
}

int cargaProductos(float precio[], char cod[][TXT]){
    char codAux[TAM];
    int i=0;
    printf("Ingrese codigo de producto (FIN para terminar):");
    leeryValidarTexto(codAux, TXT);
    while (strcmpi(codAux, "FIN")!=0 && i<TAM)
    {   
        strcpy(cod[i], codAux);
        printf("Ingrese precio del producto: ");
        scanf("%f", &precio[i]);
        i++;
        printf("Ingrese codigo de producto (FIN para terminar):");
        leeryValidarTexto(codAux, 4);
    }
    
    return i;
}

void ventas(char cod[][TXT], int ce){
    char codV[TAM];
    int cant;
    printf("Ingrese codigo del producto: ");
    leeryValidarTexto(codV, TXT);
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
    while (strlen(texto)!=3)
    {
        printf("El texto ingresado no es correcto. Reingrese: ");
        leerTexto(texto, largo);
    }
    
}