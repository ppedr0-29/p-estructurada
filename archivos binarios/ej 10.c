/*10. Dado el archivo pagos.dat con los pagos realizados por los alumnos a un curso, se desea registrar los
pagos de las cuotas. El archivo tiene el siguiente formato:
• DNI
• Fecha de último pago (3 enteros, día, mes y año)
Para registrar los pagos se ingresa el número de DNI (8 dígitos) y la fecha de pago. Se debe actualizar
el archivo de pagos, y si el DNI no se encuentra se pregunta al usuario si desea agregar un nuevo alumno.
En caso afirmativo se debe agregar un nuevo registro en dicho archivo con el nuevo pago y además
agregar el nuevo alumno al archivo alumnos.dat, dicho archivo contiene el DNI y nombre completo del
alumno (40 caracteres máximo).
Todos los datos de ingreso deben estar validados (para simplificar al validar la fecha considerar día de 1 a
31 para todos los meses).
Se procesan varios pagos hasta que se ingresa un DNI 0. Al finalizar mostrar un listado de los alumnos,
DNI y nombre de todos aquellos que adeudan la última cuota (del mes de octubre 2026). */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

typedef struct
{
    int dia;
    int mes;
    int anio;
}ddmmaa;

typedef struct
{
    int dni;
    ddmmaa fecha;
}ALU;

typedef struct
{
    int dni;
    char nombre[41];
}NALU;

void procesarArchivo();
long busqueda(FILE *, int, ALU *);
long busquedaAlumno(FILE *, int, NALU *);
void mostrarDeudores(FILE *, FILE *, int, int);
void leeyvalidaIntE2CF(int *, int, int, int);
void leerTexto(char[], int);
void leeryvalTexto(char[], int);
FILE *abrirArchivo(char[], char[]);
bool validarFecha(int, int, int);
int cantDiasMes(int, int);
int esBisiesto(int);

int main(){
    procesarArchivo();

    return 0;
}

void procesarArchivo(){
    FILE *arch=abrirArchivo("PAGOS.dat", "r+b");
    FILE *archNuevos=abrirArchivo("ALUMNOS.dat", "a+b");
    ALU datos, *pdatos=&datos;
    NALU info;
    ddmmaa fecha;
    int dniAux, nuevoAlu;
    long pos;

    printf("Ingrese DNI del alumno: ");
    leeyvalidaIntE2CF(&dniAux, 10000000, 99999999, 0);
    while (dniAux!=0)
    {
        pos=busqueda(arch, dniAux, pdatos);
        printf("Ingrese fecha de pago (XX/XX/XXXX): ");
        scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
            while (!validarFecha(fecha.dia, fecha.mes, fecha.anio))
            {
                printf("Fecha invalida. Reingrese:");
                scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
            }
        if (pos!=-1)
        {
            fseek(arch, pos*sizeof(datos), SEEK_SET);
            datos.dni=dniAux;
            datos.fecha.dia=fecha.dia;
            datos.fecha.mes=fecha.mes;
            datos.fecha.anio=fecha.anio;
            fwrite(&datos, sizeof(datos), 1, arch);
            fflush(arch);
        }else{
            printf("DNI no encontrado. Desea ingresar un nuevo alumno(0 NO - 1 SI): ");
            leeyvalidaIntE2CF(&nuevoAlu, 0, 1, 0);
            if (nuevoAlu==1)
            {
                printf("Ingrese nombre completo: ");
                leeryvalTexto(info.nombre, 41);
                fseek(arch, 0, SEEK_END);
                datos.dni=dniAux;
                datos.fecha.dia=fecha.dia;
                datos.fecha.mes=fecha.mes;
                datos.fecha.anio=fecha.anio;
                fwrite(&datos, sizeof(datos), 1, arch);
                fflush(arch);
                info.dni=dniAux;
                fseek(archNuevos, 0, SEEK_END);
                fwrite(&info, sizeof(info), 1, archNuevos);
                fflush(archNuevos);
            }
            
        }
        printf("Ingrese DNI del alumno: ");
        leeyvalidaIntE2CF(&dniAux, 10000000, 99999999, 0);
    }
    mostrarDeudores(arch, archNuevos, 10, 2026);
    fclose(arch);
    fclose(archNuevos);
}

long busquedaAlumno(FILE *arch, int dni, NALU *palumno){
    NALU alumno;
    long pos=-1;
    rewind(arch);
    fread(&alumno, sizeof(alumno), 1, arch);
    while (!feof(arch) && pos==-1)
    {
        if (alumno.dni==dni)
        {
            pos=ftell(arch)/sizeof(alumno)-1;
            *palumno=alumno;
        }
        fread(&alumno, sizeof(alumno), 1, arch);
    }
    return pos;
}

void mostrarDeudores(FILE *archPagos, FILE *archAlumnos, int mesLim, int anioLim){
    ALU pago;
    NALU alumno;
    long pos;
    printf("--ALUMNOS QUE ADEUDAN LA CUOTA %d/%d--\n", mesLim, anioLim);
    rewind(archPagos);
    fread(&pago, sizeof(pago), 1, archPagos);
    while (!feof(archPagos))
    {
        if (pago.fecha.anio<anioLim || (pago.fecha.anio==anioLim && pago.fecha.mes<mesLim))
        {
            pos=busquedaAlumno(archAlumnos, pago.dni, &alumno);
            if (pos!=-1)
            {
                printf("DNI: %d - %s\n", alumno.dni, alumno.nombre);
            }
        }
        fread(&pago, sizeof(pago), 1, archPagos);
    }
}

long busqueda(FILE *arch, int dni, ALU *pdatos){
    ALU datos;
    long pos=-1;
    rewind(arch);
    fread(&datos, sizeof(datos), 1, arch);
    while (!feof(arch) && pos==-1)
    {
        if (datos.dni==dni)
        {
            pos=ftell(arch)/sizeof(datos)-1;
            *pdatos=datos;
        }
        fread(&datos, sizeof(datos), 1, arch);
    }
    return pos;
}

void leeyvalidaIntE2CF(int *dato, int min, int max, int cf){
    scanf("%d", dato);
    while ((*dato<min || *dato>max) && *dato!=cf)
    {
        printf("Error. Reingrese:");
        scanf("%d", dato);
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

bool validarFecha(int dia, int mes, int anio){
    bool fechaValida = false;
    if (anio> 1900){
        if (mes >=1 && mes <=12){
            if (dia>=1 && dia <= cantDiasMes(mes, anio)){
                fechaValida = true;
            }
        }
    } return fechaValida;
}
int cantDiasMes(int mes, int anio){
    int cantDias =31;
    if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
        cantDias = 30;
    }else{
        if(mes==2){
            cantDias= 28 + esBisiesto(anio);
        }
    }
        
    return cantDias;
}
int esBisiesto(int anio){
    int bisiesto =0;
    if ((anio%4==0 && anio%100!=0)||(anio%400==0))
        bisiesto = 1;
    return bisiesto;
}