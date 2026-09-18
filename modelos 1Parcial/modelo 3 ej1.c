/*Ejercicio 1: 
El SMN (Servicio Meteorológico Nacional) registra las precipitaciones mensuales en diferentes estaciones de medición 
de una provincia durante un año. Los datos se reciben de forma desordenada a medida que llegan los reportes, hasta ingresar 
un Número de Estación igual a 0 (cero). Por cada medición, se registra:

Estación Meteorológica: Dato numérico (1 a 8).
Mes del año: Dato numérico (1 a 12, donde 1 es enero).
Precipitación (mm): Dato numérico positivo.

Se solicita almacenar los datos en una matriz de [8][12], acumulando los milímetros. 
Pueden llegar varios reportes para la misma estación y mes.
Los datos ingresados, deben ser validados. Implementar una función para validar que la Estación y el Mes estén 
dentro de los rangos definidos antes de afectar la matriz. 
Y también validar que la Precipitación sea un valor positivo.

Determinar e informar:
a) Todas las combinaciones Estación-Mes con la mayor cantidad de mm acumulados registrados. Informar el valor máximo encontrado, y en qué Estación(es) y Mes(es) ocurrió.
b) El total de lluvia anual acumulada por cada Estación de medición.
c) Informar si existió algún mes donde todas las estaciones registraron 0 mm de lluvia (meses de sequía total).*/