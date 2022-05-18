// Constantes

#define ERROR 0
#define OK 1
#define LARGO 12 // num+2 por los bordes 
#define ANCHO 58 // num+3 por los bordes y el centro
#define TAM_POS 2 // ej combinaciones para determinar la posicion Ej: A0 E6 H9 C7 D9
#define CANT_BARCOS 4
// Prototipos de funciones
void juego(void);
int check(char*);
int posship(char[LARGO][ANCHO], int, char*);
int posch(char);
void printbarco(int);
void menu(void);
void printtablero(char [LARGO][ANCHO]);
char getch(void);