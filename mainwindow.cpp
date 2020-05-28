#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QPixmap>
#include <QApplication>
#include <QMessageBox>
#include <chrono>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    /*
     *  Utworzenie tablicy 2d przyciskow i ich dolaczenie do grid layout.
     *  Po utworzeniu przyciskow polaczone zostaja one z funkcja obslugi klikniecia
     *  ktora przyjmuje jako argument QString. Musi byc taki typ aby dalo sie obslogiwac
     *  przesylanie argumentu. Aby program dzialal trzeba uzywac c++11. W pliku .pro dodano
     *  flage kompilatora ustawiajaca standard  c++11
     *
     */
    iconSizeX = 761/n;
    iconSizeY = 761/n;



    for(int i=0;i<n;i++)
    {

        for(int j=0;j<n;j++)
        {
            Field[i][j]=new QPushButton("", this);
            QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            sizePolicy.setHeightForWidth(Field[i][j]->sizePolicy().hasHeightForWidth());
            Field[i][j]->setSizePolicy(sizePolicy);
            Field[i][j]->setFlat(false);
            ui->gridLayout->addWidget(Field[i][j], i, j);
            QString tekst = QString::number(i);
            tekst += " ";
            tekst += QString::number(j);
            Field[i][j]->setFlat(true);
            connect(Field[i][j],  &QPushButton::clicked,  [=](){ mapButtons(tekst); });
         }
    }

    initGame();
}

void MainWindow::initGame()
{
    g1 = new GameEngine(n);
    refreshBoardView();
    //b1->printBoard();
}

void MainWindow::mapButtons(QString text)
{
    string zakodowanaPozycja =  text.toUtf8().constData();
    string delimiter = " ";
    int pozycja_x = stoi(zakodowanaPozycja.substr(0, zakodowanaPozycja.find(delimiter)));
    int pozycja_y = stoi(zakodowanaPozycja.substr(zakodowanaPozycja.find(delimiter)));
    clickAction(pozycja_x, pozycja_y);

}

void MainWindow::clickAction(int pozycja_x, int pozycja_y)
{
    int winner = -1;
    //cout << "Ruch na pozycji wiersz " << pozycja_y << "   kolumna " << pozycja_x << endl;
    winner = g1->makeMove(pozycja_y, pozycja_x);
    refreshBoardView();
    if(winner != -1)
    {
        endGame(winner);
    }

    if(g1->playerTurn == 2 && trybRozgrywki2 == "Computer" && trybRozgrywki1 != "Computer")
    {
        nextMoveAI();
    }
    if(g1->playerTurn == 1 && trybRozgrywki1 == "Computer"  && trybRozgrywki2 != "Computer")
    {
        nextMoveAI();
    }



}
void MainWindow::endGame(int flaga)
{

    if(flaga == 1)
    {
        QMessageBox::StandardButton reply = QMessageBox::information(this, "Wynik gry", "Wygrywa gracz 1");

    }
    if(flaga == 2)
    {
        QMessageBox::StandardButton reply = QMessageBox::information(this, "Wynik gry", "Wygrywa gracz 2");

    }
    if(flaga == 0)
    {
        QMessageBox::StandardButton reply = QMessageBox::information(this, "Wynik gry", "Remis - plansza została zapełniona");

    }

    delete g1;
    g1 = new GameEngine(n);
    refreshBoardView();

}


