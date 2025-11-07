typedef struct _TablaHash {
    int *datos;
    int cantidad;
    int cantOc;
    int d_hash;
} TablaHash;

TablaHash *crear(int);
TablaHash *redimensionar(TablaHash *th);
int fhash(TablaHash *th, int);
int estaVacia(TablaHash *th);
int buscar(TablaHash *th, int);
void agregar(TablaHash *th, int);
void eliminar(TablaHash * th, int);