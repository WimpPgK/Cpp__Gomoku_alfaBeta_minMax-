#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include "gameengine.h"
#include "ai.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void initGame();
    void refreshBoardView();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void obslugaKlikniecia(int pozycja_x, int pozycja_y);
    void endGame(int winner);

    QString path_freeSlot = "E:/Dropbox/InneProjekty/007_Gomoku_MinMax_AlfaBeta/programy/001/003/Images/freeSlot.jpg";
    QString path_player01 = "E:/Dropbox/InneProjekty/007_Gomoku_MinMax_AlfaBeta/programy/001/003/Images/player01.jpg";
    QString path_player02 = "E:/Dropbox/InneProjekty/007_Gomoku_MinMax_AlfaBeta/programy/001/003/Images/player02.jpg";


    static const int n = 15; // wymiar planszy
    //static const int iconSizeX = 50;
    //static const int iconSizeY = 50;
    int iconSizeX;
    int iconSizeY;

    QPushButton* Field[n][n];
    GameEngine* g1;

private slots:
    void mapowaniePrzyciskow(QString text);
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
