#ifndef LAB1_H
#define LAB1_H

#include <iostream>
#include <memory>
#include <queue>
#include <unistd.h>
#include <vector>

#define PUZZLE_ROWS 4
#define PUZZLE_SIZE 16
#define EMPTY 255
#define SWAPS_NUM 20

#define uc unsigned char 

#define swap(a, b) \
    (a = a^b),      \
    (b = a^b),      \
    (a = b^a)

#define manhattanDistance(value, index) \
    ((value > index) ? value - index : index - value)

typedef struct Node {
    uc board[PUZZLE_SIZE];  // stan planszy
    uc emptyIndex;          // pozycja pustego pola
    uc h{};                 // ocena heurystyczna
    uc depth{};             // ilość ruchów ze stanu początkowego do obecnego
    uc f{};                 // depth + h
    char movedBy{};         // Osiągnięty przez ruch z {U, D, L ,R}
    std::shared_ptr<Node> parent{};
    char pad[4]{};          // spadingowane bajty

    Node(uc puzzle[], uc emptyIndex, uc h, uc depth);
    Node(uc puzzle[], uc emptyIndex);

    [[nodiscard]] bool canEmptyUp     () const;
    [[nodiscard]] bool canEmptyDown   () const;
    [[nodiscard]] bool canEmptyRight  () const;
    [[nodiscard]] bool canEmptyLeft   () const;

    void emptyUp();
    void emptyDown();
    void emptyRight();
    void emptyLeft();

    void heuristic();
    void assignFGH(std::shared_ptr<Node>& p);

    void printAll();
    void printPath() const;
} Node;

Node* newNode(uc puzzle[], uc emptyIndex, uc h, uc depth);
void minHeuristicNode(const std::shared_ptr<Node>& start);

void printPuzzle16(const uc puzzle[]);
void copyBoard(const uc puzzle[], uc copy[]);

void permutatePuzzle(uc puzzle[]);
bool isPuzzleSolvable(const uc puzzle[]);

uc manhattan(uc puzzle[]);
uc ultraManhattan(uc puzzle[]);
uc taxiMetric(uc value, uc index);
uc linearConflicts(uc puzzle[]);

void emptyUp(uc puzzle[], uc emptyIndex);
void emptyDown(uc puzzle[], uc emptyIndex);
void emptyRight(uc puzzle[], uc emptyIndex);
void emptyLeft(uc puzzle[], uc emptyIndex);

Node::Node(uc puzzle[], uc emptyIndex, uc h, uc depth) {
    copyBoard(puzzle, Node::board);
    Node::emptyIndex = emptyIndex;
    Node::h = h;
    Node::depth = depth;
    Node::f = h + depth;
    Node::parent = nullptr;
}

Node::Node(uc puzzle[], uc emptyIndex) {
    copyBoard(puzzle, Node::board);
    Node::emptyIndex = emptyIndex;
    Node::parent = nullptr;
}

bool Node::canEmptyUp() const {
    return (this->emptyIndex >= PUZZLE_ROWS);
}

bool Node::canEmptyDown() const {
    return (this->emptyIndex < PUZZLE_SIZE - PUZZLE_ROWS);
}

bool Node::canEmptyRight() const {
    return (this->emptyIndex % PUZZLE_ROWS < 3);
}

bool Node::canEmptyLeft() const {
    return (this->emptyIndex % PUZZLE_ROWS > 0);
}

void Node::emptyUp() {
    swap(this->board[this->emptyIndex], this->board[this->emptyIndex - PUZZLE_ROWS]);
    this->emptyIndex -= PUZZLE_ROWS;
    this->movedBy = 'U';
}

void Node::emptyDown() {
    swap(this->board[this->emptyIndex], this->board[this->emptyIndex + PUZZLE_ROWS]);
    this->emptyIndex += PUZZLE_ROWS;
    this->movedBy = 'D';
}

void Node::emptyRight() {
    swap(this->board[this->emptyIndex], this->board[this->emptyIndex + 1]);
    this->emptyIndex++;
    this->movedBy = 'R';
}
void Node::emptyLeft() {
    swap(this->board[this->emptyIndex], this->board[this->emptyIndex - 1]);
    this->emptyIndex--;
    this->movedBy = 'L';
}

void Node::heuristic() {
//    uc h = 0;
//    for (size_t i = 0; i < PUZZLE_SIZE; i++) {
//        if (this->board[i] != EMPTY) {
//            h += taxiMetric(this->board[i], i);
//            // printf("manhattan distance for %hhu is %hhu\n", puzzle[i], taxiMetric(puzzle[i], i));
//        }
//    }
//    // h += linearConflicts(puzzle);
//    this->h = ultraManhattan(this->board);
    this->h = manhattan(this->board);
}

