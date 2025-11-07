#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listasimple.h"

TablaHash *crear(int tam) {
    TablaHash *th = malloc(sizeof(TablaHash));
    if (!th) return NULL;
    
    th->cantidad = tam;
    th->listas_datos = malloc(sizeof(Slist) * tam);
    if (!th->listas_datos) {
        free(th);
        return NULL;
    }

    for (int i = 0; i < tam; i++) {
        th->listas_datos[i].nodos = NULL;
        th->listas_datos[i].ultimo = 0;
    }

    return th;
}

TablaHash *redimensionar(TablaHash *th){
    if (!th) return NULL;
    
    int nuevo_tam = th->cantidad * 2;
    TablaHash *newth = crear(nuevo_tam);
    if (!newth) return NULL;
  
    for (int i = 0; i < th->cantidad; i++) {
        SNodo *actual = th->listas_datos[i].nodos;
        while (actual) {
            agregar(newth, actual->dato);
            actual = actual->sig;
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
    SNodo *actual = th->listas_datos[indice].nodos;
    
    for(int i = 0; i<th->listas_datos[indice].ultimo; i++){
        if(actual->dato == dato)
            return actual->dato;
        actual = actual->sig;
    }
    return -1;
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
    SNodo *actual = th->listas_datos[indice].nodos;

    for(int i = 0; i< th->listas_datos[indice].ultimo; i++)
        actual = actual->sig;

    actual->dato = dato;
    th->listas_datos[indice].ultimo ++;

}

void eliminar(TablaHash *th, int dato){
    if (!th) return;
    
    int indice = fhash(th, dato);
    if (indice < 0 || indice >= th->cantidad) return;

    SNodo *actual = th->listas_datos[indice].nodos;

    for(int i = 0; i< th->listas_datos[indice].ultimo; i++)
        actual = actual->sig;

    if (actual->dato == dato) {
        actual->dato = -1;
        th->cantOc--;
    }
}

void liberar(TablaHash *th) {
    if (th) {
        free(th->listas_datos);
        free(th);
    }
}