#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// Numeros argv
// 1 = archivo a leer
// 2 = bytes a leer
int main(int argv, char** argc)
{
	int descriptorFile;
	int nbytes;
	char buffer_rd[256];
	char *buffer_rd_Ptr = &(buffer_rd[0]);
	descriptorFile = open(argc[1], O_RDONLY);
	if (descriptorFile == -1)
	{
		printf("Error: No me fue posible abrir el archivo.\n");
		return -1;
	}
	else
		printf("Se logro abrir el archivo.\n");
	if(lockf(descriptorFile, F_TEST, atoi(argc[2])) == -1)
	{
		printf("El archivo se encuentra bloqueado\n");
		return -1;
	}
	printf("Se logro entrar al archivo con exito. Listo para leer.\n");
	nbytes = read(descriptorFile, buffer_rd_Ptr, atoi(argc[2]));
	if (nbytes == -1)
	{
		printf("Valio la lectura.\n");
		return -1;
	}
	else
		printf("Si se armo la lectura :D\nContenido: %s\n", buffer_rd);
	close(descriptorFile);
	return 0;
}

