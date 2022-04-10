#include "funciones.h"


void menu(){

    char resp[20];
    int res;


    do{

        system("clear");
        logo();
        printf("                         JUGAR\n");
        printf("                     INSTRUCCIONES\n");
        printf("                        CREDITOS\n");
        printf("                         SALIR\n\n");
        printf("Elije una opción: ");
        fgets(resp,20,stdin);
        rectStrings(resp);

        res= convRespToNum(resp, MENU1);

        if(res==ERROR){
            system("clear");
            logo();
            printf("\nOpcion inválida.\n");
            sleep(2);
        }
    }while(res==ERROR);


    if(res==JUGAR){
        system("clear");
        menu2();
    }
    else if(res==INSTRUCCIONES){
        //instrc();
    }
    else if(res==CREDITOS){
        //credit();
    }
    else{
        printf("Cerrando el juego...\n");
        sleep(2);
        exit(-1);
    }
    
}

void menu2(){

    char resp[20];
    int res;

    memset(resp,0,20);
    do{
        system("clear");
        logo();
        printf("                      COOP vs AI\n");
        printf("                        ONLINE\n");
        printf("                       REGRESAR\n\n\n");
        printf("Elije una opción: ");

        fflush(stdin);
        memset(resp,0,sizeof(resp));
        fgets(resp,20,stdin);

        rectStrings(resp); 

        res=convRespToNum(resp, MENU2);

        if(res==ERROR){

            system("clear");
            logo();
            printf("\nOpcion inválida.\n");
            sleep(2);
        }
    }while(res==ERROR);

    if(res==COOP){
        //coop();
    }
    else if(res==ONLINE){
        system("clear");
        menu3();
    }
    else if(res==REGRESAR){
        system("clear");
        menu();
    }

}

void menu3(){

    char resp[20];
    int res=ERROR;
    

    memset(resp,0,20);
    while(res==ERROR){
        system("clear");
        logo();
        printf("                      CLIENT\n");
        printf("                      SERVER\n");
        printf("                     REGRESAR\n\n\n");
        
        printf("Elije una opción: ");
        memset(resp,0,sizeof(resp));
        fgets(resp,20,stdin);

        rectStrings(resp);

        res=convRespToNum(resp, MENU3);

        if(res==ERROR){
            system("clear");
            logo();
            printf("\nOpcion inválida.\n");
            sleep(2);
        }
    }

    if(res==CLIENT){
        beClient();
        menu3();
    }
    else if(res==SERVER){
        beServer();
        menu3();
    }
    else if(res==REGRESAR){
        system("clear");
        menu2();
    }

}

int convRespToNum(char* resp, int menu){
    /*FUNCION QUE DEVUELVE UN NUMERO SI COINCIDE CON LA PALABRA INGRESADA*/

    if(menu==MENU1){

        if(!strcmp(resp,"JUGAR") || !strcmp(resp,"jugar")){
            return JUGAR;
        }
        else if(!strcmp(resp,"INSTRUCCIONES") || !strcmp(resp,"instrucciones")){
            return INSTRUCCIONES;        
        }
        else if(!strcmp(resp,"CREDITOS") || !strcmp(resp,"creditos")){
            return CREDITOS;        
        }
        else if(!strcmp(resp,"SALIR") || !strcmp(resp,"salir")){
            return SALIR;
        }
    }
    else if(menu==MENU2){
        if(!strcmp(resp,"coop vs ai") || !strcmp(resp,"COOP VS AI")){
            return COOP;
        }
        else if(!strcmp(resp,"online") || !strcmp(resp,"ONLINE")){
            return ONLINE;
        }
        else if(!strcmp(resp,"regresar") || !strcmp(resp,"REGRESAR")){
            return REGRESAR;
        }
    }
    else if(menu==MENU3){
        if(!strcmp(resp,"client") || !strcmp(resp,"CLIENT")){
            return CLIENT;
        }
        else if(!strcmp(resp,"server") || !strcmp(resp,"SERVER")){
            return SERVER;
        }
        else if(!strcmp(resp,"regresar") || !strcmp(resp,"REGRESAR")){
            return REGRESAR;
        }
    }    

    return ERROR;

}


void beServer(){
    
    struct sockaddr_in servaddr;
    int sockfd, sockaux,byre;
    char buf_tx[100]="ELLA NO TE ANHELA";
    char buf_rx[100];
    char ip[20];
    int port;
    char player[20];
    char player2[20];
    char posship[3];

    

    signal(SIGALRM, sig_handler);
    
    memset(player,0,20);
    memset(player2,0,20);
    memset(buf_rx,0,100);

    system("clear");
    logo();
    printf("Ingrese la direccion IP: ");
    scanf("%s",ip);
    system("clear");
    logo();
    printf("Ingrese el puerto: ");
    scanf("%d",&port);
    
    
    
    system("clear");
    logo();
    printf("Esperando al JUGADOR 2...\n");

    if((sockaux=Open_conection(&servaddr, ip, port))==ERROR){
        system("clear");
        logo();
        printf("IP invalido o PUERTO no disponible en este momento.\n");
        sleep(2);
        return;
    }
 
    alarm(30);

    sockfd=Aceptar_pedidos(sockaux);
    
    alarm(0);

//---------ACA ARRANCA----------//

    system("clear");
    logo();
    printf("Ingrese su Nombre: ");
    fgets(player,20,stdin);
    fgets(player,20,stdin);


    write(sockfd,player,strlen(player));

    byre = read(sockfd,player2,sizeof(player2));

    buf_rx[byre]=0;

        
    system("clear");
    print_tablero(player,player2);
    printf("COLOCACION DE BARCOS\n\n");
    printf("Ingrese la posicion: ");
    scanf("%s",posship);

        
    
}

