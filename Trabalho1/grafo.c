#include <stdio.h>
#include "grafo.h"
#include <assert.h>

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
    int k = 0;
    Agedge_t * edge   = agfstout(g, v);
        while (edge != NULL) {
            assert(edge);
            printf("Iterating through yet another edge \n");
            assert(agtail(edge) == v);
            edge = agnxtout(g, edge);
            k++;

        }
    return k;
}

int
grau_maximo(grafo g)
{
    int k;
    int max = 0;
    Agnode_t * node = agfstnode(g);
    while (node != NULL) {
        assert(node);
        printf("Iterating through yet another node\n");
        char  * label = agget(node, "label");
        printf("Node label is %s\n", label);
        k = grau(node,g);


        if (k >= max){
            max = k;
        }
        /* Move on to the next node */
        printf("\n");
        node  = agnxtnode(g, node);
    }
    return max;
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
