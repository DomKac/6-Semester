#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>

typedef struct Fifo {
    

} Fifo;

typedef struct Vertex {
    size_t key;
    char color;
    struct Vertex* next;
} Vertex;

Vertex* createVertex(size_t);

typedef struct Graph {
    char type;                  // D - skierowany | U - nieskierowany
    size_t n;                   // liczba wierzchołków
    struct Vertex** adjLists;   // lista sąsiedztwa
    size_t* visited;
} Graph;

// tworzy wszytskie wierzchołki (nie dodaje krawędzi)
// n - liczba wierzchołków
Graph* createGraph(size_t, char);
void addEdge(Graph* G, size_t u, size_t v);
void printGraph(struct Graph* G);
void freeGraph(Graph* G);


#endif
