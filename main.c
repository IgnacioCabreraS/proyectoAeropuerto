#include <stdio.h>
#include <wchar.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"
#include "treemap.h"

typedef struct{
    unsigned asientos;
    unsigned cantPasajeros;
}avion;

typedef struct{
    char * empresa;
    char * ciudad;
    char * pais;
    avion * infoAvion;
    double hora;
    bool ofertaAplicada;
    int precio;
}vuelo;

typedef struct{
    char * empresa;
    char * ciudad;
    char * pais;
    int descuento;
}ofertaVuelo;

// prototipos

int lower_than_double(void * , void* );
int lower_than_string(void* key1, void* key2);
char*get_csv_field (char * tmp, int k);
TreeMap* importarVuelos(TreeMap * mapaVuelos);
TreeMap* importarOfertas(TreeMap* mapaVuelos);
void* modoPasajero(TreeMap* mapaVuelos, List* listaPasajes);
void* modoAdministrador(TreeMap* mapaVuelos, List* listaPasajes);
void* comprarPasaje(TreeMap* mapaVuelos, List* listaPasajes);
void* busquedaVuelos(TreeMap* mapaVuelos);
void* estadoVuelos(List* listaPasajes);
void* revisarPasaje(List* listaPasajes);
void* ofertasDisponibles(TreeMap* mapaVuelos);
void* modificarVuelos(TreeMap* mapaVuelos);



int main (){

    TreeMap* mapaVuelos = createTreeMap(lower_than_string);
    List* listaPasajes = createList();
    importarVuelos(mapaVuelos);
    importarOfertas(mapaVuelos);
    
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

void* modoPasajero (TreeMap* mapaVuelo,List* listaPasajes){

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
            case 1: comprarPasaje(mapaVuelo,listaPasajes);break;
            case 2: busquedaVuelos(mapaVuelo);break;
            case 3: estadoVuelos(listaPasajes);break;
            case 4: revisarPasaje(listaPasajes);break;
            case 5: ofertasDisponibles(mapaVuelo);break;
            case 6: modoAdministrador(mapaVuelo,listaPasajes);break;
            default: break;
        }
    }
    
}

void* modoAdministrador (TreeMap* mapaVuelo,List* listaPasajes){

    int opcion = 1;
    while(opcion != 0){
        printf("1. Modificar informacion vuelos.\n");
        printf("2. Pasar modo pasajero.\n");
        
        scanf("%d", &opcion);
        switch (opcion){
            case 1:modificarVuelos(mapaVuelo);break;
            case 2:modoPasajero(mapaVuelo,listaPasajes);break;
            default: break;
        }
    }
}

int lower_than_double(void * key1, void * key2) {
    if(*(double*)key1 > *(double*)key2) return 1;
    return 0;
}

int lower_than_string(void* key1, void* key2){
    char* k1=(char*) key1;
    char* k2=(char*) key2;
    if(strcmp(k1,k2)<0) return 1;
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

TreeMap * importarVuelos(TreeMap * mapaVuelos){
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
                
            }

            if(i == 3){
                vueloC->precio = atoi(aux);
            }

            if(i == 4){
                avionC->cantPasajeros = atoi(aux);
            }

            if(i == 5){
                avionC->asientos = atoi(aux);
            }
            if(i == 6){
                vueloC->hora = atof(aux);
            }

            vueloC->infoAvion = avionC;

            
        }

        vueloC->ofertaAplicada=false;
        insertTreeMap(mapaVuelos,vueloC->ciudad,vueloC);
        cont++; 
        if(cont == 42) break;
    } 
}

TreeMap * importarOfertas(TreeMap * mapaVuelos){
    
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
        Pair * M = firstTreeMap(mapaVuelos);
        
        while(M != NULL){
            
            vuelo * vuelardos = (vuelo*)malloc(sizeof(vuelo));
            vuelardos = M->value;
            bool uno=false,dos=false,tres=false;

            if(strcmp(vuelardos->empresa,L->empresa) == 0){
                uno=true;
            }

            if(strcmp(vuelardos->pais,L->pais) == 0){
                dos=true;
            }

            if(strcmp(vuelardos->ciudad,L->ciudad) == 0){
                tres=true;
            }

            if(tres == true && dos == true && uno == true){
                double ofertaza;
                ofertaza = (double)L->descuento/100;
                vuelardos->precio = vuelardos->precio-(vuelardos->precio*ofertaza);
                vuelardos->ofertaAplicada= true;
                //printf("Ofertarda: %d\n",vuelardos->precio);
            }
            
            M = nextTreeMap(mapaVuelos);   
        }
        L=nextList(listaOfertas);
    }
}

void * comprarPasaje(TreeMap *mapaVuelos, List *listaPasajes){
    
}

void * busquedaVuelos(TreeMap *mapaVuelos){
    
    printf("Ingrese el destino deseado:");
    char * destiny = (char*) malloc(40*sizeof(char));
    scanf(" %[^\n]s]", destiny);

    Pair * M = firstTreeMap(mapaVuelos);
    while(M != NULL){
        vuelo * vuelardos = (vuelo*)malloc(sizeof(vuelo));
        vuelardos = M->value;

        if(strcmp(vuelardos->ciudad,destiny)==0){
            printf("VUELO: %s\n",vuelardos->ciudad);
        }

        M = nextTreeMap(mapaVuelos); 
    }



}

void * estadoVuelos(List *listaPasajes){
    
}

void * revisarPasaje(List *listaPasajes){
    
}

void * ofertasDisponibles(TreeMap *mapaVuelo){
    
}

void * modificarVuelos(TreeMap *mapaVuelo){
    
}