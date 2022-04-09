#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>


#define PORT 8081	/* El puerto donde se conectará, servidor */
#define BACKLOG 10	/* Tamaño de la cola de conexiones recibidas */
#define ERROR -1
#define OK 0

int	conectar (char argv[2][20]);

int	Open_conection (struct sockaddr_in *, char*, int); /* Función que crea la conexión*/

int	Aceptar_pedidos (int);	/* Función que acepta una conexión entrante*/

