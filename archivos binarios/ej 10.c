/*10. Dado el archivo pagos.dat con los pagos realizados por los alumnos a un curso, se desea registrar los
pagos de las cuotas. El archivo tiene el siguiente formato:
• DNI
• Fecha de último pago (3 enteros, día, mes y año)
Para registrar los pagos se ingresa el número de DNI (7 a 8 dígitos) y la fecha de pago. Se debe actualizar
el archivo de pagos, y si el DNI no se encuentra se pregunta al usuario si desea agregar un nuevo alumno.
En caso afirmativo se debe agregar un nuevo registro en dicho archivo con el nuevo pago y además
agregar el nuevo alumno al archivo alumnos.dat, dicho archivo contiene el DNI y nombre completo del
alumno (40 caracteres máximo).
Todos los datos de ingreso deben estar validados (para simplificar al validar la fecha considerar día de 1 a
31 para todos los meses).
Se procesan varios pagos hasta que se ingresa un DNI 0. Al finalizar mostrar un listado de los alumnos,
DNI y nombre de todos aquellos que adeudan la última cuota (del mes de febrero 2024). */