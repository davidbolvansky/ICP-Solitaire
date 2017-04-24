/**
* @file command.cc
* @brief Command Manager and Commands implementations
* @author Dávid Bolvanský xbolva00
*/

#include <iostream>
#include <memory>
#include "command.h"


/**
* Execute game command
* @param command pointer to command
* @return true when successful operation, false otherwise
*/
bool CommandManager::execute_command(std::shared_ptr<Command> command) {
        bool exec_success = command->execute();
        if (exec_success) {
                this->commands_stack.push(command);
        }
        return exec_success;
}

/**
* Undo last game command
* @return true when successful operation, false otherwise
*/
bool CommandManager::undo_command() {
        if (this->commands_stack.empty()) {
                return false;
        }

        std::shared_ptr<Command> top = this->commands_stack.top();
        top->undo();
        this->commands_stack.pop();
        return true;
}

/**
* Get size of stack of commands
* @return size of stack of commands
*/
int CommandManager::get_size() {
        return this->commands_stack.size();
}


/**
* Command for movement from waste deck to target deck
* @param score pointer to score
* @param source pointer to waste deck
* @param destination pointer to target deck
*/
MoveWasteDeckToTargetDeckCommand::MoveWasteDeckToTargetDeckCommand(int *score, CardDeck *source, CardDeck *destination) {
        this->source = source;
        this->destination = destination;
        this->score = score;
}

/**
* Execute movement from waste deck to target deck
* @return true when successful operation, false otherwise
*/
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

/**
* Take card back from target deck to waste deck
*/
void MoveWasteDeckToTargetDeckCommand::undo() {
        // get last card from deck
        Card *top = this->source->get();
        // turn this card face down
        if (top != nullptr) {
                top->turn_face_down();
        }

        // get last card from deck
        top = this->destination->get();
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

        // get last card of deck
        top = this->destination->get();
        // turn this card face down
        if (top != nullptr) {
            top->turn_face_up();
        }

        *this->score -= 10;
}

/**
* Command for movement from working stack to target deck
* @param score pointer to score
* @param source pointer to working stack
* @param destination pointer to target deck
*/
MoveWorkingStackToTargetDeckCommand::MoveWorkingStackToTargetDeckCommand(int *score, CardStack *source, CardDeck *destination) {
        this->source = source;
        this->destination = destination;
        this->score = score;
}

/**
* Execute movement from working stack to target deck
* @return true when successful operation, false otherwise
*/
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
                this->card_turned = top->turn_face_up();
        }

        *this->score += 10;

        return true;
}

/**
* Take card back from target deck to working stack
*/
void MoveWorkingStackToTargetDeckCommand::undo() {
        // get last card of stack
        Card *top = this->source->get();
        // turn this card face down
        if (top != nullptr && this->card_turned) {
                top->turn_face_down();
        }

        // get last card from deck
        top = this->destination->get();
        // push this card to stack
        if (top != nullptr) {
                this->source->push(*top);
        }
        // get and pop that card from deck
        this->destination->pop();

        // unset color of target deck
        if (this->destination->is_empty()) {
                this->destination->set_color(Color::NO_COLOR);
        }

        // get last card of deck
        top = this->destination->get();
        // turn this card face down
        if (top != nullptr) {
            top->turn_face_up();
        }

        *this->score -= 10;
}

/**
* Command for movement from waste deck to working stack
* @param score pointer to score
* @param source pointer to waste deck
* @param destination pointer to working stack
*/
MoveWasteDeckToWorkingStackCommand::MoveWasteDeckToWorkingStackCommand(int *score, CardDeck *source, CardStack *destination) {
        this->source = source;
        this->destination = destination;
        this->score = score;
}

/**
* Execute movement from waste deck to working stack
* @return true when successful operation, false otherwise
*/
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

/**
* Return card from working stack to waste deck
*/
void MoveWasteDeckToWorkingStackCommand::undo() {
        // get last card from stack
        Card * top = this->source->get();
        // turn this card face down
        if (top != nullptr) {
                top->turn_face_down();
        }

        // get last card from deck
        top = this->destination->get();
        // push this card to stack
        if (top != nullptr) {
                this->source->push(*top);
        }
        // pop that card from deck
        this->destination->pop();

        *this->score -= 5;
}

