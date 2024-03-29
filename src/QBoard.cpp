/**
* @file     QBoard.cpp
* @brief    view of one game
* @author   Katarina Gresova xgreso00
*/

#include <QtWidgets>
#include "QSolitaire.h"
#include "QBoard.h"

/**
 * @brief QBoard::QBoard    QBoard constructor
 * @param parent            parent widget
 * @param board             board to create games from
 * @param s                 parent window
 */
QBoard::QBoard(QWidget *parent, Board * board, QMainWindow *s)
    : QFrame(parent)
{
    p = s;
    b = board;

    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    layout = new QVBoxLayout();
    setLayout(layout);
}

/**
 * @brief QBoard::~QBoard   object destructor
 */
QBoard::~QBoard()
{
}

/**
 * @brief QBoard::setup creates all object and paints board
 */
void QBoard::setup()
{
    createObjects();
    connectSignals();
    repaint();
}

/**
 * @brief QBoard::dragEnterEvent    setup for drag enter event
 * @param event                     drag enter event
 */
void QBoard::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

/**
 * @brief QBoard::dragMoveEvent setup for drag move event
 * @param event                 drag move event
 */
void QBoard::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

/**
 * @brief QBoard::dropEvent handles card drop event
 * @param event             drop event
 */
void QBoard::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
        if (!child)
            return;

        QString name = child->objectName();
        QString sourceName = source->objectName();
        //move from waste
        if (sourceName.compare("waste") == 0) {
            //move to some target
            if (name.compare("target0") == 0) {
                game->move_card_from_waste_deck_to_target_deck(0);
            } else if (name.compare("target1") == 0) {
                game->move_card_from_waste_deck_to_target_deck(1);
            } else if (name.compare("target2") == 0) {
                game->move_card_from_waste_deck_to_target_deck(2);
            } else if (name.compare("target3") == 0) {
                game->move_card_from_waste_deck_to_target_deck(3);
            //move to some working
            } else {
                int indexW = -1;
                if (child->parent()->objectName().compare("working0") == 0) {
                    indexW = 0;
                } else if (child->parent()->objectName().compare("working1") == 0) {
                    indexW = 1;
                } else if (child->parent()->objectName().compare("working2") == 0) {
                    indexW = 2;
                } else if (child->parent()->objectName().compare("working3") == 0) {
                    indexW = 3;
                } else if (child->parent()->objectName().compare("working4") == 0) {
                    indexW = 4;
                } else if (child->parent()->objectName().compare("working5") == 0) {
                    indexW = 5;
                } else if (child->parent()->objectName().compare("working6") == 0) {
                    indexW = 6;
                }
                if (indexW > -1) {
                    game->move_card_from_waste_deck_to_working_stack(indexW);
                }
            }
        } else {
            int target = -1;
            if (sourceName.compare("target0") == 0) {
                target = 0;
            } else if (sourceName.compare("target1") == 0) {
                target = 1;
            } else if (sourceName.compare("target2") == 0) {
                target = 2;
            } else if (sourceName.compare("target3") == 0) {
                target = 3;
            }
            if (target > -1) {
                //move from some target
                int indexW = -1;
                if (child->parent()->objectName().compare("working0") == 0) {
                    indexW = 0;
                } else if (child->parent()->objectName().compare("working1") == 0) {
                    indexW = 1;
                } else if (child->parent()->objectName().compare("working2") == 0) {
                    indexW = 2;
                } else if (child->parent()->objectName().compare("working3") == 0) {
                    indexW = 3;
                } else if (child->parent()->objectName().compare("working4") == 0) {
                    indexW = 4;
                } else if (child->parent()->objectName().compare("working5") == 0) {
                    indexW = 5;
                } else if (child->parent()->objectName().compare("working6") == 0) {
                    indexW = 6;
                }
                if (indexW > -1) {
                    //move to some working
                    game->move_card_from_target_deck_to_working_stack(target, indexW);
                }
            } else {
                int indexW = -1;
                if (source->parent()->objectName().compare("working0") == 0) {
                    indexW = 0;
                } else if (source->parent()->objectName().compare("working1") == 0) {
                    indexW = 1;
                } else if (source->parent()->objectName().compare("working2") == 0) {
                    indexW = 2;
                } else if (source->parent()->objectName().compare("working3") == 0) {
                    indexW = 3;
                } else if (source->parent()->objectName().compare("working4") == 0) {
                    indexW = 4;
                } else if (source->parent()->objectName().compare("working5") == 0) {
                    indexW = 5;
                } else if (source->parent()->objectName().compare("working6") == 0) {
                    indexW = 6;
                }
                //move from some working
                if (indexW > -1) {
                    //check, if move to some target
                    if (name.compare("target0") == 0) {
                        game->move_card_from_working_stack_to_target_deck(indexW,0);
                    } else if (name.compare("target1") == 0) {
                        game->move_card_from_working_stack_to_target_deck(indexW,1);
                    } else if (name.compare("target2") == 0) {
                        game->move_card_from_working_stack_to_target_deck(indexW,2);
                    } else if (name.compare("target3") == 0) {
                        game->move_card_from_working_stack_to_target_deck(indexW,3);
                    //no move to target
                    } else {
                        int indexW2 = -1;
                        if (child->parent()->objectName().compare("working0") == 0) {
                            indexW2 = 0;
                        } else if (child->parent()->objectName().compare("working1") == 0) {
                            indexW2 = 1;
                        } else if (child->parent()->objectName().compare("working2") == 0) {
                            indexW2 = 2;
                        } else if (child->parent()->objectName().compare("working3") == 0) {
                            indexW2 = 3;
                        } else if (child->parent()->objectName().compare("working4") == 0) {
                            indexW2 = 4;
                        } else if (child->parent()->objectName().compare("working5") == 0) {
                            indexW2 = 5;
                        } else if (child->parent()->objectName().compare("working6") == 0) {
                            indexW2 = 6;
                        }
                        if (indexW2 > -1) {
                            //move to some working
                            QVector<QLabel*> *w = working.at(indexW);
                            int indexC = w->indexOf(source);
                            game->move_cards_from_working_stack_to_working_stack(indexW,indexW2,indexC);
                        }
                    }
                }
            }
        }
        repaint();

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

