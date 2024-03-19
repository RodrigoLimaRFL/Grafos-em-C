#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph.h"
#include <limits.h>

#define NEUTRAL_ELEMENT -1

struct graph_{
    int **matriz;
    bool *vertices;
    int tamanho;
    int numVertices;
};

GRAPH *MyGraph(int numero_de_vertices){
    GRAPH *my_graph = (GRAPH*) malloc (sizeof(GRAPH));
    if (my_graph == NULL){
        printf("Não foi possível alocar memória\n");
        exit(1);
    }

    my_graph->tamanho = numero_de_vertices;
    my_graph->numVertices = 0;

    if ((my_graph->vertices = (bool*) malloc (numero_de_vertices*sizeof(bool))) == NULL){
        printf("Não foi possível alocar memória\n");
        exit(1);
    }

    if ((my_graph->matriz = (int**) malloc (numero_de_vertices*sizeof(int*))) == NULL){
        printf("Não foi possível alocar memória\n");
        exit(1);
    }
    for(int i=0; i<numero_de_vertices; i++){
        if ((my_graph->matriz[i] = (int*) malloc (numero_de_vertices*sizeof(int))) == NULL){
            printf("Não foi possível alocar memória\n");
            exit(1);
        }
    }

    for (int i = 0; i<numero_de_vertices; i++){
        my_graph->vertices[i] = false;
    }

    for(int i = 0; i<numero_de_vertices; i++){
        for(int j = 0; j<numero_de_vertices; j++){
            my_graph->matriz[i][j]=NEUTRAL_ELEMENT;
        }
    }

    return my_graph;
}

bool exist_vertex(GRAPH *graph, int vertice01){
    if(graph->tamanho <= vertice01)
        return false;

    if(graph->vertices[vertice01] == true)
        return true;
    else
        return false;
}

bool add_vertex(GRAPH *graph, int vertice01){
    if(exist_vertex(graph, vertice01)){
        return false;
    }
    else if(graph->tamanho <= vertice01){
        int memory_size = vertice01 + 1;
        // realloca o vetor de vertices
        graph->vertices = (bool*) realloc(graph->vertices, memory_size*sizeof(bool));
        if(graph->vertices == NULL)
        {
            printf("Não foi possível alocar memória\n");
            exit(1);
        }

        for(int i = graph->tamanho; i<memory_size; i++){
            graph->vertices[i] = false;
        }
        
        // realloca a matriz de adjacencia
        graph->matriz = (int**) realloc(graph->matriz, memory_size*sizeof(int*));
        if(graph->matriz == NULL)
        {
            printf("Não foi possível alocar memória\n");
            exit(1);
        }

        // realloca os vetores de adjacencia que ja existem
        for(int i = 0; i < graph->tamanho; i++){
            graph->matriz[i] = (int*) realloc(graph->matriz[i], memory_size * sizeof(int));
            if (graph->matriz[i] == NULL){
                printf("Não foi possível alocar memória\n");
                exit(1);
            }
        }

        
        // aloca os vetores de adjacencia que ainda nao existem
        for(int i = graph->tamanho; i <= vertice01; i++){
            graph->matriz[i] = (int*) malloc(memory_size * sizeof(int));
            if (graph->matriz[i] == NULL){
                printf("Não foi possível alocar memória\n");
                exit(1);
            }
        }

        // preenche a matriz de adjacencia com zeros
        for(int i = graph->tamanho; i<memory_size; i++){
            for(int j = 0; j<memory_size; j++){
                graph->matriz[i][j]=NEUTRAL_ELEMENT;
            }
        }

        for(int i = 0; i<graph->tamanho; i++){
            for(int j = graph->tamanho; j<memory_size; j++){
                graph->matriz[i][j]=NEUTRAL_ELEMENT;
            }
        }

        // coloca o tamanho do grafo como o novo tamanho
        graph->tamanho = memory_size;
    }
    // coloca o valor do vertice como true
    graph->vertices[vertice01] = true;
    graph->numVertices++;
    printf("Vertice %d adicionado\n", vertice01);
    return true;
}


bool remove_vertex(GRAPH *graph, int vertice01){

}


bool add_edge(GRAPH *graph, int vertice01, int vertice02, int peso){
    if (exist_vertex(graph, vertice01) && exist_vertex(graph, vertice02)){
        graph->matriz[vertice01][vertice02] = peso;
        graph->matriz[vertice02][vertice01] = peso;
        printf("Aresta %d %d adicionada com sucesso\n", vertice01, vertice02);
        return true;
    }
    else{
        printf("Aresta não adicionada\n");
        return false;
    }
}


