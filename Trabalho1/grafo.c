#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo.h"
#include <stdlib.h>
#include <string.h>

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
    const int grau_esperado = n_vertices(g) - 1;
    for (vertice v = agfstnode(g); v != NULL; v = agnxtnode(g, v))
        if (grau_esperado != grau(v, g)) return 0;
    return 1;
}

static int
_conexo(grafo g, vertice v)
{
    static char tag[] = "visitado";
    /* retorna se vértice já foi visitado */
    if (agbindrec(v, tag, 0, TRUE)) return 0;
    /* marca vértice como visitado */
    agbindrec(v, tag, sizeof(char), TRUE);
    /* checa todos os outros vértices possíveis de acessar a partir do atual */
    int n_arestas = 0;
    for (aresta a = agfstedge(g, v); a != NULL; a = agnxtedge(g, a, v))
        n_arestas += _conexo(g, agtail(a)) + _conexo(g, aghead(a));
    return n_arestas + 1;
}

int
conexo(grafo g)
{
    return n_vertices(g) == _conexo(g, agfstnode(g));
}

int
bipartido(grafo g)
{
    vertice *ver = malloc((long unsigned int)n_vertices(g) * sizeof(vertice));
    int tam_ver = 0;
    vertice *azul = malloc((long unsigned int)n_vertices(g) * sizeof(vertice));
    int tam_azul = 0;
    int i = 0;
    int j = 0;
    int flag;
    int resp = 1;

    for (vertice v1 = agfstnode(g); v1 != NULL; v1 = agnxtnode(g, v1)) {
        flag = 0;
        for (int k = 0; k < tam_azul; k++) {
            if (v1 == azul[k]) flag = 1;
        }
        if (flag == 0) {
            ver[i] = v1;
            i++;
            tam_ver++;
            for (vertice u1 = agnxtnode(g, v1); u1 != NULL;
                 u1 = agnxtnode(g, u1)) {
                if (NULL != agedge(g, v1, u1, NULL, FALSE)) {
                    azul[j] = u1;
                    j++;
                    tam_azul++;
                }
            }
        }
    }
    for (i = 0; i < tam_ver; i++) {
        for (j = i; j < tam_ver; j++) {
            if (NULL != agedge(g, ver[i], ver[j], NULL, FALSE)) resp = 0;
        }
    }
    for (i = 0; i < tam_azul; i++) {
        for (j = i; j < tam_azul; j++) {
            if (NULL != agedge(g, azul[i], azul[j], NULL, FALSE)) resp = 0;
        }
    }
    free(ver);
    free(azul);
    return resp;
}

int
n_triangulos(grafo g)
{
    int triangulo = 0;
    for (vertice v1 = agfstnode(g); v1 != NULL; v1 = agnxtnode(g, v1)) {
        for (vertice u1 = agnxtnode(g, v1); u1 != NULL; u1 = agnxtnode(g, u1))
        {
            if (NULL != agedge(g, v1, u1, NULL, FALSE)) {
                for (vertice k1 = agnxtnode(g, u1); k1 != NULL;
                     k1 = agnxtnode(g, k1)) {
                    if (NULL != agedge(g, u1, k1, NULL, FALSE)
                        && NULL != agedge(g, k1, v1, NULL, FALSE))
                        triangulo++;
                }
            }
        }
    }
    return triangulo;
}

int **
matriz_adjacencia(grafo g)
{
    const int tam = n_vertices(g);
    /* TODO: usar truque do maziero pra inicializar matriz em uma única
     *      alocação */
    int **matriz = malloc((long unsigned int)tam * sizeof(int *));
    for (int i = 0; i < tam; i++)
        matriz[i] = calloc((size_t)tam, sizeof(int));

    int i = 0;
    for (vertice v1 = agfstnode(g); v1 != NULL; v1 = agnxtnode(g, v1)) {
        int j = i + 1;
        for (vertice u1 = agnxtnode(g, v1); u1 != NULL; u1 = agnxtnode(g, u1))
        {
            if (NULL != agedge(g, v1, u1, NULL, FALSE))
                matriz[i][j] = matriz[j][i] = 1;
            else
                matriz[i][j] = matriz[j][i] = 0;
            j++;
        }
        i++;
    }
    return matriz;
}

grafo
complemento(grafo g)
{
    // cria o nome da matriz como "complementar de <nome de g>"
    char nome[256];
    snprintf(nome, sizeof(nome), "complementar de %s", agnameof(g));
    // aloca o grafo , que herda as configuracoes do grafo g (g->desc)
    grafo aux = agopen(nome, g->desc, NULL);
    // preenche os vertices
    for (vertice v = agfstnode(g); v != NULL; v = agnxtnode(g, v))
        agnode(aux, agnameof(v), TRUE);
    // preenche as arestas
    vertice v2 = agfstnode(aux);
    for (vertice v1 = agfstnode(g); v1 != NULL; v1 = agnxtnode(g, v1)) {
        vertice u2 = agnxtnode(aux, v2);
        for (vertice u1 = agnxtnode(g, v1); u1 != NULL; u1 = agnxtnode(g, u1))
        {
            if (NULL == agedge(g, v1, u1, NULL, FALSE))
                agedge(aux, v2, u2, NULL, TRUE);
            u2 = agnxtnode(aux, u2);
        }
        v2 = agnxtnode(aux, v2);
    }
    return aux;
}

void
imprime_matriz(int **matriz, int tam)
{
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++)
            printf("%i ", matriz[i][j]);
        printf("\n");
    }
    printf("\n");
}

void
libera_matriz(int **matriz, int tam)
{
    for (int i = 0; i < tam; i++)
        free(matriz[i]);
    free(matriz);
    return;
}
