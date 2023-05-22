#ifndef UNTITLED_BOT2_H
#define UNTITLED_BOT2_H

#include <time.h>
#include <climits>
#include "board.h"

#define ROWS_NUM 5

int calculatePoints(int counter) {
    switch (counter) {
        case 1:
            return 1;
        case 2:
            return 10;
        case 3:
            return 100;
        default:
            return 0;
    }
}

/*
Heuristic that go through every possible four fields in row -> counts how many
    current player's symbols it contains -> sum points for all of them 
    - 1 symbol in row -> +1 point
    - 2 symbols in row -> +10 points
    - 3 symbols in row -> +100 points
*/
int pointsSum(int player) {
    int points = 0;
    int counter = 0;

    // check all rows
    for (int i = 0; i < ROWS_NUM; ++i) {
        // check fields i1, i2, i3, i4
        for (int j = 0; j < ROWS_NUM-1; ++j) {
            if (board[i][j] == player)
                counter++;
            else if (board[i][j] == 3-player) {
                counter = 0;
                break;
            }
        }
        points += calculatePoints(counter);
        counter = 0;

        // check fields i2, i3, i4, i5
        for (int j = 1; j < ROWS_NUM; ++j) {
            if (board[i][j] == player)
                counter++;
            else if (board[i][j] == 3-player) {
                counter = 0;
                break;
            }
        }
        points += calculatePoints(counter);
        counter = 0;
    }

    // check all columns
    for (int j = 0; j < ROWS_NUM; ++j) {
        // check fields 1j, 2j, 3j, 4j
        for (int i = 0; i < ROWS_NUM-1; ++i) {
            if (board[i][j] == player)
                counter++;
            else if (board[i][j] == 3-player) {
                counter = 0;
                break;
            }
        }
        points += calculatePoints(counter);
        counter = 0;

        // check fields 2j, 3j, 4j, 5j
        for (int i = 1; i < ROWS_NUM; ++i) {
            if (board[i][j] == player)
                counter++;
            else if (board[i][j] == 3-player) {
                counter = 0;
                break;
            }
        }
        points += calculatePoints(counter);
        counter = 0;
    }

    // check diagonal fields 21, 32, 43, 54
    for (int i = 1, j = 0; i < ROWS_NUM; ++i, ++j) {
        if (board[i][j] == player)
            counter++;
        else if (board[i][j] == 3-player) {
            counter = 0;
            break;
        }
    }
    points += calculatePoints(counter);
    counter = 0;

    // check diagonal fields 12, 23, 34, 45
    for (int i = 0, j = 1; j < ROWS_NUM; ++i, ++j) {
        if (board[i][j] == player)
            counter++;
        else if (board[i][j] == 3-player) {
            counter = 0;
            break;
        }
    }
    points += calculatePoints(counter);
    counter = 0;

    // check diagonal fields 11, 22, 33, 44
    for (int i = 0; i < ROWS_NUM-1; ++i) {
        if (board[i][i] == player)
            counter++;
        else if (board[i][i] == 3-player) {
            counter = 0;
            break;
        }
    }
    points += calculatePoints(counter);
    counter = 0;

    // check diagonal fields 22, 33, 44, 55
    for (int i = 1; i < ROWS_NUM; ++i) {
        if (board[i][i] == player)
            counter++;
        else if (board[i][i] == 3-player) {
            counter = 0;
            break;
        }
    }
    points += calculatePoints(counter);
    counter = 0;

    // ------- MIRROR DIAGONALS -------

    // check diagonal fields 41, 32, 23, 14
    for (int i = 3, j = 0; i >= 0; --i, ++j) {
        if (board[i][j] == player)
            counter++;
        else if (board[i][j] == 3-player) {
            counter = 0;
            break;
        }
    }
    points += calculatePoints(counter);
    counter = 0;

    // check diagonal fields 52, 43, 34, 25
    for (int i = 4, j = 1; j < ROWS_NUM; --i, ++j) {
        if (board[i][j] == player)
            counter++;
        else if (board[i][j] == 3-player) {
            counter = 0;
            break;
        }
    }
    points += calculatePoints(counter);
    counter = 0;

    // check diagonal fields 51, 42, 33, 24
    for (int i = 4; i > 0 ; --i) {
        if (board[i][4-i] == player)
            counter++;
        else if (board[i][4-i] == 3-player) {
            counter = 0;
            break;
        }
    }
    points += calculatePoints(counter);
    counter = 0;

    // check diagonal fields 42, 33, 24, 15
    for (int i = 3; i >= 0; --i) {
        if (board[i][4-i] == player)
            counter++;
        else if (board[i][4-i] == 3-player) {
            counter = 0;
            break;
        }
    }
    points += calculatePoints(counter);

    return points;
}


