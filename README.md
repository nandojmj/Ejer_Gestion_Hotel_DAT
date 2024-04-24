# Sistema de Gestión Hotelera en C++ alamacenando en un .DAT

Este es un sistema de gestión hotelera desarrollado en C++ que permite gestionar las reservas de un hotel, registrar consumos, generar facturas y realizar búsquedas de huéspedes.

## Funcionalidades

El sistema proporciona las siguientes funcionalidades:

- **Ingresar Datos de Huéspedes**: Permite registrar los datos de los huéspedes, incluyendo su nombre, apellido, cédula, teléfono, procedencia, tipo de habitación y número de días de estancia.

- **Ingresar Consumo del Huésped**: Permite ingresar el consumo adicional realizado por un huésped durante su estancia en el hotel.

- **Mostrar Facturas**: Muestra las facturas generadas para cada huésped, incluyendo detalles como el número de factura, nombre del huésped, habitación ocupada, tipo de habitación, valor de la habitación por día, número de días de estancia, consumo adicional y valor total.

- **Búsqueda por Habitación**: Permite buscar información de un huésped y su factura asociada a una habitación específica.

- **Búsqueda por Huésped**: Permite buscar información de un huésped por su apellido y nombre.

- **Salida de Huéspedes**: Permite dar salida a un huésped y liberar la habitación.

- **Mostrar Lista de Huéspedes**: Muestra la lista de todos los huéspedes registrados en el sistema, indicando su estado (Hospedado o No Hospedado).

- **Resetear Archivo**: Permite limpiar el archivo de datos y reiniciar el sistema.

## Almacenamiento de Datos

Los datos de los huéspedes se almacenan en un archivo binario llamado `HOTEL.DAT`. Cada registro en este archivo representa la información de un huésped, incluyendo campos como nombre, apellido, cédula, número de habitación, consumo adicional, entre otros. 

El sistema utiliza operaciones de lectura y escritura en este archivo para realizar las diferentes funciones, como agregar nuevos huéspedes, actualizar información, generar facturas y realizar búsquedas.

## Requisitos del Sistema

Para compilar y ejecutar este código, se requiere un compilador de C++ que admita las bibliotecas estándar utilizadas, así como el sistema operativo debe ser compatible con las funciones de las bibliotecas `conio.h` y `dos.h`.

## Uso del Sistema

Al ejecutar el programa, se presenta un menú con las opciones disponibles. Selecciona la opción deseada utilizando las teclas indicadas y sigue las instrucciones proporcionadas en pantalla.
