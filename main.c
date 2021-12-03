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

double horaGeneral = 0;

typedef struct{
    int asientosOcupados;
    int asientosTotales;
    int asientos[50][50];
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
void* busquedaVuelos(Map* mapaVuelos);
void* estadoVuelos(List* listaPasajes);
void* revisarPasaje(List* listaPasajes);
void* ofertasAplicadas(Map* mapaVuelos);
void* modificarVuelos(Map * mapaVuelos);


int main (){

    Map* mapaVuelos = createMap(isEqualString);
    List* listaPasajes = createList();
    List*aviones = createList();
    importarVuelos(mapaVuelos);
    importarOfertas(mapaVuelos);
    creacionAviones(mapaVuelos);
    poblarAvion(mapaVuelos);
    
    int opcion=1;
    while(opcion!=0){
        printf("1. Modo pasajero.\n");
        printf("2. Modo administrador.\n");
        printf("0. Salir.\n");
        scanf("%d",&opcion);
        switch(opcion){
            case 1:modoPasajero(mapaVuelos,listaPasajes);break; //  pasar opcion para verificar si se sale del switch
            case 2:modoAdministrador(mapaVuelos, listaPasajes);break;
        }
    }
    return 0;
}

void* modoPasajero (Map* mapaVuelos,List* listaPasajes){

    int opcion = 1;
    while(opcion != 0){
        printf("1. Comprar pasaje.\n");
        printf("2. Busqueda de vuelos.\n");
        printf("3. Estado vuelos.\n");
        printf("4. Revisar pasajes comprados.\n");
        printf("5. Ofertas disponibles.\n");
        printf("6. Pasar a modo administrador.\n");
        
        scanf("%d", &opcion);
        switch (opcion){
            case 1: comprarPasaje(mapaVuelos,listaPasajes);break;
            case 2: busquedaVuelos(mapaVuelos);break;
            //case 3: estadoVuelos(listaPasajes);break;
            //case 4: revisarPasaje(listaPasajes);break;
            case 5: ofertasAplicadas(mapaVuelos);break;
            case 6: modoAdministrador(mapaVuelos,listaPasajes);break;
            default: break;
        }
    }
    
}

void* modoAdministrador (Map* mapaVuelos,List* listaPasajes){

    int opcion = 1;
    while(opcion != 0){
        printf("1. Modificar informacion vuelos.\n");
        printf("2. Pasar modo pasajero.\n");
        
        scanf("%d", &opcion);
        switch (opcion){
            //case 1:modificarVuelos(mapaVuelos);break;
            case 2:modoPasajero(mapaVuelos,listaPasajes);break;
            default: break;
        }
    }
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
    while(L != NULL){
        vuelo * vueloski = (vuelo*)malloc(sizeof(vuelo));
        vueloski = firstList(L);
        while(vueloski!=NULL){
            
            if(vueloski->infoAvion->asientosTotales == 100){
                //printf("A\n");
                //FORMA AVION PARA 100 PAJEROS 
                
                int i,j;

                for(i=0;i<20;i++){ 
                    vueloski->infoAvion->asientos[0][i]=3;
                    //printf("3 ");
                }
                //printf("\n");
                
                for(i=0;i<30;i++){ 
                    vueloski->infoAvion->asientos[1][i]=3;
                    //printf("3 ");
                }
                //printf("\n");
                for(i=0;i<30;i++){
                    vueloski->infoAvion->asientos[2][i]=3;
                    //printf("3 ");
                }
                //printf("\n");
                for(i=0;i<20;i++){  
                    vueloski->infoAvion->asientos[3][i]=3;
                    //printf("3 ");
                }

                //printf("\n");
                //printf("Prinfteo de matriz\n");

                for(i=0; i < 4; i++){
                    if(i == 0){
                        for(j = 0; j < 20; j++){
                            if(vueloski->infoAvion->asientos[i][j] == 3){
                                //printf("[%d] ",vueloski->infoAvion->asientos[i][j]);
                            }
                        }
                    }
                    if(i == 1){
                        for(j = 0; j < 30; j++){
                            if(vueloski->infoAvion->asientos[i][j] == 3){
                                //printf("[%d] ",vueloski->infoAvion->asientos[i][j]);
                            }
                        }
                    }
                    if(i == 2){
                        for(j = 0; j < 30; j++){
                            if(vueloski->infoAvion->asientos[i][j] == 3){
                                //printf("[%d] ",vueloski->infoAvion->asientos[i][j]);
                            }
                        }
                    }
                    if(i == 3){
                        for(j = 0; j < 20; j++){
                            if(vueloski->infoAvion->asientos[i][j] == 3){
                                //printf("[%d] ",vueloski->infoAvion->asientos[i][j]);
                            }
                        }
                    }
                    //printf("\n");
                }
                
                
               
            }
            
            if(vueloski->infoAvion->asientosTotales == 90){
                //FORMA AVION PARA 90 PASAJEROS
                //printf("B\n");
                int matriz2[50][50];
                int k,l;

                for(k=0;k<3;k++){
                    for(l = 0 ; l < 30; l++){
                        vueloski->infoAvion->asientos[k][l]=3;
                        //printf("3 ");
                    } 
                    //printf("\n");
                }

                //printf("Prinfteo de matriz\n");

                for(k=0;k < 3; k++){
                    for(l = 0; l < 30; l++){
                        if(vueloski->infoAvion->asientos[k][l] == 3){
                            //printf("[%d] ",vueloski->infoAvion->asientos[k][l]);
                        }
                    }
                    //printf("\n");
                }
            }

            if(vueloski->infoAvion->asientosTotales == 80){
                //FORMA AVION PARA 80 PASAJEROS
                //printf("C\n");
                int matriz3[50][50];
                int m,n;

                for(m=0;m<4;m++){
                    for(n = 0 ; n < 20; n++){
                        vueloski->infoAvion->asientos[m][n]=3;
                        //printf("3 ");
                    } 
                    //printf("\n");
                }

                //printf("Prinfteo de matriz\n");

                for(m=0;m < 4; m++){
                    for(n = 0; n < 20; n++){
                        if(vueloski->infoAvion->asientos[m][n] == 3){
                            //printf("[%d] ",vueloski->infoAvion->asientos[m][n]);
                        }
                    }
                    //printf("\n");
                }
            }
            
            vueloski = nextList(L);
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
        vuelo * vueloski = (vuelo*)malloc(sizeof(vuelo));
        vueloski = firstList(L);
        while(vueloski!=NULL){
            printf("Nuevo avion\n");
            if(vueloski->infoAvion->asientosTotales == 100){
                
                printf("Poblamos matriz\n");
                contAsientosTomados=0;
                for(i=0;i<20;i++){ 
                    numeroRandom = rand()%2;
                    vueloski->infoAvion->asientos[0][i]=numeroRandom;
                    printf("[%d] ",vueloski->infoAvion->asientos[0][i]);
                    if(numeroRandom==1){
                        contAsientosTomados++;
                    }
                    //printf("3 ");
                }
                printf("\n");
                for(i=0;i<30;i++){ 
                    numeroRandom = rand()%2;
                    vueloski->infoAvion->asientos[1][i]=numeroRandom;
                    printf("[%d] ",vueloski->infoAvion->asientos[1][i]);
                    if(numeroRandom==1){
                        contAsientosTomados++;
                    }
                    //printf("3 ");
                }
                printf("\n");
                for(i=0;i<30;i++){
                    numeroRandom = rand()%2;
                    vueloski->infoAvion->asientos[2][i]=numeroRandom;
                    printf("[%d] ",vueloski->infoAvion->asientos[2][i]);
                    if(numeroRandom==1){
                        contAsientosTomados++;
                    }
                    //printf("3 ");
                }
                printf("\n");
                for(i=0;i<20;i++){  
                    numeroRandom = rand()%2;
                    vueloski->infoAvion->asientos[3][i]=numeroRandom;
                    printf("[%d] ",vueloski->infoAvion->asientos[3][i]);
                    if(numeroRandom==1){
                        contAsientosTomados++;
                    }
                    //printf("3 ");
                }

                vueloski->infoAvion->asientosOcupados= contAsientosTomados;
                printf("\n");
                printf("Asientos ocupados despues de randomizacion: %d\n",contAsientosTomados);

            }

            if(vueloski->infoAvion->asientosTotales == 90){
                
                contAsientosTomados=0;
                for(i=0;i<3;i++){
                    for(j = 0 ; j < 30; j++){
                        numeroRandom = rand()%2;
                        vueloski->infoAvion->asientos[i][j]=numeroRandom;
                        printf("[%d] ",vueloski->infoAvion->asientos[i][j]);
                        if(numeroRandom==1){
                            contAsientosTomados++;
                        }
                        //printf("3 ");
                    } 
                    printf("\n");
                }

                vueloski->infoAvion->asientosOcupados= contAsientosTomados;
                printf("\n");
                printf("Asientos ocupados despues de randomizacion: %d\n",contAsientosTomados);

            }

            if(vueloski->infoAvion->asientosTotales == 80){
                
                contAsientosTomados=0;
                for(i=0;i<4;i++){
                    for(j = 0 ; j < 20; j++){
                        numeroRandom = rand()%2;
                        vueloski->infoAvion->asientos[i][j]=numeroRandom;
                        printf("[%d] ",vueloski->infoAvion->asientos[i][j]);
                        if(numeroRandom==1){
                            contAsientosTomados++;
                        }
                        //printf("3 ");
                    } 
                    printf("\n");
                    
                }

                vueloski->infoAvion->asientosOcupados= contAsientosTomados;
                printf("\n");
                printf("Asientos ocupados despues de randomizacion: %d\n",contAsientosTomados);

            }
            
            vueloski = nextList(L);
        }  
        L = nextMap(mapaVuelos); 
    }

    printf("\n");
}

void* revisionHoraAvion(double horaGeneral,Map* mapaVuelos){

    if(horaGeneral == 24){
        printf("No quedan mas vuelos XD\n");
        exit(1);
    }

    double parteDecimal, auxHoraG,parteEntera;
    auxHoraG=horaGeneral;
    parteDecimal= modf(auxHoraG,&parteEntera);

    if(parteDecimal == 0.5){
       auxHoraG=auxHoraG-0.2;
       printf("HoraG: %lf\n",auxHoraG);
    }

    List * L;
    L = firstMap(mapaVuelos);
    printf("HoraG antes de whiles: %lf\n",auxHoraG);
    while(L != NULL){
        vuelo * vueloski = (vuelo*)malloc(sizeof(vuelo));
        vueloski = firstList(L);
        while(vueloski!=NULL){
            if(vueloski->hora<=auxHoraG){
                if(vueloski->habilitado == true){
                    vueloski->habilitado=false;
                    printf("Vuelo hacia %s,%s ha sido inhabilitado.\n",vueloski->ciudad,vueloski->pais);
                }
                
            }
            vueloski = nextList(L);
        }
        L = nextMap(mapaVuelos);
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

    ///////////////////////////////////////////////

    char lineaArchivo[1024];
    int i;
    int cont = 0;

    while (fgets (lineaArchivo, 1024, file) != NULL) {

        vuelo* vueloC = (vuelo*) malloc (sizeof(vuelo));
        avion* avionC = (avion*) malloc ( sizeof(avion));

        for(i = 0; i <= 6; i++){

            char* aux = get_csv_field(lineaArchivo,i);

            if(i == 0){
                vueloC->empresa = aux; 
            }
            
            if(i == 1){
                vueloC->pais = aux;
            }

            if(i == 2){
                vueloC->ciudad = aux;
                //printf("VueloC->ciudad 1 : %s\n",vueloC->ciudad);
            }

            if(i == 3){
                vueloC->precio = atoi(aux);
            }
            
            /*
            if(i == 4){
                avionC->asientosOcupados = atoi(aux);
            }
            */

            if(i == 4){
                avionC->asientosTotales = atoi(aux);
            }
            if(i == 5){
                vueloC->hora = atof(aux);
            }

            vueloC->ofertaAplicada=false;
            vueloC->habilitado=true;
            vueloC->infoAvion = avionC;
        }

        const char * M;
        M = searchMap(mapaVuelos,vueloC->ciudad);
        if(M == NULL){
            List * listaVuelardos = createList();
            pushFront(listaVuelardos,vueloC);
            insertMap(mapaVuelos,vueloC->ciudad,listaVuelardos);
            //printf("VueloC->ciudad 2: %s\n",vueloC->ciudad);
        }
        else{
            List * L = (List*)searchMap(mapaVuelos,vueloC->ciudad);
            pushFront(L,vueloC);
            //printf("VueloC->ciudad 3: %s\n",vueloC->ciudad);
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
    int cont=0;

    while (fgets (lineaArchivo, 1024, file) != NULL) {

        ofertaVuelo * oferta = (ofertaVuelo*)malloc(sizeof(ofertaVuelo));

        for(i = 0; i <= 4; i++){
            
            
            char* aux = get_csv_field(lineaArchivo,i);

            if(i == 0){
                oferta->empresa = aux;
                //printf("%s\n",oferta->empresa);
            }
            
            if(i == 1){
                oferta->pais = aux;
            }

            if(i == 2){
                oferta->ciudad = aux;
            }

            if(i == 3){
                oferta->descuento = atoi(aux);
            }
        }

        pushBack(listaOfertas,oferta);
        cont++; 
        if(cont == 20) break;

    }

    ofertaVuelo * L = (ofertaVuelo*)malloc(sizeof(ofertaVuelo));
    L = firstList(listaOfertas);
    while(L != NULL){
        //printf("INICIO\n");
        List * M = (List*)searchMap(mapaVuelos,L->ciudad);

        vuelo * vuelardoXD = (vuelo*)malloc(sizeof(vuelo));
        vuelardoXD = firstList(M);

        while(vuelardoXD != NULL){
            
            bool uno=false,dos=false,tres=false;

            if(strcmp(vuelardoXD->empresa,L->empresa) == 0){
                uno=true;
                //printf("Empresa: %s\n",vuelardoXD->empresa);
            }

            if(strcmp(vuelardoXD->pais,L->pais) == 0){
                dos=true;
                //printf("pais: %s\n",vuelardoXD->pais);
            }

            if(strcmp(vuelardoXD->ciudad,L->ciudad) == 0){
                tres=true;
                //printf("ciudad: %s\n",vuelardoXD->ciudad);
            }

            if(tres == true && dos == true && uno == true){
                double ofertaza;
                ofertaza = (double)L->descuento/100;
                vuelardoXD->precio = vuelardoXD->precio-(vuelardoXD->precio*ofertaza);
                vuelardoXD->ofertaAplicada= true;
                //printf("Ofertarda: %d\n",vuelardos->precio);
            }
            
            vuelardoXD = nextList(M);
        }
        //printf("PASA\n");
        L=nextList(listaOfertas);
    }

    
}

void * comprarPasaje(Map *mapaVuelos, List *listaPasajes){
    //--...--
}

void * busquedaVuelos(Map *mapaVuelos){
    
    printf("Ingrese el destino deseado:");
    char * destiny = (char*) malloc(40*sizeof(char));
    
    scanf(" %[^\n]s]", destiny);
    List * L;
    L = firstMap(mapaVuelos);
    int cont=1;

    printf("VUELOS ENCONTRADOS:\n");
    while(L != NULL){
        vuelo * vueloski = (vuelo*)malloc(sizeof(vuelo));
        vueloski = firstList(L);
        while(vueloski!=NULL){
            if(strcmp(vueloski->ciudad,destiny)==0){
                printf("(%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %d ||\n",cont,vueloski->empresa,vueloski->pais,vueloski->ciudad,vueloski->precio,vueloski->infoAvion->asientosOcupados,vueloski->infoAvion->asientosTotales, vueloski->hora);
                cont++;
            }
            vueloski = nextList(L);
        }
        
        L = nextMap(mapaVuelos); 
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
            printf("1. Por empresa\n");
            printf("2. Por rangos de precio\n");
            printf("3. Por rangos de hora\n");
            printf("0. Salir\n");

            scanf("%i", &opcion);
            switch (opcion){
                case 1: 
                    cont = 1;
                    
                    L = firstMap(mapaVuelos);
                    printf("Segun que empresa desea su vuelo: ");
                    char * empresa = (char*) malloc(40*sizeof(char));
                    scanf(" %[^\n]s]", empresa);

                    while(L != NULL){
                        vuelo * vueloski = (vuelo*)malloc(sizeof(vuelo));
                        vueloski = firstList(L);
                        while(vueloski!= NULL){
                            if(strcmp(vueloski->empresa,empresa)==0){
                                if(strcmp(vueloski->ciudad,destiny)==0){
                                    printf("(%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloski->empresa,vueloski->pais,vueloski->ciudad,vueloski->precio,vueloski->infoAvion->asientosOcupados,vueloski->infoAvion->asientosTotales, vueloski->hora);
                                    cont++;
                                }
                            }
                            vueloski = nextList(L);
                        }
                        L = nextMap(mapaVuelos); 
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
                    
                    L = firstMap(mapaVuelos);

                    while(L != NULL){
                        vuelo * vueloski = (vuelo*)malloc(sizeof(vuelo));
                        vueloski = firstList(L);
                        while(vueloski!= NULL){
                            if(strcmp(vueloski->ciudad,destiny)==0){
                                if(vueloski->precio >= rangoUno && vueloski->precio <= rangoDos){
                                    printf("(%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloski->empresa,vueloski->pais,vueloski->ciudad,vueloski->precio,vueloski->infoAvion->asientosOcupados,vueloski->infoAvion->asientosTotales, vueloski->hora);
                                    cont++;
                                }
                            }
                            vueloski = nextList(L);
                        }
                        L = nextMap(mapaVuelos); 
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
                    
                    L = firstMap(mapaVuelos);

                    while(L != NULL){
                        vuelo * vueloski = (vuelo*)malloc(sizeof(vuelo));
                        vueloski = firstList(L);
                        while(vueloski!= NULL){
                            if(strcmp(vueloski->ciudad,destiny)==0){
                                if(vueloski->hora >= horaUno && vueloski->hora <= horaDos){
                                    printf("(%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloski->empresa,vueloski->pais,vueloski->ciudad,vueloski->precio,vueloski->infoAvion->asientosOcupados,vueloski->infoAvion->asientosTotales, vueloski->hora);
                                    cont++;
                                }
                            }
                            vueloski = nextList(L);
                        }
                        L = nextMap(mapaVuelos); 
                    }
                break;

            }
        }        
    }
    
}

void * estadoVuelos(List *ListaPasajes){
    
}

void * revisarPasaje(List *listaPasajes){
    
}

void * ofertasAplicadas(Map * mapaVuelos){

    List * L;
    L = firstMap(mapaVuelos);
    int cont=1;
    while(L != NULL){
        vuelo * vueloski = (vuelo*)malloc(sizeof(vuelo));
        vueloski = firstList(L);
        while(vueloski!=NULL){
            if(vueloski->ofertaAplicada == true){
                printf("(%i) Empresa: %s || Pais: %s || Ciudad: %s || Precio: %i || Asientos Ocupados: %hu || Asientos Totales: %hu || Hora: %.2lf ||\n",cont,vueloski->empresa,vueloski->pais,vueloski->ciudad,vueloski->precio,vueloski->infoAvion->asientosOcupados,vueloski->infoAvion->asientosTotales, vueloski->hora);
                cont++;
            }
            vueloski = nextList(L);
        }
        
        L = nextMap(mapaVuelos);
    }
    
    horaGeneral= horaGeneral + 0.5;
    printf("HoraGeneral antes de funcion: %.2lf\n",horaGeneral);
    revisionHoraAvion(horaGeneral,mapaVuelos);
}

/*
void * modificarVuelos(List * listaVuelos){

}
*/