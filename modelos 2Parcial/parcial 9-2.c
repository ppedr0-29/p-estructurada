/* Una empresa distribuidora de energia electrica posee un archivo binario llamado "consumo.dat". 
Cada registro almacena la lectura de un medidor con el siguiente formato:
-Zona Geografica (int)
-Numero de Cliente (int)
-Consumo en kWh (float)

El archivo está ordenado por el campo Zona Geografica. 
Se solicita diseñar unn programa en C que lea el archivo secuencialmente y aplique Corte de Control para informar:
1- El consumo promedio de kWh por cada Zona Geografica.
2- Cual fue la Zona Geografica que registro el mayor consumo total de energia. */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int zona;
    int numCliente;
    float consumo;
}MEDIDOR;

void procesarCdC();
FILE *abrirArchivo(char[], char[]);

int main(){

    procesarCdC();

    return 0;
}

void procesarCdC(){
    FILE *arch=abrirArchivo("consumo.dat", "rb");
    MEDIDOR datos;
    int zonaAnterior, primero=1, zonaMayor, cant;
    float consumoProm, consumoTotal,mayorConsumo;

    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {   
        cant=0;
        consumoTotal=0;
        zonaAnterior=datos.zona;
        while (!feof(arch) && zonaAnterior==datos.zona)
        {   
            cant++;
            consumoTotal+=datos.consumo;
            fread(&datos, sizeof(datos), 1, arch);
        }
        consumoProm=consumoTotal/cant;
        printf("Zona %d con consumo promedio de %.2f\n", zonaAnterior, consumoProm);

        if (primero==1 || consumoTotal>mayorConsumo)
        {
            mayorConsumo=consumoTotal;
            primero=0;
            zonaMayor=zonaAnterior;
        }
    }
    printf("Zona %d que registro el mayor consumo con %.2f.\n", zonaMayor, mayorConsumo);
    fclose(arch);
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