#include "board.h"
#include <iostream>

using namespace std;

Board::Board(int n)
{
    this->n = n;
    board = new char* [n];
    for (int i = 0; i < n; i++)
    {
        board[i] = new char[n];
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j] = -1;
        }
    }
}

void Board::printBoard()
{
    for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (board[i][j] == -1)
                {
                    cout << "-" << "   ";
                }
                else
                {
                    cout << board[i][j] << "   ";
                }
            }
            cout << endl;
        }
}
