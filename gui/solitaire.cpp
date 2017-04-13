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
    resetSelection();

    connect(ui->save, SIGNAL (released()), this, SLOT (save()));

    connect(ui->stock_deck, SIGNAL (released()), this, SLOT (handleStockDeck()));
    connect(ui->waste_deck, SIGNAL (released()), this, SLOT (handleWasteDeck()));
    connect(ui->target_deck_1, SIGNAL (released()), this, SLOT (handleTargetDeck1()));
    connect(ui->target_deck_2, SIGNAL (released()), this, SLOT (handleTargetDeck2()));
    connect(ui->target_deck_3, SIGNAL (released()), this, SLOT (handleTargetDeck3()));
    connect(ui->target_deck_4, SIGNAL (released()), this, SLOT (handleTargetDeck4()));

    connect(ui->working0_0, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working0_1, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working0_2, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working0_3, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working0_4, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working0_5, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working0_6, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working0_7, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working0_8, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working0_9, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working0_10, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working0_11, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working0_12, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working1_0, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working1_1, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working1_2, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working1_3, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working1_4, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working1_5, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working1_6, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working1_7, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working1_8, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working1_9, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working1_10, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working1_11, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working1_12, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working1_13, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working2_0, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working2_1, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working2_2, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working2_3, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working2_4, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working2_5, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working2_6, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working2_7, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working2_8, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working2_9, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working2_10, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working2_11, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working2_12, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working2_13, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working2_14, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_0, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_1, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_2, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_3, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_4, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_5, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_6, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_7, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_8, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_9, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_10, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_11, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_12, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_13, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_14, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working3_15, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_0, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_1, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_2, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_3, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_4, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_5, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_6, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_7, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_8, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_9, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_10, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_11, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_12, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_13, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_14, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_15, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working4_16, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_0, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_1, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_2, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_3, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_4, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_5, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_6, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_7, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_8, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_9, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_10, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_11, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_12, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_13, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_14, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_15, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_16, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working5_17, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_0, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_1, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_2, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_3, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_4, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_5, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_6, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_7, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_8, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_9, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_10, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_11, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_12, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_13, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_14, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_15, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_16, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_17, SIGNAL (released()), this, SLOT (handleWorking()));
    connect(ui->working6_18, SIGNAL (released()), this, SLOT (handleWorking()));

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

    for (int j = 0; j < 7; j++) {
        CardStack *stack = game->get_working_stack_by_id(j);
        QWidget *working = ui->working->findChild<QWidget*>(("working" + std::to_string(j)).c_str());
        if (stack->is_empty()){
            QPushButton *button = working->findChildren<QPushButton*>().at(0);
            button->setVisible(true);
            for (int i = 1; i < 13 + j; i++) {
                QPushButton *button = working->findChildren<QPushButton*>().at(i);
                button->setIcon(QIcon());
                button->setVisible(false);
            }
            button->setIcon(QIcon());
        } else {
            int count = stack->get_size();
            for (int i = 0; i < count; i++) {
                card = stack->get(i);
                QPushButton *button = working->findChildren<QPushButton*>().at(i);
                button->setVisible(true);
                if (card->is_turned_face_up()) {
                    QPixmap pixmap("../images/" + QString::fromStdString(card->to_string()) + ".svg");
                    QIcon ButtonIcon(pixmap);
                    button->setIcon(ButtonIcon);
                    button->setIconSize(button->size());
                } else {
                    QPixmap pixmap("../images/back.svg");
                    QIcon ButtonIcon(pixmap);
                    button->setIcon(ButtonIcon);
                    button->setIconSize(button->size());
                }
            }
            for (int i = count; i < 13 + j; i++) {
                QPushButton *button = working->findChildren<QPushButton*>().at(i);
                button->setIcon(QIcon());
                button->setVisible(false);
            }
        }
    }
}

void Solitaire::handleWasteDeck()
{
    wasteClicked = !wasteClicked;
    targetClicked = -1;
    workingCardClicked = -1;
    workingStackClicked = -1;

}

void Solitaire::handleTargetDeck1()
{
    if (wasteClicked) {
        game->move_card_from_waste_deck_to_target_deck(0);
        wasteClicked = false;
    } else if (workingStackClicked > -1) { //ze je kliknuta len ta prva karta, este doriesim
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
    } else if (workingStackClicked > -1) {
        game->move_card_from_working_stack_to_target_deck(workingStackClicked, 1);
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
    } else if (workingStackClicked > -1) {
        game->move_card_from_working_stack_to_target_deck(workingStackClicked, 2);
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
    } else if (workingStackClicked > -1) {
        game->move_card_from_working_stack_to_target_deck(workingStackClicked, 3);
        workingCardClicked = -1;
        workingStackClicked = -1;
    } else {
        targetClicked = -1;
    }

    paintCards();
}

void Solitaire::handleWorking()
{
    QObject* obj = sender();
    QString name = obj->objectName();
    QString qcard = name.split('_').at(1);
    int card = qcard.toInt();
    QChar qstack = name.at(7);
    int stack = qstack.toLatin1() - 48;

    //chceme presunut kartu z waste balicku
    if (wasteClicked) {
        //bolo kliknute na najspodnejsiu kartu alebo je prazdny
        if (game->get_working_stack_by_id(stack)->get_size() == card + 1 || game->get_working_stack_by_id(stack)->is_empty()) {
            game->move_card_from_waste_deck_to_working_stack(stack);
            resetSelection();
            paintCards();
        }
    //chceme presunut kartu/karty z nejakeho working balicku
    } else if (workingStackClicked > -1) {
       //bolo kliknute na najspodnejsku kartu alebo je prazdny
       if (game->get_working_stack_by_id(stack)->get_size() == card + 1 || game->get_working_stack_by_id(stack)->is_empty()) {
           game->move_cards_from_working_stack_to_working_stack(workingStackClicked, stack, workingCardClicked);
           resetSelection();
           paintCards();
       }
    } else {
        resetSelection();
        workingCardClicked = card;
        workingStackClicked = stack;
    }
}

void Solitaire::resetSelection()
{
    wasteClicked = false;
    targetClicked = -1;
    workingCardClicked = -1;
    workingStackClicked = -1;
}

void Solitaire::save()
{
    game->save("subor");
}
