#include <stdio.h>
#include <wchar.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "list.h"
#include "map.h"

#define ROJO_F "\e[41m"
#define VERDE_F "\e[42m"
#define AMARILLO_F "\e[43m"	
#define RESET_COLOR "\e[0m"

double horaGeneral = 0;

typedef struct{
    int asientosOcupados;
    int asientosTotales;
    int asientos[50][50];
    int asientosComprados;
}avion;

typedef struct{
    char * empresa;
    char * ciudad;
    char * pais;
    avion * infoAvion;
    double hora;
    bool ofertaAplicada;
    int precio;
    bool habilitado;
}vuelo;

typedef struct{
    char * empresa;
    char * ciudad;
    char * pais;
    int descuento;
}ofertaVuelo;

// Prototipos
int isEqualString(void * key1, void * key2);
char*get_csv_field (char * tmp, int k);
Map* importarVuelos(Map * mapaVuelos);
Map* importarOfertas(Map* mapaVuelos);
void*creacionAviones(Map * mapaVuelos);
void* poblarAvion(Map* mapaVuelos);
void* modoPasajero(Map* mapaVuelos, List* listaPasajes);
void* modoAdministrador(Map* mapaVuelos, List* listaPasajes);
void* revisionHoraAvion(double horaGeneral, Map* mapaVuelos);
void* comprarPasaje(Map* mapaVuelos, List* listaPasajes);
void* busquedaVuelos(Map* mapaVuelos,List*listaPasajes);
void * consultaPasajes(Map * mapaVuelos,List *listaPasajes);
void* ofertasAplicadas(Map* mapaVuelos,List* listaPasajes);

int main (){

    Map* mapaVuelos = createMap(isEqualString);
    List* listaPasajes = createList();
    List*aviones = createList();
    importarVuelos(mapaVuelos); 
    importarOfertas(mapaVuelos);
    creacionAviones(mapaVuelos);
    poblarAvion(mapaVuelos);
    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  BIENVENIDO A AEREOLINEAS GC  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~! \n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
    int opcion = 1;
    while(opcion != 0){

        printf("\n                                                            MENU DE OPCIONES");
        printf("\n");
        printf("                                                    ~~----------------------------~~\n");
        printf("                                                     | 1. Comprar pasaje.         |\n");
        printf("                                                     | 2. Busqueda de vuelos.     |\n");
        printf("                                                     | 3. Consulta pasajes.       |\n");
        printf("                                                     | 4. Ofertas aplicadas.      |\n");
        printf("                                                     | 0. Salir del programa.     |\n");
        printf("                                                    ~~----------------------------~~");
        printf("\n\n");
        
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);
        printf("\n");

        switch (opcion){
            case 1: comprarPasaje(mapaVuelos,listaPasajes);break;
            case 2: busquedaVuelos(mapaVuelos,listaPasajes);break;
            case 3: consultaPasajes(mapaVuelos,listaPasajes);break;
            case 4: ofertasAplicadas(mapaVuelos,listaPasajes);break;
            default: break;
        }
    }

    return 0;
}

int isEqualString(void * key1, void * key2){
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

//Funcion para sacar las lineas de un csv.
char * get_csv_field (char * tmp, int k){
    int open_mark = 0;
    char* ret=(char*) malloc(100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){
        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }
        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }
        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }
        i++;
    }
    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }
    return NULL;
}

/*
    Funcion que apartir del mapaVuelos crea la forma de los aviones (sean de 100, 90 u 80 pasajeros)
*/
void*creacionAviones(Map * mapaVuelos){
    List * L;
    L = firstMap(mapaVuelos);
    int i,j;
    while(L != NULL){
        vuelo * vueloP = (vuelo*)malloc(sizeof(vuelo));
        vueloP  = firstList(L);
        while(vueloP !=NULL){
            
            //FORMA AVION PARA 100 PASAJEROS 
            if(vueloP ->infoAvion->asientosTotales == 100){
                
                int i,j;

                for(i = 0 ; i < 30 ; i++) vueloP->infoAvion->asientos[0][i]=3;
       
                for(i = 0 ; i < 30 ; i++) vueloP->infoAvion->asientos[1][i]=3;

                for(i = 0 ; i < 30 ; i++) vueloP->infoAvion->asientos[2][i]=3;
                
                for(i = 0 ; i < 30 ; i++) vueloP->infoAvion->asientos[3][i]=3;
               
            }
            
            //FORMA AVION PARA 90 PASAJEROS
            if(vueloP->infoAvion->asientosTotales == 90){

                for(i = 0 ; i < 3 ; i++){
                    for(j = 0 ; j < 30; j++){
                        vueloP->infoAvion->asientos[i][j]=3;
                    } 
                }


            }

            //FORMA AVION PARA 80 PASAJEROS
            if(vueloP->infoAvion->asientosTotales == 80){

                
                for(i = 0 ; i < 4 ; i++){
                    for(j = 0 ; j < 20; j++){
                        vueloP->infoAvion->asientos[i][j]=3;
                    } 
                }
            }
            
            vueloP = nextList(L);
        }
        L = nextMap(mapaVuelos);
    }
}

