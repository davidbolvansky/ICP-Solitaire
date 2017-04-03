
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

int CommandManager::get_size() {
    return this->commands_stack.size();
}

// DECK TO DECK (Main deck to visible deck)

MoveDeckToDeckCommand::MoveDeckToDeckCommand(CardDeck *source, CardDeck *destination) {
        this->source = source;
        this->destination = destination;
}

bool MoveDeckToDeckCommand::execute() {
        // return if both decks are empty
        if (this->source->is_empty() && this->destination->is_empty()) {
                return false;
        }

        // get last card of first deck
        Card * top = this->source->get();

        if (top != nullptr) {
                // try to push this card to second deck
                if (!this->destination->push(*top)) {
                        return false;
                }

                // pop last card from first deck
                this->source->pop();

                // get previous card of top of second deck
                Card * prev_top = this->destination->get(this->destination->get_size() - 2);

                // turn this card face down
                if (prev_top != nullptr) {
                        prev_top->turn_face_down();
                }

                // get last card of second deck
                Card *dest_top = this->destination->get();
                // turn this card face down
                dest_top->turn_face_up();
        } else {
                // just swap decks
                this->source->swap(*this->destination);
        }

        return true;
}

void MoveDeckToDeckCommand::undo() {
        // get last card of second deck
        Card * top = this->destination->get();

        if (top != nullptr) {
                // pop last card from second deck
                this->destination->pop();

                // push this card to first deck
                this->source->push(*top);

                // last card of second deck
                top = this->destination->get();
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
                this->destination->swap(*this->source);
        }
}


// STACK TO DECK (4 decks)

MoveStackToDeckCommand::MoveStackToDeckCommand(CardStack *source, CardDeck *destination) {
        this->source = source;
        this->destination = destination;
}

bool MoveStackToDeckCommand::execute() {
        // empty stack, do nothing
        if (this->source->is_empty()) {
                return false;
        }

        // take last card from stack
        Card * top = this->source->get();
        // try to push this card to stack
        if (!this->destination->put(*top)) { // DEBUG: use push - less restrictive
                return false;
        }

        // pop that card from stack
        this->source->pop();

        // get previous card of top of deck
        Card * prev_top =  this->destination->get(this->destination->get_size() - 2);
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
        Card * top = this->destination->get();
        // push this card to stack
        if (top != nullptr) {
                this->source->push(*top);
        }
        // get and pop that card from deck
        this->destination->pop();

        // get last card of stack
        top = this->destination->get();

        // turn new top face up
        if (top != nullptr) {
                top->turn_face_up();
        }
}

// DECK TO STACK

MoveDeckToStackCommand::MoveDeckToStackCommand(CardDeck *source, CardStack *destination) {
        this->source = source;
        this->destination = destination;
}

bool MoveDeckToStackCommand::execute() {
        // empty stack, do nothing
        if (this->source->is_empty()) {
                return false;
        }

        // take last card from stack
        Card * top = this->source->get();
        // try to push this card to stack
        if (!this->destination->put(*top)) {
                return false;
        }

        // pop that card from stack
        this->source->pop();

        // get previous card of top of deck
        Card * prev_top =  this->destination->get(this->destination->get_size() - 2);
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

void MoveDeckToStackCommand::undo() {
        // get last card from stack
        Card *src_top = this->source->get();
        // turn this card face down
        if (src_top != nullptr) {
            std::cout << src_top->to_string() << "\n";
                src_top->turn_face_down();
        }

        // get last card from deck
        Card * top = this->destination->get();
        // push this card to stack
        if (top != nullptr) {
                this->source->push(*top);
        }
        // pop that card from deck
        this->destination->pop();

        // get last card of stack
        top = this->destination->get();

        // turn new top face up
        if (top != nullptr) {
            std::cout << "PICA " << top->to_string() << "\n";
                top->turn_face_up();
        }
}

// STACK TO STACK

MoveStackToStackCommand::MoveStackToStackCommand(CardStack *source, CardStack *destination) {
        this->source = source;
        this->destination = destination;
}

bool MoveStackToStackCommand::execute() {
        // return if one of stack is empty
        if (this->source->is_empty() || this->destination->is_empty()) {
                return false;
        }

        // get last card of second stack
        this->top_card = this->destination->get();

        // get all cards since this card from first stack
        CardStack moved_cards = this->source->pop(*this->top_card);

        // return if no cards to move or cannot put them
        if (moved_cards.is_empty() || !this->destination->put(moved_cards)) {
                return false;
        }

        // get last card of first stack
        Card *src_top = this->source->get();
        // turn this card face up
        if (src_top != nullptr) {
                src_top->turn_face_up();
        }

        return true;
}

void MoveStackToStackCommand::undo() {
        // get all cards since last card of second stack from second stack
        CardStack moved_cards = this->destination->pop(*this->top_card);

        // get last card of first stack
        Card *src_top = this->source->get();
        // turn this card face down
        if (src_top != nullptr) {
                src_top->turn_face_down();
        }

        // put cards back to first stack
        this->source->put(moved_cards);
}
