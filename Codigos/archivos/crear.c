#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
// Script a Revisar de Crear un archivo
// Numeros del argv
// 1 = Nombre del archivo
int main (int argc, char** argv)
{
	int fileCreado;
	fileCreado = open(argv[1], O_CREAT | O_EXCL, 0666);
	if (fileCreado == -1)
	{
		printf("Error: No se pudo crear el archivo porque ya existe.\n");
		return -1;
	}
	else
		printf("Se logro crear el archivo con exito.\n");
	return 0;
}