//Funcion que dependiendo de la forma del avion, pobla este con sus asientos
void* poblarAvion(Map* mapaVuelos){

    srand(time(NULL));
    List * L;
    int i,j;
    int numeroRandom;
    int contAsientosTomados=0;

    L = firstMap(mapaVuelos);
    while(L != NULL){
        vuelo * vueloP = (vuelo*)malloc(sizeof(vuelo));
        vueloP = firstList(L);
        while(vueloP!=NULL){
            if(vueloP->infoAvion->asientosTotales == 100){
                
                //Con rand damos los valores a los asientos
                //Si es 0, estará disponible y si es 1, ocupado.
                //Se repiten en todas las filas de las matrices de aviones.
                contAsientosTomados = 0;
                for(i = 0 ; i < 20 ; i++){ 
                    numeroRandom = rand()%2;
                    vueloP->infoAvion->asientos[0][i]=numeroRandom;
                    if(numeroRandom==1){
                        contAsientosTomados++;
                    }
                    
                }

                for(i = 0 ; i < 30 ; i++){ 
                    numeroRandom = rand()%2;
                    vueloP->infoAvion->asientos[1][i]=numeroRandom;
                    if(numeroRandom==1){
                        contAsientosTomados++;
                    }
                    
                }

                for(i = 0 ; i < 30 ; i++){
                    numeroRandom = rand()%2;
                    vueloP->infoAvion->asientos[2][i]=numeroRandom;
                    if(numeroRandom==1){
                        contAsientosTomados++;
                    }
                }

                for(i = 0 ; i < 20 ; i++){  
                    numeroRandom = rand()%2;
                    vueloP->infoAvion->asientos[3][i]=numeroRandom;
                    if(numeroRandom==1){
                        contAsientosTomados++;
                    }
                }

                vueloP->infoAvion->asientosOcupados= contAsientosTomados;
            }

            if(vueloP->infoAvion->asientosTotales == 90){
                
                contAsientosTomados=0;
                for(i = 0 ; i < 3 ; i++){
                    for(j = 0 ; j < 30; j++){
                        numeroRandom = rand()%2;
                        vueloP->infoAvion->asientos[i][j]=numeroRandom;
                        if(numeroRandom==1){
                            contAsientosTomados++;
                        }
                    } 
                }
                vueloP->infoAvion->asientosOcupados= contAsientosTomados;
            }

            if(vueloP->infoAvion->asientosTotales == 80){
                
                contAsientosTomados=0;
                for(i = 0 ; i < 4 ; i++){
                    for(j = 0 ; j < 20; j++){
                        numeroRandom = rand()%2;
                        vueloP->infoAvion->asientos[i][j]=numeroRandom;
                        if(numeroRandom==1){
                            contAsientosTomados++;
                        }
                        
                    }
                }
                vueloP->infoAvion->asientosOcupados= contAsientosTomados;
            }
            vueloP = nextList(L);
        }  
        L = nextMap(mapaVuelos); 
    }
}

//Se verifica si la horaGeneral es mayor o igual que la hora de un avion en el mapa de vuelos.
//Se inhabilitan en el caso de que sea asi.
void* revisionHoraAvion(double horaGeneral,Map* mapaVuelos){

    if(horaGeneral == 24){
        printf("No hay mas vuelos disponibles.\n");
        exit(1);
    }

    //Separamos la parte decimal y entera de la horaGeneral y las metemos en variables.
    double parteDecimal, auxHoraG, parteEntera;
    auxHoraG = horaGeneral;
    parteDecimal = modf(auxHoraG,&parteEntera);

    // 30 minutos funcionan como 0.5, le restamos 0.2 para que se hagan bien los calculos
    if(parteDecimal == 0.5){
       auxHoraG = auxHoraG - 0.2;
    }
    printf("\n");
    printf("Hora general: %.2lf\n",auxHoraG);
    List * L;
    L = firstMap(mapaVuelos);

    //Se recorre el mapa de vuelos para inhabilitar un viaje si la horaGeneral es mayor a este.
    while(L != NULL){
        vuelo * vueloH = (vuelo*)malloc(sizeof(vuelo));
        vueloH = firstList(L);
        while(vueloH!=NULL){
            if(vueloH->hora <= auxHoraG){
                if(vueloH->habilitado == true){
                    vueloH->habilitado = false;
                    printf("Vuelo hacia %s,%s ha sido inhabilitado.\n",vueloH->ciudad,vueloH->pais);
                }
                
            }
            vueloH = nextList(L);
        }
        L = nextMap(mapaVuelos);
    }

}

//Se verifica si los vuelos comprados superan o no la horaGeneral del programa.
void * revisarHoraVuelosComprados(double horaGeneral, List * listaPasajes){
    vuelo * vueloLista = (vuelo*)malloc(sizeof(vuelo));
    vueloLista = firstList(listaPasajes);
    if(vueloLista == NULL){
        printf("No hay pasajes comprados.\n\n");
    }

    //Separamos la parte decimal y entera de la horaGeneral y las metemos en variables.
    double parteDecimal, auxHoraG, parteEntera;
    auxHoraG = horaGeneral;
    parteDecimal = modf(auxHoraG,&parteEntera);

    // 30 minutos funcionan como 0.5, le restamos 0.2 para que se hagan bien los calculos
    if(parteDecimal == 0.5){
       auxHoraG = auxHoraG - 0.2;
    }

    //Recorre la lista de pasajes buscando si la hora general es igual o mayor que la hora de un vuelo
    //Se dará la opcion al pasajero de tomar ese vuelo y salir del programa o cancelarlo.
    while(vueloLista!=NULL){
        if(auxHoraG>= vueloLista->hora){
            printf("Su vuelo hacia %s,%s esta a punto de partir!.\n",vueloLista->ciudad,vueloLista->pais);

            printf("¿Desea tomar definitivamente el vuelo? Escriba 'Si' si lo desea: ");
            char * confirmacion = (char*)malloc(3*sizeof(char));
            confirmacion = "Si";
            char* palabra = (char*)malloc(3*sizeof(char));
            scanf("%s", palabra);

            if(strcmp(palabra,confirmacion) == 0){
                printf("Vuelo no cancelado. Que tenga un buen viaje!.\n");
                exit(1);
                
            }
            else{
                popCurrent(listaPasajes);
            }
        }
        vueloLista = nextList(listaPasajes);
    }
}

