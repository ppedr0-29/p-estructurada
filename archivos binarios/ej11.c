/*11. Se dispone de un archivo llamado Rating.dat que guarda la información de los puntos obtenidos de rating
en los distintos programas de canales de cable a lo largo del día. Cada registro contiene: 
• Número de canal (entero)
• Programa (texto de 35 caracteres máximo)
• Rating (float)
El archivo se encuentra ordenado por canal.
Se solicita informar:
a. Aquellos canales que obtengan menos de 15 puntos en total.
b. El canal más visto.
c. Generar un archivo con el promedio de rating de cada canal que incluya dos campos:
• Número de canal.
• Promedio.*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef struct
{
    int numCanal;
    char programa[36];
    float rating;
}RATING;

typedef struct
{
    int numCanal;
    float promRating;
}RATINGPROM;

int main(){
    procesarArchivo();

    return 0;
}

void procesarArchivo(){
    FILE *arch=abrirArchivo("RATING.dat", "rb");
    FILE *archP=abrirArchivo("PROMEDIO.dat", "wb");
    int canalAnt, maxVisto, canalMax, cantProgramas;
    float totVisto;
    RATING datos;
    RATINGPROM info;

    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch))
    {   
        totVisto=0;
        canalAnt=datos.numCanal;
        cantProgramas=0;
        while (!feof(arch) && canalAnt==datos.numCanal)
        {
            totVisto+=datos.rating;
            cantProgramas++;
            fread(&datos, sizeof(datos), 1, arch);
        }
        
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