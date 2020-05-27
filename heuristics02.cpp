#include "heuristics02.h"
#include <windows.h>

#include <iostream>
using namespace std;

Heuristics02::Heuristics02(int n, int ai, int opponent, GameEngine* g1)
{
    this->n = n;
    this->ai = ai;
    this->opponent = opponent;
    this->g1 = g1;
}

int Heuristics02::startSearching(char** tab)
{
    int pomValue= evaluationBoardState(tab, 0);
    cout << "Oszacowana wartosc planszy to " << pomValue << endl;
    int** scoreTab = new int*[n];
    for(int i = 0 ; i < n ; i++)
        scoreTab[i] = new int[n];

    int bestScore = INT_MIN;
    int bestScorePosition_x = -1;
    int bestScorePosition_y = -1;
    int numberOfBranch = 0;

    for (int i = 0;  i < n; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            // Is the spot available?
            int neighbours = checkNeighbours(tab, j, i);
            //cout << "Liczba sasiadow to "<< neighbours << " dla " << i << " " << j <<endl;
            if (tab[i][j] == -1 && neighbours != 0)
            {
                numberOfBranch++;
                tab[i][j] = ai;
                int score = minMax(tab, 0, false);
                tab[i][j] = -1;

                scoreTab[i][j] = score;
                if (score > bestScore)
                {

                    bestScore = score;
                    bestScorePosition_x = j;
                    bestScorePosition_y = i;
                }
                //cout << "Sprawdzona pozycja " << i << " " << j << endl;
            }
            else
            {
                scoreTab[i][j] = 0;
            }

        }
    }
    if(numberOfBranch == 0)
    {
        bestScorePosition_x = n/2;
        bestScorePosition_y = n/2;
    }
    cout << "Najlepsza pozycja to wiersz " << bestScorePosition_y <<  " i kolumna " << bestScorePosition_x << endl;
    printScoreTab(scoreTab);
    //printGameTab(tab);

    return g1->makeMove(bestScorePosition_x, bestScorePosition_y);

}

int Heuristics02::checkWinner(char** tab, int depth)
{
    int winner = g1->checkWinner(tab);
    if(winner == ai)
    {
        return 10000 - depth;
    }
    else if(winner == opponent)
    {
        return -10000 + depth;
    }
    return 0;
}

int Heuristics02::evaluationBoardState(char** tab, int depth)
{
    int liczbaCiagowPoczwornychAi;
    int liczbaCiagowPotrojnychAi;
    int liczbaCiagowPodwojnychAi;
    int liczbaCiagowPoczwornychOpponent;
    int liczbaCiagowPotrojnychOpponent;
    int liczbaCiagowPodwojnychOpponent;

    int value = checkWinner(tab,depth);
    if(value != 0)
    {
        return value;
    }


    liczbaCiagowPoczwornychAi = checkPair(tab, 4, ai);
    liczbaCiagowPotrojnychAi = checkPair(tab, 3, ai);
    liczbaCiagowPodwojnychAi = checkPair(tab, 2 , ai);

    liczbaCiagowPoczwornychOpponent = checkPair(tab, 4, opponent);
    liczbaCiagowPotrojnychOpponent = checkPair(tab, 3, opponent);
    liczbaCiagowPodwojnychOpponent = checkPair(tab, 2 , opponent);



    //cout << "AI:   n4 = " << liczbaCiagowPoczwornychAi << "     n3 = " << liczbaCiagowPotrojnychAi << "      n2 = "<< liczbaCiagowPodwojnychAi << endl;

    int evaluatedValueAI = 100*liczbaCiagowPoczwornychAi+ 10*liczbaCiagowPotrojnychAi +  liczbaCiagowPodwojnychAi;
    int evaluatedValueOpponent = 100*liczbaCiagowPoczwornychOpponent+ 10*liczbaCiagowPotrojnychOpponent +  liczbaCiagowPodwojnychOpponent;
    //void evaluation()
    return evaluatedValueAI - evaluatedValueOpponent;
}



