typedef struct C_Hash{
    int dato;
    int next_hash;
}CasillaHash;

typedef struct thash{
    CasillaHash *datos;
    int cantidad;
    int cantOc;
}TablaHash;

TablaHash *crear(int);
TablaHash *redimensionar(TablaHash *th);
int fhash(TablaHash *th, int);
int estaVacia(TablaHash *th);
int buscar(TablaHash *th, int);
int buscar_recursivo(TablaHash *th, int, int);
void agregar(TablaHash *th, int);
void agregar_recursivo(TablaHash *th, int, int);
void eliminar(TablaHash * th, int);