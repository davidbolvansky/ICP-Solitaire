#ifndef COMMAND_H
#define COMMAND_H

#include <stack>
#include <memory>
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
    CardDeck *target;
public:
    MoveDeckToDeckCommand(CardDeck *source, CardDeck *target);
    virtual bool execute() override;
    virtual void undo() override;
};

class MoveStackToDeckCommand : public Command {
    CardStack *source;
    CardDeck *target;
public:
    MoveStackToDeckCommand(CardStack *source, CardDeck *target);
    virtual bool execute() override;
    virtual void undo() override;
};

class MoveStackToStackCommand : public Command {
    CardStack *source;
    CardStack *target;
    Card *top;
public:
    MoveStackToStackCommand(CardStack *source, CardStack *target);
    virtual bool execute() override;
    virtual void undo() override;
};



class CommandManager {
    std::stack<std::shared_ptr<Command>> commands_stack;
    public:
    bool execute_command(std::shared_ptr<Command> command);
    bool undo_command();
};

#endif // COMMAND_H
