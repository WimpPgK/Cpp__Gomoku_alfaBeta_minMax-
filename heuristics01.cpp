#include "heuristics01.h"
#include <windows.h>

#include <iostream>
using namespace std;

Heuristics01::Heuristics01(int n, int ai, int opponent, GameEngine* g1)
{
    this->n = n;
    this->ai = ai;
    this->opponent = opponent;
    this->g1 = g1;
}

int Heuristics01::startSearching(char** tab)
{
    int** scoreTab = new int*[n];
    for(int i = 0 ; i < n ; i++)
        scoreTab[i] = new int[n];

    int bestScore = INT_MIN;
    int bestScorePosition_x = -1;
    int bestScorePosition_y = -1;

    for (int i = 0;  i < n; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            // Is the spot available?
            if (tab[i][j] == -1)
            {

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
                cout << "Sprawdzona pozycja " << i << " " << j << endl;
            }
            else
            {
                scoreTab[i][j] = 0;
            }

        }
    }
    cout << "Najlepsza pozycja to wiersz " << bestScorePosition_y <<  " i kolumna " << bestScorePosition_x << endl;
    printScoreTab(scoreTab);

    return g1->makeMove(bestScorePosition_x, bestScorePosition_y);

}

int Heuristics01::minMax(char** tab, int depth, bool isMaximizing)
{
    /*
        Jesli osiagnieta maksymalna glebokosc
    */
    if(depth == 4)
    {
        return 10;
    }

    int result = g1->checkWinner(tab);
    /*
     * -1 gdy gra sie nie rozstrzyga
     * 0 gdy jest remis
     * 1 gdy wygrywa gracz 1
     * 2 gdyb wygrywa gracz 2
    */
    int pom;
    if (result != -1)
    {
        if (result == ai)
        {
            pom  = 100;
            pom -= depth;
            return pom;
        }

        if(result == opponent)
        {
            pom  = -100;
            pom -= depth;
            return pom;
        }
        if(result == 0)
        {
            return 0;
        }
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
                // Is the spot available?
                if (tab[i][j] == -1)
                {
                    tab[i][j] = ai;
                    int score;
                    score = minMax(tab, depth + 1, false);
                    tab[i][j] = -1;
                    if(score > bestScore)
                    {
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
                // Is the spot available?
                if (tab[i][j] == -1)
                {
                    tab[i][j] = opponent;
                    int score = minMax(tab, depth + 1, true);
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

void Heuristics01::printScoreTab(int** tab)
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


