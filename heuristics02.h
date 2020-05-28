#ifndef HEURISTICS02_H
#define HEURISTICS02_H
#include "gameengine.h"



class Heuristics02
{
    int n;
    int ai;
    int opponent;
    int numberOfVisitedNodes;
    int globalBestScore;
    int algorithmType;
    GameEngine* g1;
public:
    Heuristics02(int n, int ai, int opponent, GameEngine* g1, int algorithmType);

    int startSearching(char** tab);     // funkcja nadzorujaca algorytm minMax lub alfaBeta


    int minMax(char** tab, int depth, bool isMaximizing);               // algorytm minMax
    int alfaBeta(char** tab, int depth, bool isMaximizing);             // algorytm alfaBeta

     // funkcja oceniajaca stan planszy na podstawie wartosci zwracanych przez funkcje checkWinner i checkPair
    int evaluationBoardState(char** tab, int depth);
    int checkPair(char** tab, int a, int player);       // sprawdza ile jest niezabezpieczonych ciagow danych elementow o dlugosci a

    int checkNeighbours(char** tab, int position_x, int position_y);    // funkcja sprawdza ile sasiadow ma dane pole
    int checkWinner(char** tab, int depth);                             // funkcja sprawdz czy ktos wygral
    void printScoreTab(int** tab);
    void printGameTab(char** tab);

};

#endif // HEURISTICS02_H
