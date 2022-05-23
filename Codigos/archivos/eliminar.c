#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
// Codigo para escribir al final del archivo
// Posiciones del argv
// 1 = Nombre archivo a eliminar
int main (int argc, char** argv)
{
	const char *path_Ptr = &(argv[1][0]);
	int eliminado; 
	eliminado = unlink(path_Ptr);
	if (eliminado == 0)
		printf("Se elimino el archivo con exito.\n");
	else
		printf("No me fue posible eliminar el archivo.\n");
	return 0;
}
