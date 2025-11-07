#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

TablaHash *crear(int tam) {
    TablaHash *th = malloc(sizeof(TablaHash));
    if (!th) return NULL;
    
    th->cantidad = tam;
    th->datos = malloc(sizeof(int) * tam);
    if (!th->datos) {
        free(th);
        return NULL;
    }

    for (int i = 0; i < tam; i++) {
        th->datos[i] = -1;
    }
    
    th->cantOc = 0;
    return th;
}

TablaHash *redimensionar(TablaHash *th){
    if (!th) return NULL;
    
    int nuevo_tam = th->cantidad * 2;
    TablaHash *newth = crear(nuevo_tam);
    if (!newth) return NULL;
  
    for (int i = 0; i < th->cantidad; i++) {
        if (th->datos[i] != -1) { 
            agregar(newth, th->datos[i]);
        }
    }

    liberar(th);
    return newth;
}

int fhash(TablaHash *th, int dato){
    if (!th || th->cantidad == 0) return -1;
    return dato % th->cantidad;
}

int estaVacia(TablaHash *th){
    return th == NULL || th->cantOc == 0;
}

int buscar(TablaHash *th, int dato){
    if (!th) return -1;
    
    int indice = fhash(th, dato);
    if (indice < 0 || indice >= th->cantidad) return -1;
    
    return th->datos[indice];
}

void agregar(TablaHash *th, int dato){
    if (!th) return;

    if (th->cantOc >= 0.75 * th->cantidad) {
        TablaHash *nueva = redimensionar(th);
        if (nueva) {
            *th = *nueva;
            free(nueva);   
        }
        return;
    }
    
    int indice = fhash(th, dato);
    if (indice < 0 || indice >= th->cantidad) return;

    if (th->datos[indice] == -1) {
        th->cantOc++;
    }
    
    th->datos[indice] = dato;
}

void eliminar(TablaHash *th, int dato){
    if (!th) return;
    
    int indice = fhash(th, dato);
    if (indice < 0 || indice >= th->cantidad) return;

    if (th->datos[indice] != -1) {
        th->datos[indice] = -1;
        th->cantOc--;
    }
}

void liberar(TablaHash *th) {
    if (th) {
        free(th->datos);
        free(th);
    }
}