// Se ingresan los datos del csv Vuelos a estructuras vuelo para llenarlos en el mapa de listas.
Map * importarVuelos(Map * mapaVuelos){
    char archivo[101];
    FILE* file;

    //Se pide el nombre del .csv.
    do{
        printf("Ingresar nombre archivo: ");
        scanf("%s", &archivo);
        strcat(archivo, ".csv");
        file = fopen(archivo, "r");
    }while(!file);

    char lineaArchivo[1024];
    int i;
    int cont = 0;

    //Se recorren las lineas del .csv.
    while (fgets (lineaArchivo, 1024, file) != NULL) {

        vuelo* vueloC = (vuelo*) malloc (sizeof(vuelo));
        avion* avionC = (avion*) malloc ( sizeof(avion));

        for(i = 0; i <= 6; i++){

            char* aux = get_csv_field(lineaArchivo,i);

            if(i == 0) vueloC->empresa = aux; 
            
            if(i == 1) vueloC->pais = aux;

            if(i == 2) vueloC->ciudad = aux;

            if(i == 3) vueloC->precio = atoi(aux);
            
            if(i == 4) avionC->asientosTotales = atoi(aux);

            if(i == 5) vueloC->hora = atof(aux);

            vueloC->ofertaAplicada = false;
            vueloC->habilitado = true;
            avionC->asientosComprados=0;
            vueloC->infoAvion = avionC;
        }

        //Como usamos mapa de listas, buscamos si existe un destino asociado a una lista,
        //si existe la lista, se mete el vuelo en la lista, si no, se crea la lista y se mete el vuelo.
        const char * M;
        M = searchMap(mapaVuelos,vueloC->ciudad);
        if(M == NULL){
            List * listaVuelos = createList();
            pushFront(listaVuelos,vueloC);
            insertMap(mapaVuelos,vueloC->ciudad,listaVuelos);
        }
        else{
            List * L = (List*)searchMap(mapaVuelos,vueloC->ciudad);
            pushFront(L,vueloC);
        }
        
        cont++; 
        if(cont == 42) break;
    } 
    
    
}
 
//Funcion para aplicar ofertas del csv Ofertas a el mapa de listas con vuelos.
Map * importarOfertas(Map * mapaVuelos){
    
    FILE* file;
    file = fopen("Ofertas.csv","r");
    List * listaOfertas = createList();

    char lineaArchivo[1024];
    int i;
    int cont = 0;

    while (fgets (lineaArchivo, 1024, file) != NULL) {
        ofertaVuelo * oferta = (ofertaVuelo*)malloc(sizeof(ofertaVuelo));

        for(i = 0; i <= 4; i++){
            
            char* aux = get_csv_field(lineaArchivo,i);

            if(i == 0) oferta->empresa = aux;
            
            if(i == 1) oferta->pais = aux;

            if(i == 2) oferta->ciudad = aux;

            if(i == 3) oferta->descuento = atoi(aux);
        }
        pushBack(listaOfertas,oferta);
        cont++; 
        if(cont == 20) break;
    }

    //Pasamos por cada vuelo de la lista de ofertas buscando si está en el mapa de vuelos.
    ofertaVuelo * L = (ofertaVuelo*)malloc(sizeof(ofertaVuelo));
    L = firstList(listaOfertas);
    while(L != NULL){

        List * M = (List*)searchMap(mapaVuelos,L->ciudad);

        vuelo * vueloOferta = (vuelo*)malloc(sizeof(vuelo));
        vueloOferta = firstList(M);

        while(vueloOferta != NULL){
            
            bool uno = false, dos = false, tres = false;

            if(strcmp(vueloOferta->empresa,L->empresa) == 0){ 
                uno = true;
            }
            if(strcmp(vueloOferta->pais,L->pais) == 0){
                dos = true;
            }
            if(strcmp(vueloOferta->ciudad,L->ciudad) == 0){
                tres = true;
            } 
                
            //Si las 3 condiciones son true se aplicará la oferta
            if(tres == true && dos == true && uno == true){
                double descuento;
                descuento = (double)L->descuento / 100; // Calculo para saber el descuento
                vueloOferta->precio = vueloOferta->precio - (vueloOferta->precio * descuento); // Para obtener el precio se aplica la formula
                vueloOferta->ofertaAplicada = true;
            }
            
            vueloOferta = nextList(M);
        }
        L = nextList(listaOfertas);
    }
}

