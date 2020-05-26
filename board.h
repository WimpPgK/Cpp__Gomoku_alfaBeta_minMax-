#ifndef BOARD_H
#define BOARD_H


class Board
{
    int n;  // wymiar planszy

public:
    Board(int n);
    void printBoard();
    char** board;
};

#endif // BOARD_H
