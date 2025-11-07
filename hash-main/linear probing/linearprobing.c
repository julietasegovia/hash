#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linearprobing.h"

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

    for(int i = 0; i < th->cantidad; i++) {
        int pos_actual = (indice + i) % th->cantidad;
        
        if (th->datos[pos_actual] == -1)
            return 0;

        if (th->datos[pos_actual] == dato)
            return 1;
    }

    return 0;

}

void agregar(TablaHash *th, int dato){
    if (!th) return;

    if (buscar(th, dato))
        return;

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

    for(int i = 0; i < th->cantidad; i++){
        if (th->datos[indice + i] == -1) {
            th->cantOc++;
            th->datos[indice + i] = dato;
            break;
        }
    }

}

void eliminar(TablaHash *th, int dato){
    if (!th) return;
    
    int indice = fhash(th, dato);
    if (indice < 0 || indice >= th->cantidad) return;

    for(int i = 0; i < th->cantidad; i++) {
        int pos_actual = (indice + i) % th->cantidad;
        
        if (th->datos[pos_actual] == -1)
            return;

        if (th->datos[pos_actual] == dato) {
            th->datos[pos_actual] = -1;
            th->cantOc--;

            rehash_cluster(th, pos_actual);
            break;
        }
    }
}

// Función auxiliar para rehashear después de eliminar
void rehash_cluster(TablaHash *th, int pos_inicial) {
    int i = 1;
    while (i < th->cantidad) {
        int pos_actual = (pos_inicial + i) % th->cantidad;
        
        if (th->datos[pos_actual] == -1)
            break;

        int hash_ideal = fhash(th, th->datos[pos_actual]);
        
        if ((pos_actual > pos_inicial && 
             (hash_ideal <= pos_inicial || hash_ideal > pos_actual)) ||
            (pos_actual < pos_inicial && 
             (hash_ideal <= pos_inicial && hash_ideal > pos_actual))) {
            th->datos[pos_inicial] = th->datos[pos_actual];
            th->datos[pos_actual] = -1;
            pos_inicial = pos_actual;
            i = 0;
        }
        
        i++;
    }
}
void liberar(TablaHash *th) {
    if (th) {
        free(th->datos);
        free(th);
    }
}