void beClient(){

    
    int sockfd,byte;
    char buf_tx[100]="que pasa pa";
    char buf_rx[100];
    char cadenas[2][20];
    char player[20];
    char player2[20];
    char posship[3];
    
    memset(player,0,20);
    memset(player2,0,20);

    

    system("clear");
    logo();
    printf("Ingrese una IP o nombre de Host: ");
    scanf("%s",cadenas[0]);
    system("clear");
    logo();
    printf("Ingrese el puerto: ");
    scanf("%s",cadenas[1]);

    

    sockfd = conectar(cadenas);


    if(sockfd==ERROR){
        system("clear");
        logo();
        printf("No se pudo realizar la conexión.\n");
        sleep(2);
        system("clear");
        return;
    }
    system("clear");
    logo();
    printf("Ingrese su Nombre: ");
    fflush(stdin);
    fgets(player,20,stdin);
    fgets(player,20,stdin);
    
    if((byte=read(sockfd,player2,sizeof(player2)))<0){
        printf("No se pudo leer el socket\n");
    }
    else{
        buf_rx[byte]=0;
    }

    write(sockfd,player,strlen(player));

    system("clear");
    print_tablero(player, player2);
    printf("COLOCACION DE BARCOS\n\n");
    printf("Ingrese la posicion: ");
    scanf("%s",posship);


        
   

}


void sig_handler(int sig){
    printf("entro\n");
    menu3();
}

void logo(){
    printf(" ____________________________________________________\n");
    printf("|   ______________________________________________   |\n");
    printf("|  |                                              |  |\n");
    printf("|  |  ***     *   *****   *    *     *       *    |  |\n");
    printf("|  |  *  *   * *    *    * *   *     *      * *   |  |\n");
    printf("|  |  ****  *   *   *   *   *  *     *     *   *  |  |\n");
    printf("|  |  *   * *****   *   *****  *     *     *****  |  |\n");
    printf("|  |  *   * *   *   *   *   *  *     *     *   *  |  |\n");
    printf("|  |  ****  *   *   *   *   *  ***** ***** *   *  |  |\n");
    printf("|  |                                              |  |\n");
    printf("|  |        *   *   *   *   *    *   *            |  |\n");
    printf("|  |        **  *  * *  *   *   * *  *            |  |\n");
    printf("|  |        * * * *   * *   *  *   * *            |  |\n");
    printf("|  |        *  ** ***** *   *  ***** *            |  |\n");
    printf("|  |        *   * *   *  * *   *   * *            |  |\n");
    printf("|  |        *   * *   *   *    *   * *****        |  |\n");
    printf("|  |______________________________________________|  |\n");
    printf("|____________________________________________________|\n\n");
}

void print_tablero(char* p1, char* p2){

    int lenp1=strlen(p1);
    int espacio;
    
    rectStrings(p1);
    rectStrings(p2);
    
    espacio=(29-lenp1);

    printf("    %s",p1);
    for(int i=0;i<espacio;i++){
        printf(" ");
    }
    printf("%s\n",p2);
    printf("    ABCDEFGHIJKLMNOPQRSTUVWXYZ@ ABCDEFGHIJKLMNOPQRSTUVWXYZ@\n");
    printf("    -------------------------------------------------------\n");
    printf(" 0 |                           |                          |\n");
    printf(" 1 |                           |                          |\n");
    printf(" 2 |                           |                          |\n");
    printf(" 3 |                           |                          |\n");
    printf(" 4 |                           |                          |\n");
    printf(" 5 |                           |                          |\n");
    printf(" 6 |                           |                          |\n");
    printf(" 7 |                           |                          |\n");
    printf(" 8 |                           |                          |\n");
    printf(" 9 |                           |                          |\n");
    printf("    -------------------------------------------------------\n\n");

}

void rectStrings(char* string){
    int i,j=0;
    char aux[20];
    int len=strlen(string);

    for(i=0;i<len;i++){
        if((string[i]>='0' && string[i]<='9') || (string[i]>='a' && string[i]<='z') || (string[i]>='A' && string[i]<='Z') || string[i]==' '){
            aux[j]=string[i];
            aux[j+1]=0;
            j++;
        }
    }
    strcpy(string,aux);
}










