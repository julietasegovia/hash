#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


TablaHash *crear(int tam) {
    TablaHash *th = malloc(sizeof(TablaHash));
    th->cantidad = tam;
    th->datos = malloc(sizeof(int) * tam);
    th->cantOc = 0;

    return th;
}

TablaHash *redimensionar(TablaHash *th){
    TablaHash *newth = crear(th->cantidad * 2);
    for(int i=0; i<th->cantidad; i++){
        agregar(newth, th->datos[i]);
    }
    return newth;
}

int fhash(TablaHash *th, int dato){
    return dato % th->cantidad;
}

int estaVacia(TablaHash *th){
    return th->datos == NULL;
}

int buscar(TablaHash *th, int dato){
    int indice = fhash(th, dato);
    return th->datos[indice];
}

void agregar(TablaHash *th, int dato){
    if(th->cantOc >= 0.75 * th->cantidad)
         redimensionar(th);

    int indice = fhash(th, dato);
    th->datos[indice] = dato;
    th->cantOc ++;
}

void eliminar(TablaHash *th, int dato){
    int indice = fhash(th, dato);
    
    th->cantOc --;
}