void Node::assignFGH(std::shared_ptr<Node>& p) {
    this->heuristic();  // assign h
    this->parent = p;
    this->depth = p->depth + 1;
    this->f = this->h + this->depth;
}

void Node::printAll() {
    switch (this->movedBy) {
        case 'U':
            puts("UpNode");
            break;
        case 'D':
            puts("DwonNode");
            break;
        case 'R':
            puts("RightNode");
            break;
        case 'L':
            puts("LeftNode");
            break;
        default:
            puts("Root");
    }
    printPuzzle16(this->board);
    printf("f = %hhu\n", this->f);
    printf("g = %hhu\n", this->depth);
    printf("h = %hhu\n\n", this->h);
}

void Node::printPath() const {
    std::shared_ptr<Node> temp;
    temp = this->parent;

    std::vector<char> v;
    v.push_back(this->movedBy);
    v.push_back(temp->movedBy);
    size_t pathLength = 1;

    while (temp->parent) {
        pathLength++;
        temp = temp->parent;
        v.push_back(temp->movedBy);
    }
    puts("RUCHY:");
    while (!v.empty()) {
        printf("%c ", v.back());
        v.pop_back();
    }
    printf("\nLiczba ruchów: %zu\n", pathLength);
}

/* ---------------------------------GENERATING BOARD---------------------------------------- */

void permutatePuzzle(uc puzzle[]) {
    srand(time(0));
    int index1;
    int index2;
    do {
        for (size_t i = 0; i < SWAPS_NUM; i++) {
            index1 = rand() % (PUZZLE_SIZE-1);
            index2 = rand() % (PUZZLE_SIZE-1);
            if (index1 - index2) {
                swap(puzzle[index1], puzzle[index2]);
            }
        }
    } while (!isPuzzleSolvable(puzzle));
}

bool isPuzzleSolvable(const uc puzzle[]) {
    int inversionCount = 0;
    for (size_t i = 0; i < PUZZLE_SIZE-1; i++) {
        for (size_t j = i+1; j < PUZZLE_SIZE; j++) {
            if (puzzle[j] < puzzle[i]) {
                inversionCount++;
            }
        }
    }
//    printf("solvable: %d\n", !(inversionCount%2));
    return !(inversionCount % 2);
}

/* ---------------------------------SOLVE PUZZLE---------------------------------------- */
// ok
struct CompareNodes {
    bool operator()(const std::shared_ptr<Node>& n1, const std::shared_ptr<Node>& n2) {
        return (n1->f > n2->f);
    }
};

void emptyQueue(std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareNodes>& Q, size_t& s) {
    std::vector<std::shared_ptr<Node>> v;

    for (int i = 0; i < 100000; ++i) {
        v.push_back(Q.top());
        Q.pop();
    }
    while (!Q.empty()) {
        Q.pop();
    }
    while (!v.empty()) {
        Q.push(v.back());
        v.pop_back();
    }
    s = Q.size();
}

void AStar(const std::shared_ptr<Node>& start) {
    size_t Qsize = 0;
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareNodes> Q;
    Q.push(start);
    std::shared_ptr<Node> temp;
    size_t visitedStates = 0;
    while (!Q.empty()) {
        temp = Q.top();
        visitedStates++;
        Q.pop();            // usuwamy go z kolejki
        if (Qsize > 10000000) {
            emptyQueue(Q,Qsize);
        }
//        puts("Obecna plansza: ");
//        temp->printAll();
        if (temp->h == 0) {// wszystkie puzzle na swoim miejscu to kończymy
//            printPuzzle16(temp->board);
            temp->printPath();
            printf("Liczba odwiedzonych stanów %zu\n", visitedStates);
            return;
        }
//        usleep(1000000);

        if (temp->canEmptyUp() && temp->movedBy != 'D') {
            std::shared_ptr<Node> UpNode(new Node(temp->board, temp->emptyIndex));
            UpNode->emptyUp();
            UpNode->assignFGH(temp);
            Q.push(UpNode);
            Qsize++;
//            UpNode->printAll();
        }
        if (temp->canEmptyDown() && temp->movedBy != 'U') {
            std::shared_ptr<Node> DownNode(new Node(temp->board, temp->emptyIndex));
            DownNode->emptyDown();
            DownNode->assignFGH(temp);
            Q.push(DownNode);
            Qsize++;
        }
        if (temp->canEmptyRight() && temp->movedBy != 'L') {
            std::shared_ptr<Node> RightNode(new Node(temp->board, temp->emptyIndex));
            RightNode->emptyRight();
            RightNode->assignFGH(temp);
            Q.push(RightNode);
            Qsize++;
        }
        if (temp->canEmptyLeft() && temp->movedBy != 'R') {
            std::shared_ptr<Node> LeftNode(new Node(temp->board, temp->emptyIndex));
            LeftNode->emptyLeft();
            LeftNode->assignFGH(temp);
            Q.push(LeftNode);
            Qsize++;
        }
    }
}