/**
 * @brief QBoard::mousePressEvent   handles start of card move
 * @param event                     mouse pressed event
 */
void QBoard::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    source = child;
    if (!child->isEnabled())
        return;

    //only labels are movable
    if (strcmp(child->metaObject()->className(), "QLabel") != 0)
        return;

    QPixmap pixmap = *child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QWidget *parent = child->parentWidget();

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos() - parent->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}


/**
 * @brief QBoard::connectSignals    connects slost and signals
 */
void QBoard::connectSignals()
{
    connect(saveB, SIGNAL (released()), this, SLOT (save()));
    connect(undoB, SIGNAL (released()), this, SLOT (undo()));
    connect(hint, SIGNAL (released()), this, SLOT (on_hint_clicked()));
    connect(stock, SIGNAL (released()), this, SLOT (handleStockDeck()));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
}

/**
 * @brief QBoard::repaint      repaints whole board
 */
void QBoard::repaint()
{
    CardDeck *deck = game->get_stock_deck();
    Card *card;
    if (deck != NULL)
    {
        card = deck->get();

        if (card != NULL)
        {
            QPixmap pixmap(":/images/back.svg");
            QIcon ButtonIcon(pixmap);
            stock->setIcon(ButtonIcon);
        }
        else
        {
            QPixmap pixmap(":/images/empty.png");
            QIcon ButtonIcon(pixmap);
            stock->setIcon(ButtonIcon);
            stock->setIconSize(pixmap.size());
        }
    }
    deck = game->get_waste_deck();
    if (deck != NULL)
    {
        card = deck->get();

        if (card != NULL)
        {
            waste->setPixmap(QPixmap(":/images/" + QString::fromStdString(card->to_string()) + ".svg"));
            waste->show();
            waste->setAttribute(Qt::WA_DeleteOnClose);
            waste->setEnabled(true);
        }
        else
        {
            waste->setPixmap(QPixmap(":/images/empty.png"));
            waste->setEnabled(false);
        }
    }
    deck = game->get_target_deck_by_id(0);
    if (deck != NULL)
    {
        card = deck->get();
        if (card != NULL) {
            target0->setPixmap(QPixmap(":/images/" + QString::fromStdString(card->to_string()) + ".svg"));
            target0->show();
            target0->setAttribute(Qt::WA_DeleteOnClose);
            target0->setEnabled(true);
        }
        else
        {
            target0->setPixmap(QPixmap(":/images/empty.png"));
            target0->setEnabled(false);
        }
    }
    deck = game->get_target_deck_by_id(1);
    if (deck != NULL)
    {
        card = deck->get();
        if (card != NULL) {
            target1->setPixmap(QPixmap(":/images/" + QString::fromStdString(card->to_string()) + ".svg"));
            target1->show();
            target1->setAttribute(Qt::WA_DeleteOnClose);
            target1->setEnabled(true);
        }
        else
        {
            target1->setPixmap(QPixmap(":/images/empty.png"));
            target1->setEnabled(false);
        }
    }
    deck = game->get_target_deck_by_id(2);
    if (deck != NULL)
    {
        card = deck->get();
        if (card != NULL) {
            target2->setPixmap(QPixmap(":/images/" + QString::fromStdString(card->to_string()) + ".svg"));
            target2->show();
            target2->setAttribute(Qt::WA_DeleteOnClose);
            target2->setEnabled(true);
        }
        else
        {
            target2->setPixmap(QPixmap(":/images/empty.png"));
            target2->setEnabled(false);
        }
    }
    deck = game->get_target_deck_by_id(3);
    if (deck != NULL)
    {
        card = deck->get();
        if (card != NULL) {
            target3->setPixmap(QPixmap(":/images/" + QString::fromStdString(card->to_string()) + ".svg"));
            target3->show();
            target3->setAttribute(Qt::WA_DeleteOnClose);
            target3->setEnabled(true);
        }
        else
        {
            target3->setPixmap(QPixmap(":/images/empty.png"));
            target3->setEnabled(false);
        }
    }
    for (int j = 0; j < 7; j++) {
        CardStack *stack = game->get_working_stack_by_id(j);
        QVector<QLabel*> *w = working.at(j);
        if (stack->is_empty()){
            QLabel *label = w->at(0);
            label->setPixmap(QPixmap(":/images/empty.png"));
            label->setEnabled(false);
            for (int i = 1; i < 13 + j; i++) {
                QLabel *label = w->at(i);
                label->setPixmap(QPixmap());
                label->setEnabled(false);
            }
        } else {
            int count = stack->get_size();
            for (int i = 0; i < count; i++) {
                card = stack->get(i);
                QLabel *label = w->at(i);
                label->move(0,i*15);
                if (card->is_turned_face_up()) {
                    label->setEnabled(true);
                    label->setPixmap(QPixmap(":/images/" + QString::fromStdString(card->to_string()) + ".svg"));
                } else {
                    label->setEnabled(false);
                    label->setPixmap(QPixmap(":/images/back.svg"));
                }
                label->setVisible(true);
            }
            for (int i = count; i < 13 + j; i++) {
                QLabel *label = w->at(i);
                label->setPixmap(QPixmap());
                label->setEnabled(false);
                label->setVisible(false);
            }
        }
    }
    moves->setText("Moves: " + QString::number(game->get_moves_count()));
    score->setText("Score: " + QString::number(game->get_score()));

    if (game->is_won()) {
        int t = game->get_total_time_in_seconds().count();
        QTime ti(0,0);
        ti = ti.addSecs(t);
        QString text = ti.toString("mm:ss");
        disconnect(timer, SIGNAL(timeout()), 0, 0);
        QMessageBox::information(this, tr("You won!"), "Score: " +  QString::number(game->get_score()) + "\nMoves: " + QString::number(game->get_moves_count()) + "\nTime: " + text);
    }
}

