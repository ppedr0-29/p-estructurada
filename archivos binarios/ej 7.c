/*7. Se dispone de un archivo llamado STOCK.dat que contiene la información de los productos que vende una
fábrica. En el archivo se guarda:
• Código de artículo (entero)
• Descripción (50 caracteres máximo)
• Stock (entero)
Luego se ingresan por teclado las ventas a realizar indicando:
• Código de artículo
• Cantidad
La carga por teclado de las ventas finaliza con un código de artículo igual a 0.
Por cada venta se debe controlar si hay stock suficiente y si lo hay, restar el stock de dicho producto, sino
hay stock se debe vender lo que quede disponible y grabar un registro en un archivo Faltantes.dat con la
cantidad que no pudo venderse, dicho registro debe contener:
• Código de artículo
• Cantidad faltante
Si ya hay un registro previo en dicho archivo de faltantes con el mismo producto debe incrementarse la
cantidad. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int cod;
    char desc[51];
    int stock;
}PROD;

typedef struct
{
    int codV;
    int cantFaltante;
}VENTAS;

void procesarVentas();
long busqueda(FILE *, int, PROD *);
long busquedaF(FILE *, int, VENTAS *);
void leeyvalidaInt(int *, int);
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarVentas();

    return 0;
}

void procesarVentas(){
    PROD datos;
    VENTAS info;
    int cantSoli, cant;
    FILE *arch;
    FILE *faltantes;
    PROD *pdatos=&datos;
    VENTAS *pinfo=&info;
    long pos;
    arch=abrirArchivo("STOCK.dat", "r+b");
    faltantes=fopen("Faltantes.dat", "r+b");
    if (faltantes==NULL){
        faltantes=abrirArchivo("Faltantes.dat", "w+b");
    }

    printf("--VENTAS--\n");
    printf("Ingrese codigo del articulo: ");
    leeyvalidaInt(&info.codV, 0);
    while (info.codV!=0)
    {
        pos=busqueda(arch, info.codV, pdatos);
        if (pos!=-1)
        {
            printf("Ingrese cantidad vendida del articulo %d: ", info.codV);
            leeyvalidaInt(&cantSoli, 1);
            if (datos.stock>=cantSoli)
            {
                datos.stock-=cantSoli;
                fseek(arch, pos*sizeof(datos), SEEK_SET);
                fwrite(&datos, sizeof(datos), 1, arch);
                fflush(arch);
            }else{
                cant=(datos.stock-cantSoli)*(-1);
                printf("Se vendio el stock disponible %d, falto %d\n", datos.stock, cant);
                datos.stock=0;
                fseek(arch, pos*sizeof(datos), SEEK_SET);
                fwrite(&datos, sizeof(datos), 1, arch);
                fflush(arch);
                pos=busquedaF(faltantes, info.codV, pinfo);
                if (pos==-1)
                {   
                    info.cantFaltante=cant;
                    printf("\nSe agrego el producto %d a la lista faltantes. Faltan: %d\n", info.codV, info.cantFaltante);
                    fseek(faltantes, 0, SEEK_END);
                    fwrite(&info, sizeof(info), 1, faltantes);
                    fflush(faltantes);
                }else{
                    info.cantFaltante+=cant;
                    printf("\nSe actualizo el producto %d en la lista faltantes. Faltan: %d\n", info.codV, info.cantFaltante);
                    fseek(faltantes, pos*sizeof(info), SEEK_SET);
                    fwrite(&info, sizeof(info), 1, faltantes);
                    fflush(faltantes);
                }
            }
        }else{
            printf("Codigo inexistente.");
        }
        printf("Ingrese codigo del articulo: ");
        leeyvalidaInt(&info.codV, 0);
    }
    
    fclose(arch);
    fclose(faltantes);

}


long busqueda(FILE *arch, int cod, PROD *pdatos){
    long pos=-1;
    PROD datos;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && pos==-1)
    {
        if (datos.cod==cod)
        {
            pos=ftell(arch)/sizeof(datos)-1;
            *pdatos=datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    
    return pos;
}

long busquedaF(FILE *arch, int cod, VENTAS *pinfo){
    VENTAS info;
    long pos=-1;
    rewind(arch);
    fread(&info, sizeof(info), 1, arch);
    while (!feof(arch) && pos==-1)
    {
        if (info.codV==cod)
        {
            pos=ftell(arch)/sizeof(info)-1;
            *pinfo=info;
        }
        fread(&info, sizeof(info), 1, arch);
    }
    return pos;
}

void leeyvalidaInt(int *dato, int lim){
    scanf("%d", dato);
    while (*dato < lim)
    {
        printf("Error, reingrese codigo:");
        scanf("%d", dato);
    }
}

FILE *abrirArchivo(char nombre[], char tipo[]){
    FILE *arch;
    arch=fopen(nombre, tipo);
    if (arch==NULL){
        printf("Error.");
        getch();
        exit(1);
    }
    return arch;
}