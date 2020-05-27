#ifndef HEURISTICS02_H
#define HEURISTICS02_H
#include "gameengine.h"



class Heuristics02
{
    int n;
    int ai;
    int opponent;
    GameEngine* g1;
public:
    Heuristics02(int n, int ai, int opponent, GameEngine* g1);

    int startSearching(char** tab);
    int checkNeighbours(char** tab, int position_x, int position_y);
    int checkWinner(char** tab, int depth);
    int evaluationBoardState(char** tab, int depth);
    int checkPair(char** tab, int a, int player);
    int minMax(char** tab, int depth, bool isMaximizing);
    void printScoreTab(int** tab);
    void printGameTab(char** tab);

};

#endif // HEURISTICS02_H
