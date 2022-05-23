# Sistemas-Operativos-II---Sistema-de-Archivos
Repositorio del proyecto final de la materia de Sistemas Operativos II, en el cual se construyó un sistema de archivos con operaciones básicas.

Las principales librerías utilizadas fueron:

    stdio.h
    Esta librería hace uso de streams para poder operar con dispositivos físicos o con cualquier otro tipo de archivos soportados por el sistema.
    stdlib.h
    Este encabezado define varias funciones de propósito general, incluida la gestión de memoria dinámica, entre otros.
    sys/types.h
     El archivo define los tipos de datos utilizados en el código fuente del sistema.
    sys/stats.h
     El encabezado facilita el recopilamiento de la información de los atributos de archivos.
    fcntl.h
     Esta libreria se encarga de opciones de control de archivos.
    dirent.h
    Esta libreria es utilizada para operaciones de acceso a directorios.

El proyecto en general cuenta con los siguientes programas, cada uno es independiente del otro, aunque se pueden llamar para complementar sus funciones:

1.- copiar.c: Este programa recibe dos direcciones y copia el archivo de la primera dirección en la segunda dirección con el nombre que se le haya dado.

2.- crear.c: Este programa crea un archivo en la ruta y con el nombre que se le haya dado.

3.- eliminar.c: Este programa borra el archivo que se haya indicado en la ruta como argumento.

4.- escribir.c: Este programa recibe una ruta de un archivo y un texto a escribir, y su función es escribir este texto en el archivo indicado.

5.- info.c: Este programa lee la información principal del archivo que se haya pasado como argumento.

6.- leer.c: Este programa lee e imprime por consola la información del archivo que se haya pasado en la ruta como argumento, además de que necesita un entero para saber cuantos bytes debe leer de ese archivo.

7.- crearD.c: Crea un directorio en la ruta que haya recibido como argumento.

8.- eliminarD.c: Elimina el directorio que esté en la ruta que haya recibido como argumento, siempre y cuando esté vacío.

9.- MoverArchivoDirectorio.c: Mueve un archivo hacia el directorio que se le indique en sus argumentos, y lo borra de la ubicación original.

10.- BorrarDirectorio.c: Elimina de forma recursiva todo lo que contiene un directorio.

11.- CopiarArbol.c: Copia y pega en la ubicación que se le diga todo el contenido de un directorio.

12.- MoverArbol.c: Corta y pega en la ubicación que se le diga todo el contenido de un directorio, borrándolo de su ubicación original.

