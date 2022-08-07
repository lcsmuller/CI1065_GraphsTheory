INTEGRANTES
    Guilherme Pateiro   GRR20197152
    Lucas Müller        GRR20197160

INTRODUÇÃO
    Neste trabalho foi implementado alguns algoritmos e funcionalidades 
    ligadas à Teoria de Grafos.

grafo le_grafo(void);
    Esta função é um simples wrapper de agread(), ela recebe da entrada padrão
    um grafo conforme a especificação .dot, e então devolve a estrutura grafo
    resultante do parsing.

void destroi_grafo(grafo g);
    Esta função limpa todos recursos alocados para um grafo de entrada,
    inclusive seus vértices, arestas, e eventuais subgrafos.

grafo escreve_grafo(grafo g);
    Esta função escreve uma estrutura grafo em seu formato conforme a
    especificação .dot, na saída padrão.

int n_vertices(grafo g);
    Esta função é um simples wrapper de agnodes() que retorna a quantidade
    total de vértices do grafo.

int n_arestas(grafo g);
    Esta função é um simples wrapper de agedges() que retorna a quantidade
    total de arestas do grafo.

int grau(vertice v, grafo g);
    Esta função é um simples wrapper de agdegree() que retorna a quantidade
    total de arestas saindo de um determinado vértice.

int grau_maximo(grafo g);
    Esta função percorre cada vértice do grafo, e retorna o maior grau
    encontrado.

int grau_minimo(grafo g);
    Esta função percorre cada vértice do grafo, e retorna o menor grau
    encontrado.

int grau_medio(grafo g);
    Esta função percorre cada vértice do grafo, e retorna a media de todos os
    graus encontrados (soma de graus divido pela quantidade de vértices).

int regular(grafo g);
    Esta função armazena o grau de um primeiro vértice qualquer, então
    verifica se todos graus de vértices posteriores são idênticos, para
    satisfazer a condição de grafo regular (neste caso retorna 1).

int completo(grafo g);
    Esta função verifica se o grafo é completo, verificando se cada vértice
    do grafo possua um grau igual à quantidade total de vértices no grafo.

int conexo(grafo g);
    Esta função verifica se um grafo é conexo (é possível traçar um caminho de
    um vertíce qualquer, para qualquer outro vértice), a partir da estratégia
    coloração. Cada vértice visitado é marcado, e em uma chamada recursiva
    os seus vértices adjacentes também são visitados e marcados. Se a
    quantidade de arestas marcadas mais um for igual ao numero total de
    vértices no grafo então significa que não há um subgrafo.

int bipartido(grafo g);
    Esta função verifica se um grafo qualquer é bipartido, ou seja,verifica se
    seus vertices podem ser separados em 2 conjuntos de forma que todos os
    elementos de um conjunto não seja vizinho de todos os outros elementos 
    do mesmo conjunto. O algoritmo escolhido para verificar a bipartição é
    o de coloração 2 do grafo, para isso todos os vertices sao dividos entre
    2 vetores (vermelho, azul) e após todos os vertices serem coloridos,
    há uma comparação de 2 vertices do mesmo vetor são vizinho no grafo. 

int n_triangulos(grafo g);
    Esta função conta quanto triangulos (3 vertices unidos entre si por arestas)
    existem em um grafo. Para fazer essa contagem são escolhidos 3 vertices ,então se testa 
    se ha aresta entre 2 vertices, se houver aresta, eles testa se há arestas entre
    os 2 vertices encolhido anteriormente e o terceito vertice.

int matriz_adjacencia(grafo g);
    Essa função pega um grafo no formato de struct do vizgraph e a trasforma em uma
    matriz de adjacencia.

int complemento(g);
    Essa função recebe um grafo e gera um novo grafo contendo o grafo complementar do 
    grafo de entrada, o grafo original não é modificado. 
