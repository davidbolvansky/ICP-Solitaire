/********************************************************************************
** Form generated from reading UI file 'solitaire.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOLITAIRE_H
#define UI_SOLITAIRE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Solitaire
{
public:
    QWidget *centralWidget;
    QPushButton *stock_deck;
    QPushButton *waste_deck;
    QPushButton *target_deck_2;
    QPushButton *target_deck_3;
    QPushButton *target_deck_4;
    QPushButton *target_deck_1;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Solitaire)
    {
        if (Solitaire->objectName().isEmpty())
            Solitaire->setObjectName(QStringLiteral("Solitaire"));
        Solitaire->resize(627, 457);
        Solitaire->setStyleSheet(QStringLiteral("background-color: rgb(78, 154, 6);"));
        centralWidget = new QWidget(Solitaire);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stock_deck = new QPushButton(centralWidget);
        stock_deck->setObjectName(QStringLiteral("stock_deck"));
        stock_deck->setGeometry(QRect(10, 10, 75, 110));
        stock_deck->setCursor(QCursor(Qt::PointingHandCursor));
        stock_deck->setStyleSheet(QStringLiteral("border-style: outset; border-width: 3px; border-color: yellow; border-radius: 5px"));
        stock_deck->setFlat(false);
        waste_deck = new QPushButton(centralWidget);
        waste_deck->setObjectName(QStringLiteral("waste_deck"));
        waste_deck->setGeometry(QRect(100, 10, 75, 110));
        waste_deck->setCursor(QCursor(Qt::PointingHandCursor));
        waste_deck->setMouseTracking(false);
        waste_deck->setFocusPolicy(Qt::StrongFocus);
        waste_deck->setStyleSheet(QStringLiteral("border-style: outset; border-width: 3px; border-color: yellow; border-radius: 5px"));
        waste_deck->setCheckable(false);
        waste_deck->setAutoDefault(false);
        waste_deck->setFlat(false);
        target_deck_2 = new QPushButton(centralWidget);
        target_deck_2->setObjectName(QStringLiteral("target_deck_2"));
        target_deck_2->setGeometry(QRect(350, 10, 75, 110));
        target_deck_2->setCursor(QCursor(Qt::PointingHandCursor));
        target_deck_2->setMouseTracking(false);
        target_deck_2->setFocusPolicy(Qt::StrongFocus);
        target_deck_2->setStyleSheet(QStringLiteral("border-style: outset; border-width: 3px; border-color: yellow; border-radius: 5px"));
        target_deck_2->setCheckable(false);
        target_deck_2->setAutoDefault(false);
        target_deck_2->setFlat(false);
        target_deck_3 = new QPushButton(centralWidget);
        target_deck_3->setObjectName(QStringLiteral("target_deck_3"));
        target_deck_3->setGeometry(QRect(440, 10, 75, 110));
        target_deck_3->setCursor(QCursor(Qt::PointingHandCursor));
        target_deck_3->setMouseTracking(false);
        target_deck_3->setFocusPolicy(Qt::StrongFocus);
        target_deck_3->setStyleSheet(QStringLiteral("border-style: outset; border-width: 3px; border-color: yellow; border-radius: 5px"));
        target_deck_3->setCheckable(false);
        target_deck_3->setAutoDefault(false);
        target_deck_3->setFlat(false);
        target_deck_4 = new QPushButton(centralWidget);
        target_deck_4->setObjectName(QStringLiteral("target_deck_4"));
        target_deck_4->setGeometry(QRect(530, 10, 75, 110));
        target_deck_4->setCursor(QCursor(Qt::PointingHandCursor));
        target_deck_4->setMouseTracking(false);
        target_deck_4->setFocusPolicy(Qt::StrongFocus);
        target_deck_4->setStyleSheet(QStringLiteral("border-style: outset; border-width: 3px; border-color: yellow; border-radius: 5px"));
        target_deck_4->setCheckable(false);
        target_deck_4->setAutoDefault(false);
        target_deck_4->setFlat(false);
        target_deck_1 = new QPushButton(centralWidget);
        target_deck_1->setObjectName(QStringLiteral("target_deck_1"));
        target_deck_1->setGeometry(QRect(260, 10, 75, 110));
        target_deck_1->setCursor(QCursor(Qt::PointingHandCursor));
        target_deck_1->setMouseTracking(false);
        target_deck_1->setFocusPolicy(Qt::StrongFocus);
        target_deck_1->setStyleSheet(QStringLiteral("border-style: outset; border-width: 3px; border-color: yellow; border-radius: 5px"));
        target_deck_1->setCheckable(false);
        target_deck_1->setAutoDefault(false);
        target_deck_1->setFlat(false);
        Solitaire->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Solitaire);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Solitaire->setStatusBar(statusBar);

        retranslateUi(Solitaire);

        waste_deck->setDefault(false);
        target_deck_2->setDefault(false);
        target_deck_3->setDefault(false);
        target_deck_4->setDefault(false);
        target_deck_1->setDefault(false);


        QMetaObject::connectSlotsByName(Solitaire);
    } // setupUi

    void retranslateUi(QMainWindow *Solitaire)
    {
        Solitaire->setWindowTitle(QApplication::translate("Solitaire", "Solitaire", Q_NULLPTR));
        stock_deck->setText(QString());
        waste_deck->setText(QString());
        target_deck_2->setText(QString());
        target_deck_3->setText(QString());
        target_deck_4->setText(QString());
        target_deck_1->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Solitaire: public Ui_Solitaire {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOLITAIRE_H
