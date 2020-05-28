#include "heuristics02.h"
#include <windows.h>

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Heuristics02::Heuristics02(int n, int ai, int opponent, GameEngine* g1, int algorithmType)
{
    this->n = n;
    this->ai = ai;
    this->opponent = opponent;
    this->g1 = g1;
    this->algorithmType = algorithmType;
    numberOfVisitedNodes = 0;
}

int Heuristics02::startSearching(char** tab)
{
    /*
        inicjalizacja zmiennych poczatkowych
    */
    int** scoreTab = new int*[n];
    for(int i = 0 ; i < n ; i++)
        scoreTab[i] = new int[n];

    globalBestScore = INT_MIN;
    int bestScorePosition_x = -1;
    int bestScorePosition_y = -1;
    int numberOfBranch = 0;



    /*
        petla po wszystkich polach tablicy
    */
    for (int i = 0;  i < n; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            // sprawdzamy czy dane pole sasiaduje z polem juz zapelnionym
            int neighbours = checkNeighbours(tab, j, i);


            // jesli aktualne pole jest puste i sasiaduje z polem juz zapelnionym to jest
            // potencjalnym miejscem w ktorym mozemy zrobic ruch
            if (tab[i][j] == -1 && neighbours != 0)
            {
                numberOfBranch++;
                tab[i][j] = ai;     // ruch ai
                int score;
                if(algorithmType == 1)
                {
                    score = alfaBeta(tab, 0, false);    // wywolanie z danego pola algorytmu alfaBeta
                }
                else
                {
                    score = minMax(tab, 0, false);      // wywolanie z danego pola algorytmu minMax
                }

                tab[i][j] = -1; // cofniecie ruchu ai zeby nie wplywac na stan planszy w kolejnych iretacjach

                scoreTab[i][j] = score;
                if (score > globalBestScore)    // jesli obecny ruch by; najelpszy
                {

                    globalBestScore = score;
                    bestScorePosition_x = j;
                    bestScorePosition_y = i;
                }
                // jeseli nasz ruch jest rowny najelpszemu to wybieramy losowo z pewnym
                // prawdopodobienstwem albo poprzedni wynik albo nowy w celu wprowadzenia
                // braku determinizmu rozgrywki
                else if(score == globalBestScore &&  (double(rand())/RAND_MAX) > 0.8)
                {
                    bestScorePosition_x = j;
                    bestScorePosition_y = i;
                }
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
    //cout << "Najlepsza pozycja to wiersz " << bestScorePosition_y <<  " i kolumna " << bestScorePosition_x << endl;
    // wypisuje oplacalnosc kazdego pola w funkcji rozwazania kolejnego ruchu. Im wieksza wartosc pola, tym ruch jest lepszy
    //printScoreTab(scoreTab);
    //printGameTab(tab);            // wypisuje stan planszy w taki sposob jak widzi ja AI

    return g1->makeMove(bestScorePosition_x, bestScorePosition_y);
}



int Heuristics02::alfaBeta(char** tab, int depth, bool isMaximizing)
{
    /*
        Jesli osiagnieta maksymalna glebokosc
    */
    if(depth == 1)
    {
        return evaluationBoardState(tab, depth);    // zwracamy ocene stanu planszy

    }
    numberOfVisitedNodes++;

    /*
        jesli nie osiagnieto maksymalnej glebokosci to sprawdzamy czy jest jakis zwyciezca
    */
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
                // czy miejsce jest wolne i ma sasiada?
                int neighbours = checkNeighbours(tab, j, i);
                if (tab[i][j] == -1 && neighbours != 0)
                {
                    tab[i][j] = ai;                                     // ai wykonuje ruch na danej pozycji
                    int score = evaluationBoardState(tab, depth);       // nastepuje ocena stanu planszy po ruchu
                    alfaBeta(tab, depth + 1, false);                    // reukrencyjnie wywolana funkcja
                    tab[i][j] = -1;                                     // cofniecie ruchu


                    if(score > bestScore)   // sprawdzenie czy ruch byl lepszy od najlepszego
                    {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;   // zwrocenie najlepszego wyniku
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
                // czy miejsce jest wolne i ma sasiada?
                int neighbours = checkNeighbours(tab, j, i);
                if (tab[i][j] == -1 && neighbours != 0)
                {
                    tab[i][j] = opponent;
                    int score = evaluationBoardState(tab, depth);
                    alfaBeta(tab, depth + 1, true);
                    tab[i][j] = -1;
                    if(score < bestScore)
                    {
                        bestScore = score;
                    }

                    // DLA ALFA-BETA. Jesli ruch przeciwnika jest dla nas gorszy niz poprzednio znaleziona
                    // najlepsza kombinacja ruchow, to znaczy ze ten ruch jest zly i nie ma sensu dalej sprawdzac
                    if(score < globalBestScore)
                    {
                        return score;
                    }
                }
            }
        }
        return bestScore;
    }
}


int Heuristics02::minMax(char** tab, int depth, bool isMaximizing)
{
    /*
        Jesli osiagnieta maksymalna glebokosc
    */
    if(depth == 2)
    {
        //cout  << evaluationBoardState(tab, depth) << endl;
        return evaluationBoardState(tab, depth);

    }
    numberOfVisitedNodes++;


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


int Heuristics02::evaluationBoardState(char** tab, int depth)
{
    int liczbaCiagowPotrojnychAi = 0;
    int liczbaCiagowPodwojnychAi = 0;
    int liczbaCiagowPotrojnychOpponent = 0;
    int liczbaCiagowPodwojnychOpponent = 0;

    /*
        algorytm sprawdz czy ktos wygrywa,
        Jesli wygrywa AI to wynik: 10000 - depth
        Jesli wygrywa przeciwnik to wynik: - 10000 + depth
    */
    int value = checkWinner(tab,depth);
    if(value != 0)
    {
        return value;
    }


    liczbaCiagowPotrojnychAi = checkPair(tab, 3, ai);   // zliczamy ilosc niezabezpieczonych trojek nalezacych do AI
    liczbaCiagowPodwojnychAi = checkPair(tab, 2 , ai);  // zliczamy ilosc niezabezpieczonych dwojek nalezacych do AI

    liczbaCiagowPotrojnychOpponent = checkPair(tab, 3, opponent);  // zliczamy ilosc niezabezpieczonych trojek nalezacych do przeciwnika
    liczbaCiagowPodwojnychOpponent = checkPair(tab, 2 , opponent); // zliczamy ilosc niezabezpieczonych dwojek nalezacych do przeciwnika

    // obliczenie wskaznika oceny dla AI
    int evaluatedValueAI = 10*liczbaCiagowPotrojnychAi +  liczbaCiagowPodwojnychAi;

    // obliczenie wskaznka oceny dla przeciwnika
    int evaluatedValueOpponent = 10*liczbaCiagowPotrojnychOpponent +  liczbaCiagowPodwojnychOpponent;

     // zwrocenie globalnego wskaznika oceny stanu planszy
    return evaluatedValueAI - evaluatedValueOpponent;
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


int Heuristics02::checkPair(char** tab, int a, int player)
{

    /*
        algorytm szuka a elementow niezabezpieczonych obok siebie
    */
    int pomPlayer = 0;
    int numberOfElements = 0;


    /*
        sprawdzanie czy a elementow niezabezpieczonych jest w poziomie
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
                pomPlayer++;
            }
            if (pomPlayer >= a)
            {
                if(tab[i][j+1] == -1 && tab[i][j-a] == -1)
                {
                    numberOfElements++;
                }
                else
                {
                    pomPlayer = 0;
                }

            }
            if (tab[i][j] != player)
            {
                pomPlayer = 0;
            }
         }
         pomPlayer = 0;
    }


    /*
        sprawdzenie czy jest a elementow niezabezpieczonych w pionie
    */
    pomPlayer = 0;
    for (int j = 1; j < n -1; j++)
    {
        for (int i = 1; i < n-1; i++)
        {
            // sprawdzanie dla gracza 1
            if (tab[i][j] == player)
            {
                pomPlayer++;
            }
            if (pomPlayer >= a)
            {
                if(tab[i+1][j] == -1 && tab[i-a][j] == -1)
                {
                    numberOfElements++;
                }
                else
                {
                    pomPlayer = 0;
                }
            }
            if (tab[i][j] != player)
            {
                pomPlayer = 0;
            }
        }
        pomPlayer = 0;
    }

    /*
        sprawdzenie, czy jest a elementow niezabezpieczonych  po skosie "funkcja malejaca y = -x"
    */
    pomPlayer = 0;
    for (int i = 1; i < n -1; i++)
    {
        for (int j = 1; j < n -1; j++)
        {
            // dla gracza 1
            pomPlayer = 0;
            int pomX = 0;
            int pomY = 0;
            if (tab[i][j] == player)
            {
                pomX = j;
                pomY = i;
                while (pomY < n -1 && pomX < n -1 && tab[pomY][pomX] == player)
                {
                    pomPlayer++;
                    pomY++;
                    pomX++;
                }
                if (pomPlayer >= a)
                {
                    if(tab[pomY][pomX] == -1 && tab[pomY-(a+1)][pomX-(a+1)] == -1)
                    {
                        numberOfElements++;
                    }
                    else
                    {
                        pomPlayer = 0;
                    }

                }
            }
        }
        pomPlayer = 0;
    }


    /*
        sprawdzenie, czy jest a elementow niezabezpieczonych po skosie "funkcja rosnaca y = x"
    */
    pomPlayer = 0;
    for (int i = 1; i < n -1; i++)
    {
        for (int j = 1; j < n -1; j++)
        {
            // dla gracza 1
            pomPlayer = 0;
            int pomX = 0;
            int pomY = 0;
            if (tab[i][j] == player)
            {
                pomX = j;
                pomY = i;
                while (pomY < n-1 && pomX > 0 && tab[pomY][pomX] == player)
                {
                    pomPlayer++;
                    pomY++;
                    pomX--;
                }
                if (pomPlayer >= a)
                {
                    if(tab[pomY][pomX] == -1 && tab[pomY-(a+1)][pomX+(a+1)] == -1)
                    {
                        numberOfElements++;
                    }
                    else
                    {
                        pomPlayer = 0;
                    }
                }
            }
        }
        pomPlayer = 0;
    }
    return numberOfElements;
}



int Heuristics02::checkNeighbours(char **tab, int position_x, int position_y)   // zlicza ile sasiadow jest w poblizu pozycji xy
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
