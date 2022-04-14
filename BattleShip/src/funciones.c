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
        menu3(); // CAMBIAR A MENU 2
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
   

    

    signal(SIGALRM, sig_handler);
    
    

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
 
    alarm(15);

    sockfd=Aceptar_pedidos(sockaux);
    
    alarm(0);

 

//---------ACA ARRANCA----------//
    
   

    
    do{

        memset(player,0,20);
        memset(player2,0,20);
        memset(buf_rx,0,100);

        system("clear");
        logo();
        printf("Ingrese su Nombre: ");
        fgets(player,20,stdin);
        rectStrings(player);
        if(strlen(player)>=4){
            printf("\nESPERANDO AL PLAYER 2...");
            sleep(5);
        }
        
        else if(strlen(player)<4){
            printf("\nEl NOMBRE debe tener al menos 4 caracteres.\n");
            printf("\nPRESIONE ENTER PARA REINTENTAR...");
            getch();
        }
        else{
            printf("hola\n");
            getch();
            //CORREGIR NO SALE EL PRINT DE ARRIBA
        }

    }while(strlen(player)<4);

    

    write(sockfd,player,strlen(player));

    byre = read(sockfd,player2,sizeof(player2));

    player2[byre]=0;

    juego(sockfd,player,player2);
        
    
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



    do{

        memset(player,0,20);
        memset(player2,0,20);
        memset(buf_rx,0,100);

        system("clear");
        logo();
        printf("Ingrese su Nombre: ");
        fgets(player,20,stdin);
        rectStrings(player);
        
        if(strlen(player)>=4){
            printf("\nESPERANDO AL PLAYER 2...");
            //CORREGIR NO SALE EL PRINT DE ARRIBA
            sleep(5);
        }
        
        else if(strlen(player)<4){
            printf("\nEl NOMBRE debe tener al menos 4 caracteres.\n");
            printf("\nPRESIONE ENTER PARA REINTENTAR...");
            getch();
        }

    }while(strlen(player)<4);

    


    if((byte=read(sockfd,player2,sizeof(player2)))<0){
        printf("No se pudo leer el socket\n");
    }
    else{
        player2[byte]=0;
    }

    write(sockfd,player,strlen(player));

    

    juego(sockfd,player,player2);
   

}


void sig_handler(int sig){
    menu3();
}


void chottoMatte(int sig){
    sleep(0.1);
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
    char pos[3];
    int barco;
    int flag;
    
    memset(pos,0,3);

    for(barco=0;barco<CANTSHIP;barco++){
        do{
            do{
                system("clear");
                print_tablero(p1, p2);
                printf("COLOCACION DE BARCOS\n\n");
                printbarco(barco);
                printf("Ingrese la orientacion del BARCO %d:  ",barco+1);
                scanf("%d",&orientacion);

                if(barco<3 && (orientacion>2 || orientacion<1)){
                    printf("La orientacion ingresada no es valida\n\n");
                    printf("PRESIONE ENTER PARA REINTENTAR...");
                    flag=ERROR;
                    getch();
                }
                else if(barco==3 && (orientacion>4 || orientacion<1)){
                    printf("La orientacion ingresada no es valida\n\n");
                    printf("PRESIONE ENTER PARA REINTENTAR...");
                    flag=ERROR;
                    getch();
                }
                else{
                    flag=OK;
                }

            }while(flag!=OK);

            flag=ERROR;

            do{
                system("clear");
                print_tablero(p1, p2);
                printf("COLOCACION DE BARCOS\n\n");
                printf("Ingrese la posición del BARCO %d:  ",barco+1);
                //limpio el buffer
                while(getchar() != '\n');
                fgets(pos,3,stdin);
                rectStrings(pos);
                
                flag=check(pos);

                if(flag==ERROR){
                    printf("La posicion ingresada no es valida\n\n");
                    printf("PRESIONE ENTER PARA REINTENTAR...");
                    getch();
                }
                else{
                    //limpio el buffer
                    while(getchar() != '\n');   
                }

            }while(flag!=OK);  

            flag=ERROR;

            flag=posship(tablero,orientacion,barco,pos);

        }while(flag!=OK);
        

           
    }

}


