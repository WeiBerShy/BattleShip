#include "sock-lib.h"

#define ERROR -1
#define OK 0
#define JUGAR  1
#define INSTRUCCIONES 2
#define CREDITOS 3
#define SALIR 4
#define COOP 1
#define ONLINE 2
#define REGRESAR 3
#define CLIENT 1
#define SERVER 2
#define MENU1 1
#define MENU2 2
#define MENU3 3
#define CANTSHIP 4
#define LARGO 12
#define ANCHO 58


void menu();
void menu2();
void menu3();
int convRespToNum(char* resp, int menu);
void beServer();
void beClient();
void sig_handler(int);
void logo();
void print_tablero(char*, char*);
void rectStrings(char*);
void printbarco(int);
void juego(int, char*, char*);
int posship(char tablero[LARGO][ANCHO], int orientacion, int barco, char* posicion);