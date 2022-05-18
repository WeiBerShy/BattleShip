#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funcReference.h"
#include <unistd.h>
#include <termios.h>



void juego(void){
    int flag;                   //     A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   T   U   V   W   X   Y   Z   @       A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   T   U   V   W   X   Y   Z   @      
    char pos[TAM_POS];
    char tablero[LARGO][ANCHO]= {{'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
                                 {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
                                 {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
                                 {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
                                 {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
                                 {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
                                 {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
                                 {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
                                 {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
                                 {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
                                 {'|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
                                 {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'}};
    
    

    for(int barco=0;barco<CANT_BARCOS;barco++){
        do{  

            printtablero(tablero);
            printf("Ingrese la posicion: ");
            scanf("%s",pos);
            flag = posship(tablero,barco,pos);
        }
        while(flag!=OK);

           
    }
}

int check(char* cadena){
    int len;
    len=strlen(cadena);
   
    if(len!=2){
        printf("\nLa posicion ingresada no es correcta.\n");
        getch();
        return ERROR;
    }
    if(cadena[0]>='a' && cadena[0]<='z'){
        cadena[0]-=32;
    }  
    if((cadena[0]>='A' && cadena[0]<='Z') && (cadena[1]>='0' && cadena[1]<='9')){     
        return OK;   
    }
    else if((cadena[0]=='@') && (cadena[1]>='0' && cadena[1]<='9')){
        return OK;
    }
    printf("\nLa posicion ingresada no es correcta.\n");
    getch();

    return ERROR;
}


int posship(char tablero[LARGO][ANCHO], int barco, char* posicion){

    char ori[2]={0,0};
    int X,Y;
    char y[2];
  
    if(!check(posicion)){
        system("clear");
        return ERROR;
    }
    
    for(int i=0;i<2;i++){
        y[i]=posicion[i+1];
    }
    
    X=atoi(y)+1;
    Y=posch(posicion[0])+1;
 
    switch (barco){
    
    case 0:

        do{
            system("clear");
            printtablero(tablero);
            printf("Igrese la orientacion del barco.\n");
            printbarco(barco);
            printf("Orientacion: ");
            scanf(" %c",&ori[0]);
            
            

            if(ori[0]=='1'){

                if(tablero[X][Y]==' ' && tablero[X][Y+1]==' '){                              
                    tablero[X][Y]='#';                   
                    tablero[X][Y+1]='#';
                    system("clear");
                    return OK;
                }
                else{
                    printf("La ubicacion seleccionada Sale fuera de los limites.\n");
                    getch();
                    system("clear");
                }
                
            }
            else if(ori[0]=='2'){
                if(tablero[X][Y]==' ' && tablero[X+1][Y]==' '){
                    tablero[X][Y]='#';
                    tablero[X+1][Y]='#';
                    system("clear");
                    return OK;
                }
                else{
                    printf("La ubicacion seleccionada Sale fuera de los limites.\n");
                    getch();
                    system("clear");
                }
            }
            else{
                printf("debe responder con 1 o 2\n");
                getch();
                system("clear");
            } 

        }while((ori[0] != '1' && ori[0] != '2'));     
    
        break;

    case 1:

        do{
            system("clear");
            printtablero(tablero);
            printf("Igrese la orientacion del barco.\n");
            printbarco(barco);
            printf("Orientacion: ");
            scanf(" %c",&ori[0]);

            if(ori[0]=='1'){

                if(tablero[X][Y]==' ' && tablero[X][Y+1]==' ' && tablero[X][Y-1]==' '){
                    tablero[X][Y]='#';
                    tablero[X][Y+1]='#';
                    tablero[X][Y-1]='#';
                    system("clear");
                    return OK;
                }
                else{
                    printf("La ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                    getch();
                    system("clear");
                }

            }
            else if(ori[0]=='2'){

                if(tablero[X][Y]==' ' && tablero[X+1][Y]==' ' && tablero[X-1][Y]==' '){
                    tablero[X][Y]='#';
                    tablero[X+1][Y]='#';
                    tablero[X-1][Y]='#';
                    system("clear");
                    return OK;
                }
                else{
                    printf("La ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                    getch();
                    system("clear");
                }
            }
            else {
                printf("debe responder con 1 o 2\n");
                getch();
                system("clear");
            }

        }while(ori[0] != '1' && ori[0] != '2');     
    
        break;

    case 2:

        do{
            system("clear");
            printtablero(tablero);
            printf("Igrese la orientacion del barco.\n");
            printbarco(barco);
            printf("Orientacion: ");
            scanf(" %c",&ori[0]);

            if(ori[0]=='1'){

                if(tablero[X][Y]==' ' && tablero[X][Y+1]==' ' && tablero[X][Y-1]==' ' && tablero[X][Y+2]==' '){

                    tablero[X][Y]='#';
                    tablero[X][Y+1]='#';
                    tablero[X][Y-1]='#';
                    tablero[X][Y+2]='#';
                    system("clear");
                    return OK;
                }
                else{
                    printf("La ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                    getch();
                    system("clear");
                }
            }
            else if(ori[0]=='2'){
                
                if(tablero[X][Y]==' ' && tablero[X+1][Y]==' ' && tablero[X-1][Y]==' ' && tablero[X+2][Y]==' '){
                    tablero[X][Y]='#';
                    tablero[X+1][Y]='#';
                    tablero[X-1][Y]='#';
                    tablero[X+2][Y]='#';
                    system("clear");
                    return OK;
                }
                else{
                    printf("La ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                    getch();
                    system("clear");
                }
            }
            else {
                printf("debe responder con 1 o 2\n");
                getch();
                system("clear");
            }

        }while(ori[0] != '1' && ori[0] != '2');     
    
        break; 

    case 3:

         do{
            system("clear");
            printtablero(tablero);
            printf("Igrese la orientacion del barco.\n");
            printbarco(barco);
            printf("Orientacion: ");
            scanf(" %c",&ori[0]);

            if(ori[0]=='1'){

                if(tablero[X][Y]==' ' && tablero[X][Y+1]==' ' && tablero[X][Y-1]==' ' && tablero[X+1][Y]==' '){

                    tablero[X][Y]='#';                    
                    tablero[X][Y+1]='#';
                    tablero[X][Y-1]='#';
                    tablero[X+1][Y]='#';
                    system("clear");
                    return OK;
                }
                else{
                    printf("La ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                    getch();
                    system("clear");
                }
            }
            else if(ori[0]=='2'){

                if(tablero[X][Y]==' ' && tablero[X+1][Y]==' ' && tablero[X-1][Y]==' ' && tablero[X][Y+1]==' '){
                    tablero[X][Y]='#';
                    tablero[X+1][Y]='#';
                    tablero[X-1][Y]='#';
                    tablero[X][Y+1]='#';
                    system("clear");
                    return OK;
                }
                else{
                    printf("La ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                    getch();
                    system("clear");
                }
            }
            else if(ori[0]=='3'){

                if(tablero[X][Y]==' ' && tablero[X][Y+1]==' ' && tablero[X][Y-1]==' ' && tablero[X-1][Y]==' '){

                    tablero[X][Y]='#';
                    tablero[X][Y+1]='#';
                    tablero[X][Y-1]='#';
                    tablero[X-1][Y]='#';
                    system("clear");
                    return OK;
                }
                else{
                    printf("La ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                    getch();
                    system("clear");
                }
            }
            else if(ori[0]=='4'){

                if(tablero[X][Y]==' ' && tablero[X+1][Y]==' ' && tablero[X-1][Y]==' ' && tablero[X][Y-1]==' '){
                    tablero[X][Y]='#';
                    tablero[X+1][Y]='#';
                    tablero[X-1][Y]='#';
                    tablero[X][Y-1]='#';
                    system("clear");
                    return OK;
                }
                else{
                    printf("La ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                    getch();
                    system("clear");
                }
            }        
            else {
                printf("debe responder con 1, 2, 3 o 4\n");
                getch();
                system("clear");
            }
        }while(ori[0] < '1' && ori[0] > '4');
       
        break;
    }

    return ERROR;
}


int posch(char caracter){

    char posc[28]="ABCDEFGHIJKLMNOPQRSTUVWXYZ@";
    int i;

    for(i=0;i<28;i++){

        if(posc[i]==caracter){
            return i;
        }
    }

    return ERROR;
}


void printbarco(int barco){

   switch (barco){
   
    case 0:
      
        printf("1     2 #\n  ##    #\n\n");

        break;
    case 1:
      
        printf("1      2 #\n  ###    #\n         #\n\n");

        break;
    case 2:
      
        printf("1       2 #\n  ####    #\n          #\n          #\n\n");

        break;
    case 3:
      
        printf("1      2 #   3  #   4  #\n  ###    ##    ###    ##\n   #     #             #\n\n");

        break;    
   }
}


void menu(){

    char opc[14];

    do{

        system("clear");

        for(int i=0;i<14;i++){
            opc[i]=0;
        }

        printf("    ___________________________________________________\n");
        printf("   |  _______________________________________________  |\n");
        printf("   | |                                               | |\n");
        printf("   | |  ***     *   *****   *    *     *        *    | |\n");
        printf("   | |  *  *   * *    *    * *   *     *       * *   | |\n");
        printf("   | |  ****  *   *   *   *   *  *     *      *   *  | |\n");
        printf("   | |  *   * *****   *   *****  *     *      *****  | |\n");
        printf("   | |  *   * *   *   *   *   *  *     *      *   *  | |\n");
        printf("   | |  ****  *   *   *   *   *  ***** ****** *   *  | |\n");
        printf("   | |                                               | |\n");
        printf("   | |        *   *   *   *   *   *    *             | |\n");
        printf("   | |        **  *  * *  *   *  * *   *             | |\n");
        printf("   | |        * * * *   * *   * *   *  *             | |\n");
        printf("   | |        *  ** ***** *   * *****  *             | |\n");
        printf("   | |        *   * *   *  * *  *   *  *             | |\n");
        printf("   | |        *   * *   *   *   *   *  *****         | |\n");
        printf("   | |                                               | |\n");
        printf("   | |_______________________________________________| |\n");
        printf("   |___________________________________________________|\n\n");
        printf("                         JUGAR\n");
        printf("                      INSTRUCCIONES\n");
        printf("                         SALIR\n\n");

        printf("Elija una opción: ");
        scanf("%s",&opc[0]);

        switch (opc[0]){
        
        case 'J':
            system("clear");
            juego();
            break;
        
        case 'I':
            //instrucciones();
            break;
        
        case 'S':
            break;
        }
    }while(strcmp(opc,"SALIR")!=0);
}


void printtablero(char tablero[LARGO][ANCHO]){

    printf("\n     ABCDEFGHIJKLMNOPQRSTUVWXYZ@ ABCDEFGHIJKLMNOPQRSTUVWXYZ@\n");
    for(int i=0;i<12;i++){
        if(i==0 || i==11){
        printf("    %s\n",tablero[i]);    
        }
        else
        printf("  %d %s\n",i-1,tablero[i]);
    }
}


char getch(){

    char buf = 0;
    struct termios old ={0};
    fflush(stdout);
    if(tcgetattr(0,&old) < 0)
      //  perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;    
    old.c_cc[VTIME] = 0; 
    if(tcsetattr(0, TCSANOW,&old) < 0);
      //  perror("tcsetattr ICANON");
    if(read(0,&buf,1) < 0);
     //   perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0);
      //  perror("tcsetattr ~ICANON");

    return buf; 
}
  




