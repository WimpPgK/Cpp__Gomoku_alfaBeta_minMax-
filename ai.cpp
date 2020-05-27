#include "ai.h"
#include <windows.h>
#include <iostream>
#include "heuristics01.h"
#include "heuristics02.h"

using namespace std;
AI::AI(int n, GameEngine* g1)
{
    this->n = n;
    this->g1 = g1;
    cout << "Konstruktor dziala" << endl;
}


int AI::makeBestMove(char** tab, int playerID)
{
    /*
        ustalenie jakie id ma sztuczna inteligencja a jakie przeciwnik
    */
    ai = playerID;
    if(playerID == 1)
    {
        opponent = 2;
    }
    else
    {
        opponent = 1;
    }
    /*
    Heuristics01* h1 = new Heuristics01(n, ai, opponent, g1);
    int wynik = h1->startSearching(tab);
    return wynik;
    */

    Heuristics02* h2 = new Heuristics02(n, ai, opponent, g1);
    int wynik = h2->startSearching(tab);
    return wynik;

    //heuristics01(tab, scoreTab);


}




int AI::heuristics01(char** tab, int** scoreTab)
{

}

int AI::minMax(char** tab, int depth, bool isMaximizing)
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

void AI::printScoreTab(int** tab)
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

int AI::boardEvaluationFunvtion01(char** tab)
{

}

