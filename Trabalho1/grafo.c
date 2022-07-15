#include <stdio.h>
#include "grafo.h"

/** uma aresta de um grafo ou subgrafo */
typedef Agedge_t *aresta;

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
    return agdegree(g, v, TRUE, TRUE);
}

int
grau_maximo(grafo g)
{
    int max = 0, tmp;
    for (vertice v = agfstnode(g); v != NULL; v = agnxtnode(g, v))
        if (max < (tmp = grau(v, g))) max = tmp;
    return max;
}

int
grau_minimo(grafo g)
{
    vertice v = agfstnode(g);
    int min = grau(v, g), tmp;
    if (v != NULL) {
        for (v = agnxtnode(g, v); v != NULL; v = agnxtnode(g, v))
	    if (min > (tmp = grau(v, g))) min = tmp;
    }
    return min;
}

int
grau_medio(grafo g)
{
    int sum = 0, k = 0;
    for (vertice v = agfstnode(g); v != NULL; v = agnxtnode(g, v)) {
	sum += grau(v, g);
	++k;
    }
    return k != 0 ? sum / k : 0;
}

int
regular(grafo g)
{
    vertice v = agfstnode(g);
    const int grau_esperado = grau(v, g);
    if (v != NULL) {
        for (v = agnxtnode(g, v); v != NULL; v = agnxtnode(g, v))
	    if (grau_esperado != grau(v, g)) return 0;
    }
    return 1;
}

int
completo(grafo g)
{
    /* para ser completo é preciso ser não direcionado e simples */
    if (agisdirected(g) || agissimple(g)) return 0;
    /* cada vértice deverá apontar para todos os outros vértices restantes */
    const int grau_esperado = n_arestas(g) - 1;
    for (vertice v = agfstnode(g); v != NULL; v = agnxtnode(g, v))
	if (grau_esperado != grau(v, g)) return 0;
    return 1;
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
