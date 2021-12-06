#include <stdio.h>
#include <wchar.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
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
    
    int opcion = 1;
    while(opcion != 0){
        printf("1. Comprar pasaje.\n");
        printf("2. Busqueda de vuelos.\n");
        printf("3. Consulta pasajes.\n");
        printf("4. Ofertas aplicadas.\n");
        printf("0. Salir del programa.\n");
        
        scanf("%d", &opcion);
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

void* revisionHoraAvion(double horaGeneral,Map* mapaVuelos){

    if(horaGeneral == 24){
        printf("No hay mas vuelos disponibles.\n");
        exit(1);
    }

    double parteDecimal, auxHoraG, parteEntera;
    auxHoraG = horaGeneral;
    parteDecimal = modf(auxHoraG,&parteEntera);

    if(parteDecimal == 0.5){
       auxHoraG = auxHoraG - 0.2;
    }

    printf("Hora general: %.2lf\n",auxHoraG);

    List * L;
    L = firstMap(mapaVuelos);

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

void * revisarHoraVuelosComprados(double horaGeneral, List * listaPasajes){
    vuelo * vueloLista = (vuelo*)malloc(sizeof(vuelo));
    vueloLista = firstList(listaPasajes);
    if(vueloLista == NULL){
        printf("No hay pasajes comprados.\n\n");
    }

    double parteDecimal, auxHoraG, parteEntera;
    auxHoraG = horaGeneral;
    parteDecimal = modf(auxHoraG,&parteEntera);

    if(parteDecimal == 0.5){
       auxHoraG = auxHoraG - 0.2;
    }

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

Map * importarVuelos(Map * mapaVuelos){
    char archivo[101];
    FILE* file;

    do{
        printf("Ingresar nombre archivo: ");
        scanf("%s", &archivo);
        strcat(archivo, ".csv");
        file = fopen(archivo, "r");
    }while(!file);

    char lineaArchivo[1024];
    int i;
    int cont = 0;

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

        const char * M;
        M = searchMap(mapaVuelos,vueloC->ciudad);
        if(M == NULL){
            List * listaVuelardos = createList();
            pushFront(listaVuelardos,vueloC);
            insertMap(mapaVuelos,vueloC->ciudad,listaVuelardos);
        }
        else{
            List * L = (List*)searchMap(mapaVuelos,vueloC->ciudad);
            pushFront(L,vueloC);
        }
        
        cont++; 
        if(cont == 42) break;
    } 
    
    
}

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
                

            if(tres == true && dos == true && uno == true){
                double descuento;
                descuento = (double)L->descuento / 100;
                vueloOferta->precio = vueloOferta->precio - (vueloOferta->precio * descuento);
                vueloOferta->ofertaAplicada = true;
            }
            
            vueloOferta = nextList(M);
        }
        L = nextList(listaOfertas);
    }

}

