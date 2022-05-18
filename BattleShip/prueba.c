#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int funcion();

int main(){

    char p2[10]="Marco";
    char aux[10];
    char* aux2;

    aux2=(char*)malloc(sizeof(char)*20);

    printf("hola\n");

    strcpy(aux,p2);
    strcat(aux,"...");
    printf("hola\n");
    aux2 = strcat("ESPERANDO A ",aux);
printf("hola\n");
    puts(aux2);

    return 0;
}

int funcion(){

    

    return rand()%10;

}