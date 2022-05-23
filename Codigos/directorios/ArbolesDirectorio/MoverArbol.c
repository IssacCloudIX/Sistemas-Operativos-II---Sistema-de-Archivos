#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <libgen.h>
// Codigo para copiar todo un directorio y su contenido hacia otro
// Posiciones del argv
// 1 = Nombre del directorio origen
// 2 = Nombre del directorio destino
//Ambas carpetas deben existir

int copiarArchivo(char* dirOrigen, char* dirDestino);
int validarDirectorio(char* ruta);
char *obtenerRuta(char *dir);

int main(int argc, char **argv)
{
	puts("Argumentos del main: ");
	puts(argv[1]);
	puts(argv[2]);
	
	char *pathOrigen;
	char *pathDestino;
	char pathConstante[100];
	
	pathOrigen = obtenerRuta(argv[1]);
	pathDestino = obtenerRuta(argv[2]);
	
	if(argv[3] != NULL)
		strcpy(pathConstante, argv[3]);
		
	if(argc < 3)
	{
		puts("Te falta algun argumento");
		return -1;
	}
	
	puts("Transformados: ");
	puts(pathOrigen);
	puts(pathDestino);
	puts(pathConstante);
		
	DIR *ptrDirOrigen = opendir(pathOrigen);
	
	struct dirent *dirInfo;
	while(dirInfo = readdir(ptrDirOrigen))
	{
		if(strcmp(".", dirInfo->d_name) && strcmp("..", dirInfo->d_name))
		{

			char validacion[100];
			strcpy(validacion, pathOrigen);
			strcat(validacion, "/");
			strcat(validacion, dirInfo->d_name);
			if(validarDirectorio(validacion))
			{
				printf("----ENTRANDO A CARPETA: %s----\n", dirInfo->d_name);
				if(strcmp(pathDestino, validacion) == 0)
				{
					puts("Esta es la carpeta destino");
				}
				else
				{
					char rutaCarpeta[100];
					strcpy(rutaCarpeta, pathDestino);
					strcat(rutaCarpeta, "/");
					strcat(rutaCarpeta,  dirInfo->d_name);	
					mkdir(rutaCarpeta, 0775);
					char nuevoOrigen[100];
					strcpy(nuevoOrigen, pathOrigen);
					strcat(nuevoOrigen, "/");
					strcat(nuevoOrigen,  dirInfo->d_name);
					char nuevoDestino[100];
					strcpy(nuevoDestino, pathDestino);
					strcat(nuevoDestino, "/");
					strcat(nuevoDestino,  dirInfo->d_name);
					strcpy(pathConstante, pathOrigen);
					puts(pathConstante);
					char *nuevoArreglo[4] = {argv[0], nuevoOrigen, nuevoDestino, pathConstante};
					main(4, nuevoArreglo);
					
				}
			}
			if(!validarDirectorio(validacion))
			{
				printf("----COPIANDO ARCHIVO: %s----\n", dirInfo->d_name);
				char pathFinal[100];
				strcpy(pathFinal, pathOrigen);
				strcat(pathFinal, "/");
				strcat(pathFinal, dirInfo->d_name);
				printf("----PATH REAL ARCHIVO ORIGEN: %s----\n", pathFinal);
				char strDestinoFile[200];
				strcpy(strDestinoFile, pathDestino);
				strcat(strDestinoFile, "/");
				strcat(strDestinoFile, dirInfo->d_name);
				printf("----PATH REAL ARCHIVO DESTINO: %s----\n", strDestinoFile);
				copiarArchivo(pathFinal, strDestinoFile);
			}
			
		}
	}
	char comando[100];
	strcpy(comando, "./BorrarDirectorio ");
	strcat(comando, pathConstante);
	system(comando);

	return 0;
}

char *obtenerRuta(char *dir)
{

	FILE *fp;
	char *ruta = malloc(200);
	char path[1035];
	char comando[100];
	strcpy(comando, "readlink -f ");
	strcat(comando, dir);

	/* Open the command for reading. */
	fp = popen(comando, "r");
	if (fp == NULL) {
	printf("Failed to run command\n" );
	exit(1);
	}

	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path), fp) != NULL) {
		strcpy(ruta, path);
	}
	/* close */
	pclose(fp);
	
	*(ruta + strlen(path) - 1) = '\0';
	
	return ruta;

}

int validarDirectorio(char* ruta)
{
    struct stat path_stat;
    stat(ruta, &path_stat);
    return S_ISDIR(path_stat.st_mode);
}


int copiarArchivo(char* dirOrigen, char* dirDestino)
{
	struct stat st;
	int origenFile, destinoFile;
	int bytesEscribir, bytesLeer, nbytes;
	if (strcmp(dirOrigen, dirDestino) == 0)
	{
		printf("Error: %s y %s son el mismo archivo.\n", dirOrigen, dirDestino);
		return -1;
	}
	stat(dirOrigen, &st);
	//Tamano del archivo origen en bytes. 
	bytesLeer = st.st_size;
	char buffer[bytesLeer];
	char *buffer_Ptr = (&buffer[0]);
	origenFile = open(dirOrigen, O_RDONLY);
	if (origenFile == -1)
	{
		printf("Error: No se puede abrir el archivo de origen.\n");
		return -1;
	}
	destinoFile = open(dirDestino, O_WRONLY);
	if (destinoFile == -1)
	{
		destinoFile = open(dirDestino, O_CREAT | O_WRONLY, 0666);
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
}


