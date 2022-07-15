#include <stdio.h>
#include "grafo.h"

int
main(void)
{
    grafo g = le_grafo();


    printf(" numero de vertices do grafo: %i \n", n_vertices(g));
    printf(" numero de arestas do grafo: %i \n", n_arestas(g));
    printf("grau maximo : %i \n", grau_maximo(g));
    escreve_grafo(g);
    destroi_grafo(g);

    return 0;
}
