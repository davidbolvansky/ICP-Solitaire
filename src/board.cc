/**
* @file board.cc
* @brief Board implementation
* @author Dávid Bolvanský xbolva00
*/

#include <iostream>
#include "board.h"

/**
* Board constructor
*/
Board::Board() {
        this->game_count_limit = DEFAULT_GAME_COUNT_LIMIT;
}

/**
* Create new game
* @return pointer to new game
*/
Game * Board::create_new_game() {
        if (this->get_games_count() + 1 > this->get_games_count_limit()) {
                return nullptr;
        }

        Game * new_game = new Game {};
        return this->add_game(new_game);
}

/**
* Add game to board
* @param g pointer to game
* @return pointer to game
*/
Game * Board::add_game(Game *g) {
        std::shared_ptr<Game> game_ptr {g};
        this->games.push_back(game_ptr);
        return this->games.back().get();
}

/**
* Cancel (remove) game from board
* @return true on success, false otherwise
*/
bool Board::cancel_game(Game *g) {
        int i = 0;
        if ((i = this->get_game_id(g)) != -1) {
                this->games.erase(this->games.begin() + i);
                return true;
        }
        return false;
}

/**
* Get game index
* @param g pointer to game
* @return index of game, -1 if game was not found
*/
int Board::get_game_id(Game *g) {
        for (unsigned int i = 0; i < this->games.size(); ++i) {
                if (this->get_game(i) == g) {
                        return i;
                }
        }
        return -1;
}

/*
* Get game using index
* @param index index of game
* @return pointer to game
*/
Game * Board::get_game(int index) {
        if (index < 0 || index > this->get_games_count() - 1) {
                return nullptr;
        }
        return this->games[index].get();
}

/**
* Import game from filename
* @param filename file containg game
* @return pointer to game, nullptr if any failure during importing
*/
Game * Board::import_game(std::string filename) {
        if (this->get_games_count() + 1 > this->get_games_count_limit()) {
                return nullptr;
        }
        Game *imported_game = Game::load(filename);
        if (imported_game == nullptr) {
                return nullptr;
        }

        return this->add_game(imported_game);
}

/**
* Export game to filename
* @param filename save game to this filename
* @return true on success, false otherwise
*/
bool Board::export_game(int index, std::string filename) {
        Game *export_game = this->get_game(index);
        if (export_game == nullptr) {
                return false;
        }

        return export_game->save(filename);
}

/**
* Get number of games currently at board
* @return number of games at board
*/
int Board::get_games_count() {
        return this->games.size();
}

/**
* Set limit for maximum number of games at board
* @param limit maximum number of games
*/
void Board::set_game_count_limit(int limit) {
        this->game_count_limit = limit;
}

/**
* Get limit for maximum number of games at board
* @return maximum number of games
*/
int Board::get_games_count_limit() {
        return this->game_count_limit;
}
