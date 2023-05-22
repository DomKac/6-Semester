#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <list>
#include <queue>
#include <chrono>
#include <iostream>

#define UNVISITED -1
#define MAX_SIZE 1000012

void addEdge(std::vector<int> *v, int vp, int vk, char type)
{
    v[vp].push_back(vk);
    if (type == 'U')
        v[vk].push_back(vp);
}

void printAdjList(std::vector<int> *v, size_t n)
{
    for (size_t i = 1; i < n + 1; i++)
    {
        printf("%lu | ", i);
        for (auto &node : v[i])
        {
            printf("%d ", node);
        }
        puts("");
    }
}

int t = 0;       
int sscCount = 0; 

std::vector<int> disc;      // size n
std::vector<int> low;      // size n
std::vector<bool> onStack; // size n
std::vector<int> stack;
// int *low = new int[MAX_SIZE];
// int *disc = new int[MAX_SIZE];
// int *stack = new int[MAX_SIZE];
// bool *onStack = new bool[MAX_SIZE];


void dfs(std::vector<int>* v, int n, int i);

void ssc(std::vector<int>* v, int n)
{
    disc.resize(n + 1, UNVISITED);
    low.resize(n + 1, 0);
    onStack.resize(n + 1, false);
    // for (size_t i = 0; i < MAX_SIZE; i++)
    // {
    //     disc[i] = UNVISITED;
    //     low[i] = 0;
    //     onStack[i] = false;
    // }
    
    for (int i = 1; i <= n; i++) {
        if (disc[i] == UNVISITED) {
            dfs(v, n, i);
        }
    }
    printf("\nIlosc silnie spojnych skladowych wynosi: %d\n", sscCount);
}

size_t last = -1;

void dfs(std::vector<int>* v, int n, int at)
{
    stack.push_back(at);
    // stack[last] = at;
    // last++;
    onStack[at] = true;
    disc[at] = low[at] = t++;

    for (auto &to : v[at])
    {
        if (disc[to] == UNVISITED)
            dfs(v, n, to);
        if (onStack[to])
            low[at] = (low[at] < low[to]) ? low[at] : low[to];
    }
    if (disc[at] == low[at])
    {
        
        printf("Silnie spójna składowa: %d\n", sscCount+1);
        size_t count = 0;
        while (!stack.empty())
        // while (last != 0)
        {
            count++;
            int node = stack.back();
            // int node = stack[last];
            stack.pop_back();
            // last--;
            onStack[node] = false;
            low[node] = disc[at];
            if (n <= 200)
                printf("%d ", node);
            if (node == at)
                break;
        }
        printf("\nLiczba wierzchołków: %zu\n\n", count);
        count = 0;
        sscCount++;
    }
}

int main(int argc, char **argv)
{
    FILE *dane;
    dane = fopen(argv[1], "r");

    if (argc != 2)
    {
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
    std::vector<int> *adjList = new std::vector<int>[n + 1];
    /* wierzchołek początkowy/końcowy krawędzi */
    int vp, vk;
    while (EOF != fscanf(dane, "%d %d\n", &vp, &vk)) {
        addEdge(adjList, vp, vk, typ[0]);
    }
    fclose(dane);

    // printAdjList(adjList,n);
    auto start_time = std::chrono::high_resolution_clock::now();
    ssc(adjList, n);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto program_time = end_time - start_time;
    std::cout << "\nCzas działania programu: " <<  program_time/std::chrono::milliseconds(1) << "ms.\n";
    puts("");
    delete[] adjList;
    adjList = NULL;
    return EXIT_SUCCESS;
}
