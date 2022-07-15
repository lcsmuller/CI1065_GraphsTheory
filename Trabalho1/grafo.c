#include <stdio.h>
#include "grafo.h"

grafo
le_grafo(void)
{
    return agread(stdin, NULL);
}

void
destroi_grafo(grafo g)
{
    agclose(g);
}

grafo
escreve_grafo(grafo g)
{
    return 0 == agwrite(g, stdout) ? g : NULL;
}

int
n_vertices(grafo g)
{
    return agnnodes(g);
}

int
n_arestas(grafo g)
{
    return agnedges(g);
}

int
grau(vertice v, grafo g)
{
    (void)v;
    (void)g;
    return 0;
}

int
grau_maximo(grafo g)
{
    (void)g;
    return 0;
}

int
grau_minimo(grafo g)
{
    (void)g;
    return 0;
}

int
grau_medio(grafo g)
{
    (void)g;
    return 0;
}

int
regular(grafo g)
{
    (void)g;
    return 0;
}

int
completo(grafo g)
{
    (void)g;
    return 0;
}

int
conexo(grafo g)
{
    (void)g;
    return 0;
}

int
bipartido(grafo g)
{
    (void)g;
    return 0;
}

int
n_triangulos(grafo g)
{
    (void)g;
    return 0;
}

int **
matriz_adjacencia(grafo g)
{
    (void)g;
    return NULL;
}

grafo
complemento(grafo g)
{
    (void)g;
    return NULL;
}
