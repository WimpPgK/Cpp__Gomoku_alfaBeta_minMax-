#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QPixmap>
#include <QApplication>
#include <QMessageBox>

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
            connect(Field[i][j],  &QPushButton::clicked,  [=](){ mapowaniePrzyciskow(tekst); });
         }
    }

    initGame();

    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)
        {
            /*
            Field[i][j]->setFlat(true);
            Field[i][j]->setIcon(freeSlot);
            Field[i][j]->setIconSize(QSize(iconSizeX,iconSizeY));*/

        }
    }


}

void MainWindow::initGame()
{
    g1 = new GameEngine(n);
    refreshBoardView();
    //b1->printBoard();
}

void MainWindow::mapowaniePrzyciskow(QString text)
{
    string zakodowanaPozycja =  text.toUtf8().constData();
    string delimiter = " ";
    int pozycja_x = stoi(zakodowanaPozycja.substr(0, zakodowanaPozycja.find(delimiter)));
    int pozycja_y = stoi(zakodowanaPozycja.substr(zakodowanaPozycja.find(delimiter)));
    obslugaKlikniecia(pozycja_x, pozycja_y);

}

void MainWindow::obslugaKlikniecia(int pozycja_x, int pozycja_y)
{
    int winner = -1;
    cout << "Ruch na pozycji wiersz " << pozycja_y << "   kolumna " << pozycja_x << endl;
    winner = g1->makeMove(pozycja_y, pozycja_x);
    refreshBoardView();
    if(winner != -1)
    {
        endGame(winner);
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


    //QPixmap player01 ("E:/Dropbox/InneProjekty/006_/Programy/GUI/Connect4/Graphic/002.jpg");
    //QPixmap player02 ("E:/Dropbox/InneProjekty/006_/Programy/GUI/Connect4/Graphic/003.jpg");

    if(g1->playerTurn == 1)
       {
           ui->label_nextMove->setPixmap(player01.scaled(50, 50, Qt::IgnoreAspectRatio));
       }
       else if (g1->playerTurn == 2)
       {
           ui->label_nextMove->setPixmap(player02.scaled(50, 50, Qt::IgnoreAspectRatio));
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
    winner = a1->makeBestMove(g1->b1->board,g1->playerTurn);
    refreshBoardView();
    if(winner != -1)
    {
        endGame(winner);
    }
}
