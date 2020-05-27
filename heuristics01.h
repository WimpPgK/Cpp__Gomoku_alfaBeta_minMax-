#ifndef HEURISTICS01_H
#define HEURISTICS01_H
#include "gameengine.h"



class Heuristics01
{
    int n;
    int ai;
    int opponent;
    GameEngine* g1;
public:
    Heuristics01(int n, int ai, int opponent, GameEngine* g1);
    int startSearching(char** tab);
    int minMax(char** tab, int depth, bool isMaximizing);
    void printScoreTab(int** tab);

};

#endif // HEURISTICS01_H
