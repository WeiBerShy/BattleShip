#include "sock-lib.h"

#define ERROR -1
#define OK 0
#define JUGAR  1
#define INSTRUCCIONES 2
#define CREDITOS 3
#define SALIR 4
#define COOP 5
#define ONLINE 6
#define REGRESAR 7
#define CLIENT 8
#define SERVER 9
#define MENU1 10
#define MENU2 11
#define MENU3 12


void menu();
void menu2();
void menu3();
int convRespToNum(char* resp, int menu);
void beServer();
void beClient();
void sig_handler(int);
void logo();
void print_tablero(char*, char*);