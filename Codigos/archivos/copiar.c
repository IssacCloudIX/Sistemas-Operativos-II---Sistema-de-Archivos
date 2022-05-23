#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
struct stat st;
// Codigo para escribir al final del archivo
// Posiciones del argv
// 1 = Nombre del archivo origen
// 2 = Nombre del archivo destino
int main (int argc, char** argv)
{
	int origenFile, destinoFile;
	int bytesEscribir, bytesLeer, nbytes;
	if (strcmp(argv[1], argv[2]) == 0)
	{
		printf("Error: %s y %s son el mismo archivo.\n", argv[1], argv[2]);
		return -1;
	}
	stat(argv[1], &st);
	//Tamano del archivo origen en bytes. 
	bytesLeer = st.st_size;
	char buffer[bytesLeer];
	char *buffer_Ptr = (&buffer[0]);
	origenFile = open(argv[1], O_RDONLY);
	if (origenFile == -1)
	{
		printf("Error: No se puede abrir el archivo de origen.\n");
		return -1;
	}
	destinoFile = open(argv[2], O_WRONLY);
	if (destinoFile == -1)
	{
		destinoFile = open(argv[2], O_CREAT | O_WRONLY, 0666);
		if (destinoFile == -1)
		{
			printf("Error: No se puede abrir el archivo de destino.\n");
			return -1;
		}
	}
	if (lockf(origenFile, F_TEST, bytesLeer) == -1)
	{
		printf("Error: El archivo de origen se encuentra bloqueado. No es posible realizar la lectura.\n");
		return -1;
	}
	printf("Se logro entrar al archivo origen con exito. Listo para leer.\n");
	bytesEscribir = read(origenFile, buffer_Ptr, bytesLeer);
	if (bytesEscribir == -1)
	{
		printf("Error: No se pudo realizar la lectura.\n");
		return -1;
	}
	else
		printf("Si se logro la lectura del archivo origen. Preparandose para escritura en archivo destino.\n"); 
	close(origenFile);
	if (lockf(destinoFile, F_TLOCK, bytesEscribir) == -1)
	{
		printf("Error: No se pudo bloquear el archivo de destino para escritura.\n");
		return -1;
	}
	printf("Se ha bloqueado el archivo destino con exito.\n");
	nbytes = write(destinoFile, buffer_Ptr, bytesEscribir);
	if (nbytes == -1)
	{
		printf("Error: No se pudo escribir en el archivo destino.\n");
		return -1;
	}
	printf("Se logro escribir en el archivo destino.\n");
	if (lockf(destinoFile, F_ULOCK, bytesEscribir) == -1)
	{
		printf("Error: No se pudo desbloquear el archivo destino.\n");
		return -1;
	}
	printf("Archivo Destino desbloqueado.\n");
	close(destinoFile);
	printf("Copia terminada con exito.\n");
	return 0;
}






