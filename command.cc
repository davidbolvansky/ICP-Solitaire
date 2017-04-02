
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
        // return if both decks are empty
        if (this->source->is_empty() && this->target->is_empty()) {
                return false;
        }

        // get last card of first deck
        Card * top = this->source->get();

        if (top != nullptr) {
                // try to push this card to second deck
                if (!this->target->push(*top)) {
                        return false;
                }

                // pop last card from first deck
                this->source->pop();

                // get previous card of top of second deck
                Card * prev_top = this->target->get(this->target->get_size() - 2);

                // turn this card face down
                if (prev_top != nullptr) {
                        prev_top->turn_face_down();
                }

                // get last card of second deck
                Card *tgt_top = this->target->get();
                // turn this card face down
                tgt_top->turn_face_up();
        } else {
                // just swap decks
                this->source->swap(*this->target);
        }

        return true;
}

void MoveDeckToDeckCommand::undo() {
        // get last card of second deck
        Card * top = this->target->get();

        if (top != nullptr) {
                // pop last card from second deck
                this->target->pop();
                // push this card to first deck
                this->source->push(*top);

                // get last card of second deck
                top = this->target->get();

                // turn this card face up
                if (top != nullptr) {
                        top->turn_face_up();
                }

                // get last card of first deck
                Card *src_top = this->source->get();
                // turn this card face down
                src_top->turn_face_down();
        } else {
                // just swap decks
                this->target->swap(*this->source);
        }
}


// STACK TO DECK (4 decks)

MoveStackToDeckCommand::MoveStackToDeckCommand(CardStack *source, CardDeck *target) {
        this->source = source;
        this->target = target;
}

bool MoveStackToDeckCommand::execute() {
        // empty stack, do nothing
        if (this->source->is_empty()) {
                return false;
        }

        // take last card from stack
        Card * top = this->source->get();
        // try to push this card to stack
        if (!this->target->put(*top)) { // DEBUG: use push - less restrictive
                return false;
        }

        // pop that card from stack
        this->source->pop();

        // get previous card of top of deck
        Card * prev_top =  this->target->get(this->target->get_size() - 2);
        // turn this card face down
        if (prev_top != nullptr) {
                prev_top->turn_face_down();
        }

        // take last card from stack
        top = this->source->get();
        // turn this card face up
        if (top != nullptr) {
                top->turn_face_up();
        }

        return true;
}

void MoveStackToDeckCommand::undo() {
        // get last card from stack
        Card *src_top = this->source->get();
        // turn this card face down
        if (src_top != nullptr) {
                src_top->turn_face_down();
        }

        // get last card from deck
        Card * top = this->target->get();
        // push this card to stack
        if (top != nullptr) {
                this->source->push(*top);
        }
        // pop that card from deck
        this->target->pop();

        // get new top of deck
        top = this->target->get();
        // turn new top face up
        if (top != nullptr) {
                top->turn_face_up();
        }
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
                src_top->turn_face_down();
        }

        this->source->put(moved_cards);
}
