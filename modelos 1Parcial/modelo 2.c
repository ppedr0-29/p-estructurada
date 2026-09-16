/*Una clínica veterinaria requiere un programa en C para gestionar su inventario. 
El sistema debe reservar memoria dinámica inicialmente para 40 artículos. 
De cada producto se registra la siguiente información:
Código: Formato alfanumérico "XXX/000" (tres letras, una barra y tres números).
Nombre completo: Cadena de caracteres.
Tipo: Carácter validado ('A' Alimentos, 'V' Vacunas, 'C' Cuidados).
Inventario: Cantidad en stock (número real).
Luego de preparar el sistema, se comenzarán a registrar las compras de reposición. 
Por cada compra se ingresará el Código del artículo y la Cantidad comprada (validar que sea un real mayor a 0). 
El ingreso de compras finalizará al introducir el código "FFF/000".
Durante este proceso de compras, se debe contemplar lo siguiente:
Si el código ya existe en el arreglo, se debe actualizar su inventario sumando la cantidad comprada.
Si el código no existe, se debe dar de alta como un artículo nuevo, solicitando al usuario el nombre y el tipo, 
y redimensionando la memoria del arreglo para agregarlo.
Al finalizar el programa, se debe informar por pantalla:
La cantidad total acumulada en el inventario por cada Tipo de artículo.
La cantidad exacta de artículos nuevos que fueron añadidos al catálogo original.*/