/// @brief Heuristic that checks if opponent can win in next move if we don't block him
/// @param player number of current player 
/// @return
int blockOpponent(int player) {
    int points = 0;
    int counter = 0;

    // check all rows
    for (int i = 0; i < ROWS_NUM; ++i) {
        // check fields i1, i2, i3, i4
        for (int j = 0; j < ROWS_NUM-1; ++j) {
            if (board[i][j] == player) {
                counter = 0;
                break;
            }
            else if (board[i][j] == 3-player) {
                counter++;
            }
        }
        if (counter == 3)
            points-=1000;
        counter = 0;

        // check fields i2, i3, i4, i5
        for (int j = 1; j < ROWS_NUM; ++j) {
            if (board[i][j] == player)
                counter=0;
            else if (board[i][j] == 3-player) {
                counter++;
            }
        }
        if (counter == 3)
            points-=1000;
        counter = 0;
    }
    // check all columns
    for (int j = 0; j < ROWS_NUM; ++j) {
        // check fields 1j, 2j, 3j, 4j
        for (int i = 0; i < ROWS_NUM-1; ++i) {
            if (board[i][j] == player){
                counter=0;
                break;
            }
            else if (board[i][j] == 3-player) {
                counter++;
            }
        }
        if (counter == 3)
            points-=1000;
        counter = 0;

        // check fields 2j, 3j, 4j, 5j
        for (int i = 1; i < ROWS_NUM; ++i) {
            if (board[i][j] == player){
                counter=0;
                break;
            }
            else if (board[i][j] == 3-player) {
                counter++;
            }
        }
        if (counter == 3)
            points-=1000;
        counter = 0;
    }

    // check diagonal fields 21, 32, 43, 54
    for (int i = 1, j = 0; i < ROWS_NUM; ++i, ++j) {
        if (board[i][j] == player){
            counter=0;
            break;
        }
        else if (board[i][j] == 3-player) {
            counter++;
        }
    }
    if (counter == 3)
        points-=1000;
    counter = 0;

    // check diagonal fields 12, 23, 34, 45
    for (int i = 0, j = 1; j < ROWS_NUM; ++i, ++j) {
        if (board[i][j] == player){
            counter=0;
            break;
        }
        else if (board[i][j] == 3-player) {
            counter++;
        }
    }
    if (counter == 3)
        points-=1000;
    counter = 0;

    // check diagonal fields 11, 22, 33, 44
    for (int i = 0; i < ROWS_NUM-1; ++i) {
        if (board[i][i] == player){
            counter=0;
            break;
        }
        else if (board[i][i] == 3-player) {
            counter++;
        }
    }
    if (counter == 3)
        points-=1000;
    counter = 0;

    // check diagonal fields 22, 33, 44, 55
    for (int i = 1; i < ROWS_NUM; ++i) {
        if (board[i][i] == player){
            counter=0;
            break;
        }
        else if (board[i][i] == 3-player) {
            counter++;
        }
    }
    if (counter == 3)
        points-=1000;
    counter = 0;

    // ------- MIRROR DIAGONALS -------

    // check diagonal fields 41, 32, 23, 14
    for (int i = 3, j = 0; i >= 0; --i, ++j) {
        if (board[i][j] == player){
            counter=0;
            break;
        }
        else if (board[i][j] == 3-player) {
            counter++;
        }
    }
    if (counter == 3)
        points-=1000;
    counter = 0;

    // check diagonal fields 52, 43, 34, 25
    for (int i = 4, j = 1; j < ROWS_NUM; --i, ++j) {
        if (board[i][j] == player){
            counter=0;
            break;
        }
        else if (board[i][j] == 3-player) {
            counter++;
        }
    }
    if (counter == 3)
        points-=1000;
    counter = 0;

    // check diagonal fields 51, 42, 33, 24
    for (int i = 4; i > 0 ; --i) {
        if (board[i][4-i] == player){
            counter=0;
            break;
        }
        else if (board[i][4-i] == 3-player) {
            counter++;
        }
    }
    if (counter == 3)
        points-=1000;
    counter = 0;

    // check diagonal fields 42, 33, 24, 15
    for (int i = 3; i >= 0; --i) {
        if (board[i][4-i] == player){
            counter=0;
            break;
        }
        else if (board[i][4-i] == 3-player) {
            counter++;
        }
    }
    if (counter == 3)
        points-=1000;
    return points;
}