/**
 * @brief QBoard::save  creates save window and allows to save current game to file
 */
void QBoard::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Game to File"));
    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        } else {
            game->save(fileName.toStdString());
        }
    }
}

/**
 * @brief QBoard::undo  launch undo functionality
 */
void QBoard::undo()
{
    game->undo();
    repaint();
}

/**
 * @brief QBoard::on_hint_clicked   creates window with hints
 */
void QBoard::on_hint_clicked()
{
    std::vector<Move> moves = MoveFinder::get_available_moves(game);
    std::string hints;
    for (unsigned int i = 0; i < moves.size(); ++i) {
            Move move = moves[i];
            switch (move.get_move_type()) {
            case STOCK_DECK_TO_WASTE_DECK:
                    hints += "Take card from stock deck to waste deck.\n";
                    break;
            case WASTE_DECK_TO_TARGET_DECK:
                    hints += "Take card from waste deck to " + std::to_string(move.get_destination_index() + 1)  + ". target deck.\n";
                    break;
            case WASTE_DECK_TO_WORKING_STACK:
                    hints += "Take card from waste deck to " + std::to_string(move.get_destination_index() + 1) + ". working pack.\n";
                    break;
            case TARGET_DECK_TO_WORKING_STACK:
                    hints += "Take card from " + std::to_string(move.get_source_index() + 1) + ". target deck to " + std::to_string(move.get_destination_index() + 1) + ". working stack.\n";
                    break;
            case WORKING_STACK_TO_TARGET_DECK:
                    hints += "Take card from " + std::to_string(move.get_source_index() + 1) + ". working stack to " + std::to_string(move.get_destination_index() + 1) + ". target deck.\n";
                    break;
            case WORKING_STACK_TO_WORKING_STACK:
                    hints += "Take card from " + std::to_string(move.get_source_index() + 1) + ". working stack to " + std::to_string(move.get_destination_index() + 1) + ". working stack since " + std::to_string(move.get_card_index() + 1) + ". card.\n";
                    break;
            }
    }

    QMessageBox::information(this, tr("Hints"), hints.c_str());
}

