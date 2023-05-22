#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <queue>
#include <chrono>
#include <iostream>

void addEdge(std::vector<int> v[], int vp, int vk, char type) {
    v[vp].push_back(vk);
    if (type == 'U')
        v[vk].push_back(vp);
}

void printAdjList(std::vector<int> v[], int n) {
    for (int i = 1; i < n+1; i++) {
        printf("%d | ", i);
        for (auto & node : v[i]) {
            printf("%d ", node);
        }
        puts("");
    }
}

#define UNVISITED -1

std::vector<int> vColor;
std::queue<int> fifo;

bool bfs(std::vector<int> v[], size_t n, size_t s) {

    vColor[s] = 0;
    fifo.push(s);

    size_t u; 
    while (!fifo.empty()) {
        u = fifo.front();
        fifo.pop();
        for (auto & node : v[u]) {
            if (vColor[node] == UNVISITED) {
                // jeśli trafiliśmy na wierzchołek pierwszy raz to ustawiamy mu kolor przeciwny do poprzednika
                vColor[node] = 1 - vColor[u];
                fifo.push(node);
            }
            else if (vColor[node] == vColor[u]){
                // trafiliśmy już wcześniej na ten wierchołek i ma ten sam kolor co wierzchołek u
                return false;
            }
        }
    }
    return true;
}

std::vector<int>* V = new std::vector<int>[2];

bool printbfs(std::vector<int> v[], size_t n, size_t s) {

    vColor[s] = 0;
    fifo.push(s);
    V[0].push_back(s);
    size_t u; 
    while (!fifo.empty()) {
        u = fifo.front();
        fifo.pop();
        for (auto & node : v[u]) {
            if (vColor[node] == UNVISITED) {
                // jeśli trafiliśmy na wierzchołek pierwszy raz to ustawiamy mu kolor przeciwny do poprzednika
                vColor[node] = 1 - vColor[u];
                fifo.push(node);
                V[1 - vColor[u]].push_back(node);
            }
            else if (vColor[node] == vColor[u]){
                // trafiliśmy już wcześniej na ten wierchołek i ma ten sam kolor co wierzchołek u
                return false;
            }
        }
    }
    return true;
}

// O(|V| + |E|)
bool isBipartite(std::vector<int> v[], int n) {
    vColor.resize(n+1, UNVISITED);
    if (n <= 200) {
        for (int i = 1; i <= n; i++) {
            if (vColor[i] == UNVISITED){
                if (!printbfs(v,n,i))
                    return false;
            }
        }
        puts("Wierzcholki nalezace do V0:");
        for (int i = 0; i < (int)V[0].size(); i++){
            printf("%d ", V[0][i]);
        }
        puts("\nWierzcholki nalezace do V1:");
        for (int i = 0; i < (int)V[1].size() ; i++){
            printf("%d ", V[1][i]);
        }
        puts("");
    }
    
    for (int i = 1; i <= n; i++) {
        if (vColor[i] == UNVISITED){
            if (!bfs(v,n,i))
                return false;
        }
    }
    return true;
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
    int n;
    fscanf(dane, "%d\n", &n);
    printf("|V| = %d\n", n);

    /* liczba krawędzi |E| */
    int m; 
    fscanf(dane, "%d\n", &m);
    printf("|E| = %d\n", m);

    // tworzymy pustą listę sąsiedztwa | n+1 bo wierzchołki indeksowane od 1 do n
    std::vector<int>* adjList = new std::vector<int>[n+1];

    /* wierzchołek początkowy/końcowy krawędzi */
    int vp, vk;
    while (EOF != fscanf(dane, "%d %d\n", &vp, &vk)){
        addEdge(adjList, vp, vk, typ[0]);
    }
    fclose(dane);
    // printAdjList(adjList, n);
    puts("");

    auto start_time = std::chrono::high_resolution_clock::now();
    if (isBipartite(adjList,n))
        puts("Dwudzielny!!!");
    else
        puts("NIE jest dwudzielny!");
    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    std::cout << "\nCzas działania programu: " <<  time/std::chrono::milliseconds(1) << "ms.\n";
    puts("");


    delete[] adjList;
    adjList = NULL;  
    delete[] V;
    V = NULL;

    return EXIT_SUCCESS;
}
