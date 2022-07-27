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

/* verifica contexto do vértice para conexo() */
struct contexto_vertice {
    Agrec_t header;
    long visitado; /* TRUE se foi visitado, FALSE caso contrário */
};

static char TAG[] = "contexto_vertice";

static int
_vertices_acessiveis(grafo g, vertice v)
{
    struct contexto_vertice *cxt = agbindrec(v, TAG, 0, FALSE);
    if (NULL == cxt)
        cxt = agbindrec(v, TAG, sizeof *cxt, FALSE);
    else if (TRUE == cxt->visitado) /* retorna se vértice já foi visitado */
        return 0;
    cxt->visitado = TRUE; /* marca vértice como visitado */
    /* checa todos os outros vértices possíveis de acessar a partir do atual */
    int n_arestas = 0;
    for (aresta a = agfstedge(g, v); a != NULL; a = agnxtedge(g, a, v))
        n_arestas += _vertices_acessiveis(g, agtail(a))
                     + _vertices_acessiveis(g, aghead(a));
    return n_arestas + 1;
}

int
conexo(grafo g)
{
    int retval = n_vertices(g) == _vertices_acessiveis(g, agfstnode(g));
    struct contexto_vertice *cxt;
    /* reseta flag para 'visitas' do vértice */
    for (vertice v = agfstnode(g); v != NULL; v = agnxtnode(g, v))
        if (NULL != (cxt = agbindrec(v, TAG, 0, FALSE))) cxt->visitado = FALSE;
    return retval;
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

    vertice v1 = agfstnode(g);
    ver[i] = v1;
    i++;
    tam_ver++;
    for (vertice u1 = agnxtnode(g, v1); u1 != NULL; u1 = agnxtnode(g, u1)) {
        if (NULL != agedge(g, v1, u1, NULL, FALSE)) {
            azul[j] = u1;
            j++;
            tam_azul++;
        }
    }
    int k_azul_antigo = 0;
    int k_ver_antigo = tam_ver;
    int flag_vermelho;
    int flag_azul;
    while (i + j < n_vertices(g)){
        flag_vermelho = 0;
        for (int k = k_azul_antigo; k < tam_azul; k++) {
            v1 = azul[k];
            for (vertice u1 = agfstnode(g); u1 != NULL; u1 = agnxtnode(g, u1)) {
                if (NULL != agedge(g, v1, u1, NULL, FALSE)) {
                    flag = 0;
                    for (int L = 0; L < tam_ver; L++) {
                        if (u1 == ver[L]) {
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag){
                        flag_vermelho = 1;
                        ver[i] = u1;
                        i++;
                        tam_ver++;
                    }
                }
            }
        }
        k_azul_antigo = tam_azul;
        
        flag_azul = 0;
        for (int k = k_ver_antigo; k < tam_ver; k++) {
            v1 = ver[k];
            for (vertice u1 = agfstnode(g); u1 != NULL; u1 = agnxtnode(g, u1)) {
                if (NULL != agedge(g, v1, u1, NULL, FALSE)) {
                    flag = 0;
                    for (int L = 0; L < tam_azul; L++) {
                        if (u1 == azul[L]) {
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag){
                        flag_azul = 1;
                        azul[j] = u1;
                        j++;
                        tam_azul++;
                    }
                }
            }    
        }
        k_ver_antigo = tam_ver;

        if(!flag_azul && !flag_vermelho){
            for(v1 = agfstnode(g); v1 != NULL; v1 = agnxtnode(g, v1)){
                flag_azul = 0;
                flag_vermelho = 0;
                for (int L = 0; L < tam_azul; L++) {
                    if (v1 == azul[L]) {
                        flag_azul = 1;
                        break  ;
                    }
                }
                if (flag_azul == 0){
                    for (int L = 0; L < tam_ver; L++) {
                        if (v1 == ver[L]) {
                            flag_vermelho = 1;
                        }
                    }
                }
                if(!flag_vermelho && !flag_azul){
                    ver[i] = v1;
                    i++;
                    tam_ver ++;
                    break;
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
