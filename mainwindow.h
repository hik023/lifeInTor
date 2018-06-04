#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSlider>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QList>
#include <QRadioButton>
#include <QTimer>
#include "Field.h"
#include "Game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
//    First window
    QLabel *beginLabel;
    QLabel *widthLabel;
    QLabel *heightLabel;
    QLabel *freqLabel;
    QLineEdit *fieldWidthEdit;
    QLineEdit *fieldHeightEdit;
    QPushButton *fieldBtn;
    QPushButton *loadBtn;
    QTimer *tmr;
//    Second window
//    QList<QTableWidget> *tablesList;
    QPushButton *saveBtn;
    QTableWidget *fieldTable;
    QLineEdit *freqTimer;
    QPushButton *setTimer;
    QLabel *bornLabel;
    QTableWidget *bornCount;
    QPushButton *setBornCountBtn;
    QPushButton *startBtn;
    QPushButton *stopBtn;
    QLabel *epochLabel;
    QRadioButton *pencilRBtn;
    QRadioButton *eraserRBtn;
    int epoch, bornNum;
    bool states[3][9];
//    QSlider *epochSlider;
    Game *game;
    Field *gField ;

    void drawField();
    void startNewGame(int, int);

private slots:
//    void epochSlot(int);
    void setBornNumSlot();
    void createFieldSlot();
    void nullCheck();
    void clickCellStateSlot(int, int);
    void clickCellSlot(int, int);
    void setFreqSlot();
    void saveSlot();
    void loadSlot();
    void startGameSlot();
    void stopGameSlot();
    void updateStateSlot();
};

#endif // MAINWINDOW_H
