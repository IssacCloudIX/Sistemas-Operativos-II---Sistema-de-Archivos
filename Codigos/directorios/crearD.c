#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

// Posiciones del argv
// 1 = nombre directorio
//Si el directorio ya existe, el directorio no se creará.
int main(int argc, char** argv)
{
	int creado;
	char *path = &(argv[1][0]); 
	creado = mkdir(path, 0775);
	if (creado == -1)
	{
		printf("Error: No ha sido posible crear el directorio.\n");
		return -1;
	}
	printf("Directorio creado con exito.\n");
	return 0;
}

