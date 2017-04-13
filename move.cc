#include "move.h"

Move::Move(MoveType move) {
        this->move = move;
}

Move::Move(MoveType move, int dest_index) {
        this->move = move;
        this->dest_index = dest_index;
}

Move::Move(MoveType move, int src_index, int dest_index){
        this->move = move;
        this->src_index = src_index;
        this->dest_index = dest_index;
}

Move::Move(MoveType move, int src_index, int dest_index, int card_index) {
        this->move = move;
        this->src_index = src_index;
        this->dest_index = dest_index;
        this->card_index = card_index;
}

MoveType Move::get_move_type() {
        return this->move;
}
int Move::get_source_index() {
        return this->src_index;
}
int Move::get_destination_index() {
        return this->dest_index;
}
int Move::get_card_index() {
        return this->card_index;
}

std::vector<Move> MoveFinder::get_available_moves(Game *game) {
        std::vector<Move> moves;

        // swap stock with waste deck
        if (game->get_stock_deck()->is_empty()) {
                if (!game->get_waste_deck()->is_empty()) {
                        moves.push_back(Move {STOCK_DECK_TO_WASTE_DECK});
                }
        } else { // take card from stock to waste
                moves.push_back(Move {STOCK_DECK_TO_WASTE_DECK});
        }

        if (!game->get_waste_deck()->is_empty()) {
                Card *waste_top = game->get_waste_deck()->get();

                // go thru target decks
                for (int i = 0; i < DECKS_COUNT; ++i) {
                        Card * target_top = game->get_target_deck_by_id(i)->get();
                        if (!target_top) {
                                if (waste_top->get_value() == 1) {
                                        moves.push_back(Move {WASTE_DECK_TO_TARGET_DECK, i});
                                }
                                continue;
                        }
                        if (waste_top->is_same_color(target_top->get_color()) && waste_top->compare_value(*target_top) == 1) {
                                moves.push_back(Move {WASTE_DECK_TO_TARGET_DECK, i});
                        }
                }

                // go thru working stacks
                for (int i = 0; i < STACKS_COUNT; ++i) {
                        Card * working_top = game->get_working_stack_by_id(i)->get();
                        if (!working_top) {
                                if (waste_top->get_value() == 13) {
                                        moves.push_back(Move {WASTE_DECK_TO_WORKING_STACK, i});
                                }
                                continue;
                        }
                        if (!waste_top->similar_color_to(*working_top) && waste_top->compare_value(*working_top) == -1) {
                                moves.push_back(Move {WASTE_DECK_TO_WORKING_STACK, i});
                        }
                }
        }


        // Stacks to stacks
        int i = 0;
        int j = 0;
        for (i = 0; i < STACKS_COUNT; ++i) {
                Card * working_top = game->get_working_stack_by_id(i)->get();
                if (!working_top) continue;

                for (j = 0; j < STACKS_COUNT; ++j) {

                        for (int c = 0; c < CARDS_PER_PACK; ++c) {
                                Card * working_card = game->get_working_stack_by_id(j)->get(c);
                                if (!working_card) {
                                        if (c == 0 && working_top->get_value() == 13) {
                                                moves.push_back(Move {WORKING_STACK_TO_WORKING_STACK, i, j, 1});
                                                break;
                                        }
                                        continue;
                                }

                                if (!working_card->is_turned_face_up()) {
                                        continue;
                                }

                                if (!working_top->similar_color_to(*working_card) && working_top->compare_value(*working_card) == 1) {
                                        moves.push_back(Move {WORKING_STACK_TO_WORKING_STACK, j, i, c});
                                        break;
                                }
                        }
                }
        }

        // Stacks to decks
        i = 0;
        j = 0;
        for (i = 0; i < STACKS_COUNT; ++i) {
                Card * working_top = game->get_working_stack_by_id(i)->get();
                if (!working_top) continue;

                for (j = 0; j < DECKS_COUNT; ++j) {
                        Card * target_top = game->get_target_deck_by_id(j)->get();
                        if (!target_top) {
                                if (working_top->get_value() == 1) {
                                        moves.push_back(Move {WORKING_STACK_TO_TARGET_DECK, i, j});
                                }
                                continue;
                        }
                        if (working_top->is_same_color(target_top->get_color()) && working_top->compare_value(*target_top) == 1) {
                                moves.push_back(Move {WORKING_STACK_TO_TARGET_DECK, i, j});
                        }
                }
        }

        // Decks to stacks
        i = 0;
        j = 0;
        for (i = 0; i < DECKS_COUNT; ++i) {
                Card * target_top = game->get_target_deck_by_id(i)->get();
                if (!target_top) continue;


                for (j = 0; j < STACKS_COUNT; ++j) {
                        Card * working_top = game->get_working_stack_by_id(j)->get();
                        if (!working_top) {
                                if (target_top->get_value() == 13) {
                                        moves.push_back(Move {TARGET_DECK_TO_WORKING_STACK, i, j});
                                }
                                continue;
                        }
                        if (!target_top->similar_color_to(*working_top) && target_top->compare_value(*working_top) == -1) {
                                moves.push_back(Move {TARGET_DECK_TO_WORKING_STACK, i, j});
                        }
                }
        }

        return moves;
}
