/**
* @file     QSolitaire.h
* @brief    main view, can contains multiple games
* @author   Katarina Gresova xgreso00
*/

#ifndef QGAME_H
#define QGAME_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "QBoard.h"
#include "./board.h"

class QSolitaire : public QMainWindow
{
    Q_OBJECT

public:
    explicit QSolitaire(QWidget *parent = 0);
    ~QSolitaire();
    void removeGame(QBoard *board);

private:
    QWidget *p;
    QGridLayout *layout;
    QGridLayout *horizontalLayout;
    QPushButton *newGame;
    QPushButton *loadB;
    Board * mainBoard;
    QBoard *board0;
    QBoard *board1;
    QBoard *board2;
    QBoard *board3;

protected:
    int getNumberOfActiveGames();
    void setProperSizes();

private slots:
    void addNewGame();
    void load();
};

#endif // QGAME_H