uc taxiMetric(uc value, uc index) {
    return abs(value/PUZZLE_ROWS - index/PUZZLE_ROWS) + abs(value%PUZZLE_ROWS - index%PUZZLE_ROWS);
}

uc linearConflicts(uc puzzle[]) {
    uc conflicts = 0;
    for (size_t c = 0; c < PUZZLE_ROWS; c++) {
        for (size_t r = 0; r < PUZZLE_SIZE; r+=PUZZLE_ROWS) {
            for (size_t i = r+PUZZLE_ROWS; i < PUZZLE_SIZE; i+=PUZZLE_ROWS) {
                if (puzzle[r+c]%PUZZLE_ROWS == puzzle[i+c]%PUZZLE_ROWS && puzzle[r+c] > puzzle[i+c]) {
                    conflicts+=2;
//                    printf("Konfilkt pionowy %hhu z %hhu\n", puzzle[r+c], puzzle[i+c]);
                }
            }
        }
    }

    for (size_t r = 0; r < PUZZLE_SIZE; r+=4) {
        for (size_t c = 0; c < PUZZLE_ROWS-1; c++) {
            for (size_t i = c+1; i < PUZZLE_ROWS; i++) {
                if (puzzle[r+c]/PUZZLE_ROWS == puzzle[r+i]/PUZZLE_ROWS && puzzle[r+c] > puzzle[r+i]) {
                    conflicts+=2;
//                    printf("Konfilkt poziomy %hhu z %hhu\n", puzzle[r+c], puzzle[r+i]);
                }
            }
        }
    }
    return conflicts;
}


uc manhattan(uc puzzle[]) {
    uc h = 0;
    for (size_t i = 0; i < PUZZLE_SIZE; i++) {
        if (puzzle[i] != EMPTY) {
            h += taxiMetric(puzzle[i], i);
            // printf("manhattan distance for %hhu is %hhu\n", puzzle[i], taxiMetric(puzzle[i], i));
        }
    }
    return h;
}

uc ultraManhattan(uc puzzle[]) {
    return manhattan(puzzle) + linearConflicts(puzzle);
}

/* ---------------------------------MOVES---------------------------------------- */



void emptyUp(uc puzzle[], uc emptyIndex) {
    swap(puzzle[emptyIndex], puzzle[emptyIndex - PUZZLE_ROWS]);
}

void emptyDown(uc puzzle[], uc emptyIndex) {
    swap(puzzle[emptyIndex], puzzle[emptyIndex + PUZZLE_ROWS]);
}

void emptyRight(uc puzzle[], uc emptyIndex) {
    swap(puzzle[emptyIndex], puzzle[emptyIndex + 1]);
}
void emptyLeft(uc puzzle[], uc emptyIndex) {
    swap(puzzle[emptyIndex], puzzle[emptyIndex - 1]);
}

/* ---------------------------------PRINT BOARD---------------------------------------- */

void printPuzzle16(const uc puzzle[]) {
    for(size_t i = 0; i < PUZZLE_ROWS; ++i) {
        printf("%hhu\t", puzzle[i]);
    }
    puts("");
    for(size_t i = PUZZLE_ROWS; i < 2*PUZZLE_ROWS; ++i) {
        printf("%hhu\t", puzzle[i]);
    }
    puts("");
    for(size_t i = 2*PUZZLE_ROWS; i < 3*PUZZLE_ROWS; ++i) {
        printf("%hhu\t", puzzle[i]);
    }
    puts("");
    for(size_t i = 3*PUZZLE_ROWS; i < 4*PUZZLE_ROWS; ++i) {
        printf("%hhu\t", puzzle[i]);
    }
    puts("");
}

void copyBoard(const uc puzzle[], uc copy[]) {
    for (int i = 0; i < PUZZLE_SIZE; ++i) {
        copy[i] = puzzle[i];
    }
}
void printBoard1D(uc puzzle[]) {
    for (size_t i = 0; i < PUZZLE_SIZE; ++i) {
        printf("%hhu, ", puzzle[i]);
    }
    puts("");
}

#endif
