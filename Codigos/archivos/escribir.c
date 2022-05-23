#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
// Codigo para escribir al final del archivo
// Posiciones del argv
// 1 = Nombre del archivo
// 2 = Cadena a escribir
int main (int argc, char** argv)
{
	int descriptorFile;
	int nbytes; 
	char *input_Ptr = &(argv[2][0]);
	char salto = '\n';
	char *salto_Ptr = &salto;
	descriptorFile = open(argv[1], O_WRONLY | O_APPEND);
	if (descriptorFile == -1)
	{
		printf("Error: No se puede abrir el archivo.\n");
		return -1;
	}
	else
		printf("Exito al abrir el archivo\n");
	if (lockf(descriptorFile, F_TLOCK, strlen(argv[2])) == -1)
	{
		printf("No se pudo bloquear el archivo\n");
		return -1;
	}
	printf("Se ha bloqueado el archivo con exito\n");
	nbytes = write(descriptorFile, input_Ptr, strlen(argv[2]));
	if (nbytes == -1)
	{
		printf("Valio la escritura\n");
		return -1;
	}
	nbytes = write(descriptorFile, salto_Ptr, 1);
	if (nbytes == -1)
	{
		printf("Valio la escritura\n");
		return -1;
	}
	printf("Si se armo la escritura.\n");
	if (lockf(descriptorFile, F_ULOCK, strlen(argv[2])))
	{
		printf("No pude desbloquear el archivo.\n");
		return -1;
	}
	else
		printf("Archivo Desbloqueado\n");
	close(descriptorFile);
	return 0;
}