int evaluate(int player) {

    if (winCheck(player) || loseCheck(3-player))
        return INT_MAX;
    if (winCheck(3-player) || loseCheck(player))
        return INT_MIN;

    return pointsSum(player) - pointsSum(3-player) + blockOpponent(player);

}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

// This is the minimax function. It considers all
// the possible ways the game can go and returns
// the value of the board
int minimax(int player, int depth, int maxDepth, bool isMax, int alpha, int beta)
{

    if (depth == maxDepth || loseCheck(2) || winCheck(1) || loseCheck(1) || winCheck(2))
        return evaluate(player);

    // If this maximizer's move
    if (isMax)
    {
        int best = INT_MIN;
        // Traverse all cells

        for (int i = 0; i<ROWS_NUM; i++)
        {
            for (int j = 0; j<ROWS_NUM; j++)
            {
                // Check if cell is empty
                if (board[i][j] == 0)
                {
                    // Make the move
                    board[i][j] = player; // Maximizer = player 1 = 'X'

//                    // Standard minimax
//                    // Call minimax recursively and choose
//                    // the maximum value
//                    best = max( best,
//                                minimax(player, depth+1, maxDepth, !isMax, alpha, beta) );
////                    printBoard();
////                    printf("Depth: %d, Points: %d\n", depth, best);
//
//                    // Undo the move
//                    board[i][j] = 0;


                    // Alpha-Beta Pruning
                    int value = minimax(player, depth+1, maxDepth, !isMax, alpha, beta);
                    best = max(best, value);
                    alpha = max(alpha, best);

                    // Undo the move
                    board[i][j] = 0;

                    if (beta <= alpha) {
                        return best;
                    }
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
        int best = INT_MAX;

        // Traverse all cells
        for (int i = 0; i<ROWS_NUM; i++)
        {
            for (int j = 0; j<ROWS_NUM; j++)
            {
                // Check if cell is empty
                if (board[i][j]==0)
                {
                    // Make the move
                    board[i][j] = 3-player; // Minimaizer = player 2 = O


//                    // Standard minimax
//                    // Call minimax recursively and choose
//                    // the minimum value
//                    best = min(best,
//                               minimax(player, depth+1, maxDepth, !isMax, alpha, beta));
//
//                    // Undo the move
//                    board[i][j] = 0;


                    // Alpha-Beta Pruning
                    int value = minimax(player, depth+1, maxDepth, !isMax, alpha, beta);
                    best = min(best, value);
                    beta = min(beta, best);

                    // Undo the move
                    board[i][j] = 0;

                    if (beta <= alpha) {
                        return best;
                    }

                }
            }
        }
        return best;
    }
}

// This will return the best possible move for the player
int findBestMove(int maxDepth, int player)
{
    int bestMove;
    int bestVal = INT_MIN;
    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i<ROWS_NUM; i++)
    {
        for (int j = 0; j<ROWS_NUM; j++)
        {
            // Check if cell is empty
            if (board[i][j]== 0)
            {
                // Make the move
                board[i][j] = player;

                // compute evaluation function for this
                // move.
                int moveVal = minimax(player, 0, maxDepth, false, INT_MIN, INT_MAX);

                // Undo the move
                board[i][j] = 0;

                // If the value of the current move is
                // more than the best value, then update
                if (moveVal > bestVal)
                {
                    bestMove = 10 * (i+1) + (j+1);
                    bestVal = moveVal;
                }
                // if is equal to current best take it or not 
                else if (moveVal == bestVal) {
                    srand(time(NULL));
                    int r = rand() % 1000;
                    r%=2;
                    if (r) {
                        bestMove = 10 * (i+1) + (j+1);
                        bestVal = moveVal;
                    }
                }
            }
        }
    }
    // printf("\033[31mMAX: PICKED MOVE: %d\033[0m", bestVal);

    return bestMove;
}

#endif //UNTITLED_BOT2_H