bool exist_edge(GRAPH *graph, int vertice01, int vertice02){
    if(exist_vertex(graph, vertice01) == false || exist_vertex(graph, vertice02) == false){
        printf("Um de seus vértices não existe, tente novamente. ");
        return false;
    }

    if(graph->matriz[vertice01][vertice02] != NEUTRAL_ELEMENT){
        return true;
        //printf("Essa aresta existe");
    }
    else{
        //printf("Essa aresta não existe");
        return false;
    }
}

int* get_adj_vertex(GRAPH *graph, int vertice01){
    if(exist_vertex(graph, vertice01) == false){
        printf("Vértice não existe\n");
        return NULL;
    }

    int *adjacentes = (int*) malloc(graph->tamanho*sizeof(int));
    if(adjacentes == NULL){
        printf("Não foi possível alocar memória\n");
        exit(1);
    }

    int contador = 0;
    for(int i = 0; i<graph->tamanho; i++){
        if(exist_edge(graph, vertice01, i) == true){
            adjacentes[contador] = i;
            contador++;
        }
    }
    
    for(int i = 0; i<contador; i++){
        printf("%d ", adjacentes[i]);
    }
    printf("\n");

    return adjacentes;
}


bool remove_edge(GRAPH *graph, int vertice01, int vertice02){
    if(exist_edge(graph, vertice01, vertice02) == false){
        printf("Aresta não existe\n");
        return false;
    }

    graph->matriz[vertice01][vertice02] = NEUTRAL_ELEMENT;
    graph->matriz[vertice02][vertice01] = NEUTRAL_ELEMENT;
    printf("Aresta %d %d removida\n", vertice01, vertice02);
    return true;
}


void print_info(GRAPH *graph){
    for(int i = 0; i<graph->tamanho; i++){
        if(graph->vertices[i] == true){
            printf("Vértice %d => Arestas: { ", i);
            for(int j = 0; j<graph->tamanho; j++){
                if(graph->matriz[i][j] != NEUTRAL_ELEMENT){
                    printf("(%i, %i); ", i, j);
                }
            }
            printf("}\n");
        }
    }
}


int number_of_vertexs(GRAPH *graph){
    int counter = 0;

    for(int i = 0; i<graph->tamanho; i++){
        if(graph->vertices[i] == true){
            counter++;
        }
    }

    return counter;
}


bool remove_graph(GRAPH **graph){
    for(int i = 0; i<(*graph)->tamanho; i++){
        free((*graph)->matriz[i]);
        ((*graph)->matriz[i] = NULL);
    }
    free((*graph)->matriz);
    (*graph)->matriz = NULL;
    free((*graph)->vertices);
    (*graph)->vertices = NULL;
    free(*graph);
    (*graph) = NULL;
    return true;
} 


bool menor_peso_graph(GRAPH *graph){
    int aresta[2] = {0, 0};
    int peso = INT_MAX;
    int* vertices = malloc(graph->numVertices*sizeof(int));

    int contador = 0;
    for(int i = 0; i<graph->tamanho; i++)
    {
        if(exist_vertex(graph, i))
        {
            vertices[contador] = i;
            contador++;
        }
    }
    
    for(int i = 0; i<graph->numVertices; i++)
    {
        for (int j = i; j<graph->numVertices; j++)
        {
            if(graph->matriz[vertices[i]][vertices[j]] != NEUTRAL_ELEMENT && graph->matriz[vertices[i]][vertices[j]] < peso)
            {
                aresta[0] = vertices[i];
                aresta[1] = vertices[j];
                peso = graph->matriz[vertices[i]][vertices[j]];
            }
        }
    }

    free(vertices);
    
    if(peso != INT_MAX)
    {
        //printf("(%i, %i)\n", aresta[0], aresta[1]);
        remove_edge(graph, aresta[0], aresta[1]);
        return true;
    }
    else
    {
        return false;
    }
} 


int** adjacency_matrix(GRAPH *graph){
    int* vertices = malloc(graph->numVertices*sizeof(int));

    int contador = 0;
    for(int i = 0; i<graph->tamanho; i++)
    {
        if(exist_vertex(graph, i))
        {
            vertices[contador] = i;
            contador++;
        }
    }

    int** matriz = (int**) malloc(graph->numVertices*sizeof(int*));

    for(int i = 0; i<graph->numVertices; i++)
    {
        matriz[i] = (int*) malloc(graph->numVertices*sizeof(int));
    }

    for(int i = 0; i<graph->numVertices; i++)
    {
        for(int j = 0; j<graph->numVertices; j++)
        {
            matriz[i][j] = graph->matriz[vertices[i]][vertices[j]];
        }
    }

    free(vertices);

    return matriz;
}

void print_matrix(GRAPH *graph){
    for(int i = 0; i<graph->tamanho; i++){
        for(int j = 0; j<graph->tamanho; j++){
            printf("%d ", graph->matriz[i][j]);
        }
        printf("\n");
    }
}



