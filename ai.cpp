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
    //cout << "Konstruktor dziala" << endl;
}



// funkcja odpowiedzialna za zarzadzanie wykonywaniem kolejnego ruchu przez AI
int AI::makeBestMove(char** tab, int playerID, int heuristicType, int algorithmType)
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
      uruchomienie odpowiedniego algorytmu znajdowania kolejnego ruchu
    */
    if(heuristicType == 1)
    {
        Heuristics01* h1 = new Heuristics01(n, ai, opponent, g1, algorithmType);
        int score = h1->startSearching(tab);
        return score;
    }
    if(heuristicType == 2)
    {
        Heuristics02* h2 = new Heuristics02(n, ai, opponent, g1, algorithmType);
        int score = h2->startSearching(tab);
        return score;

    }
}
