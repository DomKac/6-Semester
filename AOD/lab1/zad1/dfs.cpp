#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <queue>
#include <chrono>
#include <iostream>

#include "graph.h"

void addEdge(std::vector<size_t> v[], size_t vp, size_t vk, char type) {
    v[vp].push_back(vk);
    if (type == 'U')
        v[vk].push_back(vp);
}

void printAdjList(std::vector<size_t> v[], size_t n) {
    for (size_t i = 1; i < n+1; i++) {
        printf("%zu | ", i);
        for (auto & node : v[i]) {
            printf("%zu ", node);
        }
        puts("");
    }
}

std::vector<bool> visited;
std::vector<int> parent;
std::vector<size_t> depth;

bool start = true;
void dfs(std::vector<size_t> v[], size_t n, size_t s) {
    if (start){
        visited.resize(n+1, false);
        parent.resize(n+1, -1);
        depth.resize(n+1, 0);
        parent[s] = 0;
        start = false;
    }
    visited[s] = true;
    printf("%zu ", s);
    for (auto & node : v[s]) {
        if (!visited[node]){
            parent[node] = (int)s;
            depth[node] = depth[s] + 1;
            dfs(v, n, node);
        }
    }
}

void printDFStree(std::vector<size_t> v[], size_t n) {
    printf("\nDFS tree:\n");
    for (size_t i = 1; i <= n; i++) {
        printf("Vertex %zu, parent: %d, depth: %zu\n", i, parent[i], depth[i]);
    }
}

int main(int argc, char** argv) {

    FILE *dane;
    dane = fopen(argv[1], "r");

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (dane == NULL)
        return EXIT_FAILURE;

    /* D - skierowany | U - nieskierowany */
    char typ[2];
    fscanf(dane, "%s\n", typ);
    printf("%s\n", typ);

    /* liczba wierzchołków |V| */
    size_t n;
    fscanf(dane, "%lu\n", &n);
    printf("|V| = %lu\n", n);

    /* liczba krawędzi |E| */
    size_t m; 
    fscanf(dane, "%lu\n", &m);
    printf("|E| = %lu\n", m);

    // tworzymy pustą listę sąsiedztwa | n+1 bo wierzchołki indeksowane od 1 do n
    std::vector<size_t> adjList[n+1];

    /* wierzchołek początkowy/końcowy krawędzi */
    size_t vp, vk;
    while (EOF != fscanf(dane, "%lu %lu\n", &vp, &vk)){
        addEdge(adjList, vp, vk, typ[0]);
    }
    fclose(dane);

    printAdjList(adjList, n);
    bool printree;
    puts("Wypisywac drzewo bfs? (1 - tak | 0 - nie)");
    std::cin >> printree;
    size_t s;
    printf("Podaj liczbę naturalną od 1 do %zu\n", n);
    std::cin >> s;

    puts("");
    auto start_time = std::chrono::high_resolution_clock::now();
    dfs(adjList, n, s);
    if (printree){
        printDFStree(adjList, n);
    }
        auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    std::cout << "\nCzas działania programu: " <<  time/std::chrono::milliseconds(1) << "ms.\n";
    puts("");

    return EXIT_SUCCESS;
}
