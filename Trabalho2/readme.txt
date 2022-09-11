INTEGRANTES
    Guilherme Pateiro   GRR20197152
    Lucas Müller        GRR20197160

INTRODUÇÃO
    Neste trabalho foi implementado o algoritmo de decomposição de um grafo
    direcionado em seus componentes fortes.

grafo decompoe(grafo g):
    Esta função decompoẽ o grafo direcionado fornecido em seus componentes
    fortes, e imprime no stdout a lista dos componentes resultantes da mesma.

    Cada bloco lógico da função está devidamente comentado com a ação esperada
    no topo do seu escopo.

    Utilizamos de `agbind()` (além das funções recomendadas pelo professor)
    para armazenar atributos de cada vértice, de forma que seja fácil modificar
    o valor de estado e componente a que pertencem.

vertice *rev_posordem(grafo G):
    Esta função gera um vetor de vertices de G que é resultado de uma pós-ordem
    em uma busca em profundidade no grafo reverso de G 

    Essa função utiliza alguma funções auxiliares:
        - grafo grafo_reverso(grafo g):
            gera um grafo reverso ao grafo g
        - void dfsR(grafo g, vertice v, vertice *vv, int *cnt):
            faz um busca em profundidade recursiva no grafo g a partir do
            vertice v colocando o resultado dessa busca em vv[cnt]

    O vetor de vertices retornado é utilizado na função decompoe(g) de
    maneira reversa (N .. 0)

void _decompoe(grafo g, vrtice v);
    Essa função é chamada recursivamente com objetivo de marcar os vértices com
    o número do componente em que ele se encontra, para fazer a marcação é
    utilizado a função `agbind()