int Heuristics02::checkPair(char** tab, int a, int player)
{

    /*
        algorytm szuka 3 elementow obok siebie
    */
    int pomGracz = 0;
    int numberOfElements = 0;


    /*
        sprawdzanie czy jest wygrany w poziomie
    */
    for (int i = 1; i < n -1; i++)
    {

        for (int j = 1; j < n -1; j++)
        {

            /*
                zliczamy ile jest zetonow gracza w poziomie pod rzad
            */
            if (tab[i][j] == player)
            {
                pomGracz++;
            }
            if (pomGracz >= a)
            {
                if(tab[i][j+1] == -1 && tab[i][j-a] == -1)
                {
                    numberOfElements++;
                }
                else
                {
                    pomGracz = 0;
                }

            }
            if (tab[i][j] != player)
            {
                pomGracz = 0;
            }
         }
         pomGracz = 0;
    }


    /*
        sprawdzenie czy jest wygrany w pionie
    */
    pomGracz = 0;
    for (int j = 1; j < n -1; j++)
    {
        for (int i = 1; i < n-1; i++)
        {
            // sprawdzanie dla gracza 1
            if (tab[i][j] == player)
            {
                pomGracz++;
            }
            if (pomGracz >= a)
            {
                if(tab[i+1][j] == -1 && tab[i-a][j] == -1)
                {
                    numberOfElements++;
                }
                else
                {
                    pomGracz = 0;
                }
            }
            if (tab[i][j] != player)
            {
                pomGracz = 0;
            }
        }
        pomGracz = 0;
    }

    /*
        sprawdzenie, czy jest wygrany po skosie "funkcja malejaca y = -x"
    */
    pomGracz = 0;
    for (int i = 1; i < n -1; i++)
    {
        for (int j = 1; j < n -1; j++)
        {
            // dla gracza 1
            pomGracz = 0;
            int pomX = 0;
            int pomY = 0;
            if (tab[i][j] == player)
            {
                pomX = j;
                pomY = i;
                while (pomY < n -1 && pomX < n -1 && tab[pomY][pomX] == player)
                {
                    pomGracz++;
                    pomY++;
                    pomX++;
                    //cout <<"Gracz1 - pozycja "<< pomY << "  " << pomX << "  "<< pomGracz1 << endl;
                }
                //cout << endl << endl;
                if (pomGracz >= a)
                {
                    if(tab[pomY][pomX] == -1 && tab[pomY-(a+1)][pomX-(a+1)] == -1)
                    {
                        numberOfElements++;
                    }
                    else
                    {
                        pomGracz = 0;
                    }

                }
            }
        }
        pomGracz = 0;
    }


    /*
        sprawdzenie, czy jest wygrany po skosie "funkcja rosnaca y = x"
    */
    pomGracz = 0;
    for (int i = 1; i < n -1; i++)
    {
        for (int j = 1; j < n -1; j++)
        {
            // dla gracza 1
            pomGracz = 0;
            int pomX = 0;
            int pomY = 0;
            if (tab[i][j] == player)
            {
                pomX = j;
                pomY = i;
                while (pomY < n-1 && pomX > 0 && tab[pomY][pomX] == player)
                {
                    pomGracz++;
                    pomY++;
                    pomX--;
                }
                if (pomGracz >= a)
                {
                    if(tab[pomY][pomX] == -1 && tab[pomY-(a+1)][pomX+(a+1)] == -1)
                    {
                        numberOfElements++;
                    }
                    else
                    {
                        pomGracz = 0;
                    }
                }
            }
        }
        pomGracz = 0;
    }
    return numberOfElements;
}


int Heuristics02::minMax(char** tab, int depth, bool isMaximizing)
{
    /*
        Jesli osiagnieta maksymalna glebokosc
    */
    if(depth == 3)
    {
        //cout  << evaluationBoardState(tab, depth) << endl;
        return evaluationBoardState(tab, depth);

    }


    int value = checkWinner(tab,depth);
    if(value != 0)
    {
        return value;
    }


    /*
            maksymalizujemy wartosc dla naszego ruchu
    */
    if (isMaximizing)
    {
        int bestScore = INT_MIN;
        for (int i = 0; i < n; i++)
        {
            for(int j = 0 ; j < n ; j++)
            {
                // Is the spot available and have neighbours?
                int neighbours = checkNeighbours(tab, j, i);
                if (tab[i][j] == -1 && neighbours != 0)
                {
                    tab[i][j] = ai;
                    int score = evaluationBoardState(tab, depth);
                    minMax(tab, depth + 1, false);
                    tab[i][j] = -1;
                    if(score > bestScore)
                    {
                        //cout << score << endl;
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
    /*
         gdy jest ruch przeciwnika to szukamy najmniejszej wartości
    */
    else
    {
        int bestScore = INT_MAX;
        for (int i = 0; i < n; i++)
        {

            for(int j = 0 ; j < n ; j++)
            {
                // Is the spot available and have neighbours?
                int neighbours = checkNeighbours(tab, j, i);
                if (tab[i][j] == -1 && neighbours != 0)
                {
                    tab[i][j] = opponent;
                    int score = evaluationBoardState(tab, depth);
                    minMax(tab, depth + 1, true);
                    tab[i][j] = -1;
                    if(score < bestScore)
                    {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
}

int Heuristics02::checkNeighbours(char **tab, int position_x, int position_y)
{
    int licznik = 0;
    if(position_x == 0)
        position_x += 1;
    if(position_x == n-1)
        position_x -= 1;
    if(position_y == 0)
        position_y += 1;
    if(position_y == n-1)
        position_y -= 1;


    for(int i = position_x - 1; i <= position_x + 1 ; i++)
    {
        for(int j = position_y - 1; j <= position_y + 1 ; j++)
        {
            if(i == position_x && j == position_y)
            {
                continue;
            }
            if(tab[j][i] != -1)
            {
                licznik++;
            }
        }
    }

    return licznik;

}

void Heuristics02::printScoreTab(int** tab)
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << +tab[i][j] << "   ";
        }

        cout << endl;
    }
}

void Heuristics02::printGameTab(char** tab)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << +tab[i][j] << "   ";
        }

        cout << endl;
    }
}
