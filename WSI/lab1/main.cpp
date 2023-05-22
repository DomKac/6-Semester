#include <cstdlib>
#include <memory>

#include "lab1.h"

using namespace std;

int main() {
    uc puzzle[PUZZLE_SIZE] = {4,0,1,2,8,5,7,3,12,9,6,11,13,10,14, EMPTY};
//
    uc test_puzzles[10][PUZZLE_SIZE] = {
            {3, 13, 14, 8, 5, 7, 10, 2, 12, 4, 0, 11, 1, 6, 9, 255,},
            {2, 1, 9, 5, 7, 10, 6, 8, 12, 3, 13, 11, 14, 0, 4, 255,},
            {8, 14, 4, 7, 10, 6, 0, 5, 12, 2, 1, 11, 9, 13, 3, 255,},
            {5, 9, 3, 10, 6, 0, 13, 7, 12, 8, 14, 11, 4, 1, 2, 255,},
            {7, 4, 2, 6, 0, 13, 1, 10, 12, 5, 9, 11, 3, 14, 8, 255,},
            {10, 3, 8, 0, 13, 1, 14, 6, 12, 7, 4, 11, 2, 9, 5, 255,},
            {6, 2, 5, 13, 1, 14, 9, 0, 12, 10, 3, 11, 8, 4, 7, 255,},
            {0, 8, 7, 1, 14, 9, 4, 13, 12, 6, 2, 11, 5, 3, 10, 255,},
            {13, 5, 10, 14, 9, 4, 3, 1, 12, 0, 8, 11, 7, 2, 6, 255,},
            {1, 7, 6, 9, 4, 3, 2, 14, 12, 13, 5, 11, 10, 8, 0, 255,}
    };

    for (int i = 0; i < 10; ++i) {
//        permutatePuzzle(puzzle);
//        printBoard1D();
//        shared_ptr<Node> start(new Node(test_puzzles[i], 15, ultraManhattan(test_puzzles[i]), 0));
        shared_ptr<Node> start(new Node(test_puzzles[i], 15, manhattan(test_puzzles[i]), 0));
        AStar(start);
    }
//    printPuzzle16(puzzle);

//    printBoard1D(test_puzzles[1]);
    // Startowy node
//    shared_ptr<Node> start(new Node(puzzle, 15, ultraManhattan(puzzle), 0));
//    AStar(start);

    return EXIT_SUCCESS;
}
