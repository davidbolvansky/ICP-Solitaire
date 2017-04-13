#ifndef SOLITAIRE_H
#define SOLITAIRE_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "../game.h"
#include "../card.h"
#include "../board.h"

namespace Ui {
class Solitaire;
}

class Solitaire : public QMainWindow
{
    Q_OBJECT

public:
    explicit Solitaire(QWidget *parent = 0);
    ~Solitaire();
    void createGame();
    void paintCards();
    void resetSelection();

private slots:
    void handleStockDeck();
    void handleWasteDeck();
    void handleTargetDeck1();
    void handleTargetDeck2();
    void handleTargetDeck3();
    void handleTargetDeck4();
    void handleWorking();
    void save();

private:
    Ui::Solitaire *ui;
    Board *main;
    Game *game;
    bool wasteClicked = false;
    int targetClicked = -1;
    int workingStackClicked = -1;
    int workingCardClicked = -1;
};

#endif // SOLITAIRE_H
