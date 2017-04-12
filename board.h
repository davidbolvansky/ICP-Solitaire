#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "game.h"

const int DEFAULT_GAME_COUNT_LIMIT = 4;

class Board {
    int game_count_limit;
    std::vector<std::shared_ptr<Game>> games;
    public:
    Board();
    Game * create_new_game();
    Game * add_game(Game *g);
    Game * get_game(int index);
    Game * import_game(std::string filename);
    bool cancel_game(Game *g);
    int get_game_by_id(Game *g);
    bool export_game(int index, std::string filename);
    int get_games_count();
    void set_game_count_limit(int limit);
    int get_games_count_limit();
};


#endif
