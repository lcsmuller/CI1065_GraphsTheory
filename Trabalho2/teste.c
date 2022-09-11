#include <stdio.h>
#include <stdlib.h>

#include "grafo.h"

int
main(void)
{
    grafo g = le_grafo();

    puts("Grafo original:");
    escreve_grafo(g);
    decompoe(g);
    int i = 0;
    for(grafo p = agfstsubg(g); p != NULL ; p = agnxtsubg(p)){
    	printf("\nComponente %d:\n", i + 1);
    	escreve_grafo(p); 
    	i++;
    }
    destroi_grafo(g);

    return 0;
}
