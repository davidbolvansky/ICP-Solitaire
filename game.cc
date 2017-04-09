#include <iostream>
#include "game.h"


int Game::games_counter = 0;

Game::Game() {
        this->stock_deck = CardDeck::create_standard_deck();
        this->stock_deck.shuffle();

        for (int working_stack_index = 0; working_stack_index < STACKS_COUNT; ++working_stack_index) {
                for (int cards_per_pack = 0; cards_per_pack < working_stack_index + 1; ++cards_per_pack) {
                        Card * top = this->stock_deck.pop();
                        if (working_stack_index == cards_per_pack) {
                                top->turn_face_up();
                        }
                        this->working_card_stacks[working_stack_index].push(*top);
                }
        }

        score = 0;
        games_counter++;
}


void Game::undo() {
        this->command_manager.undo_command();
}

bool Game::move_card_from_stock_deck_to_waste_deck() {
        MoveStockDeckToWasteDeckCommand *dtd = new MoveStockDeckToWasteDeckCommand {&this->score, &this->stock_deck, &this->waste_deck};
        std::shared_ptr<Command> cmd {dtd};
        return this->command_manager.execute_command(cmd);
}

bool Game::move_card_from_waste_deck_to_working_stack(int stack_index) {
        if (stack_index < 0 || stack_index > 6) {
                return false;
        }
        MoveWasteDeckToWorkingStackCommand *dts = new MoveWasteDeckToWorkingStackCommand {&this->score,&this->waste_deck, &this->working_card_stacks[stack_index]};
        std::shared_ptr<Command> cmd {dts};
        return this->command_manager.execute_command(cmd);;
}

bool Game::move_card_from_waste_deck_to_target_deck(int deck_index) {
        if (deck_index < 0 || deck_index > 3) {
                return false;
        }
        MoveWasteDeckToTargetDeckCommand *dtd = new MoveWasteDeckToTargetDeckCommand {&this->score, &this->waste_deck, &this->target_card_decks[deck_index]};
        std::shared_ptr<Command> cmd {dtd};
        return this->command_manager.execute_command(cmd);
}

bool Game::move_card_from_target_deck_to_working_stack(int deck_index, int stack_index) {
        if (deck_index < 0 || deck_index > DECKS_COUNT - 1) {
                return false;
        }
        if (stack_index < 0 || stack_index > STACKS_COUNT - 1) {
                return false;
        }
        MoveTargetDeckToWorkingStackCommand *dts = new MoveTargetDeckToWorkingStackCommand {&this->score, &this->target_card_decks[deck_index], &this->working_card_stacks[stack_index]};
        std::shared_ptr<Command> cmd {dts};
        return this->command_manager.execute_command(cmd);
}

bool Game::move_card_from_working_stack_to_target_deck(int stack_index, int deck_index) {
        if (deck_index < 0 || deck_index > DECKS_COUNT - 1) {
                return false;
        }
        if (stack_index < 0 || stack_index > STACKS_COUNT - 1) {
                return false;
        }
        MoveWorkingStackToTargetDeckCommand *std = new MoveWorkingStackToTargetDeckCommand {&this->score, &this->working_card_stacks[stack_index], &this->target_card_decks[deck_index]};
        std::shared_ptr<Command> cmd {std};
        return this->command_manager.execute_command(cmd);
}

bool Game::move_cards_from_working_stack_to_working_stack(int src_stack_index, int dest_stack_index, int card_index) {
        if (src_stack_index < 0 || src_stack_index > STACKS_COUNT - 1) {
                return false;
        }
        if (dest_stack_index < 0 || dest_stack_index > STACKS_COUNT - 1) {
                return false;
        }
        if (card_index < 0 || card_index > CARDS_PER_PACK - 1) {
                return false;
        }

        Card * top = get_working_stack_by_id(src_stack_index)->get(card_index);
        if (top == nullptr) {
            return false;
        }

        MoveWorkingStackToWorkingStackCommand *sts = new MoveWorkingStackToWorkingStackCommand {&this->score, &this->working_card_stacks[src_stack_index], &this->working_card_stacks[dest_stack_index], top};
        std::shared_ptr<Command> cmd{sts};
        return this->command_manager.execute_command(cmd);
}

CardDeck * Game::get_target_deck_by_id(int index) {
        return &target_card_decks[index];
}

CardStack * Game::get_working_stack_by_id(int index) {
        return &this->working_card_stacks[index];
}

CardDeck * Game::get_stock_deck() {
        return &this->stock_deck;
}

CardDeck * Game::get_waste_deck() {
        return &this->waste_deck;
}

bool Game::save(std::string filename) {
        // todo
        return true;
}

Game * Game::load(std::string filename) {
        Game *loaded_game = new Game;
        return loaded_game;
}

int Game::get_games_count() {
        return games_counter;
}

int Game::get_score() {
        if (this->score < 0) {
            this->score = 0;
        }

        return this->score;
}

int Game::get_moves_count() {
        return this->command_manager.get_size();
}

void Game::start() {
        this->started_at = std::chrono::high_resolution_clock::now();
        this->paused = false;
}

void Game::pause() {
        if (this->paused) return;
        this->paused_at = std::chrono::high_resolution_clock::now();
        this->paused = true;
}

void Game::resume() {
        if (!this->paused) return;
        this->started_at += std::chrono::high_resolution_clock::now() - this->paused_at;
        this->paused = false;
}

// http://www.informit.com/articles/article.aspx?p=1881386&seqNum=2
std::chrono::seconds Game::get_total_time_in_seconds() {
        if (this->paused) {
                return std::chrono::duration_cast<std::chrono::seconds>(this->paused_at - this->started_at);
        }
        else {
                return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - this->started_at);
        }
}