void MainWindow::refreshBoardView()
{
    /*
     * przygotowanie grafik do przyciskow
     */
    QPixmap freeSlot(path_freeSlot);
    QPixmap player01(path_player01);
    QPixmap player02(path_player02);

    QIcon freeSlotIcon(freeSlot);
    QIcon player01Icon(player01);
    QIcon player02Icon(player02);

    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            if(g1->b1->board[i][j] == -1)
            {
                Field[i][j]->setIcon(freeSlotIcon);
                Field[i][j]->setIconSize(QSize(iconSizeX,iconSizeY));
            }
            else if(g1->b1->board[i][j] == 1)
            {
                Field[i][j]->setIcon(player01);
                Field[i][j]->setIconSize(QSize(iconSizeX,iconSizeY));
            }
            else
            {
                Field[i][j]->setIcon(player02);
                Field[i][j]->setIconSize(QSize(iconSizeX,iconSizeY));
            }


        }
    }

    if(g1->playerTurn == 1)
    {
        ui->label_nextMove->setPixmap(player01.scaled(70, 70, Qt::IgnoreAspectRatio));
    }
    else if (g1->playerTurn == 2)
    {
        ui->label_nextMove->setPixmap(player02.scaled(70, 70, Qt::IgnoreAspectRatio));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    AI* a1 = new AI(n, g1);
    int winner = -1;
    if(g1->playerTurn == 1)
    {
        winner = a1->makeBestMove(g1->b1->board,g1->playerTurn, heuristicType1, algorithm_type1);
    }
    else
    {
        winner = a1->makeBestMove(g1->b1->board,g1->playerTurn, heuristicType2, algorithm_type2);
    }
    refreshBoardView();
    if(winner != -1)
    {
        endGame(winner);
    }
}

void MainWindow::on_pushButton_confirmChanges_clicked()
{

    QString QString_role_player1 = ui->comboBox_role_player1->currentText();
    trybRozgrywki1 = QString_role_player1.toLocal8Bit().constData();

    QString QString_role_player2 = ui->comboBox_role_player2->currentText();
    trybRozgrywki2 = QString_role_player2.toLocal8Bit().constData();

    QString QString_heuristic_player1 = ui->comboBox_heuristic_player1->currentText();
    string heuristicTypePom1 = QString_heuristic_player1.toLocal8Bit().constData();
    heuristicType1 = 0;
    if(heuristicTypePom1 == "Board evaluation 1")
    {
        heuristicType1 = 1;
    }
    else if (heuristicTypePom1 == "Board evaluation 2")
    {
         heuristicType1 = 2;
    }


    QString QString_heuristic_player2 = ui->comboBox_heuristic_player2->currentText();
    string heuristicTypePom2 = QString_heuristic_player2.toLocal8Bit().constData();
    heuristicType2 = 0;
    if(heuristicTypePom2 == "Board evaluation 1")
    {
        heuristicType2 = 1;
    }
    else if (heuristicTypePom2 == "Board evaluation 2")
    {
         heuristicType2 = 2;
    }


    QString QString_algorithm_typePom1 = ui->comboBox_algorithm_player1->currentText();
    string algorithm_typePom1 = QString_algorithm_typePom1.toLocal8Bit().constData();

    if(algorithm_typePom1 == "AlfaBeta")
    {
        algorithm_type1 = 1;
    }
    else if (algorithm_typePom1 == "MinMax")
    {
         algorithm_type1 =  2;
    }


    QString QString_algorithm_typePom2 = ui->comboBox_algorithm_player2->currentText();
    string algorithm_typePom2 = QString_algorithm_typePom2.toLocal8Bit().constData();
    if(algorithm_typePom2 == "AlfaBeta")
    {
        algorithm_type2 = 1;
    }
    else if (algorithm_typePom2 == "MinMax")
    {
         algorithm_type2 =  2;
    }

    if (trybRozgrywki1 == "Computer" && trybRozgrywki2 == "Computer")
    {
        AIvsAI();
    }
    if (trybRozgrywki1 == "Computer")
    {
        nextMoveAI();
    }



}

void MainWindow::AIvsAI()
{
    int totalTimePlayer1 = 0;
    int totalTimePlayer2 = 0;

    auto start = std::chrono::high_resolution_clock::now();


    while(true)
    {
        int flaga = nextMoveAI();
        qApp->processEvents();
        if(flaga  == 1)
        {
            cout << "Zatrzymanie" << endl;
            break;
        }
    }

    auto finish = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << "Execution time[s]:		" << elapsed.count() << " s\n";
}

int MainWindow::nextMoveAI()
{
    AI* a1 = new AI(n, g1);
    int winner = -1;
    if(g1->playerTurn == 1)
    {
        winner = a1->makeBestMove(g1->b1->board,g1->playerTurn, heuristicType1, algorithm_type1);
    }
    else
    {
        winner = a1->makeBestMove(g1->b1->board,g1->playerTurn, heuristicType2, algorithm_type2);
    }

    refreshBoardView();
    if(winner != -1)
    {
        endGame(winner);
        return 1;
    }
    return 0;

}
