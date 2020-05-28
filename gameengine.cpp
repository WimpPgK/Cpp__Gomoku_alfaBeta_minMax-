#include "gameengine.h"
#include <iostream>
using namespace std;

GameEngine::GameEngine(int n)
{
    this->n = n;
    b1 = new Board(n);
    playerTurn = 1;
}


int GameEngine::makeMove(int position_x, int position_y)
{
    if(b1->board[position_y][position_x] == -1)
    {
        if(playerTurn == 1)
        {
            b1->board[position_y][position_x] = 1;
            playerTurn = 2;
        }
        else
        {
            b1->board[position_y][position_x] = 2;
            playerTurn = 1;
        }
    }

    return checkWinner(b1->board);
}

int GameEngine::checkWinner(char** board)
{

        int pomPlayer1 = 0;
        int pomPlayer2 = 0;
        /*
            sprawdzanie czy jest wygrany w poziomie
        */
        for (int i = 0; i < n; i++)
        {

            for (int j = 0; j < n; j++)
            {

                /*
                    zliczamy ile jest zetonow gracza w poziomie pod rzad
                */


                // sprawdzanie dla gracza 1
                if (b1->board[i][j] == 1)
                {
                    pomPlayer1++;
                }
                if (pomPlayer1 >= 5)
                {
                    return 1;
                }
                if (b1->board[i][j] != 1)
                {
                    pomPlayer1 = 0;
                }



                // sprawdzanie dla gracza 2
                if (b1->board[i][j] == 2)
                {
                    pomPlayer2++;

                }
                if (pomPlayer2 >= 5)
                {
                    return 2;
                }
                if (b1->board[i][j] != 2)
                {
                    pomPlayer2 = 0;
                }
            }
            pomPlayer1 = 0;
            pomPlayer2 = 0;
        }


        /*
            sprawdzenie czy jest wygrany w pionie
        */
        pomPlayer1 = 0;
        pomPlayer2 = 0;
        for (int j = 0; j < n; j++)
        {
            for (int i = 0; i < n; i++)
            {
                // sprawdzanie dla gracza 1
                if (b1->board[i][j] == 1)
                {
                    pomPlayer1++;
                }
                if (pomPlayer1 >= 5)
                {
                    return 1;
                }
                if (b1->board[i][j] != 1)
                {
                    pomPlayer1 = 0;
                }



                // sprawdzanie dla gracza 2
                if (b1->board[i][j] == 2)
                {
                    pomPlayer2++;

                }
                if (pomPlayer2 >= 5)
                {
                    return 2;
                }
                if (b1->board[i][j] != 2)
                {
                    pomPlayer2 = 0;
                }
            }
            pomPlayer1 = 0;
            pomPlayer2 = 0;
        }

        /*
            sprawdzenie, czy jest wygrany po skosie "funkcja malejaca y = -x"
        */
        pomPlayer1 = 0;
        pomPlayer2 = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // dla gracza 1
                pomPlayer1 = 0;
                pomPlayer2 = 0;
                int pomX = 0;
                int pomY = 0;
                if (b1->board[i][j] == 1)
                {
                    pomX = j;
                    pomY = i;
                    while (pomY < n && pomX < n && b1->board[pomY][pomX] == 1)
                    {
                        pomPlayer1++;
                        pomY++;
                        pomX++;
                        //cout <<"Gracz1 - pozycja "<< pomY << "  " << pomX << "  "<< pomGracz1 << endl;
                    }
                    //cout << endl << endl;
                    if (pomPlayer1 >= 5)
                    {
                        return 1;
                    }
                }

                // dla gracza 2
                pomX = 0;
                pomY = 0;
                if (b1->board[i][j] == 2)
                {
                    pomX = j;
                    pomY = i;
                    while (pomY < n && pomX < n && b1->board[pomY][pomX] == 2 )
                    {
                        pomPlayer2++;
                        pomY++;
                        pomX++;

                    }
                    if (pomPlayer2 >= 5)
                    {
                        return 2;
                    }
                }
            }
            pomPlayer1 = 0;
            pomPlayer2 = 0;
        }


        /*
            sprawdzenie, czy jest wygrany po skosie "funkcja rosnaca y = x"
        */
        pomPlayer1 = 0;
        pomPlayer2 = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // dla gracza 1
                pomPlayer1 = 0;
                pomPlayer2 = 0;
                int pomX = 0;
                int pomY = 0;
                if (b1->board[i][j] == 1)
                {
                    pomX = j;
                    pomY = i;
                    while (pomY < n && pomX >= 0 && b1->board[pomY][pomX] == 1)
                    {
                        pomPlayer1++;
                        pomY++;
                        pomX--;
                    }
                    if (pomPlayer1 >= 5)
                    {
                        return 1;
                    }
                }

                // dla gracza 2
                pomX = 0;
                pomY = 0;
                if (b1->board[i][j] == 2)
                {
                    pomX = j;
                    pomY = i;
                    while (pomY < n && pomX >= 0 && b1->board[pomY][pomX] == 2)
                    {
                        pomPlayer2++;
                        pomY++;
                        pomX--;

                    }
                    if (pomPlayer2 >= 5)
                    {
                        return 2;
                    }
                }
            }
            pomPlayer1 = 0;
            pomPlayer2 = 0;
        }


        /*
          sprawdzenie czy plansza jest pelna - czyli remis
        */
        bool boardIsFull = true;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (b1->board[i][j] == -1)
                    {
                        boardIsFull  = false;
                        break;
                    }
                }
                if (boardIsFull  == false)
                {
                    break;
                }
            }

            if(boardIsFull  == true)
            {
                return 0;
            }
        return -1;
}
