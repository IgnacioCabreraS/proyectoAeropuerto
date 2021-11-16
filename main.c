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
    unsigned asientos;// matriz
    unsigned cantPasajeros;
}avion;

typedef struct{
    char destino;
    double hora;
    struct avion;
    char empresa;
}vuelo;



int main (){

    int opcion=1;
    while(opcion!=0){
        printf("Para entrar en modo cliente escriba '1'.\n");
        printf("Para entrar en modo administrador escriba '2'.\n");
        printf("Si desea salir del programa, escriba '0'.\n");
        scanf("%d", &opcion);
        
        switch(opcion){
            case 1:modoCliente();break;
            case 2:modoAdministrador();break;
        }
    }
    return 0;
}
