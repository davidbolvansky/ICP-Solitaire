#include <QtWidgets>
#include "QSolitaire.h"

QSolitaire::QSolitaire(QWidget *parent) :
    QMainWindow(parent) {

    p = parent;

    p->setFixedSize(900, 550);
    QVBoxLayout *main = new QVBoxLayout(p);

    newGame = new QPushButton("New Game");
    connect(newGame, SIGNAL (released()), this, SLOT (addNewGame()));
    main->addWidget(newGame);

    horizontalLayout = new QGridLayout();
    main->addLayout(horizontalLayout);

    mainBoard = new Board{};
    board0 = NULL;
    board1 = NULL;
    board2 = NULL;
    board3 = NULL;

    parent->setWindowTitle(QObject::tr("Solitaire"));
    parent->show();
}

QSolitaire::~QSolitaire()
{

}

void QSolitaire::addNewGame()
{
    if (board0 == NULL) {
        board0 = new QBoard(p, mainBoard, this);
        horizontalLayout->addWidget(board0,0,0);
    } else if (board1 == NULL) {
        board1 = new QBoard(p, mainBoard, this);
        horizontalLayout->addWidget(board1,0,1);
    } else if (board2 == NULL) {
        board2 = new QBoard(p, mainBoard, this);
        horizontalLayout->addWidget(board2,1,0);
    } else if (board3 == NULL) {
        board3 = new QBoard(p, mainBoard, this);
        horizontalLayout->addWidget(board3,1,1);
    }
    setProperSizes();
}

int QSolitaire::getNumberOfActiveGames()
{
    int i = 0;
    if (board0 != NULL)
        i++;
    if (board1 != NULL)
        i++;
    if (board2 != NULL)
        i++;
    if (board3 != NULL)
        i++;
    return i;
}

void QSolitaire::setProperSizes()
{
    if (getNumberOfActiveGames() == 0) {
        //uvodna obrazovka
        p->setFixedSize(900, 550);
    } else if (getNumberOfActiveGames() == 1) {
        if (board0 != NULL)
            board0->setBigSize();
        if (board1 != NULL)
            board1->setBigSize();
        if (board2 != NULL)
            board2->setBigSize();
        if (board3 != NULL)
            board3->setBigSize();
        p->setFixedSize(900, 550);
    } else {
        if (board0 != NULL)
            board0->setSmallSize();
        if (board1 != NULL)
            board1->setSmallSize();
        if (board2 != NULL)
            board2->setSmallSize();
        if (board3 != NULL)
            board3->setSmallSize();
        p->setFixedSize(1100, 700);
    }

}

void QSolitaire::removeGame(QBoard *board)
{
    board->close();
    if (board == board0) {
        board0->close();
        board0 = NULL;
    }
    if (board == board1) {
        board1->close();
        board1 = NULL;
    }
    if (board == board2) {
        board2->close();
        board2 = NULL;
    }
    if (board == board3) {
        board3->close();
        board3 = NULL;
    }
    setProperSizes();
}