int posship(char tablero[LARGO][ANCHO], int orientacion, int barco, char* posicion){

    
    int X,Y;
    char x[2];
  
    //guarto el ultimo caracter de posicion en x junto a '\0'
    for(int i=0;i<2;i++){
        x[i]=posicion[i+1];
    }
    
    X=atoi(x)+1;
    Y=posch(posicion[0])+1;
 
    switch (barco){
    
    case 0:           

        if(orientacion==1){

            if(tablero[X][Y]==' ' && tablero[X][Y+1]==' '){                              
                tablero[X][Y]='#';                   
                tablero[X][Y+1]='#';
                system("clear");
                return OK;
            }
            else{
                printf("\nLa ubicacion seleccionada Sale fuera de los limites.\n");
                printf("\nPRECIONES ENTER PARA REINTENTAR...");
                getch();
                system("clear");
                return ERROR;
            }
            
        }
        else if(orientacion==2){
            if(tablero[X][Y]==' ' && tablero[X+1][Y]==' '){
                tablero[X][Y]='#';
                tablero[X+1][Y]='#';
                system("clear");
                return OK;
            }
            else{
                printf("\nLa ubicacion seleccionada Sale fuera de los limites.\n");
                printf("\nPRECIONES ENTER PARA REINTENTAR...");
                getch();
                system("clear");
                return ERROR;
            }
        }


          
    
        break;

    case 1:

        if(orientacion==1){

            if(tablero[X][Y]==' ' && tablero[X][Y+1]==' ' && tablero[X][Y-1]==' '){
                tablero[X][Y]='#';
                tablero[X][Y+1]='#';
                tablero[X][Y-1]='#';
                system("clear");
                return OK;
            }
            else{
                printf("\nLa ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                printf("\nPRECIONES ENTER PARA REINTENTAR...");
                getch();
                system("clear");
                return ERROR;
            }

        }
        else if(orientacion==2){

            if(tablero[X][Y]==' ' && tablero[X+1][Y]==' ' && tablero[X-1][Y]==' '){
                tablero[X][Y]='#';
                tablero[X+1][Y]='#';
                tablero[X-1][Y]='#';
                system("clear");
                return OK;
            }
            else{
                printf("\nLa ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                printf("\nPRECIONES ENTER PARA REINTENTAR...");
                getch();
                system("clear");
                return ERROR;
            }
        }
           
    
        break;

    case 2:

        if(orientacion==1){

            if(tablero[X][Y]==' ' && tablero[X][Y+1]==' ' && tablero[X][Y-1]==' ' && tablero[X][Y+2]==' '){

                tablero[X][Y]='#';
                tablero[X][Y+1]='#';
                tablero[X][Y-1]='#';
                tablero[X][Y+2]='#';
                system("clear");
                return OK;
            }
            else{
                printf("\nLa ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                printf("\nPRECIONES ENTER PARA REINTENTAR...");
                getch();
                system("clear");
                return ERROR;
            }
        }
        else if(orientacion==2){
            
            if(tablero[X][Y]==' ' && tablero[X+1][Y]==' ' && tablero[X-1][Y]==' ' && tablero[X+2][Y]==' '){
                tablero[X][Y]='#';
                tablero[X+1][Y]='#';
                tablero[X-1][Y]='#';
                tablero[X+2][Y]='#';
                system("clear");
                return OK;
            }
            else{
                printf("\nLa ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                printf("\nPRECIONES ENTER PARA REINTENTAR...");
                getch();
                system("clear");
                return ERROR;
            }
        }
          
    
        break; 

    case 3:

         

        if(orientacion==1){

            if(tablero[X][Y]==' ' && tablero[X][Y+1]==' ' && tablero[X][Y-1]==' ' && tablero[X+1][Y]==' '){

                tablero[X][Y]='#';                    
                tablero[X][Y+1]='#';
                tablero[X][Y-1]='#';
                tablero[X+1][Y]='#';
                system("clear");
                return OK;
            }
            else{
                printf("\nLa ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                printf("\nPRECIONES ENTER PARA REINTENTAR...");
                getch();
                system("clear");
                return ERROR;
            }
        }
        else if(orientacion==2){

            if(tablero[X][Y]==' ' && tablero[X+1][Y]==' ' && tablero[X-1][Y]==' ' && tablero[X][Y+1]==' '){
                tablero[X][Y]='#';
                tablero[X+1][Y]='#';
                tablero[X-1][Y]='#';
                tablero[X][Y+1]='#';
                system("clear");
                return OK;
            }
            else{
                printf("\nLa ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                printf("\nPRECIONES ENTER PARA REINTENTAR...");
                getch();
                system("clear");
                return ERROR;
            }
        }
        else if(orientacion==3){

            if(tablero[X][Y]==' ' && tablero[X][Y+1]==' ' && tablero[X][Y-1]==' ' && tablero[X-1][Y]==' '){

                tablero[X][Y]='#';
                tablero[X][Y+1]='#';
                tablero[X][Y-1]='#';
                tablero[X-1][Y]='#';
                system("clear");
                return OK;
            }
            else{
                printf("\nLa ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                printf("\nPRECIONES ENTER PARA REINTENTAR...");
                getch();
                system("clear");
                return ERROR;
            }
        }
        else if(orientacion==4){

            if(tablero[X][Y]==' ' && tablero[X+1][Y]==' ' && tablero[X-1][Y]==' ' && tablero[X][Y-1]==' '){
                tablero[X][Y]='#';
                tablero[X+1][Y]='#';
                tablero[X-1][Y]='#';
                tablero[X][Y-1]='#';
                system("clear");
                return OK;
            }
            else{
                printf("\nLa ubicacion seleccionada ya esta ocupada o sale fuera de los limites.\n");
                printf("\nPRECIONES ENTER PARA REINTENTAR...");
                getch();
                system("clear");
                return ERROR;
            }
        }        
       
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












