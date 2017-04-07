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



class MoveDeckToDeckCommand : public Command {
    CardDeck *source;
    CardDeck *destination;
public:
    MoveDeckToDeckCommand(CardDeck *source, CardDeck *destination);
    virtual bool execute() override;
    virtual void undo() override;
};

class MoveStackToDeckCommand : public Command {
    CardStack *source;
    CardDeck *destination;
public:
    MoveStackToDeckCommand(CardStack *source, CardDeck *destination);
    virtual bool execute() override;
    virtual void undo() override;
};

class MoveDeckToStackCommand : public Command {
    CardDeck *source;
    CardStack *destination;
public:
    MoveDeckToStackCommand(CardDeck *source, CardStack *destination);
    virtual bool execute() override;
    virtual void undo() override;
};

class MoveStackToStackCommand : public Command {
    CardStack *source;
    CardStack *destination;
    Card * top_card;
    CardStack moved_cards{13};
public:
    MoveStackToStackCommand(CardStack *source, CardStack *destination, Card *top_card);
    virtual bool execute() override;
    virtual void undo() override;
};

class MoveMainDeckToDiscardDeckCommand : public Command {
    CardDeck *source;
    CardDeck *destination;
public:
    MoveMainDeckToDiscardDeckCommand(CardDeck *source, CardDeck *destination);
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
