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

/**
* @file QBoard.h
* @brief view of one game
* @author Katarina Gresova xgreso00
*/

#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>
#include <QLabel>
#include <QLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVector>
#include <QMainWindow>
#include "./game.h"
#include "./board.h"

class QDragEnterEvent;
class QDropEvent;

class QBoard : public QFrame
{
    Q_OBJECT

public:
    QBoard(QWidget *parent = 0, Board * board = nullptr, QMainWindow *s = 0);
    ~QBoard();
    void setBigSize();
    void setSmallSize();
    void setup();
    Game *game;

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void createObjects();
    void connectSignals();
    void repaint();

private:
    QMainWindow *p;
    QBoard *main;
    QLabel *source;
    QVBoxLayout *layout;

    QHBoxLayout *menu;
    QPushButton *saveB;
    QPushButton *undoB;
    QPushButton *hint;
    QPushButton *score;
    QPushButton *moves;
    QPushButton *time;
    QPushButton *endGame;

    QHBoxLayout *cards;
    QVBoxLayout *left;
    QVBoxLayout *right;
    QWidget *stockQ;
    QPushButton *stock;
    QWidget *wasteQ;
    QLabel *waste;
    QLabel *target0;
    QLabel *target1;
    QLabel *target2;
    QLabel *target3;

    QHBoxLayout *bottom;
    QVector<QVector<QLabel*>*> working;
    QVector<QLabel*> working0v;
    QVector<QLabel*> working1v;
    QVector<QLabel*> working2v;
    QVector<QLabel*> working3v;
    QVector<QLabel*> working4v;
    QVector<QLabel*> working5v;
    QVector<QLabel*> working6v;

    QWidget *working0;
    QWidget *working1;
    QWidget *working2;
    QWidget *working3;
    QWidget *working4;
    QWidget *working5;
    QWidget *working6;

    Board *b;

private slots:
    void save();
    void undo();
    void on_hint_clicked();
    void handleStockDeck();
    void showTime();
    void removeGame();

};

#endif // DRAGWIDGET_H
