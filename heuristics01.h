#ifndef HEURISTICS01_H
#define HEURISTICS01_H
#include "gameengine.h"



class Heuristics01
{
    int n;                  // wymiar planszy
    int ai;                 // id sztucznej inteligencji
    int opponent;           // id przeciwnika
    int algorithmType;      // typ algorytmu, czyli czy AI ma zastosowac alfaBeta czy minMax
    GameEngine* g1;
public:
    Heuristics01(int n, int ai, int opponent, GameEngine* g1, int algorithmType);
    int startSearching(char** tab);     // funkcja nadzorujaca algorytm alfaBeta lub minMax
    int alfaBetaMinMax(char** tab, int depth, bool isMaximizing);   // najwaznejsza funkcja odpowiedzialna za znajdowanie najlepszego mozliwego ruchu


    void printScoreTab(int** tab);      // wypisuje oplacalnosc kazdego pola w funkcji rozwazania kolejnego ruchu. Im wieksza wartosc pola, tym ruch jest lepszy
    void printGameTab(char** tab);      // wypisuje stan planszy w pominieciem interfejsu graficznego

    int checkNeighbours(char** tab, int position_x, int position_y);


};

#endif // HEURISTICS01_H
