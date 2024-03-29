/**
* @file game.cc
* @brief Game implementation
* @author Dávid Bolvanský xbolva00
*/

#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include "game.h"

/**
* Game constructor
*/
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
}

/**
* Game constructor, load game from file
* @param filename load game from this file
*/
Game::Game(std::string filename) {
        std::ifstream file(filename);
        if (!file) {
                throw std::runtime_error("file not found");
        }
        std::string line;
        int color;
        int value;
        bool is_turned_face_up;
        int save_to = 0;
        while (std::getline(file, line)) {
                if (line.find("#") != std::string::npos) {
                        save_to++;
                        continue;
                }

                std::istringstream line_stream(line);

                if (save_to == 14) {
                        line_stream >> value;
                        this->score = value;
                        continue;
                }

                line_stream >> color >> value >> is_turned_face_up;

                Card c {static_cast<Color> (color), value, is_turned_face_up};

                if (save_to == 1) {
                        this->stock_deck.push(c);
                } else if (save_to == 2) {
                        this->waste_deck.push(c);
                } else if (save_to  >= 3 && save_to <= 6) {
                        this->target_card_decks[save_to - 3].push(c);
                } else if (save_to  >= 7 && save_to <= 13) {
                        this->working_card_stacks[save_to - 7].push(c);
                }
        }

        for (int i = 0; i < DECKS_COUNT; ++i) {
                CardDeck * deck = get_target_deck_by_id(i);
                if (!deck->is_empty()) {
                        Card * top = deck->get();
                        deck->set_color(top->get_color());
                }
        }

        file.close();
}

/**
* Undo last move in game
*/
void Game::undo() {
        this->command_manager.undo_command();
}

/**
* Move card from stock deck to waste deck
* @return true when successful operation, false otherwise
*/
bool Game::move_card_from_stock_deck_to_waste_deck() {
        MoveStockDeckToWasteDeckCommand *dtd = new MoveStockDeckToWasteDeckCommand {&this->score, &this->stock_deck, &this->waste_deck};
        std::shared_ptr<Command> cmd {dtd};
        return this->command_manager.execute_command(cmd);
}

/**
* Move card from waste deck to working stack
* @param stack_index index of working stack
* @return true when successful operation, false otherwise
*/
bool Game::move_card_from_waste_deck_to_working_stack(int stack_index) {
        if (stack_index < 0 || stack_index > STACKS_COUNT - 1) {
                return false;
        }
        MoveWasteDeckToWorkingStackCommand *dts = new MoveWasteDeckToWorkingStackCommand {&this->score,&this->waste_deck, &this->working_card_stacks[stack_index]};
        std::shared_ptr<Command> cmd {dts};
        return this->command_manager.execute_command(cmd);;
}

/**
* Move card from waste deck to target deck
* @param deck_index index of target deck
* @return true when successful operation, false otherwise
*/
bool Game::move_card_from_waste_deck_to_target_deck(int deck_index) {
        if (deck_index < 0 || deck_index > DECKS_COUNT - 1) {
                return false;
        }
        MoveWasteDeckToTargetDeckCommand *dtd = new MoveWasteDeckToTargetDeckCommand {&this->score, &this->waste_deck, &this->target_card_decks[deck_index]};
        std::shared_ptr<Command> cmd {dtd};
        return this->command_manager.execute_command(cmd);
}

/**
* Move card from target deck to working stack
* @param deck_index index of target deck
* @param stack_index index of working stack
* @return true when successful operation, false otherwise
*/
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

/**
* Move card from working stack to target deck
* @param stack_index index of working stack
* @param deck_index index of target deck
* @return true when successful operation, false otherwise
*/
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


/**
* Move card from working stack to working stack
* @param src_stack_index index of source working stack
* @param dest_stack_index index of destination working stack
* @param card_index index of card in source working stack
* @return true when successful operation, false otherwise
*/
bool Game::move_cards_from_working_stack_to_working_stack(int src_stack_index, int dest_stack_index, int card_index) {
        if (src_stack_index < 0 || src_stack_index > STACKS_COUNT - 1) {
                return false;
        }
        if (dest_stack_index < 0 || dest_stack_index > STACKS_COUNT - 1) {
                return false;
        }
        if (card_index < 0 || card_index > CARDS_PER_STACK - 1) {
                return false;
        }

        Card * top = get_working_stack_by_id(src_stack_index)->get(card_index);
        if (top == nullptr) {
                return false;
        }

        MoveWorkingStackToWorkingStackCommand *sts = new MoveWorkingStackToWorkingStackCommand {&this->score, &this->working_card_stacks[src_stack_index], &this->working_card_stacks[dest_stack_index], top};
        std::shared_ptr<Command> cmd {sts};
        return this->command_manager.execute_command(cmd);
}

