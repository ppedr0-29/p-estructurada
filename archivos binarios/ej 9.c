/*9. Se dispone de un archivo denominado INSCRIPTOS.dat que contiene la información de los inscriptos a un
curso de programación. El archivo aún no está completo ya que la inscripción se realiza por partes. Por
cada inscripto se tiene la siguiente información:
• DNI (entero)
• Apellido y Nombres (texto de 20 caracteres máximo)
• Pagado (campo entero donde 1 indica que pagó y 0 que aún adeuda la matrícula)
Se desea realizar un programa que cumpla con dos funciones:
a. Registrar los pagos de los alumnos ya inscriptos.
b. SI hay cupo, agregar nuevos inscriptos (el cupo máximo es de 60 alumno).
El programa solicitará el ingreso del DNI y lo buscará entre los inscriptos, en caso de que lo encuentre
dará la opción para registrar el pago (si es que no está pago ya). En caso de que no lo encuentre dará la
opción para inscribirlo al curso (el pago se realiza luego). En el momento que ya no quede cupo en el curso
si llega un nuevo inscripto se le preguntará si desea quedar registrado para un curso futuro, y en caso
afirmativo se le solicitará el teléfono y se guardará el nombre, DNI y teléfono en un archivo
Interesados.dat.
El ingreso de datos finaliza con un DNI negativo. */

#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int dni;
    char ayn[21];
    int pago; //1 pago, 0 no pago.
}INSC;

typedef struct 
{
    int dni;
    char ayn[21];
    int tel;
}INTERES;

void procesarArchivo();
long busqueda(FILE *, int, INSC *);
int cantidadRegistros(FILE *, int);
void leeyvalidaIntE2(int *, int, int);
void leeyvalidaIntE2CF(int *, int, int, int);
void leerTexto(char[], int);
void leeryvalTexto(char[], int);
FILE *abrirArchivo(char[], char[]);

int main(){
    procesarArchivo();

    return 0;
}

void procesarArchivo(){
    FILE *arch=abrirArchivo("INSCRIPTOS.dat", "r+b");
    FILE *archInteresados=abrirArchivo("INTERESADOS.dat", "ab");
    INSC datos;
    INTERES info;
    int dniAux, inscribir, contarRegistros, listaE;
    INSC *pdatos=&datos;
    long pos;

    printf("Ingrese DNI:");
    leeyvalidaIntE2CF(&dniAux, 10000000, 99999999, 0);
    while (dniAux>=0)
    {
        pos=busqueda(arch, dniAux, pdatos);
        if (pos!=-1)
        {
            if (datos.pago==0)
            {
                printf("El inscripto pago?(0 NO - 1 SI): ");
                leeyvalidaIntE2(&datos.pago, 0, 1);
                fseek(arch, pos*sizeof(datos), SEEK_SET);
                fwrite(&datos, sizeof(datos), 1, arch);
                fflush(arch);
            }else{
                printf("El inscripto ya pago.\n");
            }
        }else{
            contarRegistros=cantidadRegistros(arch, sizeof(INSC));
            if (contarRegistros<60)
            {
                printf("No se encontro el DNI. Desea inscribirlo al curso?(0 NO - 1 SI): ");
                leeyvalidaIntE2(&inscribir, 0, 1);
                if (inscribir==1)
                {
                    printf("Ingresar apellido y nombre: ");
                    leeryvalTexto(datos.ayn, 21);
                    datos.dni=dniAux;
                    datos.pago=0;
                    printf("Usuario inscripto. Pago pendiente.\n");
                    fseek(arch, 0, SEEK_END);
                    fwrite(&datos, sizeof(datos), 1, arch);
                    fflush(arch);
                }
            }else{
                printf("Cupos completados. Desea ingresar en lista de espera(0 NO - 1 SI): ");
                leeyvalidaIntE2(&listaE, 0 , 1);
                if (listaE==1)
                {
                    printf("Ingrese su numero de telefono: ");
                    leeyvalidaIntE2(&info.tel, 1100000000, 1199999999);
                    printf("Ingrese su apellido y nombre: ");
                    leeryvalTexto(info.ayn, 21);
                    info.dni=dniAux;
                    fseek(archInteresados, 0, SEEK_END);
                    fwrite(&info, sizeof(info), 1, archInteresados);
                }
            }
        }
        printf("Ingrese DNI:");
        leeyvalidaIntE2CF(&dniAux, 10000000, 99999999, 0);
    }
    fclose(arch);
    fclose(archInteresados);
}

long busqueda(FILE *arch, int dni, INSC *pdatos){
    INSC datos;
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

int cantidadRegistros(FILE *arch, int tamRegistro){
    int cant;
    fseek(arch, 0, SEEK_END);
    cant=ftell(arch)/tamRegistro;
    return cant;
}

void leeyvalidaIntE2(int *dato, int min, int max){
    scanf("%d", dato);
    while (*dato<min || *dato>max)
    {
        printf("Error. Reingrese:");
        scanf("%d", dato);
    }
}

void leeyvalidaIntE2CF(int *dato, int min, int max, int cf){
    scanf("%d", dato);
    while ((*dato<min || *dato>max) && *dato>=cf)
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