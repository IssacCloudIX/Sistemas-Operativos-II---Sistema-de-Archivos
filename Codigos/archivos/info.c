#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <libgen.h>
struct stat st;
struct tm * timeinfo; 
// Codigo para escribir al final del archivo
// Posiciones del argv
// 1 = Nombre del archivo
int main (int argc, char** argv)
{
	char *buffer_Ptr = &(argv[1][0]);
	char buff[20];
	int informacion;
	struct stat *buffer_st_Ptr = &st; 
	informacion = stat(buffer_Ptr, buffer_st_Ptr);
	if (informacion == -1)
	{
		printf("Error: No se pudo conseguir informacion del archivo.\n");
		return -1;
	}
	char *path = realpath(argv[1], NULL); 
	char *name = basename(argv[1]);
	printf("Obtencion de informacion lograda con exito.\n");
	printf("Nombre del archivo: %s\n", name);
	printf("Tamano del archivo: %ld bytes\n", st.st_size);
	printf("Ruta: %s\n", path);
	timeinfo = localtime(&(st.st_mtime));
	strftime(buff, 20, "%b %d %H:%M", timeinfo);
	printf("Fecha de ultima modificacion del archivo: %s\n", buff);
	printf("Informacion completa del archivo desplegada.\n");
	free(path);
	return 0;
}
