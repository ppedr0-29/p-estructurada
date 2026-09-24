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

