
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

MoveWasteDeckToTargetDeckCommand::MoveWasteDeckToTargetDeckCommand(int *score, CardDeck *source, CardDeck *destination) {
        this->source = source;
        this->destination = destination;
        this->score = score;
}

bool MoveWasteDeckToTargetDeckCommand::execute() {
        // empty stack, do nothing
        if (this->source->is_empty()) {
                return false;
        }

        // get last card of first deck
        Card * top = this->source->get();

        // set color of target deck
        if (this->destination->is_empty() && top->get_value() == 1) {
            this->destination->set_color(top->get_color());
        }

        // try to put this card to second deck
        if (!this->destination->put(*top)) {
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

        // take last card from stack
        top = this->source->get();
        // turn this card face up
        if (top != nullptr) {
                top->turn_face_up();
        }

        *this->score += 10;

        return true;
}

void MoveWasteDeckToTargetDeckCommand::undo() {
        // get last card from deck
        Card *src_top = this->source->get();
        // turn this card face down
        if (src_top != nullptr) {
                src_top->turn_face_down();
        }

        // get last card from deck
        Card * top = this->destination->get();
        // push this card to deck
        if (top != nullptr) {
                this->source->push(*top);
        }
        // pop that card from deck
        this->destination->pop();

        // unset color of target deck
        if (this->destination->is_empty()) {
            this->destination->set_color(Color::NO_COLOR);
        }

        *this->score -= 10;
}

// STACK TO DECK (4 decks)

MoveWorkingStackToTargetDeckCommand::MoveWorkingStackToTargetDeckCommand(int *score, CardStack *source, CardDeck *destination) {
        this->source = source;
        this->destination = destination;
        this->score = score;
}

bool MoveWorkingStackToTargetDeckCommand::execute() {
        // empty stack, do nothing
        if (this->source->is_empty()) {
                return false;
        }

        // take last card from stack
        Card * top = this->source->get();

        // set color of target deck
        if (this->destination->is_empty() && top->get_value() == 1) {
            this->destination->set_color(top->get_color());
        }

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

        *this->score += 10;

        return true;
}

void MoveWorkingStackToTargetDeckCommand::undo() {
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

        // get previous card of top of deck
        Card * prev_top =  this->destination->get(this->destination->get_size() - 2);
        // turn this card face down
        if (prev_top != nullptr) {
                prev_top->turn_face_down();
        }

        // get last card of stack
        top = this->destination->get();

        // turn new top face up
        if (top != nullptr) {
                top->turn_face_up();
        }

        // unset color of target deck
        if (this->destination->is_empty()) {
            this->destination->set_color(Color::NO_COLOR);
        }

        *this->score -= 10;
}

// DECK TO STACK

MoveWasteDeckToWorkingStackCommand::MoveWasteDeckToWorkingStackCommand(int *score, CardDeck *source, CardStack *destination) {
        this->source = source;
        this->destination = destination;
        this->score = score;
}

bool MoveWasteDeckToWorkingStackCommand::execute() {
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

        // take last card from stack
        top = this->source->get();
        // turn this card face up
        if (top != nullptr) {
                top->turn_face_up();
        }

        *this->score += 5;

        return true;
}

void MoveWasteDeckToWorkingStackCommand::undo() {
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
        // pop that card from deck
        this->destination->pop();

        *this->score -= 5;
}

//

MoveTargetDeckToWorkingStackCommand::MoveTargetDeckToWorkingStackCommand(int *score, CardDeck *source, CardStack *destination) {
        this->source = source;
        this->destination = destination;
        this->score = score;
}

bool MoveTargetDeckToWorkingStackCommand::execute() {
        // empty deck, do nothing
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

        // take last card from stack
        top = this->source->get();
        // turn this card face up
        if (top != nullptr) {
                top->turn_face_up();
        }

        *this->score -= 15;
        return true;
}

void MoveTargetDeckToWorkingStackCommand::undo() {
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
        // pop that card from deck
        this->destination->pop();

        *this->score += 15;
}

// STACK TO STACK

MoveWorkingStackToWorkingStackCommand::MoveWorkingStackToWorkingStackCommand(int *score, CardStack *source, CardStack *destination, Card *top_card) {
        this->source = source;
        this->destination = destination;
        this->top_card = top_card;
        this->score = score;
}

bool MoveWorkingStackToWorkingStackCommand::execute() {
        // return if one of stack is empty
        if (this->source->is_empty()) {
                return false;
        }

        // check if card is turned face up
        if (!this->top_card->is_turned_face_up()) {
                return false;
        }

        // get all cards since this card from first stack
        this->moved_cards = this->source->top(*this->top_card);

        // put one card
        if(this->moved_cards.get_size() == 1) {
                Card * top = this->moved_cards.get();
                // return if cannot put card
                if (!this->destination->put(*top)) {
                        return false;
                }
        } else { // put more cards
                 // return if cannot put cards
                if (!this->destination->put(moved_cards)) {
                        return false;
                }
        }

        // pop all cards since this card from first stack
        this->source->pop(*this->top_card);

        // get last card of first stack
        Card *src_top = this->source->get();
        // turn this card face up
        if (src_top != nullptr) {
                src_top->turn_face_up();
        }

        return true;
}

void MoveWorkingStackToWorkingStackCommand::undo() {
        // get last card of first stack
        Card *src_top = this->source->get();
        // turn this card face down
        if (src_top != nullptr) {
                src_top->turn_face_down();
        }

        // put cards back to first stack
        this->source->push(this->moved_cards);

        // pop cards from second stack
        this->destination->pop(*this->top_card);

        // get last card of first stack
        src_top = this->source->get();
        // turn this card face up
        if (src_top != nullptr) {
                src_top->turn_face_up();
        }
}

// Main to discard DECK
MoveStockDeckToWasteDeckCommand::MoveStockDeckToWasteDeckCommand(int *score, CardDeck *source, CardDeck *destination) {
        this->source = source;
        this->destination = destination;
        this->score = score;
}

bool MoveStockDeckToWasteDeckCommand::execute() {
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
                // turn this card face up
                dest_top->turn_face_up();
        } else {
                // just swap decks
                this->source->swap(*this->destination);
                this->source->reverse();
        }

        return true;
}

void MoveStockDeckToWasteDeckCommand::undo() {
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
                this->destination->reverse();
        }
}
