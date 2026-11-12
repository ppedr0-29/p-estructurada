/*Ejercicio 1. El banco “Del Plata” tiene el archivo binario cuentas.dat con los siguientes datos por cuenta:
Número de cuenta (entero)
Titular (hasta 40 caracteres)
Tipo (carácter: ‘C’ cuenta corriente, ‘A’ caja de ahorro)
Saldo (float)
Cantidad de movimientos (entero)

Se solicita:
a) Ingresar por teclado un monto fijo de cargo de mantenimiento (mayor a 0) y descontarlo del saldo de todas las cuentas corrientes (‘C’). 
La modificación debe hacerse sobre el propio archivo, mientras se lee.
b) Copiar a otro archivo, descubiertos.dat, el registro completo de las cuentas cuyo saldo haya quedado negativo después del cargo.
c) Informar, mediante una función, la cantidad de registros de descubiertos.dat.
d) Explicar con sus palabras cómo se hace la eliminación lógica de un registro y en qué se diferencia de la física.*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int id;
    char titular[41];
    char tipo;
    float saldo;
    int cantMov;
}BANCO;

void procesarArchivo();
void nuevoArchivo();
int cantRegistros(FILE *, int);
void leeyvalidaFloat(float *, int);
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarArchivo();
    nuevoArchivo();

    return 0;
}

void procesarArchivo(){
    FILE *arch=abrirArchivo("cuentas.dat", "r+b");
    BANCO datos;
    float montoFijo;
    printf("Ingrese monto fijo de cargo por mantenimiento: ");
    leeyvalidaFloat(&montoFijo, 0);

    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.tipo=='C')
        {
            datos.saldo-=montoFijo;
            fseek(arch, -(long)sizeof(datos), SEEK_CUR);
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    fclose(arch);
}

void nuevoArchivo(){
    FILE *arch=abrirArchivo("cuentas.dat", "rb");
    FILE *archN=abrirArchivo("descubiertos.dat", "wb");
    int cantR;
    BANCO datos;
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        if (datos.saldo<0)
        {
            fwrite(&datos, sizeof(datos), 1, archN);
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    cantR=cantRegistros(archN, sizeof(datos));
    printf("La cantidad de descubiertos es %d\n", cantR);
    fclose(arch);
    fclose(archN);
}

int cantRegistros(FILE *arch, int tam){
    int cant;
    fseek(arch, 0, SEEK_END);
    cant=ftell(arch)/tam;
    return cant;
}

void leeyvalidaFloat(float *dato, int lim){
    scanf("%f", dato);
    while (*dato<=lim)
    {
        printf("Error. Reingrese: ");
        scanf("%f", dato);
    }
}

FILE *abrirArchivo(char nombre[], char tipo[]){
    FILE *arch=fopen(nombre, tipo);
    if (arch==NULL)
    {
        printf("Error.");
        getch();
        exit(1);
    }
    return arch;
}