//

/**
* Command for movement from target deck to working stack
* @score pointer to score
* @param source pointer to target deck
* @param destination pointer to working stack
*/
MoveTargetDeckToWorkingStackCommand::MoveTargetDeckToWorkingStackCommand(int *score, CardDeck *source, CardStack *destination) {
        this->source = source;
        this->destination = destination;
        this->score = score;
}

/**
* Execute movement from target deck to working stack
* @return true when successful operation, false otherwise
*/
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

        // unset color of target deck
        if (this->source->is_empty()) {
                this->source->set_color(Color::NO_COLOR);
        }

        // take last card from stack
        top = this->source->get();
        // turn this card face up
        if (top != nullptr) {
                top->turn_face_up();
        }

        *this->score -= 15;
        return true;
}

/**
* Return card from working stack to target deck
*/
void MoveTargetDeckToWorkingStackCommand::undo() {
        // get last card from stack
        Card * top = this->source->get();
        // turn this card face down
        if (top != nullptr) {
                top->turn_face_down();
        }

        // get last card from deck
        top = this->destination->get();

        // set color of target deck
        if (this->source->is_empty()) {
                this->source->set_color(top->get_color());
        }

        // push this card to deck
        if (top != nullptr) {
                this->source->push(*top);
        }

        // pop that card from deck
        this->destination->pop();

        *this->score += 15;
}

/**
* Command for movement from working stack to working stack
* @param score pointer to score
* @param source pointer to source working stack
* @param destination pointer to destination working stack
* @param top_card card in source working stack
*/
MoveWorkingStackToWorkingStackCommand::MoveWorkingStackToWorkingStackCommand(int *score, CardStack *source, CardStack *destination, Card *top_card) {
        this->source = source;
        this->destination = destination;
        this->top_card = top_card;
        this->score = score;
}

/**
* Execute movement from source working stack to destination working stack
* @return true when successful operation, false otherwise
*/
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
                if (!this->destination->put(this->moved_cards)) {
                        return false;
                }
        }

        // pop all cards since this card from first stack
        this->source->pop(*this->top_card);

        // get last card of first stack
        Card *top = this->source->get();
        // turn this card face up
        if (top != nullptr) {
                this->card_turned = top->turn_face_up();
        }

        return true;
}

/**
* Take cards back from destination working stack to source working stack
*/
void MoveWorkingStackToWorkingStackCommand::undo() {
        // get last card of first stack
        Card *top = this->source->get();
        // turn this card face down
        if (top != nullptr && this->card_turned) {
                top->turn_face_down();
        }

        // put cards back to first stack
        this->source->push(this->moved_cards);

        // pop cards from second stack
        this->destination->pop(*this->top_card);

        // get last card of first stack
        top = this->source->get();
        // turn this card face up
        if (top != nullptr) {
                top->turn_face_up();
        }
}

/**
* Command for movement from stock deck to waste deck
* @param score pointer to score
* @param source pointer to stock deck
* @param destination pointer to waste deck
*/
MoveStockDeckToWasteDeckCommand::MoveStockDeckToWasteDeckCommand(int *score, CardDeck *source, CardDeck *destination) {
        this->source = source;
        this->destination = destination;
        this->score = score;
}

/**
* Execute movement from stock deck to waste deck
* @return true when successful operation, false otherwise
*/
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
                top = this->destination->get();
                // turn this card face up
                top->turn_face_up();
        } else {
                // just swap decks
                this->source->swap(*this->destination);
                this->source->reverse();
                *this->score -= 100;
        }

        return true;
}

/**
* Take card back from waste deck to stock deck
*/
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
                Card *top = this->source->get();
                // turn this card face down
                top->turn_face_down();
        } else {
                // just swap decks
                this->destination->swap(*this->source);
                this->destination->reverse();
                *this->score += 100;
        }
}
