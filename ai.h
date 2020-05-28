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
    int makeBestMove(char** tab, int playerID, int heuristicType, int algorithmType);



};

#endif // AI_H
