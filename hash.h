typedef struct _TablaHash {
    int *datos;
    int cantidad;
    int cantOc;
} TablaHash;

TablaHash *crear(int);
TablaHash *redimensionar(TablaHash *th);
int fhash(TablaHash *th, int);
int estaVacia(TablaHash *th);
int buscar(TablaHash *th, int);
void agregar(TablaHash *th, int);
void eliminar(TablaHash * th, int);