/**
 * @brief QBoard::handleStockDeck   handles click on stock deck
 */
void QBoard::handleStockDeck()
{
    game->move_card_from_stock_deck_to_waste_deck();
    repaint();
}

/**
 * @brief QBoard::showTime  shows current time from game
 */
void QBoard::showTime()
{
    int t = game->get_total_time_in_seconds().count();
    QTime ti(0,0);
    ti = ti.addSecs(t);
    QString text = ti.toString("mm:ss");
    time->setText(text);
}

/**
 * @brief QBoard::setBigSize    resizes all components to bigger version
 */
void QBoard::setBigSize()
{
    this->setFixedSize(900,530);
    stock->setFixedSize(75,110);
    stock->setIconSize(QSize(75,110));
    waste->setFixedSize(75,110);
    waste->setScaledContents(true);
    target0->setFixedSize(75,110);
    target0->setScaledContents(true);
    target1->setFixedSize(75,110);
    target1->setScaledContents(true);
    target2->setFixedSize(75,110);
    target2->setScaledContents(true);
    target3->setFixedSize(75,110);
    target3->setScaledContents(true);
    for (int j = 0; j < 7; j++) {
        QVector<QLabel*> *w = working.at(j);
        for (int i = 0; i < 13 + j; i++) {
            QLabel *label = w->at(i);
            label->setFixedSize(75,110);
            label->setScaledContents(true);
         }
     }

}

/**
 * @brief QBoard::setSmallSize  resizes all components to smaller version
 */
void QBoard::setSmallSize()
{
    this->setFixedSize(550,320);
    stock->setFixedSize(40,70);
    stock->setIconSize(QSize(40,70));
    waste->setFixedSize(40,70);
    waste->setScaledContents(true);
    target0->setFixedSize(40,70);
    target0->setScaledContents(true);
    target1->setFixedSize(40,70);
    target1->setScaledContents(true);
    target2->setFixedSize(40,70);
    target2->setScaledContents(true);
    target3->setFixedSize(40,70);
    target3->setScaledContents(true);
    for (int j = 0; j < 7; j++) {
        QVector<QLabel*> *w = working.at(j);
        for (int i = 0; i < 13 + j; i++) {
            QLabel *label = w->at(i);
            label->setFixedSize(40,70);
            label->setScaledContents(true);
         }
     }

}

/**
 * @brief QBoard::removeGame    handles removing of current game
 */
void QBoard::removeGame()
{
    ((QSolitaire*)p)->removeGame(this);
    this->close();
    b->cancel_game(this->game);
}

/**
 * @brief QBoard::createObjects creates all objects on board
 */
