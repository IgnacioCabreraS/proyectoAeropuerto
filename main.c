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
}vuelo;

// prototipos

int lower_than_double(void * , void* );
char*get_csv_field (char * tmp, int k);
TreeMap* importar(TreeMap * mapaVuelo);
void* modoPasajero(TreeMap* mapaVuelo, List* listaPasajes);
void* modoAdministrador(TreeMap* mapaVuelo, List* listaPasajes);
void* comprarPasaje(TreeMap* mapaVuelo, List* listaPasajes);
void* busquedaVuelos(TreeMap* mapaVuelo);
void* estadoVuelos(List* listaPasajes);
void* revisarPasaje(List* listaPasajes);
void* ofertasDisponibles(TreeMap* mapaVuelo);
void* modificarVuelos(TreeMap* mapaVuelo);



int main (){

    TreeMap* mapaVuelo = createTreeMap(lower_than_double);
    List* listaPasajes = createList();
    importar(mapaVuelo);
    
    int opcion=1;
    while(opcion!=0){
        printf("1. Modo pasajero.\n");
        printf("2. Modo administrador.\n");
        scanf("%d",&opcion);
        switch(opcion){
            case 1:modoPasajero(mapaVuelo,listaPasajes);break; //  pasar opcion para verificar si se sale del switch
            case 2:modoAdministrador(mapaVuelo, listaPasajes);break;
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

TreeMap * importar(TreeMap * mapaVuelos){
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
                vueloC->ciudad = aux;
            }

            if(i == 2){
                vueloC->pais = aux;
            }

            if(i == 3){
                avionC->asientos = atoi(aux);
            }
             if(i == 4){
                avionC->cantPasajeros = atoi(aux);
            }

            if(i == 5){
                vueloC->hora = atof(aux);
            }

            vueloC->infoAvion = avionC;
        }
        cont++; 
        if(cont == 42) break;
    } 
}

void * comprarPasaje(TreeMap *mapaVuelo, List *listaPasajes){
    
}

void * busquedaVuelos(TreeMap *mapaVuelo){
    
}

void * estadoVuelos(List *listaPasajes){
    
}

void * revisarPasaje(List *listaPasajes){
    
}

void * ofertasDisponibles(TreeMap *mapaVuelo){
    
}

void * modificarVuelos(TreeMap *mapaVuelo){
    
}