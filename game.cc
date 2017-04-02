#include <iostream>
#include "card.h"
#include "card_deck.h"
#include "card_stack.h"
#include "game.h"
#include "command.h"


int Game::games_counter = 0;

Game::Game() {
        this->main_card_deck = CardDeck::create_standard_deck();
        this->main_card_deck.shuffle();

        for (int working_stack_index = 0; working_stack_index < STACKS_COUNT; ++working_stack_index) {
                for (int cards_per_pack = 0; cards_per_pack < working_stack_index + 1; ++cards_per_pack) {
                        Card top = *this->main_card_deck.pop();
                        if (working_stack_index == cards_per_pack) {
                                top.turn_face_up();
                        }
                        this->working_card_stacks[working_stack_index].push(top);
                }

                this->working_card_stacks[working_stack_index].print();
        }

        std::cout<< "Zostatok pre main stack" << std::endl;

        this->main_card_deck.print();
        this->main_visible_card_deck.print();

        std::cout<< "Command execute move DTD" << std::endl;


        MoveDeckToDeckCommand *dtd = new MoveDeckToDeckCommand {&this->main_card_deck, &this->main_visible_card_deck};

        CommandManager cm;
        std::shared_ptr<Command> p{dtd};

        for (int i = 0; i < 8; ++i) {
            cm.execute_command(p);
        }

        this->main_card_deck.print();
        this->main_visible_card_deck.print();

        std::cout<< "Command undo move DTD" << std::endl;

        cm.undo_command();


        this->main_card_deck.print();
        this->main_visible_card_deck.print();


        games_counter++;
}

CardDeck Game::get_target_deck_by_color(Color c) {
        switch (c) {
        case SPADES: return this->target_spades_deck;
                break;

        case DIAMONDS: return this->target_diamonds_deck;
                break;

        case HEARTS: return this->target_hearts_deck;
                break;

        case CLUBS: return this->target_clubs_deck;
                break;

        default:
                throw std::out_of_range ("target deck out of range");
                break;
        }
}

CardStack Game::get_working_stack_by_id(int index) {
        if (index < 0 || index > 6) {
                throw std::out_of_range ("working stack out of range");
        }
        return this->working_card_stacks[index];
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
