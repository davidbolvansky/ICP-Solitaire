
#include <iostream> // DEBUG
#include <memory>
#include "command.h"


bool CommandManager::execute_command(std::shared_ptr<Command> command) {
        bool exec_success = command->execute();
        if (exec_success) {
                this->commands_stack.push(command);
        }
        return exec_success;
}

bool CommandManager::undo_command() {
        if (this->commands_stack.empty()) {
                return false;
        }

        std::shared_ptr<Command> top = this->commands_stack.top();
        top->undo();
        this->commands_stack.pop();
        return true;
}

// DECK TO DECK (Main deck to visible deck)

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

void MoveDeckToDeckCommand::undo() {
        Card * top = this->target->get();

        if (top != nullptr) {
                this->target->pop();
                this->source->push(*top);
        } else {
                this->target->swap(*this->source);
        }
}


// STACK TO DECK (4 decks)

MoveStackToDeckCommand::MoveStackToDeckCommand(CardStack *source, CardDeck *target) {
        this->source = source;
        this->target = target;
}

bool MoveStackToDeckCommand::execute() {
        if (this->source->is_empty()) {
                return false;
        }

        Card * top = this->source->get();
        this->source->pop();
        this->target->push(*top);

        return true;
}

void MoveStackToDeckCommand::undo() {
        Card * top = this->target->get();
        this->target->pop();
        this->source->push(*top);
}

// STACK TO STACK

MoveStackToStackCommand::MoveStackToStackCommand(CardStack *source, CardStack *target) {
        this->source = source;
        this->target = target;
}

bool MoveStackToStackCommand::execute() {
        if (this->source->is_empty() || this->target->is_empty()) {
                return false;
        }

        this->top = this->target->get();

        CardStack moved_cards = this->source->pop(*top);
        if (moved_cards.is_empty() || !this->target->put(moved_cards)) {
                return false;
        }

        Card *src_top = this->source->get();
        if (src_top != nullptr) {
                src_top->turn_face_up();
        }

        return true;
}

void MoveStackToStackCommand::undo() {
        CardStack moved_cards = this->target->pop(*this->top);
        Card *src_top = this->source->get();
        if (src_top != nullptr) {
                src_top->turn_face_up();
        }
        this->source->put(moved_cards);
}
