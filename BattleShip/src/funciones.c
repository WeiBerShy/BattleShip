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
    char port[20];
    char player[20];
    char player2[20];
    char posship[3];
    int i;

    

    signal(SIGALRM, sig_handler);
    
    memset(player,0,20);
    memset(player2,0,20);
    memset(buf_rx,0,100);

    system("clear");
    logo();
    printf("Ingrese la direccion IP: ");
    fgets(ip,20,stdin);
    rectStrings(ip);
    system("clear");
    logo();
    printf("Ingrese el puerto: ");
    fgets(port,20,stdin);
    rectStrings(port);
    
    
    
    system("clear");
    logo();
    printf("Esperando al JUGADOR 2...\n");

    if((sockaux=Open_conection(&servaddr, ip, atoi(port)))==ERROR){
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
    rectStrings(player);


    write(sockfd,player,strlen(player));

    byre = read(sockfd,player2,sizeof(player2));

    buf_rx[byre]=0;

    i=0;
    do{
        system("clear");
        print_tablero(player, player2);
        printf("COLOCACION DE BARCOS\n\n");
        printbarco(i);
        printf("Ingrese la posicion: ");
        fgets(posship,3,stdin);
        rectStrings(posship);
        i++;
        
    }while(i<CANTSHIP);
        
    
}

void beClient(){

    
    int sockfd,byte;
    char buf_tx[100]="que pasa pa";
    char buf_rx[100];
    char cadenas[2][20];
    char player[20];
    char player2[20];
    
    
    memset(player,0,20);
    memset(player2,0,20);

    

    system("clear");
    logo();
    printf("Ingrese una IP o nombre de Host: ");
    fgets(cadenas[0],20,stdin);
    rectStrings(cadenas[0]);
    system("clear");
    logo();
    printf("Ingrese el puerto: ");
    fgets(cadenas[1],20,stdin);
    rectStrings(cadenas[1]);

    

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
    fgets(player,20,stdin);
    rectStrings(player);
    
    if((byte=read(sockfd,player2,sizeof(player2)))<0){
        printf("No se pudo leer el socket\n");
    }
    else{
        buf_rx[byte]=0;
    }

    write(sockfd,player,strlen(player));

    

        
   

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
    
    espacio=(28-lenp1);

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
        if((string[i]>='0' && string[i]<='9') || (string[i]>='a' && string[i]<='z') || (string[i]>='A' && string[i]<='Z') || string[i]==' ' || string[i]=='.'){
            aux[j]=string[i];
            aux[j+1]=0;
            j++;
        }
    }
    strcpy(string,aux);
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

void juego(int sockfd, char* p1, char* p2){

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

    int orientacion;
    char ori[2];
    char pos[3];
    int barco;
    int flag;
    

   /* do{
        system("clear");
        print_tablero(p1, p2);
        printf("COLOCACION DE BARCOS\n\n");
        for(i=0;i<=CANTSHIP;i++){
            printbarco(i);
            printf("Ingrese la orientacion: ");
            fgets(poss,2,stdin);
            rectStrings(poss);
            pos=atoi(poss);
        }
        
    }while(i!=CANTSHIP);*/

    for(barco=0;barco<CANTSHIP;barco++){
        system("clear");
        print_tablero(p1, p2);
        printf("COLOCACION DE BARCOS\n\n");
        do{
            printbarco(barco);
            printf("Ingrese la orientacion del BARCO %d:  ",barco+1);
            fgets(ori,2,stdin);
            rectStrings(ori);
            orientacion=atoi(ori);
            flag=posship(tablero,orientacion,barco,pos);
        }while(flag!=OK);
        

           
    }


   /* for(int barco=0;barco<CANTSHIP;barco++){
        do{  

            printtablero(tablero);
            printf("Ingrese la posicion: ");
            scanf("%s",pos);
            flag = posship(tablero,barco,pos);
        }
        while(flag!=OK);

           
    }*/
}


int posship(char tablero[LARGO][ANCHO], int orientacion, int barco, char* posicion){

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