/*
    Funcion donde el usuario ingresa el destino donde desea ir, se muestran en pantalla los asientos que tenga el avion seleccionado
    y el debe escoger en forma de coordenadas los asientos que quiera segun la cantidad de pasajes que se compraron.
*/
void * comprarPasaje(Map *mapaVuelos, List *listaPasajes){

    printf("Ingrese el destino deseado: ");
    char * destiny = (char*) malloc(40*sizeof(char));
    scanf(" %[^\n]s]", destiny);
    int cont = 0;
    printf("\n");
    vuelo *pasajeAux = (vuelo*)malloc(sizeof(vuelo));
    pasajeAux = firstList(listaPasajes);

    //Si el destino ya fue comprado anteriormente, se vuelve al menu.
    while(pasajeAux !=NULL){
        if(strcmp(pasajeAux->ciudad,destiny)==0){
            printf("No puede comprar 2 pasajes para el mismo destino.\n");
            return 0;
        }
        pasajeAux = nextList(listaPasajes);
    }

    List * L = (List*)searchMap(mapaVuelos,destiny);
    vuelo * vueloCompra = (vuelo*)malloc(sizeof(vuelo));
    vueloCompra = firstList(L);
    printf("                                                         _-VUELOS DISPONIBLES-_                                                                     \n");
    printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------\n");
    // Verificacion si hay aviones disponibles en el mapa de vuelos.
    while(vueloCompra!=NULL){
        if(vueloCompra->habilitado == true){
            if(vueloCompra->infoAvion->asientosComprados < 1){
                cont++;
                printf("|| (%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloCompra->empresa,vueloCompra->pais,vueloCompra->ciudad,vueloCompra->precio,vueloCompra->infoAvion->asientosOcupados,vueloCompra->infoAvion->asientosTotales, vueloCompra->hora);
                
            }
                 
        }
        vueloCompra = nextList(L);
    }

    printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------\n");

    if(cont==0){
        printf("\nNo hay vuelos disponibles con este destino.\n");
        return 0;
    }

    int eleccion;
    int contador;
    int i,j;
    
    do{
        printf("\nIngrese el numero del vuelo deseado: ");
        scanf("%d", &eleccion);
    }while(eleccion <= 0 || eleccion > cont);
    
    vueloCompra = firstList(L);
    cont=1;
    
    while(vueloCompra!=NULL){
        // Verificar que todas las condiciones se cumplan. 
        if((eleccion == cont) && (vueloCompra->habilitado == true) && (vueloCompra->infoAvion->asientosComprados<1)){
            printf("                                                           _-VUELO ESCOGIDO-_                                                                     \n");
            printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("|| (%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloCompra->empresa,vueloCompra->pais,vueloCompra->ciudad,vueloCompra->precio,vueloCompra->infoAvion->asientosOcupados,vueloCompra->infoAvion->asientosTotales, vueloCompra->hora);
            printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------\n");
            int pasajesCompra;
            do{
                printf("\nCuantos pasajes desea comprar: ");
                scanf("%d",&pasajesCompra);
            }while(pasajesCompra + vueloCompra->infoAvion->asientosOcupados > vueloCompra->infoAvion->asientosTotales);

            int pago;
            do{
                printf("\nPague su pasaje: ");
                scanf("%d",&pago);
            }while(pago < vueloCompra->precio * pasajesCompra);

            if(pago>vueloCompra->precio * pasajesCompra){
                printf("\nVuelo pagado. Su vuelto es de: %d\n",pago-vueloCompra->precio * pasajesCompra);
            }

            if(pago == vueloCompra->precio * pasajesCompra){
                printf("\nVuelo pagado.\n");    
            }
            printf("\n");
            vueloCompra->infoAvion->asientosOcupados = vueloCompra->infoAvion->asientosOcupados+pasajesCompra;
            vueloCompra->infoAvion->asientosComprados = pasajesCompra;
            
            if(vueloCompra->infoAvion->asientosTotales == vueloCompra->infoAvion->asientosOcupados){
                vueloCompra->habilitado = false;
            }
            // Se muestra cuales asientos estan ocupados y cuales estan desocupados. 
            printf("                                                              _-ASIENTOS-_                                                                     \n");
            printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
            if(vueloCompra->infoAvion->asientosTotales == 100){

                printf("    [0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [10][11][12][13][14][15][16][17][18][19][20][21][22][23][24][25][26][27][28][29]\n");

                printf("[0] ");
                for(i = 0 ; i < 20 ;i++){
                    if(vueloCompra->infoAvion->asientos[0][i] == 0){
                        printf(        VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[0][i]);
                    }else{
                        printf(        ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[0][i]);
                    }
                }
                printf("\n");

                printf("[1] ");
                for(i = 0 ; i < 30 ; i++){ 
                    if(vueloCompra->infoAvion->asientos[1][i] == 0){
                        printf(        VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[1][i]);
                    }else{
                        printf(        ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[1][i]);
                    }
                }
                printf("\n");

                printf("[2] ");
                for(i = 0 ; i  <30 ; i++){
                    if(vueloCompra->infoAvion->asientos[2][i] == 0){
                        printf(        VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[2][i]);
                    }else{
                        printf(        ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[2][i]);
                    }
                }
                printf("\n");
                    
                printf("[3] ");
                for(i = 0 ; i < 20 ; i++){
                    if(vueloCompra->infoAvion->asientos[3][i] == 0){
                        printf(        VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[3][i]);
                    }else{
                        printf(        ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[3][i]);
                    }
                }
                printf("\n");

                contador = 0;

                printf("\n                             _-------------------------------------------------------------------------------_\n");
                printf("                              |  Seleccione el/los asientos a comprar que fueron mostrados anteriormente  |\n");
                printf("                            _---------------------------------------------------------------------------------_\n");
                    
                printf("\n                                         ******RECORDATORIO: 1 = OCUPADO y 0 = DISPONIBLE******                 \n\n");

                do{
                        
                    int x,y;

                    do{
                        printf("Seleccione coordenada X de pasaje numero %d: ",contador);
                        scanf("%d",&x);
                    }while(x>3 || x<0);

                    printf("\n");

                    do{
                        printf("Seleccione coordenada Y de pasaje numero %d: ",contador);
                        scanf("%d",&y);
                    }while(y>30 || y<0);

                    printf("\n");
                    //Si las coordenadas apuntan a un 0, se compra ese asiento.
                    if(vueloCompra->infoAvion->asientos[x][y] ==  0){
                        printf("Asiento agregado correctamente.\n");
                        vueloCompra->infoAvion->asientos[x][y] = 2;
                        contador++;
                    }
                    printf("\n");
                    if(vueloCompra->infoAvion->asientos[x][y] ==  1){
                        printf("Asiento ya esta ocupado.\n");
                    }
                    printf("\n");
                    if(vueloCompra->infoAvion->asientos[x][y] ==  3){
                        printf("Asiento no existe.\n");
                    }

                }while(contador != pasajesCompra);

                printf("                                                            _-ASIENTO RESERVADO-_                                                                     ");
                printf("\n");
                printf("\n");
                for(i = 0 ; i < 20 ; i++){
                    if(vueloCompra->infoAvion->asientos[0][i] == 0){
                        printf(VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[0][i]);
                    }
                    if(vueloCompra->infoAvion->asientos[0][i] == 1){
                        printf(ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[0][i]);
                    }
                    if(vueloCompra->infoAvion->asientos[0][i] == 2){
                        printf(AMARILLO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[0][i]);
                    }
                }
                printf("\n");

                    
                for(i = 0 ; i < 30 ; i++){
                    if(vueloCompra->infoAvion->asientos[1][i] == 0){
                        printf(VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[1][i]);
                    }
                    if(vueloCompra->infoAvion->asientos[1][i] == 1){
                        printf(ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[1][i]);
                    }
                    if(vueloCompra->infoAvion->asientos[1][i] == 2){
                        printf(AMARILLO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[1][i]);
                    }
                }
                printf("\n");

                    
                for(i = 0 ; i < 30 ; i++){
                    if(vueloCompra->infoAvion->asientos[2][i] == 0){
                        printf(VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[2][i]);
                    }
                    if(vueloCompra->infoAvion->asientos[2][i] == 1){
                        printf(ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[2][i]);
                    }
                    if(vueloCompra->infoAvion->asientos[2][i] == 2){
                        printf(AMARILLO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[2][i]);
                    }
                }
                printf("\n");
                    
                    
                for(i = 0 ; i < 20 ; i++){
                    if(vueloCompra->infoAvion->asientos[3][i] == 0){
                        printf(VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[3][i]);
                    }
                    if(vueloCompra->infoAvion->asientos[3][i] == 1){
                        printf(ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[3][i]);
                    }
                    if(vueloCompra->infoAvion->asientos[3][i] == 2){
                        printf(AMARILLO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[3][i]);
                    }
                }
                    printf("\n");
            }

            if(vueloCompra->infoAvion->asientosTotales == 90){

                printf("    [0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [10][11][12][13][14][15][16][17][18][19][20][21][22][23][24][25][26][27][28][29]\n");

                for(i = 0 ; i < 3 ; i++){
                    printf("[%d] ",i);
                    for(j = 0 ; j < 30; j++){
                        if(vueloCompra->infoAvion->asientos[i][j] == 0){
                            printf(VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[i][j]);
                        }else{
                            printf(ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[i][j]);
                        }
                    } 
                    printf("\n");
                } 

                contador = 0;

                printf("\n                             _-------------------------------------------------------------------------------_\n");
                printf("                              |  Seleccione el/los asientos a comprar que fueron mostrados anteriormente  |\n");
                printf("                            _---------------------------------------------------------------------------------_\n");
                    
                printf("\n                                         ******RECORDATORIO: 1 = OCUPADO y 0 = DISPONIBLE******                 \n\n");

                do{
                        
                    int x,y;
                        
                    do{
                        printf("Seleccione coordenada X de pasaje numero %d: ",contador);
                        scanf("%d",&x);
                    }while(x>2 || x<0);

                    do{
                        printf("Seleccione coordenada Y de pasaje numero %d: ",contador);
                        scanf("%d",&y);
                    }while(y>30 || y<0);
                        
                        
                        

                    if(vueloCompra->infoAvion->asientos[x][y] ==  0){
                        printf("Asiento agregado correctamente.\n");
                        vueloCompra->infoAvion->asientos[x][y] = 2;
                        contador++;
                    }

                    if(vueloCompra->infoAvion->asientos[x][y] ==  1){
                        printf("Asiento ya esta ocupado.\n");
                    }

    
                }while(contador != pasajesCompra);
                
                printf("                                                            _-ASIENTO RESERVADO-_                                                                     ");
                printf("\n");

                for(i = 0 ; i < 3 ; i++){
                    for(j = 0 ; j < 30; j++){
                        if(vueloCompra->infoAvion->asientos[i][j] == 0){
                            printf(VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[i][j]);
                        }
                        if(vueloCompra->infoAvion->asientos[i][j] == 1){
                            printf(ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[i][j]);
                        }
                        if(vueloCompra->infoAvion->asientos[i][j] == 2){
                            printf(AMARILLO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[i][j]);
                        }

                    } 
                    printf("\n");
                } 

            }
                
                
            if(vueloCompra->infoAvion->asientosTotales == 80){

                printf("    [0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [10][11][13][14][15][16][17][18][19][20]\n");

                for(i = 0 ; i < 4 ; i++){
                    printf("[%d] ",i);
                    for(j = 0 ; j < 20; j++){
                        if(vueloCompra->infoAvion->asientos[i][j] == 0){
                            printf(VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[i][j]);
                        }else{
                            printf(ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[i][j]);
                        }
                    } 
                    printf("\n");
                }
                    
                contador = 0;
                printf("\n                             _-------------------------------------------------------------------------------_\n");
                printf("                              |  Seleccione el/los asientos a comprar que fueron mostrados anteriormente  |\n");
                printf("                            _---------------------------------------------------------------------------------_\n");
                    
                printf("\n                                         ******RECORDATORIO: 1 = OCUPADO y 0 = DISPONIBLE******                 \n\n");
                do{
                        
                    int x,y;
                        
                    do{
                        printf("Seleccione coordenada X de pasaje numero %d: ",contador);
                        scanf("%d",&x);
                    }while(x>3 || x<0);

                    do{
                        printf("Seleccione coordenada Y de pasaje numero %d: ",contador);
                        scanf("%d",&y);
                    }while(y>20 || y<0);
                        
                    

                    if(vueloCompra->infoAvion->asientos[x][y] ==  0){
                        printf("Asiento agregado correctamente.\n");
                        vueloCompra->infoAvion->asientos[x][y] = 2;
                        contador++;
                    }

                    if(vueloCompra->infoAvion->asientos[x][y] ==  1){
                        printf("Asiento ya esta ocupado.\n");
                    }

    
                }while(contador != pasajesCompra);
                
                printf("                                                            _-ASIENTO RESERVADO-_                                                                     ");
                printf("\n");
                
                for(i = 0 ; i < 4 ; i++){
                    for(j = 0 ; j < 20; j++){
                        if(vueloCompra->infoAvion->asientos[i][j] == 0){
                            printf(VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[i][j]);
                        }
                        if(vueloCompra->infoAvion->asientos[i][j] == 1){
                            printf(ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[i][j]);
                        }
                        if(vueloCompra->infoAvion->asientos[i][j] == 2){
                            printf(AMARILLO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[i][j]);
                        }

                    } 
                    printf("\n");
                } 
            }
            pushBack(listaPasajes, vueloCompra);             
            
        }
        cont++;
        vueloCompra = nextList(L);
    }

    horaGeneral= horaGeneral + 0.5;
    revisionHoraAvion(horaGeneral,mapaVuelos);
    revisarHoraVuelosComprados(horaGeneral, listaPasajes);
}

/*
    Funcion que pide un vuelo por pantalla, lo busca y pregunta si se desea buscar de forma mas especifica (por filtros) o regresar
    Al menu principal
*/
void * busquedaVuelos(Map *mapaVuelos, List * listaPasajes){
    
    printf("Ingrese el destino deseado:");
    char * destino = (char*) malloc(40*sizeof(char));
    int cont=1;
    scanf(" %[^\n]s]", destino);

    //Se muestran los vuelos con el destino querido y se muestran, se les van a aplicar filtros que el usuario desea.

    List * L = searchMap(mapaVuelos,destino);
    vuelo * vueloBusqueda = (vuelo*)malloc(sizeof(vuelo));
    vueloBusqueda = firstList(L);

    if(vueloBusqueda == NULL){
        printf("No existen vuelos con este destino.\n");
        return 0;
    }

    printf("                                                         _-VUELOS ENCONTRADOS-_                                                                     \n");
    printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------\n");
    while(vueloBusqueda!=NULL){
        if(strcmp(vueloBusqueda->ciudad,destino) == 0){
            if(vueloBusqueda->habilitado == true){
                printf("|| (%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloBusqueda->empresa,vueloBusqueda->pais,vueloBusqueda->ciudad,vueloBusqueda->precio,vueloBusqueda->infoAvion->asientosOcupados,vueloBusqueda->infoAvion->asientosTotales, vueloBusqueda->hora);
                cont++;   
            }
        }
        vueloBusqueda = nextList(L);
    } 
    printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------\n");
    
    // -----------FILTROS------------
    
    printf("Desea filtrar su busqueda?\n");
    
    printf("Escriba 'Si' si quiere desplegar un mernu con los filtros a escoger\n");
    
    char * confirmacion = (char*)malloc(3*sizeof(char));
    confirmacion = "Si";
    char* palabra = (char*)malloc(3*sizeof(char));
    printf("Respuesta: ");
    scanf("%s", palabra);
    if(strcmp(palabra,confirmacion) == 0){
        //Se van a trabajar con la lista ya encontrada por el destino del usuario.
        int opcion=1;
        while(opcion != 0){
            printf("\n                                                            MENU DE OPCIONES");
            printf("\n");
            printf("                                                    ~~----------------------------~~\n");
            printf("                                                     | 1. Por empresa.            |\n");
            printf("                                                     | 2. Por rangos de precio.   |\n");
            printf("                                                     | 3. Por rangos de hora.     |\n");
            printf("                                                     | 0. Salir del menu.         |\n");
            printf("                                                    ~~----------------------------~~");
            printf("\n\n");

            printf("Elige una opcion: ");
            scanf("%i", &opcion);
            switch (opcion){
                case 1:
                    //Se pide la empresa deseada y se muestran los vuelos que coincidan con este.
                    cont = 1;
                    printf("Segun que empresa desea su vuelo: ");
                    char * empresa = (char*) malloc(40*sizeof(char));
                    scanf(" %[^\n]s]", empresa);
                    vueloBusqueda = firstList(L);
                    printf("                                                         _-VUELOS POR EMPRESA-_                                                                     \n");
                    printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------\n");
                    while(vueloBusqueda != NULL){
                        if(strcmp(vueloBusqueda->empresa,empresa) == 0){
                            if(vueloBusqueda->habilitado == true){
                                printf("|| (%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloBusqueda->empresa,vueloBusqueda->pais,vueloBusqueda->ciudad,vueloBusqueda->precio,vueloBusqueda->infoAvion->asientosOcupados,vueloBusqueda->infoAvion->asientosTotales, vueloBusqueda->hora);
                                cont++;
                            }
                        }
                        vueloBusqueda = nextList(L);
                    }
                    printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------\n");
                break;
                
                case 2:
                    //Se piden los rangos de precio para aplicarlos como condicion a la lista de vuelos.
                    cont = 1;
                    printf("Ingrese rango de precio\n");
                    
                    printf("Ingrese el rango minimo: ");
                    int rangoUno;
                    scanf("%i", &rangoUno);
                    printf("Ingrese el rango maximo: ");
                    int rangoDos;
                    scanf("%i", &rangoDos);
                    vueloBusqueda = firstList(L);

                    while(vueloBusqueda != NULL){
                        if(vueloBusqueda->precio >= rangoUno && vueloBusqueda->precio <= rangoDos){
                            if(vueloBusqueda->habilitado == true){
                                printf("|| (%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloBusqueda->empresa,vueloBusqueda->pais,vueloBusqueda->ciudad,vueloBusqueda->precio,vueloBusqueda->infoAvion->asientosOcupados,vueloBusqueda->infoAvion->asientosTotales, vueloBusqueda->hora);
                                cont++;
                            }
                        }
                        vueloBusqueda = nextList(L);
                    }
                    
                break;

                case 3:
                    //Se pide un minimo y maximo de hora para aplicar como condicion cuando se muestren los vuelos. 
                    cont = 1;
                    printf("Ingrese una rangos de horas\n");
                    printf("Ingrese hora minima: ");
                    double horaUno;
                    scanf("%lf", &horaUno);
                    printf("Ingrese hora maxima: ");
                    double horaDos;
                    scanf("%lf", &horaDos);
                    vueloBusqueda = firstList(L);
                    printf("                                                       _-VUELOS POR RANGO HORARIO-_                                                                     \n");
                    printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------\n");
                    while(vueloBusqueda != NULL){
                        if(vueloBusqueda->hora >= horaUno && vueloBusqueda->hora <= horaDos){
                            if(vueloBusqueda->habilitado == true){
                                printf("|| (%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloBusqueda->empresa,vueloBusqueda->pais,vueloBusqueda->ciudad,vueloBusqueda->precio,vueloBusqueda->infoAvion->asientosOcupados,vueloBusqueda->infoAvion->asientosTotales, vueloBusqueda->hora);
                                cont++;
                            }
                        }
                        vueloBusqueda = nextList(L);
                    }
                    printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------\n");
                break;
            }
        }        
    }

    horaGeneral= horaGeneral + 0.5;
    revisionHoraAvion(horaGeneral,mapaVuelos);
    revisarHoraVuelosComprados(horaGeneral,listaPasajes);
}

/*
    Funcion que comprueba si hay algun pasaje ya comprado y si lo hay, pregunta por pantalla si desea ver informacion sobre 
    Este pasaje (horarios de salida del avion, asientos del avion o datos sobre el vuelo) o regresar al menu principal
*/
void * consultaPasajes(Map* mapaVuelos,List *listaPasajes){
    
    vuelo*vueloComprado = (vuelo*)malloc(sizeof(vuelo));

    if((vueloComprado = firstList(listaPasajes)) == NULL){
        printf("No hay pasajes comprados.\n");
        return 0;
    }

    int cont = 0;
    int i,j;
    printf("                                                       _-CONSULTA PASAJES-_                                                                     \n");
    printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------\n");
    //Se recorre la lista de pasajes para mostrar todo lo comprado.
    vueloComprado = firstList(listaPasajes);
    while(vueloComprado != NULL){
        cont++;
        printf("|| (%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloComprado->empresa,vueloComprado->pais,vueloComprado->ciudad,vueloComprado->precio,vueloComprado->infoAvion->asientosOcupados,vueloComprado->infoAvion->asientosTotales, vueloComprado->hora);
        
        vueloComprado = nextList(listaPasajes);
    }
    printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------\n");
    int eleccion;
    do{
        printf("\nIngrese el numero del vuelo deseado: ");
        scanf("%d", &eleccion);
    }while(eleccion <= 0 || eleccion > cont);
    vueloComprado = firstList(listaPasajes);
    cont=1;


    while(vueloComprado != NULL && eleccion != cont){
        
        int opcion = 1;
        while(opcion != 0){
            printf("\n                                                          MENU DE OPCIONES");
            printf("\n");
            printf("                                                   ~~-----------------------------~~\n");
            printf("                                                    | 1. Consulta salida avion.   |\n");
            printf("                                                    | 2. Consulta asientos avion. |\n");
            printf("                                                    | 3. Consulta datos vuelo.    |\n");
            printf("                                                    | 0. Salir del menu.          |\n");
            printf("                                                   ~~-----------------------------~~");
            printf("\n\n");
            printf("Ingrese su opcion: ");
            scanf("%d", &opcion);
            switch (opcion){
                case 1:

                    //Se muestra la hora del avion y cuanto queda para esta hora.
                    printf("\nSu avion saldra a las: %.2lf\n", vueloComprado->hora);
                    
                    double parteDecimal, auxHoraG, parteEntera;
                    auxHoraG = horaGeneral;
                    parteDecimal = modf(auxHoraG, &parteEntera);
                    double horaDespegue = vueloComprado->hora;

                    if(parteDecimal == 0.5) parteDecimal=0.3;

                    double horaNueva = parteEntera + parteDecimal;
                    horaNueva = horaDespegue - horaNueva;
                    printf("Quedan %.2lf horas.\n",horaNueva);
                    
                break;

                case 2:
                    //Se muestran las filas de los asientos del avion, en los casos de 100, 90 y 80 asientos.
                    if(vueloComprado->infoAvion->asientosTotales == 100){
                        printf("\n\n");
                        for(i = 0; i < 20 ; i++){
                            if(vueloComprado->infoAvion->asientos[0][i] == 0){
                                printf(VERDE_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[0][i]);
                            }
                            if(vueloComprado->infoAvion->asientos[0][i] == 1){
                                printf(ROJO_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[0][i]);
                            }
                            if(vueloComprado->infoAvion->asientos[0][i] == 2){
                                printf(AMARILLO_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[0][i]);
                            }
                        }
                        printf("\n");

                    
                        for(i = 0 ; i < 30 ; i++){
                            if(vueloComprado->infoAvion->asientos[1][i] == 0){
                                printf(VERDE_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[1][i]);
                            }
                            if(vueloComprado->infoAvion->asientos[1][i] == 1){
                                printf(ROJO_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[1][i]);
                            }
                            if(vueloComprado->infoAvion->asientos[1][i] == 2){
                               printf(AMARILLO_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[1][i]);
                            }
                        }
                        printf("\n");

                    
                        for(i = 0 ; i < 30 ; i++){
                            if(vueloComprado->infoAvion->asientos[2][i] == 0){
                                printf(VERDE_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[2][i]);
                            }
                            if(vueloComprado->infoAvion->asientos[2][i] == 1){
                                printf(ROJO_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[2][i]);
                            }
                            if(vueloComprado->infoAvion->asientos[2][i] == 2){
                                printf(AMARILLO_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[2][i]);
                            }
                        }
                        printf("\n");
                    
                    
                        for(i = 0 ; i < 20 ; i++){
                            if(vueloComprado->infoAvion->asientos[3][i] == 0){
                                printf(VERDE_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[3][i]);
                            }
                            if(vueloComprado->infoAvion->asientos[3][i] == 1){
                                printf(ROJO_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[3][i]);
                            }
                            if(vueloComprado->infoAvion->asientos[3][i] == 2){
                                printf(AMARILLO_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[3][i]);
                            }
                        }
                        printf("\n\n");
                        
                        printf("                                               ***----------------------AVION--------------------***\n");
                        printf("                                                 | Pasajes comprados: %d                         |\n", vueloComprado->infoAvion->asientosComprados);
                        printf("                                                 | Pasajeros a bordo: %d                         |\n", vueloComprado->infoAvion->asientosOcupados);
                        printf("                                                 | Capacidad total del avion:  %d                |\n", vueloComprado->infoAvion->asientosOcupados);
                        printf("                                               ***-----------------------------------------------***\n");
                    }

                    if(vueloComprado->infoAvion->asientosTotales == 90){
                        printf("\n\n");
                        for(i = 0 ; i < 3 ; i++){
                            printf("[%d] ",i);
                            for(j = 0 ; j < 30; j++){
                                if(vueloComprado->infoAvion->asientos[i][j] == 0){
                                    printf(VERDE_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[i][j]);
                                }
                                if(vueloComprado->infoAvion->asientos[3][i] == 1){
                                    printf(ROJO_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[3][i]);
                                }
                                if(vueloComprado->infoAvion->asientos[3][i] == 2){
                                    printf(AMARILLO_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[3][i]);
                                }

                            } 
                            printf("\n");
                        } 
                        printf("\n\n");
                        printf("                                               ***----------------------AVION--------------------***\n");
                        printf("                                                 | Pasajes comprados: %d                          |\n", vueloComprado->infoAvion->asientosComprados);
                        printf("                                                 | Pasajeros a bordo: %d                         |\n", vueloComprado->infoAvion->asientosOcupados);
                        printf("                                                 | Capacidad total del avion:  %d                |\n", vueloComprado->infoAvion->asientosOcupados);
                        printf("                                               ***-----------------------------------------------***\n");

                    }

                    if(vueloComprado->infoAvion->asientosTotales == 80){
                        printf("\n\n");
                        for(i = 0 ; i < 4 ; i++){
                            printf("[%d] ",i);
                            for(j = 0 ; j < 20; j++){
                                if(vueloComprado->infoAvion->asientos[i][j] == 0){
                                    printf(VERDE_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[i][j]);
                                }
                                if(vueloComprado->infoAvion->asientos[3][i] == 1){
                                printf(ROJO_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[3][i]);
                                }
                                if(vueloComprado->infoAvion->asientos[3][i] == 2){
                                    printf(AMARILLO_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[3][i]);
                                }
                            } 
                            printf("\n");
                        }
                        printf("\n\n");
                        printf("                                               ***----------------------AVION--------------------***\n");
                        printf("                                                 | Pasajes comprados: %d                             | \n", vueloComprado->infoAvion->asientosComprados);
                        printf("                                                 | Pasajeros a bordo: %d                         | \n", vueloComprado->infoAvion->asientosOcupados);
                        printf("                                                 | Capacidad total del avion: %d                 | \n", vueloComprado->infoAvion->asientosOcupados);
                        printf("                                               ***-----------------------------------------------***\n");

                    }

                break;
 
                case 3:
                    //Se muestran los datos principales del vuelo.
                    printf("                                                   ***-----------------DATOS-VUELOS------------------***\n");
                    printf("                                                     | Pais : %s                         |\n", vueloComprado->pais);
                    printf("                                                     | Ciudad : %s                                |\n", vueloComprado->ciudad);
                    printf("                                                     | Empresa : %s                               |\n", vueloComprado->empresa);
                    printf("                                                     | Precio del vuelo : $%i                    |\n", vueloComprado->precio);
                    printf("                                                     | Cantidad asientos comprados : %i               |\n", vueloComprado->infoAvion->asientosComprados);
                    printf("                                                   ***-----------------------------------------------***\n");
                break;
            
                default: break;
            }
        }        
        cont++;
        vueloComprado=nextList(listaPasajes);
    }

    horaGeneral= horaGeneral + 0.5;
    revisionHoraAvion(horaGeneral,mapaVuelos);
    revisarHoraVuelosComprados(horaGeneral,listaPasajes);
}

/*
    Funcion que muestra todos los vuelos del mapaVuelos que tengan una oferta aplicada
*/
void * ofertasAplicadas(Map * mapaVuelos, List * listaPasajes){

    //Se recorre todo el mapa de vuelos, si tienen una oferta aplicada y a su vez están habilitados
    //se muestran en pantalla.
    List * L;
    L = firstMap(mapaVuelos);
    int cont = 1;
    printf("                                                       _-VUELOS EN OFERTA-_                                                                     \n");
    printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------\n");
    while(L != NULL){
        vuelo * vueloOferta = (vuelo*)malloc(sizeof(vuelo));
        vueloOferta = firstList(L);
        while(vueloOferta!=NULL){
            if(vueloOferta->ofertaAplicada == true && vueloOferta->habilitado == true){
                printf("|| (%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloOferta->empresa,vueloOferta->pais,vueloOferta->ciudad,vueloOferta->precio,vueloOferta->infoAvion->asientosOcupados,vueloOferta->infoAvion->asientosTotales, vueloOferta->hora);
                cont++;
            }
            vueloOferta = nextList(L);
        }
        
        L = nextMap(mapaVuelos);
    }
    printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------\n");
    horaGeneral= horaGeneral + 0.5;
    revisionHoraAvion(horaGeneral,mapaVuelos);
    revisarHoraVuelosComprados(horaGeneral,listaPasajes);
}