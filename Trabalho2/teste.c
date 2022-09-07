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
    destroi_grafo(g);

    return 0;
}