/**
* Get target deck
* @param index index of target deck
* @return pointer to target deck
*/
CardDeck * Game::get_target_deck_by_id(int index) {
        return &this->target_card_decks[index];
}

/**
* Get working stack
* @param index index of working stack
* @return pointer to working stack
*/
CardStack * Game::get_working_stack_by_id(int index) {
        return &this->working_card_stacks[index];
}

/**
* Get stock deck
* @return pointer to stock deck
*/
CardDeck * Game::get_stock_deck() {
        return &this->stock_deck;
}

/**
* Get waste deck
* @return pointer to waste deck
*/
CardDeck * Game::get_waste_deck() {
        return &this->waste_deck;
}

/**
* Save game to file
* @param filename save game to this file
* @return true on success, false if cannot save game to file
*/
bool Game::save(std::string filename) {
        std::ofstream file (filename);
        if (!file) return false;

        file << "# Stock deck" << std::endl;

        for (int i = 0; i < this->stock_deck.get_size(); ++i) {
                Card *c = this->stock_deck.get(i);
                file << c->get_color() << " " << c->get_value() << " " << c->is_turned_face_up() << std::endl;
        }

        file << "# Waste deck" << std::endl;

        for (int i = 0; i < this->waste_deck.get_size(); ++i) {
                Card *c = this->waste_deck.get(i);
                file << c->get_color() << " " << c->get_value() << " " << c->is_turned_face_up() << std::endl;
        }

        for (int t = 0; t < DECKS_COUNT; ++t) {
                file << "# Target deck " << t + 1 << std::endl;
                for (int i = 0; i < CARDS_PER_PACK; ++i) {
                        Card *c = this->get_target_deck_by_id(t)->get(i);
                        if (!c) break;
                        file << c->get_color() << " " << c->get_value() << " " << c->is_turned_face_up() << std::endl;
                }

        }

        for (int t = 0; t < STACKS_COUNT; ++t) {
                file << "# Working stack " << t + 1 << std::endl;
                for (int i = 0; i < CARDS_PER_STACK; ++i) {
                        Card *c = this->working_card_stacks[t].get(i);
                        if (!c) break;
                        file << c->get_color() << " " << c->get_value() << " " << c->is_turned_face_up() << std::endl;
                }

        }

        file << "# Score" << std::endl;
        file << this->score << std::endl;

        file.close();
        return true;
}

/**
* Load game from file
* @param filename load game from this file
* @return pointer to game on success, null pointer if error
*/
Game * Game::load(std::string filename) {
        Game *loaded_game = nullptr;
        try {
                loaded_game = new Game {filename};
        }
        catch(std::exception const& e) {
                // nothing
        }
        return loaded_game;
}

/**
* Get score in game
* @return score
*/
int Game::get_score() {
        if (this->score < 0) {
            this->score = 0;
        }

        return this->score;
}

/**
* Get number of moves in game
* @return number of moves
*/
int Game::get_moves_count() {
        return this->command_manager.get_size();
}

/**
* Check if game is won
* @return true if game is won, false otherwise
*/
bool Game::is_won() {
        int all_cards_in_target_decks = 0;
        for (int i = 0; i < DECKS_COUNT; ++i) {
                all_cards_in_target_decks += this->get_target_deck_by_id(i)->get_size();
        }

        return all_cards_in_target_decks == ALL_CARDS_COUNT;
}

/**
* Start game timer
*/
void Game::start() {
        this->started_at = std::chrono::high_resolution_clock::now();
        this->paused = false;
}

/**
* Pause game timer
*/
void Game::pause() {
        if (this->paused) return;
        this->paused_at = std::chrono::high_resolution_clock::now();
        this->paused = true;
}

/**
* Resume game timer
*/
void Game::resume() {
        if (!this->paused) return;
        this->started_at += std::chrono::high_resolution_clock::now() - this->paused_at;
        this->paused = false;
}

/**
* Get total game play time in seconds
* @return play time in seconds
*/
std::chrono::seconds Game::get_total_time_in_seconds() {
        if (this->paused) {
                return std::chrono::duration_cast<std::chrono::seconds>(this->paused_at - this->started_at);
        }
        else {
                return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - this->started_at);
        }
}
