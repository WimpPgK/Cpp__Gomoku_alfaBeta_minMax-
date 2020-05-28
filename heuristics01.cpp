#include "heuristics01.h"
#include <windows.h>

#include <iostream>
using namespace std;

Heuristics01::Heuristics01(int n, int ai, int opponent, GameEngine* g1,int algorithmType)
{
    this->n = n;
    this->ai = ai;
    this->opponent = opponent;
    this->g1 = g1;
    this->algorithmType = algorithmType;
}

int Heuristics01::startSearching(char** tab)
{
    /*
        inicjalizacja wartosci poczatkowych
    */
    int** scoreTab = new int*[n];
    for(int i = 0 ; i < n ; i++)
        scoreTab[i] = new int[n];

    int bestScore = INT_MIN;
    int bestScorePosition_x = -1;   // zmienna do przechowywania pozycji x'owej najlepszego pola
    int bestScorePosition_y = -1;   // zmienna do przechowywania pozycji y'owej najlepszego pola
    int numberOfBranch = 0;         // licznik odwiedzonych galezi

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
                // robimy ruch na danej pozycji i uruchamiamy algorytm minMax lub alfaBeta
                tab[i][j] = ai;
                int score = alfaBetaMinMax(tab, 0, false);

                //po sprawdzeniu danej pozycji cofamy ruch zeby nie wplywac na stan planszy
                tab[i][j] = -1;


                scoreTab[i][j] = score;
                // sprawdzamy czy wynik dla naszego pola jest lepszy od najelpszego
                // jesli jest najlepszy to zapisujemy jego wartosci
                if (score > bestScore)
                {

                    bestScore = score;
                    bestScorePosition_x = j;
                    bestScorePosition_y = i;
                }
                // jeseli nasz ruch jest rowny najelpszemu to wybieramy losowo z pewnym
                // prawdopodobienstwem albo poprzedni wynik albo nowy w celu wprowadzenia
                // braku determinizmu rozgrywki
                else if(score == bestScore &&  (double(rand())/RAND_MAX) > 0.8)
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
    // jesli cala plansza byla pusta to pierwszy ruch robimy na srodku
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


int Heuristics01::alfaBetaMinMax(char** tab, int depth, bool isMaximizing)
{
    /*
        Jesli osiagnieta maksymalna glebokosc
    */
    if(depth == 4)
    {
        return 10;
    }


    /*
        jesli nie osiagnieto maksymalnej glebokosci to sprawdzamy czy jest jakis zwyciezca
    */
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
            // jesli wygrywa ai to funkcja zwraca 100 pomniejszone o glebokosc
            pom  = 100;
            pom -= depth;
            return pom;
        }

        if(result == opponent)
        {
            // jesli wygrywa przeciwnik to funkcja zwraca -100 powiekszone o glebokosc
            pom  = -100;
            pom += depth;
            return pom;
        }
        if(result == 0)
        {
            // jesli jest remis
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
                // czy miejsce jest wolne i ma sasiada?
                int neighbours = checkNeighbours(tab, j, i);
                if (tab[i][j] == -1 && neighbours != 0)
                {
                    tab[i][j] = ai;     // ai wykonuje ruch na danej pozycji
                    int score;
                    score = alfaBetaMinMax(tab, depth + 1, false);  // rekurencyjne wywolanie funkcji
                    tab[i][j] = -1;     // cofniecie ruchu

                    // jesli ruch byl lepszy od najlepszego
                    if(score > bestScore)
                    {
                        bestScore = score;
                    }
                    if(algorithmType == 1)  // jesli algorytm to alfa beta
                    {
                        // gdy ai wygrywa to nie ma juz sensu sprawdzac innych opcji
                        // bo ta jest dostatecznie dobra
                        if(score > 0)
                        {
                            return score;
                        }
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
                // czy miejsce jest wolne i ma sasiada?
                int neighbours = checkNeighbours(tab, j, i);
                if (tab[i][j] == -1 && neighbours != 0)
                {
                    tab[i][j] = opponent;   // przeciwnik wykonuje ruch
                    int score = alfaBetaMinMax(tab, depth + 1, true);   // wywolanie rekurencyjne
                    tab[i][j] = -1;         // cofniecie ruchu

                    // jesli ruch byl lepszy niz poprzedni anjelpszy
                    if(score < bestScore)
                    {
                        bestScore = score;
                    }
                    if(algorithmType == 1)
                    {
                        if(score < 0)
                        {
                            return score;
                        }
                    }
                }
            }
        }
        return bestScore;
    }
}

int Heuristics01::checkNeighbours(char **tab, int position_x, int position_y)
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

void Heuristics01::printGameTab(char** tab)
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
