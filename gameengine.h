#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "board.h"


class GameEngine
{
    int n;



public:
    GameEngine(int n);
    int makeMove(int pozycja_x, int pozycja_y);
    int checkWinner(char** board);
    int playerTurn;

    Board* b1;
private:

};

#endif // GAMEENGINE_H
