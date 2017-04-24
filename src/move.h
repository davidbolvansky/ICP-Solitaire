/**
* @file: move.h
* @brief: Move and Move Finder interfaces
* @author: Dávid Bolvanský xbolva00
*/

#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include "game.h"

// Forward declaration
class Game;

// All Solitaire moves
enum MoveType {STOCK_DECK_TO_WASTE_DECK, WASTE_DECK_TO_TARGET_DECK, WASTE_DECK_TO_WORKING_STACK, TARGET_DECK_TO_WORKING_STACK, WORKING_STACK_TO_TARGET_DECK, WORKING_STACK_TO_WORKING_STACK};

class Move {
    MoveType move;
    int src_index;
    int dest_index;
    int card_index;
    public:
    Move(MoveType move);
    Move(MoveType move, int dest_index);
    Move(MoveType move, int src_index, int dest_index);
    Move(MoveType move, int src_index, int dest_index, int card_index);
    MoveType get_move_type();
    int get_source_index();
    int get_destination_index();
    int get_card_index();
};

class MoveFinder {
    Game *game;
    public:
    MoveFinder();
    static std::vector<Move> get_available_moves(Game *game);
};

#endif // MOVE_H
