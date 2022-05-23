#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Posiciones del argv
// 1 = nombre directorio
int main(int argc, char** argv)
{
	int eliminado;
	char *path = &(argv[1][0]); 
	eliminado = rmdir(path);
	if (eliminado == -1)
	{
		printf("Error: El directorio no se encuentra vacio\n");
		return -1; 
	}
	printf("Directorio eliminado con exito\n");
	return 0;
}

