#include <iostream>
#include "card.h"
#include "card_deck.h"
#include "card_stack.h"
#include "game.h"

int Game::games_counter = 0;

Game::Game() {
    this->main_card_stack = CardDeck::create_standard_deck();
    this->main_card_stack.shuffle();

    for (int working_stack_index = 0; working_stack_index < STACKS_COUNT; ++working_stack_index) {
        for (int cards_per_pack = 0; cards_per_pack < working_stack_index + 1; ++cards_per_pack) {
            Card top = *this->main_card_stack.pop();
            if (working_stack_index == cards_per_pack) {
                top.turn_face_up();
            }
            this->working_card_stacks[working_stack_index].push(top);
        }

        this->working_card_stacks[working_stack_index].print();
    }

    std::cout<< "Zostatok pre main stack" << std::endl;

    this->main_card_stack.print();

    games_counter++;
}

bool Game::save_game() {
    // todo
}

Game Game::load_game() {
    Game a;
    return a;
}

int Game::get_games_count() {
    return games_counter;
}
