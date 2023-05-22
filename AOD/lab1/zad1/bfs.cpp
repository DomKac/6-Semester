#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <queue>
#include <chrono>
#include <iostream>

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

void bfs(std::vector<size_t> v[], size_t n, size_t s, bool printtree) {

    // lista w której będziemy trzymać informacje ktore wierzchołki odwiedziliśmy
    std::vector<bool> visited;
    visited.resize(n+1, false);
    visited[s] = true;
    // stos/kolejka wierzchołków do zbadania
    std::queue<size_t> fifo;
    fifo.push(s);
    // lista rodziców i poziomów wierzchołków dla drzewa BFS
    std::vector<int> parent;
    parent.resize(n+1, 0);
    std::vector<size_t> level;
    level.resize(n+1, 0);

    size_t u; 
    while (!fifo.empty()) {
        u = fifo.front();
        fifo.pop();
        printf("%zu ", u);
        // wzięliśmy pierwszy element ze stosu i przechodzimy po jego sąsiadach
        for (auto & node : v[u]) {
            // jeżeli wierzchołek był wcześniej odwiedzony pomijamy go,
            // w przeciwnym wypadku wrzucamy go na stos/kolejkę
            if (!visited[node]) {
                visited[node] = true;
                fifo.push(node);
                // ustawiamy wierzchołek u jako rodzica i zwiększamy poziom
                parent[node] = u;
                level[node] = level[u] + 1;
            }            
        }
    }
    puts(""); 

    if(printtree) {
        // wypisujemy drzewo BFS
        printf("BFS tree:\n");
        for (size_t i = 1; i <= n; i++) {
            printf("Vertex %zu, parent: %d, level: %zu\n", i, parent[i], level[i]);
        }
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

    printAdjList(adjList, n);
    puts("");
    
    bool printree;
    puts("Wypisywac drzewo bfs? (1 - tak | 0 - nie)");
    std::cin >> printree;
    size_t s;
    printf("Podaj liczbę naturalną od 1 do %zu\n", n);
    std::cin >> s;

    auto start_time = std::chrono::high_resolution_clock::now();
    bfs(adjList, n, s, printree);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    std::cout << "\nCzas działania programu: " <<  time/std::chrono::milliseconds(1) << "ms.\n";
    puts("");

    fclose(dane);

    return EXIT_SUCCESS;
}
