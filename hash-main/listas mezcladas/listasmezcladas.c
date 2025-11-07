#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listasmezcladas.h"

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
        th->datos[i].next_hash = -1;
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
        if (th->datos[i].next_hash != -1) { 
            agregar(newth, th->datos[i].dato);
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

int buscar(TablaHash *th, int dato) {
    if (!th) return -1;
    
    int indice = fhash(th, dato);
    if (indice < 0 || indice >= th->cantidad) return -1;
    
    // Si la casilla está vacía, el dato no existe
    if (th->datos[indice].dato == -1)
        return -1;
    
    // Buscar en la cadena de colisiones
    return buscar_recursivo(th, dato, indice);
}

int buscar_recursivo(TablaHash *th, int dato, int indice){

    if(th->datos[indice].dato == dato)
        return dato;

    else if (th->datos[indice].next_hash != -1)
        buscar_recursivo(th, dato, th->datos[indice].next_hash);

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

    if (th->datos[indice].dato == -1) {
        th->cantOc++;
        th->datos[indice].dato = dato;
    }

    else agregar_recursivo(th, dato, indice);

}

agregar_recursivo(TablaHash *th, int dato, int indice){
    int new_indice = indice + 1;

    if(th->datos[new_indice].dato == -1){
        th->datos[new_indice].dato = dato;
        th->datos[new_indice].next_hash = -1;
        th->datos[indice].next_hash = new_indice;
        th->cantOc++;
    }
    else
        if (th->datos[indice].next_hash != -1)
            agregar_recursivo(th, dato, th->datos[indice].next_hash);
        else
            agregar_recursivo(th, dato, new_indice);

}
