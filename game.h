#ifndef GAME_H
#define GAME_H

#include <vector>
#include <chrono>
#include "card.h"

const int DECKS_COUNT = 4;
const int STACKS_COUNT = 7;
const int ALL_CARDS_COUNT = 52;
const int CARDS_PER_PACK = 13;

class Game {
    CardDeck main_card_stack {ALL_CARDS_COUNT};
    CardDeck main_visible_card_stack {ALL_CARDS_COUNT};

    CardDeck target_spades_deck {CARDS_PER_PACK, SPADES};
    CardDeck target_diamonds_deck {CARDS_PER_PACK, DIAMONDS};
    CardDeck target_hearts_deck {CARDS_PER_PACK, HEARTS};
    CardDeck target_clubs_deck {CARDS_PER_PACK, CLUBS};

    CardStack working_card_stacks [STACKS_COUNT] = { CardStack {CARDS_PER_PACK}, CardStack {CARDS_PER_PACK}, CardStack {CARDS_PER_PACK},
                                                    CardStack {CARDS_PER_PACK}, CardStack {CARDS_PER_PACK}, CardStack {CARDS_PER_PACK}, CardStack {CARDS_PER_PACK}};
    int score;
    std::chrono::high_resolution_clock::time_point timer;
    static int games_counter;
    public:
    Game();
    bool save_game();
    Game load_game();

static int get_games_count();
};

#endif // GAME_H
