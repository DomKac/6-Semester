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

std::vector<char> vColor; // B - biały | S - szary | C - czarny 
std::list<int> topSort;
bool is_dag = true;

void dfs(std::vector<int> v[], int n, int s) {

    vColor[s] = 'S';
    for (auto & node : v[s]) {
            if (vColor[node] == 'B')
                dfs(v, n, node);
            else if (vColor[node] == 'S'){
                is_dag = false;
            }
    }
    vColor[s] = 'C';
    topSort.push_front(s);
}

void topologicalSort(std::vector<int> v[], int n) {
    
    vColor.resize(n+1, 'B');
    for (int i = 1; i <= n; i++) {    
        if (vColor[i] == 'B')
            dfs(v,n,i);
    }
    
}

void printTopSort() {
    puts("Wierzchołki w porządku topologicznym: ");
    // printf("Rozmiar topSorta %zu\n", topSort.size());
    for (auto & node : topSort)
       printf("%d ", node);
    puts("");
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
    topologicalSort(adjList, n);
    if (is_dag){
        puts("Graf acykliczny! (DAG)");
        if (n <= 200)
            printTopSort();
    }
    else
        puts("Graf cykliczny!");

    auto end_time = std::chrono::high_resolution_clock::now();
    auto time = end_time - start_time;
    std::cout << "\nCzas działania programu: " <<  time/std::chrono::milliseconds(1) << "ms.\n";
    puts("");  

    delete[] adjList;
    adjList = NULL;  

    return EXIT_SUCCESS;
}
