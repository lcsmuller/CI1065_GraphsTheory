#include <stdio.h>
#include "grafo.h"

int
main(void)
{
    grafo g = le_grafo();

    printf(" numero de vertices do grafo: %i \n", n_vertices(g));
    printf(" numero de arestas do grafo: %i \n", n_arestas(g));
    printf(" grau maximo: %i | grau mínimo: %i | grau médio: %i \n",
	   	grau_maximo(g), grau_minimo(g), grau_medio(g));
    printf(" numero de triangulos do grafo: %i \n", n_triangulos(g));
    printf(" regular: %i | completo: %i  | bipartido: %i \n", regular(g), completo(g), bipartido(g));

    escreve_grafo(g);
    //destroi_grafo(g);

    grafo comp = complemento(g); 
	printf(" numero de vertices do grafo: %i \n", n_vertices(comp));
    printf(" numero de arestas do grafo: %i \n", n_arestas(comp));
    printf(" grau maximo: %i | grau mínimo: %i | grau médio: %i \n",
		grau_maximo(comp), grau_minimo(comp), grau_medio(comp));
    printf(" numero de triangulos do grafo: %i \n", n_triangulos(comp));
    printf(" regular: %i | completo: %i  | bipartido: %i \n", regular(comp), completo(comp), bipartido(comp));

    int **matriz = matriz_adjacencia(g); 
    imprime_matriz(matriz,n_vertices(g));
	escreve_grafo(comp);
    libera_matriz(matriz,n_vertices(g));
    destroi_grafo(comp);
	destroi_grafo(g);
    
    return 0;
}