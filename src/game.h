/**
* @file game.h
* @brief Game interface
* @author Dávid Bolvanský xbolva00
*/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <chrono>
#include "card.h"
#include "card_deck.h"
#include "card_stack.h"
#include "command.h"
#include "move.h"

const int DECKS_COUNT = 4; /**< Number of decks in game */
const int STACKS_COUNT = 7; /**< Number of stacks in game */
const int ALL_CARDS_COUNT = 52; /**< Number of all card */
const int CARDS_PER_PACK = 13; /**< // Number of cards in pack */
const int CARDS_PER_STACK = 19; /**< Maximal number of cards in stack */

class Game {
    CardDeck stock_deck {ALL_CARDS_COUNT};
    CardDeck waste_deck {ALL_CARDS_COUNT};

    CardDeck target_card_decks [DECKS_COUNT] = { CardDeck {CARDS_PER_PACK} , CardDeck {CARDS_PER_PACK}, CardDeck {CARDS_PER_PACK}, CardDeck {CARDS_PER_PACK}};
    CardStack working_card_stacks [STACKS_COUNT] = { CardStack {CARDS_PER_STACK}, CardStack {CARDS_PER_STACK}, CardStack {CARDS_PER_STACK},
                                                    CardStack {CARDS_PER_STACK}, CardStack {CARDS_PER_STACK}, CardStack {CARDS_PER_STACK}, CardStack {CARDS_PER_STACK}};
    int score;
    bool paused;
    std::chrono::high_resolution_clock::time_point started_at;
    std::chrono::high_resolution_clock::time_point paused_at;
    CommandManager command_manager;
    public:
    Game();
    Game(std::string filename);
    CardDeck * get_target_deck_by_id(int index);
    CardStack * get_working_stack_by_id(int index);
    CardDeck * get_stock_deck();
    CardDeck * get_waste_deck();
    bool save(std::string filename);
    static Game * load(std::string filename);
    int get_score();
    int get_moves_count();
    void start();
    void pause();
    void resume();

    void undo();
    bool move_card_from_stock_deck_to_waste_deck();
    bool move_card_from_waste_deck_to_working_stack(int stack_index);
    bool move_card_from_waste_deck_to_target_deck(int deck_index);
    bool move_card_from_target_deck_to_working_stack(int deck_index, int stack_index);
    bool move_card_from_working_stack_to_target_deck(int stack_index, int deck_index);
    bool move_cards_from_working_stack_to_working_stack(int src_stack_index , int dest_stack_index, int card_index);

    std::chrono::seconds get_total_time_in_seconds();
};

#endif // GAME_H
