/*Ejercicio 2: Un centro odontológico administra una agenda de 40 turnos para un día determinado. Cada turno se representa mediante una estructura con los siguientes datos:

DNI del Paciente (entero).

Nombre del Paciente (cadena de hasta 50 caracteres).

Estado del Turno (entero: 1 para "Pendiente", 2 para "Atendido", 3 para "Cancelado").

Se deben ingresar los datos de los 40 turnos en un vector de estructuras. Al ingresar el DNI se debe validar que el paciente no tenga ya un turno asignado en el vector.
Finalizada la carga se ingresará una secuencia de DNI de pacientes que van llegando a la recepción, terminando con DNI = 0.

Si el DNI existe, se debe cambiar el estado del turno a 2: "Atendido".
Si el DNI no existe, se lo contabilizara como "Paciente No Registrados".

Informar:
a) La cantidad total de pacientes que asistieron, pero no tenían turno.
b) El listado completo de la agenda ordenado de forma ascendente por DNI, mostrando DNI, Nombre y el estado.

Implementar al menos dos funciones: Una para la búsqueda del código en el vector de estructuras, y otra para el ordenamiento.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){

}