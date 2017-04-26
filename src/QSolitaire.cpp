/**
* @file     QSolitaire.cpp
* @brief    main view, can contains multiple games
* @author   Katarina Gresova xgreso00
*/

#include <QtWidgets>
#include "QSolitaire.h"

/**
 * @brief QSolitaire::QSolitaire    constructor
 * @param parent                    parent widget
 */
QSolitaire::QSolitaire(QWidget *parent) :
    QMainWindow(parent) {

    p = parent;

    p->setFixedSize(900, 550);
    QVBoxLayout *main = new QVBoxLayout(p);
    QHBoxLayout *top = new QHBoxLayout();
    main->addLayout(top);

    newGame = new QPushButton("New Game");
    connect(newGame, SIGNAL (released()), this, SLOT (addNewGame()));
    top->addWidget(newGame);

    loadB = new QPushButton("Load Game");
    connect(loadB, SIGNAL (released()), this, SLOT (load()));
    top->addWidget(loadB);

    horizontalLayout = new QGridLayout();
    main->addLayout(horizontalLayout);

    mainBoard = new Board{};
    board0 = new QBoard(p, mainBoard, this);
    board0->game = mainBoard->create_new_game();
    board0->game->start();
    board0->setup();
    horizontalLayout->addWidget(board0,0,0);
    board1 = NULL;
    board2 = NULL;
    board3 = NULL;
    setProperSizes();

    parent->setWindowTitle(QObject::tr("Solitaire"));
    parent->show();
}

/**
 * @brief QSolitaire::~QSolitaire   dectructor
 */
QSolitaire::~QSolitaire()
{

}

/**
 * @brief QSolitaire::addNewGame    adds new game to window, if possible
 */
void QSolitaire::addNewGame()
{
    if (board0 == NULL) {
        board0 = new QBoard(p, mainBoard, this);
        board0->game = mainBoard->create_new_game();
        board0->game->start();
        board0->setup();
        horizontalLayout->addWidget(board0,0,0);
    } else if (board1 == NULL) {
        board1 = new QBoard(p, mainBoard, this);
        board1->game = mainBoard->create_new_game();
        board1->game->start();
        board1->setup();
        horizontalLayout->addWidget(board1,0,1);
    } else if (board2 == NULL) {
        board2 = new QBoard(p, mainBoard, this);
        board2->game = mainBoard->create_new_game();
        board2->game->start();
        board2->setup();
        horizontalLayout->addWidget(board2,1,0);
    } else if (board3 == NULL) {
        board3 = new QBoard(p, mainBoard, this);
        board3->game = mainBoard->create_new_game();
        board3->game->start();
        board3->setup();
        horizontalLayout->addWidget(board3,1,1);
    }
    setProperSizes();
}

/**
 * @brief QSolitaire::getNumberOfActiveGames    return number of games on window
 * @return
 */
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

/**
 * @brief QSolitaire::setProperSizes    resizes games to fit
 */
void QSolitaire::setProperSizes()
{
    if (getNumberOfActiveGames() == 1) {
        if (board0 != NULL)
            board0->setBigSize();
        if (board1 != NULL)
            board1->setBigSize();
        if (board2 != NULL)
            board2->setBigSize();
        if (board3 != NULL)
            board3->setBigSize();
        p->setFixedSize(920, 580);
    } else {
        if (board0 != NULL)
            board0->setSmallSize();
        if (board1 != NULL)
            board1->setSmallSize();
        if (board2 != NULL)
            board2->setSmallSize();
        if (board3 != NULL)
            board3->setSmallSize();
        p->setFixedSize(1120, 700);
    }
}

/**
 * @brief QSolitaire::removeGame    removes game from window
 * @param board                     game to be removed
 */
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

/**
 * @brief QSolitaire::load  creates load window and allows to load game from file
 */
void QSolitaire::load()
{
    if (getNumberOfActiveGames() < 4)
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open New Game"));
        if (fileName.isEmpty())
            return;
        else {

            QFile file(fileName);

            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }

            if (board0 == NULL) {
                board0 = new QBoard(p, mainBoard, this);
                board0->game = board0->game->load(fileName.toStdString());
                board0->setup();
                horizontalLayout->addWidget(board0,0,0);
            } else if (board1 == NULL) {
                board1 = new QBoard(p, mainBoard, this);
                board1->game = board1->game->load(fileName.toStdString());
                board1->setup();
                horizontalLayout->addWidget(board1,0,1);
            } else if (board2 == NULL) {
                board2 = new QBoard(p, mainBoard, this);
                board2->game = board2->game->load(fileName.toStdString());
                board2->setup();
                horizontalLayout->addWidget(board2,1,0);
            } else if (board3 == NULL) {
                board3 = new QBoard(p, mainBoard, this);
                board3->game = board3->game->load(fileName.toStdString());
                board3->setup();
                horizontalLayout->addWidget(board3,1,1);
            }
            setProperSizes();
        }
    }

}
