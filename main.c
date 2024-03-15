#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(){
    GRAPH *grafo1 = MyGraph(4);
    
    add_vertex(grafo1, 1);
    add_vertex(grafo1, 5);
    add_vertex(grafo1, 6);
    add_vertex(grafo1, 0);

    add_edge(grafo1, 1, 5, 1);
    add_edge(grafo1, 1, 6, 2);
    add_edge(grafo1, 1, 0, 3);
    add_edge(grafo1, 5, 6, 4);
    add_edge(grafo1, 5, 0, 5);
    add_edge(grafo1, 0, 0, 6);
    remove_edge(grafo1, 0, 0);

    menor_peso_graph(grafo1);

    print_matrix(grafo1);
    int** mat = adjacency_matrix(grafo1);

    for(int i = 0; i < number_of_vertexs(grafo1); i++)
    {
        for(int j = 0; j < number_of_vertexs(grafo1); j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < number_of_vertexs(grafo1); i++)
    {
        free(mat[i]);
    }
    free(mat);

    print_info(grafo1); 

    remove_graph(&grafo1);

    return 0;
}