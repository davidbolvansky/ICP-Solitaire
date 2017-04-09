#ifndef COMMAND_H
#define COMMAND_H

#include <stack>
#include <memory>
#include "card.h"
#include "card_deck.h"
#include "card_stack.h"

// interface
class Command {
    public:
    virtual bool execute() = 0;
    virtual void undo() = 0;
};



class MoveWasteDeckToTargetDeckCommand : public Command {
    CardDeck *source;
    CardDeck *destination;
    int *score;
public:
    MoveWasteDeckToTargetDeckCommand(int *score, CardDeck *source, CardDeck *destination);
    virtual bool execute() override;
    virtual void undo() override;
};

class MoveWorkingStackToTargetDeckCommand : public Command {
    CardStack *source;
    CardDeck *destination;
    int *score;
public:
    MoveWorkingStackToTargetDeckCommand(int *score, CardStack *source, CardDeck *destination);
    virtual bool execute() override;
    virtual void undo() override;
};

class MoveWasteDeckToWorkingStackCommand : public Command {
    CardDeck *source;
    CardStack *destination;
    int *score;
public:
    MoveWasteDeckToWorkingStackCommand(int *score, CardDeck *source, CardStack *destination);
    virtual bool execute() override;
    virtual void undo() override;
};

class MoveTargetDeckToWorkingStackCommand : public Command {
    CardDeck *source;
    CardStack *destination;
    int *score;
public:
    MoveTargetDeckToWorkingStackCommand(int *score, CardDeck *source, CardStack *destination);
    virtual bool execute() override;
    virtual void undo() override;
};

class MoveWorkingStackToWorkingStackCommand : public Command {
    CardStack *source;
    CardStack *destination;
    Card * top_card;
    CardStack moved_cards{13};
    int *score;
public:
    MoveWorkingStackToWorkingStackCommand(int *score, CardStack *source, CardStack *destination, Card *top_card);
    virtual bool execute() override;
    virtual void undo() override;
};

class MoveStockDeckToWasteDeckCommand : public Command {
    CardDeck *source;
    CardDeck *destination;
    int *score;
public:
    MoveStockDeckToWasteDeckCommand(int *score, CardDeck *source, CardDeck *destination);
    virtual bool execute() override;
    virtual void undo() override;
};



class CommandManager {
    std::stack<std::shared_ptr<Command>> commands_stack;
    public:
    bool execute_command(std::shared_ptr<Command> command);
    bool undo_command();
    int get_size();
};

#endif // COMMAND_H
