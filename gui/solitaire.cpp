#include "solitaire.h"
#include "ui_solitaire.h"
#include <string>
#include <iostream>
#include "../game.h"
#include "../board.h"
#include "../card.h"
#include "../card_deck.h"

#define BOOL_STR(b) ((b)?"true":"false")

Solitaire::Solitaire(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Solitaire)
{
    ui->setupUi(this);



    createGame();
}

Solitaire::~Solitaire()
{
    delete ui;
}

void Solitaire::createGame()
{
    main = new Board;
    game = main->create_new_game();
    game->start();

    paintCards();

    connect(ui->stock_deck, SIGNAL (released()), this, SLOT (handleStockDeck()));
    connect(ui->waste_deck, SIGNAL (released()), this, SLOT (handleWasteDeck()));
    connect(ui->target_deck_1, SIGNAL (released()), this, SLOT (handleTargetDeck1()));
    connect(ui->target_deck_2, SIGNAL (released()), this, SLOT (handleTargetDeck2()));
    connect(ui->target_deck_3, SIGNAL (released()), this, SLOT (handleTargetDeck3()));
    connect(ui->target_deck_4, SIGNAL (released()), this, SLOT (handleTargetDeck4()));
}

void Solitaire::handleStockDeck()
{
    wasteClicked = false;
    targetClicked = -1;
    workingCardClicked = -1;
    workingStackClicked = -1;
    game->move_card_from_stock_deck_to_waste_deck();
    paintCards();
}

void Solitaire::paintCards()
{
    CardDeck *deck = game->get_stock_deck();
    Card *card;
    if (deck != NULL)
    {
        card = deck->get();

        if (card != NULL)
        {
            QPixmap pixmap("../images/back.svg");
            QIcon ButtonIcon(pixmap);
            ui->stock_deck->setIcon(ButtonIcon);
            ui->stock_deck->setIconSize(QSize(ui->stock_deck->size().width(), ui->stock_deck->size().height()));
        }
        else
        {
            ui->stock_deck->setIcon(QIcon());
        }
    }

    deck = game->get_waste_deck();
    if (deck != NULL)
    {
        card = deck->get();
        if (card != NULL) {
            QPixmap pixmap("../images/" + QString::fromStdString(card->to_string()) + ".svg");
            QIcon ButtonIcon(pixmap);
            ui->waste_deck->setIcon(ButtonIcon);
            ui->waste_deck->setIconSize(ui->waste_deck->size());
        }
        else
        {
            ui->waste_deck->setIcon(QIcon());
        }
    }

    deck = game->get_target_deck_by_id(0);
    if (deck != NULL)
    {
        card = deck->get();
        if (card != NULL) {
            QPixmap pixmap("../images/" + QString::fromStdString(card->to_string()) + ".svg");
            QIcon ButtonIcon(pixmap);
            ui->target_deck_1->setIcon(ButtonIcon);
            ui->target_deck_1->setIconSize(ui->target_deck_1->size());
        }
        else
        {
            ui->target_deck_1->setIcon(QIcon());
        }
    }

    deck = game->get_target_deck_by_id(1);
    if (deck != NULL)
    {
        card = deck->get();
        if (card != NULL) {
            QPixmap pixmap("../images/" + QString::fromStdString(card->to_string()) + ".svg");
            QIcon ButtonIcon(pixmap);
            ui->target_deck_2->setIcon(ButtonIcon);
            ui->target_deck_2->setIconSize(ui->target_deck_2->size());
        }
        else
        {
            ui->target_deck_2->setIcon(QIcon());
        }
    }

    deck = game->get_target_deck_by_id(2);
    if (deck != NULL)
    {
        card = deck->get();
        if (card != NULL) {
            QPixmap pixmap("../images/" + QString::fromStdString(card->to_string()) + ".svg");
            QIcon ButtonIcon(pixmap);
            ui->target_deck_3->setIcon(ButtonIcon);
            ui->target_deck_3->setIconSize(ui->target_deck_3->size());
        }
        else
        {
            ui->target_deck_3->setIcon(QIcon());
        }
    }

    deck = game->get_target_deck_by_id(3);
    if (deck != NULL)
    {
        card = deck->get();
        if (card != NULL) {
            QPixmap pixmap("../images/" + QString::fromStdString(card->to_string()) + ".svg");
            QIcon ButtonIcon(pixmap);
            ui->target_deck_4->setIcon(ButtonIcon);
            ui->target_deck_4->setIconSize(ui->target_deck_4->size());
        }
        else
        {
            ui->target_deck_4->setIcon(QIcon());
        }
    }
}

void Solitaire::handleWasteDeck()
{
    wasteClicked = !wasteClicked;
}

//TODO: dovoli mi vratit kartu z target decku na waste deck. je to ok?
void Solitaire::handleTargetDeck1()
{
    if (wasteClicked) {
        game->move_card_from_waste_deck_to_target_deck(0);
        wasteClicked = false;
    } else if (workingStackClicked > -1 && workingCardClicked == 1) { //ze je kliknuta len ta prva karta, este doriesim
        game->move_card_from_working_stack_to_target_deck(workingStackClicked, 0);
        workingCardClicked = -1;
        workingStackClicked = -1;
    } else {
        targetClicked = -1;
    }

    paintCards();
}

void Solitaire::handleTargetDeck2()
{
    if (wasteClicked) {
        game->move_card_from_waste_deck_to_target_deck(1);
        wasteClicked = false;
    } else if (workingStackClicked > -1 && workingCardClicked == 1) {
        game->move_card_from_working_stack_to_target_deck(workingStackClicked, 0);
        workingCardClicked = -1;
        workingStackClicked = -1;
    } else {
        targetClicked = -1;
    }

    paintCards();
}

void Solitaire::handleTargetDeck3()
{
    if (wasteClicked) {
        game->move_card_from_waste_deck_to_target_deck(2);
        wasteClicked = false;
    } else if (workingStackClicked > -1 && workingCardClicked == 1) {
        game->move_card_from_working_stack_to_target_deck(workingStackClicked, 0);
        workingCardClicked = -1;
        workingStackClicked = -1;
    } else {
        targetClicked = -1;
    }

    paintCards();
}

void Solitaire::handleTargetDeck4()
{
    if (wasteClicked) {
        game->move_card_from_waste_deck_to_target_deck(3);
        wasteClicked = false;
    } else if (workingStackClicked > -1 && workingCardClicked == 1) {
        game->move_card_from_working_stack_to_target_deck(workingStackClicked, 0);
        workingCardClicked = -1;
        workingStackClicked = -1;
    } else {
        targetClicked = -1;
    }

    paintCards();
}


