#ifndef GRAPH_H
    #define GRAPH_H

    #include <stdbool.h>
                       
    typedef struct graph_ GRAPH;

    //

    bool add_vertex(GRAPH *graph, int vertice01); //Estava no primeiro pdf

    bool remove_vertex(GRAPH *graph, int vertice01); //Não está no pdf, mas é racional

    //

    GRAPH *MyGraph(int numero_de_vertices); //Cria o graph;

    bool add_edge(GRAPH *graph, int vertice01, int vertice02, int peso); //Adicionar uma aresta
    
    bool exist_edge(GRAPH *graph, int vertice01, int vertice02); //Checa se uma aresta existe

    int* get_adj_vertex(GRAPH *graph, int vertice01); //Retorna um vetor de interios, que representa os vértices adjacentes

    bool remove_edge(GRAPH *graph, int vertice01, int vertice02); //Remove uma aresta

    void print_info(GRAPH *graph); //Imprime os vértices e arestas

    int number_of_vertexs(GRAPH *graph); //Retorna o numero de vértices que tem meu graph

    bool remove_graph(GRAPH **graph); //Apaga o graph;

    bool menor_peso_graph(GRAPH *graph); //Apaga a aresta de menor peso;

    int** adjacency_matrix(GRAPH *graph); //Retorna a matriz de adjcencia;

    void print_matrix(GRAPH *graph); //Imprime a matriz de adjcencia;

#endif