void QBoard::createObjects()
{

    //top menu with buttons and info
    menu = new QHBoxLayout();
    layout->addLayout(menu);
    saveB = new QPushButton("Save Game");
    menu->addWidget(saveB);
    undoB = new QPushButton("Undo");
    menu->addWidget(undoB);
    hint = new QPushButton("Hint");
    menu->addWidget(hint);
    endGame = new QPushButton("End Game");
    connect(endGame, SIGNAL (released()), this, SLOT (removeGame()));
    menu->addWidget(endGame);
    moves = new QPushButton();
    moves->setStyleSheet("border-width: 3px; border-radius: 5px");
    moves->setEnabled(false);
    menu->addWidget(moves);
    score = new QPushButton();
    score->setStyleSheet("border-width: 3px; border-radius: 5px");
    score->setEnabled(false);
    menu->addWidget(score);
    time = new QPushButton();
    time->setStyleSheet("border-width: 3px; border-radius: 5px");
    time->setEnabled(false);
    menu->addWidget(time);

    //layout for everything else then top menu
    cards = new QHBoxLayout();
    layout->addLayout(cards);

    //decks on left
    left = new QVBoxLayout();
    cards->addLayout(left,1);
    QLabel *glue = new QLabel();
    glue->setPixmap(QPixmap());
    left->addWidget(glue);
    stockQ = new QWidget;
    stock = new QPushButton(stockQ);
    stock->setStyleSheet("border-width: 3px; border-radius: 5px");
    left->addWidget(stockQ);
    wasteQ = new QWidget;
    waste = new QLabel(wasteQ);
    waste->setObjectName("waste");
    left->addWidget(wasteQ);
    QLabel *glue2 = new QLabel();
    glue2->setPixmap(QPixmap());
    left->addWidget(glue2);

    //for all working stacks
    bottom = new QHBoxLayout();
    cards->addLayout(bottom,6);

    working0 = new QWidget();
    bottom->addWidget(working0);
    working0->setObjectName("working0");
    bottom->addWidget(working0);
    for (int i = 0; i < 13; i++) {
        working0v.append(new QLabel(working0));
    }
    working.append(&working0v);

    working1 = new QWidget();
    bottom->addWidget(working1);
    working1->setObjectName("working1");
    bottom->addWidget(working1);
    for (int i = 0; i < 14; i++) {
        working1v.append(new QLabel(working1));
    }
    working.append(&working1v);

    working2 = new QWidget(this);
    working2->setObjectName("working2");
    bottom->addWidget(working2);
    for (int i = 0; i < 15; i++) {
        working2v.append(new QLabel(working2));
    }
    working.append(&working2v);

    working3 = new QWidget(this);
    working3->setObjectName("working3");
    bottom->addWidget(working3);
    for (int i = 0; i < 16; i++) {
        working3v.append(new QLabel(working3));
    }
    working.append(&working3v);

    working4 = new QWidget(this);
    working4->setObjectName("working4");
    bottom->addWidget(working4);
    for (int i = 0; i < 17; i++) {
        working4v.append(new QLabel(working4));
    }
    working.append(&working4v);

    working5 = new QWidget(this);
    working5->setObjectName("working5");
    bottom->addWidget(working5);
    for (int i = 0; i < 18; i++) {
        working5v.append(new QLabel(working5));
    }
    working.append(&working5v);

    working6 = new QWidget(this);
    working6->setObjectName("working6");
    bottom->addWidget(working6);
    for (int i = 0; i < 19; i++) {
        working6v.append(new QLabel(working6));
    }
    working.append(&working6v);

    //target decks
    right = new QVBoxLayout();
    cards->addLayout(right,1);
    QWidget *target0Q = new QWidget;
    target0 = new QLabel(target0Q);
    target0->setObjectName("target0");
    right->addWidget(target0Q);
    QWidget *target1Q = new QWidget;
    target1 = new QLabel(target1Q);
    target1->setObjectName("target1");
    right->addWidget(target1Q);
    QWidget *target2Q = new QWidget;
    target2 = new QLabel(target2Q);
    target2->setObjectName("target2");
    right->addWidget(target2Q);
    QWidget *target3Q = new QWidget;
    target3 = new QLabel(target3Q);
    target3->setObjectName("target3");
    right->addWidget(target3Q);
}
