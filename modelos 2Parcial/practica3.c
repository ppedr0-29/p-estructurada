/*En la empresa “Pedido Ya Mismo” tienen el archivo Repartos.dat con los siguientes datos: 
• Zona (entero) 
• Descripción (de hasta 50 caracteres) 
• Peso (float) en kilos por pedido 
Sabemos que el archivo está ordenado por zona y necesitamos conocer los siguientes datos: 
a. Las zonas que tengan menos de 15 kg en total. 
b. La zona que haya acumulado el mayor peso total de envíos. 
c. Generar un nuevo archivo binario llamado PesoTotal.dat que 
contenga un registro por cada zona incluyendo la zona y el peso total por zona.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
    int zona;
    char desc[51];
    float peso;
}PEYA;

typedef struct
{
    int zona;
    float pesoTxZ;
}PTOTAL;

void procesarArchivo();
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarArchivo();
}

void procesarArchivo(){
    FILE *arch=abrirArchivo("Repartos.dat", "rb");
    FILE *archT=abrirArchivo("PesoTotal.dat", "wb");
    PEYA datos;
    PTOTAL info;
    float totalxzona, mayPesoxZona=-1;
    int zonaAnterior, zonaMayor;
    
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {
        zonaAnterior= datos.zona;
        totalxzona=0;
        while (!feof(arch) && datos.zona==zonaAnterior)
        {
            totalxzona+=datos.peso;
            fread(&datos, sizeof(datos), 1, arch);
        }
        
        if (totalxzona<15)
        {
            printf("Zona %d con %.2f\n", zonaAnterior, totalxzona);
        }

        if (totalxzona > mayPesoxZona)
        {
            mayPesoxZona=totalxzona;
            zonaMayor=zonaAnterior;
        }
        
        info.zona=zonaAnterior;
        info.pesoTxZ=totalxzona;

        fwrite(&info, sizeof(info),1, archT);
        
    }
    
    printf("Zona con mayor peso acumulado: %d\n", zonaMayor);
    printf("Peso total acumulado: %.2f kg\n", mayPesoxZona);

    fclose(arch);
    fclose(archT);
}

FILE *abrirArchivo(char nombre[], char tipo[]){
    FILE *arch=fopen(nombre, tipo);
    if(arch==NULL){
        printf("Error.");
        getch();
        exit(1);
    }
    return arch;
}