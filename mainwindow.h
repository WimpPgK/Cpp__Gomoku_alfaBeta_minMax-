#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include "gameengine.h"
#include "ai.h"
#include <iostream>
QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void clickAction(int pozycja_x, int pozycja_y);
    void initGame();
    void AIvsAI();
    int nextMoveAI();
    void endGame(int winner);
    void refreshBoardView();


	/*
					TE SCIEZKI NALEZY ZMIENIC
	*/
    QString path_freeSlot = "E:/Dropbox/InneProjekty/007_Gomoku_MinMax_AlfaBeta/programy/001/003/Images/freeSlot.jpg";
    QString path_player01 = "E:/Dropbox/InneProjekty/007_Gomoku_MinMax_AlfaBeta/programy/001/003/Images/player01.jpg";
    QString path_player02 = "E:/Dropbox/InneProjekty/007_Gomoku_MinMax_AlfaBeta/programy/001/003/Images/player02.jpg";
	

    static const int n = 15; // wymiar planszy
    int iconSizeX;
    int iconSizeY;
    int heuristicType1;
    int heuristicType2;
    int algorithm_type1;
    int algorithm_type2;
    QPushButton* Field[n][n];
    GameEngine* g1;
    std::string trybRozgrywki1;
    std::string trybRozgrywki2;



    /*
        obsluga przyciskow z interfejsu
    */
private slots:
    void mapButtons(QString text);
    void on_pushButton_clicked();
    void on_pushButton_confirmChanges_clicked();
};
#endif // MAINWINDOW_H
