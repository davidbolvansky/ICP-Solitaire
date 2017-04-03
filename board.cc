#include <iostream> // DEBUG
#include "board.h"

Board::Board() {
        this->game_count_limit = DEFAULT_GAME_COUNT_LIMIT;
}

Game * Board::create_new_game() {
        Game * new_game = new Game{};
        return this->add_game(new_game);
}

Game * Board::add_game(Game *g) {
        if (get_games_count() > this->get_games_count_limit()) {
                return nullptr;
        }

        std::shared_ptr<Game> game_ptr {g};
        this->games.push_back(game_ptr);
        return this->games.back().get();
}

Game * Board::get_game(int index) {
        if (index < 0 || index > this->get_games_count()) {
                return nullptr;
        }
        return this->games[index].get();
}

Game * Board::import_game(std::string filename) {
        Game *imported_game = Game::load(filename);
        if (imported_game == nullptr) {
                return nullptr;
        }

        return this->add_game(imported_game);
}

bool Board::export_game(int index, std::string filename) {
    Game *export_game = this->get_game(index);
    if (export_game == nullptr) {
        return false;
    }

    return export_game->save(filename);
}

int Board::get_games_count() {
        return Game::get_games_count();
}

void Board::set_game_count_limit(int limit) {
        this->game_count_limit = limit;
}

int Board::get_games_count_limit() {
        return this->game_count_limit;
}
