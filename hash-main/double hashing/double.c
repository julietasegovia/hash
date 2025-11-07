#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "double.h"

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

    th->d_hash = encontrar_primo_menor(tam);
    
    return th;
}

int encontrar_primo_menor(int n) {
    if (n <= 2) return 1;
    
    for (int i = n - 1; i > 1; i--) {
        int es_primo = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                es_primo = 0;
                break;
            }
        }
        if (es_primo) {
            return i;
        }
    }
    return 1;
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
    if (!th) return 0;
    
    int indice = fhash(th, dato);
    if (indice < 0 || indice >= th->cantidad) return 0;
    
    for(int i = 0; i<th->cantidad; i++){
        if(th->datos[indice] == -1)
            return 0;
        else if(th->datos[indice] == dato)
            return 1;
        indice += th->d_hash;
    }
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

    for(int i = 0; i<th->cantidad; i++){
        if(th->datos[indice] == -1){
            th->datos[indice] = dato;
            th->cantOc ++;
            break;
        }
        indice += th->d_hash;
    }
}

void eliminar(TablaHash *th, int dato){
    if (!th) return;

    if (! buscar(th, dato)) return;
    
    int indice = fhash(th, dato);
    if (indice < 0 || indice >= th->cantidad) return;

    for(int i = 0; i<th->cantidad; i++){
        if(th->datos[indice] == -1){
            th->datos[indice] = -1;
            th->cantOc--;
            break;
        }
        indice += th->d_hash;
    }
}

void liberar(TablaHash *th) {
    if (th) {
        free(th->datos);
        free(th);
    }
}