void * comprarPasaje(Map *mapaVuelos, List *listaPasajes){

    printf("Ingrese el destino deseado: ");
    char * destiny = (char*) malloc(40*sizeof(char));
    scanf(" %[^\n]s]", destiny);
    int cont = 0;

    vuelo *pasajeAux = (vuelo*)malloc(sizeof(vuelo));
    pasajeAux = firstList(listaPasajes);

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

    // Verificacion si hay aviones disponibles
    while(vueloCompra!=NULL){
        if(vueloCompra->habilitado == true){
            if(vueloCompra->infoAvion->asientosComprados < 1){
                cont++;
                printf("ASIENTOS COMPRADOS: %d\n",vueloCompra->infoAvion->asientosComprados);
                printf("(%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloCompra->empresa,vueloCompra->pais,vueloCompra->ciudad,vueloCompra->precio,vueloCompra->infoAvion->asientosOcupados,vueloCompra->infoAvion->asientosTotales, vueloCompra->hora);
                
            }
                 
        }
        vueloCompra = nextList(L);
    }

    if(cont==0){
        printf("No hay vuelos disponibles con este destino.\n");
        return 0;
    }

    int eleccion;
    int contador;
    int i,j;
    
    do{
        printf("Ingrese el numero del vuelo deseado: ");
        scanf("%d", &eleccion);
    }while(eleccion <= 0 || eleccion > cont);
    
    vueloCompra = firstList(L);
    cont=1;
    
    
    while(vueloCompra!=NULL){
        
        printf("PRE IF: (%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloCompra->empresa,vueloCompra->pais,vueloCompra->ciudad,vueloCompra->precio,vueloCompra->infoAvion->asientosOcupados,vueloCompra->infoAvion->asientosTotales, vueloCompra->hora);
        
        if((eleccion == cont) && (vueloCompra->habilitado == true) && (vueloCompra->infoAvion->asientosComprados<1)){
            printf("(%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloCompra->empresa,vueloCompra->pais,vueloCompra->ciudad,vueloCompra->precio,vueloCompra->infoAvion->asientosOcupados,vueloCompra->infoAvion->asientosTotales, vueloCompra->hora);
                
                int pasajesCompra;
                do{
                    printf("Cuantos pasajes desea comprar: ");
                    scanf("%d",&pasajesCompra);
                }while(pasajesCompra + vueloCompra->infoAvion->asientosOcupados > vueloCompra->infoAvion->asientosTotales);

                int pago;
                do{
                    printf("Pague su pasaje: ");
                    scanf("%d",&pago);
                }while(pago < vueloCompra->precio * pasajesCompra);

                if(pago>vueloCompra->precio * pasajesCompra){
                    printf("Vuelo pagado. Su vuelto es de: %d\n",pago-vueloCompra->precio * pasajesCompra);
                }

                if(pago==vueloCompra->precio * pasajesCompra){
                    printf("Vuelo pagado.\n");
                    
                }

                vueloCompra->infoAvion->asientosOcupados = vueloCompra->infoAvion->asientosOcupados+pasajesCompra;
                vueloCompra->infoAvion->asientosComprados = pasajesCompra;

                if(vueloCompra->infoAvion->asientosTotales == vueloCompra->infoAvion->asientosOcupados){
                    vueloCompra->habilitado = false;
                }

                if(vueloCompra->infoAvion->asientosTotales == 100){

                    printf("    [0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [10][11][12][13][14][15][16][17][18][19][20][21][22][23][24][25][26][27][28][29]\n");

                    printf("[0] ");
                    for(i = 0 ; i < 20 ;i++){
                        if(vueloCompra->infoAvion->asientos[0][i] == 0){
                            printf(VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[0][i]);
                        }else{
                            printf(ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[0][i]);
                        }
                    }
                    printf("\n");

                    printf("[1] ");
                    for(i = 0 ; i < 30 ; i++){ 
                        if(vueloCompra->infoAvion->asientos[1][i] == 0){
                            printf(VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[1][i]);
                        }else{
                            printf(ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[1][i]);
                        }
                    }
                    printf("\n");

                    printf("[2] ");
                    for(i = 0 ; i  <30 ; i++){
                        if(vueloCompra->infoAvion->asientos[2][i] == 0){
                            printf(VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[2][i]);
                        }else{
                            printf(ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[2][i]);
                        }
                    }
                    printf("\n");
                    
                    printf("[3] ");
                    for(i = 0 ; i < 20 ; i++){
                        if(vueloCompra->infoAvion->asientos[3][i] == 0){
                            printf(VERDE_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[3][i]);
                        }else{
                            printf(ROJO_F "[%d] "RESET_COLOR,vueloCompra->infoAvion->asientos[3][i]);
                        }
                    }
                    printf("\n");

                    contador = 0;

                    printf("\n_--------------------------------------------------------------------------------_\n");
                    printf("   |  Seleccione el/los asientos a comprar que fueron mostrados anteriormente     |\n");
                    printf("  _--------------------------------------------------------------------------------_\n");
                    
                    printf("\n          ******RECORDATORIO: 1 = OCUPADO y 0 = DISPONIBLE******                 \n\n");
                    do{
                        
                        int x,y;

                        do{
                            printf("Seleccione coordenada X de pasaje numero %d: ",contador);
                            scanf("%d",&x);
                        }while(x>3 || x<0);

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

                        if(vueloCompra->infoAvion->asientos[x][y] ==  3){
                            printf("Asiento no existe.\n");
                        }

    
                    }while(contador != pasajesCompra);

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

                    printf("\n_--------------------------------------------------------------------------------_\n");
                    printf("   |  Seleccione el/los asientos a comprar que fueron mostrados anteriormente     |\n");
                    printf("  _--------------------------------------------------------------------------------_\n");
                    
                    printf("\n         ******RECORDATORIO: 1 = OCUPADO y 0 = DISPONIBLE******                 \n\n");

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
                    printf("\n_--------------------------------------------------------------------------------_\n");
                    printf("   |  Seleccione el/los asientos a comprar que fueron mostrados anteriormente     |\n");
                    printf("  _--------------------------------------------------------------------------------_\n");
                    
                    printf("\n         ******RECORDATORIO: 1 = OCUPADO y 0 = DISPONIBLE******                 \n\n");
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
                        
                        printf("Seleccione coordenada X de pasaje numero %d: ",contador);
                        scanf("%d",&x);
                        printf("Seleccione coordenada Y de pasaje numero %d: ",contador);
                        scanf("%d",&y);

                        if(vueloCompra->infoAvion->asientos[x][y] ==  0){
                            printf("Asiento agregado correctamente.\n");
                            vueloCompra->infoAvion->asientos[x][y] = 2;
                            contador++;
                        }

                        if(vueloCompra->infoAvion->asientos[x][y] ==  1){
                            printf("Asiento ya esta ocupado.\n");
                        }

    
                    }while(contador != pasajesCompra);

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
            
            //cont++;
        }
        cont++;
        vueloCompra = nextList(L);
    }

    horaGeneral= horaGeneral + 0.5;
    revisionHoraAvion(horaGeneral,mapaVuelos);
    revisarHoraVuelosComprados(horaGeneral, listaPasajes);
}

void * busquedaVuelos(Map *mapaVuelos, List * listaPasajes){
    
    printf("Ingrese el destino deseado:");
    char * destino = (char*) malloc(40*sizeof(char));
    int cont=1;
    scanf(" %[^\n]s]", destino);

    List * L = searchMap(mapaVuelos,destino);
    vuelo * vueloBusqueda = (vuelo*)malloc(sizeof(vuelo));
    vueloBusqueda = firstList(L);

    printf("VUELOS ENCONTRADOS:\n");
    while(vueloBusqueda!=NULL){
        if(strcmp(vueloBusqueda->ciudad,destino) == 0){
            if(vueloBusqueda->habilitado == true){
                printf("(%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %d ||\n",cont,vueloBusqueda->empresa,vueloBusqueda->pais,vueloBusqueda->ciudad,vueloBusqueda->precio,vueloBusqueda->infoAvion->asientosOcupados,vueloBusqueda->infoAvion->asientosTotales, vueloBusqueda->hora);
                cont++;   
            }
        }
        vueloBusqueda = nextList(L);
    } 
    
    // -----------FILTROS------------
    printf("Desea filtrar su busqueda?\n");
    printf("Escriba 'Si' si quiere desplegar un mernu con los filtros a escoger\n");
    char * confirmacion = (char*)malloc(3*sizeof(char));
    confirmacion = "Si";
    char* palabra = (char*)malloc(3*sizeof(char));
    scanf("%s", palabra);
    if(strcmp(palabra,confirmacion) == 0){

        int opcion=1;
        while(opcion != 0){

            printf("---------Opciones--------\n");
            printf("1. Por empresa.\n");
            printf("2. Por rangos de precio.\n");
            printf("3. Por rangos de hora.\n");
            printf("0. Salir de Consulta Pasajes.\n");

            scanf("%i", &opcion);
            switch (opcion){
                case 1: 
                    cont = 1;
                    printf("Segun que empresa desea su vuelo: ");
                    char * empresa = (char*) malloc(40*sizeof(char));
                    scanf(" %[^\n]s]", empresa);
                    vueloBusqueda = firstList(L);

                    while(vueloBusqueda != NULL){
                        if(strcmp(vueloBusqueda->empresa,empresa) == 0){
                            if(vueloBusqueda->habilitado == true){
                                printf("(%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloBusqueda->empresa,vueloBusqueda->pais,vueloBusqueda->ciudad,vueloBusqueda->precio,vueloBusqueda->infoAvion->asientosOcupados,vueloBusqueda->infoAvion->asientosTotales, vueloBusqueda->hora);
                                cont++;
                            }
                        }
                        vueloBusqueda = nextList(L);
                    }

                break;
                
                case 2:
                    
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
                                printf("(%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloBusqueda->empresa,vueloBusqueda->pais,vueloBusqueda->ciudad,vueloBusqueda->precio,vueloBusqueda->infoAvion->asientosOcupados,vueloBusqueda->infoAvion->asientosTotales, vueloBusqueda->hora);
                                cont++;
                            }
                        }
                        vueloBusqueda = nextList(L);
                    }
                    
                break;

                case 3:
                    cont = 1;
                    printf("Ingrese una rangos de horas\n");
                    printf("Ingrese hora minima: ");
                    double horaUno;
                    scanf("%lf", &horaUno);
                    printf("Ingrese hora maxima: ");
                    double horaDos;
                    scanf("%lf", &horaDos);
                    vueloBusqueda = firstList(L);

                    while(vueloBusqueda != NULL){
                        if(vueloBusqueda->hora >= horaUno && vueloBusqueda->hora <= horaDos){
                            if(vueloBusqueda->habilitado == true){
                                printf("(%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloBusqueda->empresa,vueloBusqueda->pais,vueloBusqueda->ciudad,vueloBusqueda->precio,vueloBusqueda->infoAvion->asientosOcupados,vueloBusqueda->infoAvion->asientosTotales, vueloBusqueda->hora);
                                cont++;
                            }
                        }
                        vueloBusqueda = nextList(L);
                    }
                break;
            }
        }        
    }

    horaGeneral= horaGeneral + 0.5;
    revisionHoraAvion(horaGeneral,mapaVuelos);
    revisarHoraVuelosComprados(horaGeneral,listaPasajes);
}

// COMPROBAR HORA CONSULTA SALIDA AVION
void * consultaPasajes(Map* mapaVuelos,List *listaPasajes){
    
    vuelo*vueloComprado = (vuelo*)malloc(sizeof(vuelo));

    if((vueloComprado = firstList(listaPasajes)) == NULL){
        printf("No hay pasajes comprados.\n");
        return 0;
    }

    int cont = 1;
    int i,j;
    vueloComprado = firstList(listaPasajes);

    while(vueloComprado != NULL){
        printf("(%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloComprado->empresa,vueloComprado->pais,vueloComprado->ciudad,vueloComprado->precio,vueloComprado->infoAvion->asientosOcupados,vueloComprado->infoAvion->asientosTotales, vueloComprado->hora);
        cont++;
        vueloComprado = nextList(listaPasajes);
    }

    int eleccion;
    do{
        printf("Ingrese el numero del vuelo deseado: ");
        scanf("%d", &eleccion);
    }while(eleccion <= 0 || eleccion > cont);
    vueloComprado = firstList(listaPasajes);
    cont=1;


    while(vueloComprado != NULL && eleccion == cont){
        
        int opcion = 1;
        while(opcion != 0){
            
            printf("1. Consulta salida avion.\n");
            printf("2. Consulta asientos avion.\n");
            printf("3. Consulta datos vuelo.\n");
            printf("0. Salir del programa.\n");
        
            scanf("%d", &opcion);
            switch (opcion){
                case 1:

                    printf("Su avion saldra a las: %.2lf\n", vueloComprado->hora);
                    
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
                
                    if(vueloComprado->infoAvion->asientosTotales == 100){
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
                        printf("\n");
                        
                        printf("***----------------------AVION--------------------***\n");
                        printf("  | Pasajes comprados: %d                         |\n", vueloComprado->infoAvion->asientosComprados);
                        printf("  | Pasajeros a bordo: %d                         |\n", vueloComprado->infoAvion->asientosOcupados);
                        printf("  | Capacidad total del avion:  %d                |\n", vueloComprado->infoAvion->asientosOcupados);
                        printf("***-----------------------------------------------***\n");
                    }

                    if(vueloComprado->infoAvion->asientosTotales == 90){

                        for(i = 0 ; i < 3 ; i++){
                            printf("[%d] ",i);
                            for(j = 0 ; j < 30; j++){
                                if(vueloComprado->infoAvion->asientos[i][j] == 0){
                                    printf(VERDE_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[i][j]);
                                }else{
                                    printf(ROJO_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[i][j]);
                                }
                            } 
                            printf("\n");
                        } 

                        printf("***----------------------AVION--------------------***\n");
                        printf("  | Pasajes comprados: %d                         |\n", vueloComprado->infoAvion->asientosComprados);
                        printf("  | Pasajeros a bordo: %d                         |\n", vueloComprado->infoAvion->asientosOcupados);
                        printf("  | Capacidad total del avion:  %d                |\n", vueloComprado->infoAvion->asientosOcupados);
                        printf("***-----------------------------------------------***\n");

                    }

                    if(vueloComprado->infoAvion->asientosTotales == 80){
                        
                        for(i = 0 ; i < 4 ; i++){
                            printf("[%d] ",i);
                            for(j = 0 ; j < 20; j++){
                                if(vueloComprado->infoAvion->asientos[i][j] == 0){
                                    printf(VERDE_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[i][j]);
                                }else{
                                    printf(ROJO_F "[%d] "RESET_COLOR,vueloComprado->infoAvion->asientos[i][j]);
                                }
                            } 
                            printf("\n");
                        }

                        printf("***----------------------AVION--------------------***\n");
                        printf("  | Pasajes comprados: %d                         | \n", vueloComprado->infoAvion->asientosComprados);
                        printf("  | Pasajeros a bordo: %d                         | \n", vueloComprado->infoAvion->asientosOcupados);
                        printf("  | Capacidad total del avion:  %d                | \n", vueloComprado->infoAvion->asientosOcupados);
                        printf("***-----------------------------------------------***\n");

                    }

                break;
 
                case 3:
                    printf("***-----------------DATOS-VUELOS------------------***\n");
                    printf("  | Pais : %s                                     |\n", vueloComprado->pais);
                    printf("  | Ciudad : %s                                   |\n", vueloComprado->ciudad);
                    printf("  | Empresa : %s                                  |\n", vueloComprado->empresa);
                    printf("  | Precio del vuelo : $%i                        |\n", vueloComprado->precio);
                    printf("  | Cantidad asientos comprados : %i              |\n", vueloComprado->infoAvion->asientosComprados);
                    printf("***-----------------------------------------------***\n");
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

// FUNCION LISTA
void * ofertasAplicadas(Map * mapaVuelos, List * listaPasajes){

    List * L;
    L = firstMap(mapaVuelos);
    int cont = 1;
    while(L != NULL){
        vuelo * vueloOferta = (vuelo*)malloc(sizeof(vuelo));
        vueloOferta = firstList(L);
        while(vueloOferta!=NULL){
            if(vueloOferta->ofertaAplicada == true){
                printf("(%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloOferta->empresa,vueloOferta->pais,vueloOferta->ciudad,vueloOferta->precio,vueloOferta->infoAvion->asientosOcupados,vueloOferta->infoAvion->asientosTotales, vueloOferta->hora);
                cont++;
            }
            vueloOferta = nextList(L);
        }
        
        L = nextMap(mapaVuelos);
    }
    
    horaGeneral= horaGeneral + 0.5;
    revisionHoraAvion(horaGeneral,mapaVuelos);
    revisarHoraVuelosComprados(horaGeneral,listaPasajes);
}