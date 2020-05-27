#include "gameengine.h"
#include <iostream>
using namespace std;

GameEngine::GameEngine(int n)
{
    this->n = n;
    b1 = new Board(n);
    playerTurn = 1;
}


int GameEngine::makeMove(int pozycja_x, int pozycja_y)
{
    if(b1->board[pozycja_y][pozycja_x] == -1)
    {
        cout << 'a' - b1->board[pozycja_y][pozycja_x] << endl;
        if(playerTurn == 1)
        {
            b1->board[pozycja_y][pozycja_x] = 1;
            playerTurn = 2;
        }
        else
        {
            b1->board[pozycja_y][pozycja_x] = 2;
            playerTurn = 1;
        }
    }

    return checkWinner(b1->board);
}

int GameEngine::checkWinner(char** board)
{

        int pomGracz1 = 0;
        int pomGracz2 = 0;
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
                    pomGracz1++;
                }
                if (pomGracz1 >= 5)
                {
                    return 1;
                }
                if (b1->board[i][j] != 1)
                {
                    pomGracz1 = 0;
                }



                // sprawdzanie dla gracza 2
                if (b1->board[i][j] == 2)
                {
                    pomGracz2++;

                }
                if (pomGracz2 >= 5)
                {
                    return 2;
                }
                if (b1->board[i][j] != 2)
                {
                    pomGracz2 = 0;
                }
            }
            pomGracz1 = 0;
            pomGracz2 = 0;
        }


        /*
            sprawdzenie czy jest wygrany w pionie
        */
        pomGracz1 = 0;
        pomGracz2 = 0;
        for (int j = 0; j < n; j++)
        {
            for (int i = 0; i < n; i++)
            {
                // sprawdzanie dla gracza 1
                if (b1->board[i][j] == 1)
                {
                    pomGracz1++;
                }
                if (pomGracz1 >= 5)
                {
                    return 1;
                }
                if (b1->board[i][j] != 1)
                {
                    pomGracz1 = 0;
                }



                // sprawdzanie dla gracza 2
                if (b1->board[i][j] == 2)
                {
                    pomGracz2++;

                }
                if (pomGracz2 >= 5)
                {
                    return 2;
                }
                if (b1->board[i][j] != 2)
                {
                    pomGracz2 = 0;
                }
            }
            pomGracz1 = 0;
            pomGracz2 = 0;
        }

        /*
            sprawdzenie, czy jest wygrany po skosie "funkcja malejaca y = -x"
        */
        pomGracz1 = 0;
        pomGracz2 = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // dla gracza 1
                pomGracz1 = 0;
                pomGracz2 = 0;
                int pomX = 0;
                int pomY = 0;
                if (b1->board[i][j] == 1)
                {
                    pomX = j;
                    pomY = i;
                    while (pomY < n && pomX < n && b1->board[pomY][pomX] == 1)
                    {
                        pomGracz1++;
                        pomY++;
                        pomX++;
                        //cout <<"Gracz1 - pozycja "<< pomY << "  " << pomX << "  "<< pomGracz1 << endl;
                    }
                    //cout << endl << endl;
                    if (pomGracz1 >= 5)
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
                        pomGracz2++;
                        pomY++;
                        pomX++;

                    }
                    if (pomGracz2 >= 5)
                    {
                        return 2;
                    }
                }
            }
            pomGracz1 = 0;
            pomGracz2 = 0;
        }


        /*
            sprawdzenie, czy jest wygrany po skosie "funkcja rosnaca y = x"
        */
        pomGracz1 = 0;
        pomGracz2 = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // dla gracza 1
                pomGracz1 = 0;
                pomGracz2 = 0;
                int pomX = 0;
                int pomY = 0;
                if (b1->board[i][j] == 1)
                {
                    pomX = j;
                    pomY = i;
                    while (pomY < n && pomX >= 0 && b1->board[pomY][pomX] == 1)
                    {
                        pomGracz1++;
                        pomY++;
                        pomX--;
                    }
                    if (pomGracz1 >= 5)
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
                    while (pomY < n && pomX >= 0 < n && b1->board[pomY][pomX] == 2)
                    {
                        pomGracz2++;
                        pomY++;
                        pomX--;

                    }
                    if (pomGracz2 >= 5)
                    {
                        return 2;
                    }
                }
            }
            pomGracz1 = 0;
            pomGracz2 = 0;
        }


        /*

          sprawdzenie czy plansza jest pelna - czyli remis

        */
        bool planszaPelna = true;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (b1->board[i][j] == -1)
                    {
                        planszaPelna = false;
                        break;
                    }
                }
                if (planszaPelna == false)
                {
                    break;
                }
            }

            if(planszaPelna == true)
            {
                return 0;
            }


        return -1;
}
