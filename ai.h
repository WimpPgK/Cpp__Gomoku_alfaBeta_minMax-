#ifndef AI_H
#define AI_H
#include "gameengine.h"


class AI
{
    int n;
    int ai;
    int opponent;
    GameEngine* g1;


public:
    AI(int n, GameEngine* g1);
    void printScoreTab(int** tab);
    int heuristics01(char** tab, int** scoreTab);
    int heuristics02(char** tab, int** scoreTab);

    int makeBestMove(char** tab,int);
    int minMax(char** tab,int depth, bool isMaximizing);
    int alfaBeta(char** tab,int depth, bool isMaximizing);
    int boardEvaluationFunvtion01(char** tab);
    int boardEvaluationFunvtion02(char** tab);
    int boardEvaluationFunvtion03(char** tab);


};

#endif // AI_H
