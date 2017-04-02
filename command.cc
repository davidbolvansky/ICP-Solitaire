
#include <iostream> // DEBUG
#include <memory>
#include "command.h"


bool CommandManager::execute_command(std::shared_ptr<Command> command) {
    this->commands_stack.push(command);
    return command->execute();
}

bool CommandManager::undo_command() {
    if (this->commands_stack.empty()) {
        return false;
    }

    std::shared_ptr<Command> top = this->commands_stack.top();
    this->commands_stack.pop();
    return top->undo();
}

MoveDeckToDeckCommand::MoveDeckToDeckCommand(CardDeck *source, CardDeck *target) {
    this->source = source;
    this->target = target;
}

bool MoveDeckToDeckCommand::execute() {
    if (this->source->is_empty() && this->target->is_empty()) {
        return false;
    }
    Card * top = this->source->get();

    if (top != nullptr) {
         this->source->pop();
         this->target->push(*top);
    } else {
         this->source->swap(*this->target);
    }

    return true;
}

bool MoveDeckToDeckCommand::undo() {
    if (this->source->is_empty() && this->target->is_empty()) {
        return false;
    }

    Card * top = this->target->get();

    if (top != nullptr) {
         this->target->pop();
         this->source->push(*top);
    } else {
         this->target->swap(*this->source);
    }

    return true;
}
