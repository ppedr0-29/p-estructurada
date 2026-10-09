/*Ejercicio 2: Estadísticas de Jugadores de Fútbol
Una liga necesita un programa para gestionar el rendimiento de los jugadores a lo largo del torneo. 
Por cada jugador se debe almacenar:
DNI del jugador (entero).
Nombre o Apodo (cadena de hasta 30 caracteres).
Goles Totales (entero, inicia en 0).
Asistencias Totales (entero, inicia en 0).

1. Carga Inicial y Memoria Dinámica:
Asignar un arreglo dinámico con una capacidad inicial de 10 elementos.
Cada vez que el arreglo se llene, aumentar su capacidad de 5 en 5.
Validar que el DNI no se encuentre duplicado en el sistema.
La carga inicial finaliza al ingresar DNI = 0.
2. Actualización de Partidos:
Al terminar la carga, se ingresan las estadísticas de la jornada. Por cada registro se lee: 
DNI, Goles anotados en el partido y Asistencias dadas en el partido. Este ingreso también finaliza con DNI = 0.

Si el DNI existe: Sumar los nuevos goles y asistencias a sus totales acumulados.
Si el DNI no existe: No agregarlo al vector, simplemente contabilizarlo en un contador de "Registros de jugadores no inscriptos".
3. Reporte Final:
Mostrar el listado completo de los jugadores registrados, ordenado de forma descendente por Goles Totales.
Informar la cantidad total de registros ignorados por no pertenecer a jugadores inscriptos. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TXT 31

typedef struct {
    int dni;
    char nombre[TXT];
    int golesT;
    int asistT;
} JUGADOR;

JUGADOR * INGRESO(JUGADOR *, int *, int *);
JUGADOR ingreso(JUGADOR *, int *);
void actualizacion(JUGADOR *, int *, int *);
void informe(JUGADOR *, int *, int *);
void burbujeo(JUGADOR *, int);
int busqueda(JUGADOR *, int, int *);
void intercambio(JUGADOR *, JUGADOR *);
void leerTexto(char [], int);
void leeryvalTexto(char [], int);
void leeyvalidaIntE2CF(int *, int, int, int);
void leeyvalidaInt(int *, int);

int main() {
    JUGADOR *datos;
    int capIni = 10, cantJug = 0, noInscriptos = 0;

    datos = (JUGADOR*) malloc(capIni * sizeof(JUGADOR));
    if (datos == NULL) {
        printf("Error al reservar memoria.\n");
        exit(1);
    }

    datos = INGRESO(datos, &capIni, &cantJug);
    actualizacion(datos, &cantJug, &noInscriptos);
    informe(datos, &cantJug, &noInscriptos);

    free(datos);

    return 0;
}

JUGADOR ingreso(JUGADOR *datos, int *ce) {
    JUGADOR aux;

    printf("Ingrese DNI del jugador: ");
    leeyvalidaIntE2CF(&aux.dni, 10000000, 99999999, 0);
    if (aux.dni != 0) {
        while (busqueda(datos, aux.dni, ce) != -1) {
            printf("El dni ya fue ingresado. Reingrese: ");
            leeyvalidaIntE2CF(&aux.dni, 10000000, 99999999, 0);
        }
        if (aux.dni != 0) {
            printf("Ingrese nombre: ");
            leeryvalTexto(aux.nombre, TXT);
            aux.golesT=0;
            aux.asistT=0;
        }
    }
    return aux;
}

JUGADOR * INGRESO(JUGADOR *datos, int *mem, int *ce) {
    JUGADOR *auxR;
    JUGADOR aux;
    int i = 0;

    aux = ingreso(datos, &i);
    while (aux.dni != 0) {
        if (i == *mem) {
            *mem += 5;
            auxR = (JUGADOR*) realloc(datos, *mem * sizeof(JUGADOR));
            if (auxR != NULL) {
                datos = auxR;
            } else {
                exit(1);
            }
        }
        *(datos + i) = aux;
        i++;
        aux = ingreso(datos, &i);
    }
    *ce = i;
    return datos;
}

void actualizacion(JUGADOR *datos, int *ce, int *noReg) {
    int dni, gol, asist, pos;

    printf("Ingrese DNI (0 fin): ");
    leeyvalidaIntE2CF(&dni, 10000000, 99999999, 0);
    while (dni != 0) {
        pos = busqueda(datos, dni, ce);
        if (pos != -1) {
            printf("Ingrese los goles: ");
            leeyvalidaInt(&gol, 0);
            printf("Ingrese las asistencias: ");
            leeyvalidaInt(&asist, 0);
            (datos + pos)->golesT += gol;
            (datos + pos)->asistT += asist;
        } else {
            printf("DNI no registrado\n");
            (*noReg)++;
        }
        printf("Ingrese DNI (0 fin): ");
        leeyvalidaIntE2CF(&dni, 10000000, 99999999, 0);
    }
}

void burbujeo(JUGADOR *datos, int ce) {
    int cota = ce - 1;
    int desordenado = 1;
    while (desordenado) {
        desordenado = 0;
        for (int j = 0; j < cota; j++) {
            if ((datos + j)->golesT < (datos + j + 1)->golesT) {
                intercambio(&datos[j], &datos[j + 1]);
                desordenado = j;
            }
        }
        cota = desordenado;
    }
}

void leerTexto(char texto[], int largo) {
    fflush(stdin);
    fgets(texto, largo, stdin);
    int i = 0;
    while (texto[i] != '\0') {
        if (texto[i] == '\n') {
            texto[i] = '\0';
        }
        i++;
    }
}

void leeryvalTexto(char texto[], int largo) {
    leerTexto(texto, largo);
    while (strlen(texto) == 0) {
        printf("Error. Reingrese: ");
        leerTexto(texto, largo);
    }
}

void leeyvalidaIntE2CF(int *dato, int min, int max, int CF) {
    scanf("%d", dato);
    while ((*dato < min || *dato > max) && *dato != CF) {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
}

void leeyvalidaInt(int *dato, int lim) {
    scanf("%d", dato);
    while (*dato < lim) {
        printf("Error. Reingrese: ");
        scanf("%d", dato);
    }
}

int busqueda(JUGADOR *datos, int dni, int *ce) {
    int pos = -1, i = 0;
    while (pos == -1 && i < *ce) {
        if ((datos + i)->dni == dni) {
            pos = i;
        }
        i++;
    }
    return pos;
}

void intercambio(JUGADOR *a, JUGADOR *b) {
    JUGADOR aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void informe(JUGADOR *datos, int *ce, int *noReg) {
    burbujeo(datos, *ce);
    printf("El total de no inscriptos fue %d\n", *noReg);

    for (int i = 0; i < *ce; i++) {
        printf("DNI %d, %s con %d goles.\n", (datos + i)->dni, (datos + i)->nombre, (datos + i)->golesT);
    }
}