#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "board.h"


class GameEngine
{
    int n;  // wymiar planszy
public:

    GameEngine(int n);
    // funkcja odpowiedzialna za wykonanie ruchu i sprawdzenie stanu planszy po tym ruchu
    int makeMove(int pozycja_x, int pozycja_y);

    // funkcja sprawdza czy ktos wygral
    int checkWinner(char** board);

    int playerTurn; // czyj jest aktualnie ruch
    Board* b1;      // plansza
private:

};

#endif // GAMEENGINE_H
