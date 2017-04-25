/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include "QSolitaire.h"
#include "QBoard.h"

QBoard::QBoard(QWidget *parent, Board * board, QMainWindow *s)
    : QFrame(parent)
{
    p = s;
    b = board;

    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);
    layout = new QVBoxLayout();
    setLayout(layout);

    game = board->create_new_game();
    game->start();

    createObjects();
    connectSignals();
    repaint();

}

QBoard::~QBoard()
{

}

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
        //presun z waste
        if (sourceName.compare("waste") == 0) {
            //na niektory target
            if (name.compare("target0") == 0) {
                game->move_card_from_waste_deck_to_target_deck(0);
            } else if (name.compare("target1") == 0) {
                game->move_card_from_waste_deck_to_target_deck(1);
            } else if (name.compare("target2") == 0) {
                game->move_card_from_waste_deck_to_target_deck(2);
            } else if (name.compare("target3") == 0) {
                game->move_card_from_waste_deck_to_target_deck(3);
            //na niektory working
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
                //zdroj bol niektory working
                if (indexW > -1) {
                    //zostenie, ci ciel je niektory target
                    if (name.compare("target0") == 0) {
                        game->move_card_from_working_stack_to_target_deck(indexW,0);
                    } else if (name.compare("target1") == 0) {
                        game->move_card_from_working_stack_to_target_deck(indexW,1);
                    } else if (name.compare("target2") == 0) {
                        game->move_card_from_working_stack_to_target_deck(indexW,2);
                    } else if (name.compare("target3") == 0) {
                        game->move_card_from_working_stack_to_target_deck(indexW,3);
                    //ciel nie je target.
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

void QBoard::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    source = child;
    if (!child->isEnabled())
        return;

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



void QBoard::connectSignals()
{
    connect(saveB, SIGNAL (released()), this, SLOT (save()));
    connect(loadB, SIGNAL (released()), this, SLOT (load()));
    connect(undoB, SIGNAL (released()), this, SLOT (undo()));
    connect(hint, SIGNAL (released()), this, SLOT (on_hint_clicked()));
    connect(stock, SIGNAL (released()), this, SLOT (handleStockDeck()));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
}

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
}

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

void QBoard::load()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Address Book"));
    if (fileName.isEmpty())
        return;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        game = game->load(fileName.toStdString());
        repaint();
    }

}

void QBoard::undo()
{
    game->undo();
    repaint();
}

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

    if (hints.empty()) {
        hints = "Game is lost, no possible moves.\n";
    }

    QMessageBox::information(this, tr("Hints"), hints.c_str());
}


void QBoard::handleStockDeck()
{
    game->move_card_from_stock_deck_to_waste_deck();
    repaint();
}

void QBoard::showTime()
{
    int t = game->get_total_time_in_seconds().count();
    QTime ti(0,0);
    ti = ti.addSecs(t);
    QString text = ti.toString("mm:ss");
    time->setText(text);
}

void QBoard::setBigSize()
{
    this->setFixedSize(900,520);
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

void QBoard::setSmallSize()
{
    this->setFixedSize(550,320);
    stock->setFixedSize(40,70);
    stock->setIconSize(QSize(40,70));
    waste->setMaximumSize(40,70);
    waste->setScaledContents(true);
    target0->setMaximumSize(40,70);
    target0->setScaledContents(true);
    target1->setMaximumSize(40,70);
    target1->setScaledContents(true);
    target2->setMaximumSize(40,70);
    target2->setScaledContents(true);
    target3->setMaximumSize(40,70);
    target3->setScaledContents(true);
    for (int j = 0; j < 7; j++) {
        QVector<QLabel*> *w = working.at(j);
        for (int i = 0; i < 13 + j; i++) {
            QLabel *label = w->at(i);
            label->setMaximumSize(40,70);
            label->setScaledContents(true);
         }
     }

}


void QBoard::removeGame()
{
    ((QSolitaire*)p)->removeGame(this);
    this->close();
    b->cancel_game(this->game);
}

void QBoard::createObjects()
{
    menu = new QHBoxLayout();
    layout->addLayout(menu);
    saveB = new QPushButton("Save Game");
    menu->addWidget(saveB);
    loadB = new QPushButton("Load Game");
    menu->addWidget(loadB);
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

    cards = new QHBoxLayout();
    layout->addLayout(cards);

    left = new QVBoxLayout();
    cards->addLayout(left,1);
    left->addWidget(new QLabel());
    stockQ = new QWidget;
    stock = new QPushButton(stockQ);
    stock->setStyleSheet("border-width: 3px; border-radius: 5px");
    left->addWidget(stockQ);
    wasteQ = new QWidget;
    waste = new QLabel(wasteQ);
    waste->setObjectName("waste");
    left->addWidget(wasteQ);
    left->addWidget(new QLabel());

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
