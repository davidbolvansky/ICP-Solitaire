#include <iostream>
#include "game.h"


int Game::games_counter = 0;

Game::Game() {
        this->main_card_deck = CardDeck::create_standard_deck();
        this->main_card_deck.shuffle();

        for (int working_stack_index = 0; working_stack_index < STACKS_COUNT; ++working_stack_index) {
                for (int cards_per_pack = 0; cards_per_pack < working_stack_index + 1; ++cards_per_pack) {
                        Card top = *this->main_card_deck.pop();
                        //std::cout << top.to_string() << "\n";
                        if (working_stack_index == cards_per_pack) {
                                top.turn_face_up();
                        }
                        this->working_card_stacks[working_stack_index].push(top);
                }
                //std::cout << "top" << this->working_card_stacks[working_stack_index].get()->to_string() << "\n";
                //this->working_card_stacks[working_stack_index].print();
        }
        /*Card a = Card{Color::SPADES, 1};
           this->target_card_decks[0].put(a);

           this->target_card_decks[0].print();

           this->working_card_stacks[6].print();

           MoveDeckToStackCommand *dts = new MoveDeckToStackCommand {&this->target_card_decks[0], &this->working_card_stacks[6]};
           std::shared_ptr<Command> cmd {dts};
           this->command_manager.execute_command(cmd);

           this->working_card_stacks[6].print();

           exit(0);*/

        /*std::cout<< "Zostatok pre main stack" << std::endl;

           this->main_card_deck.print();
           this->discard_card_deck.print();

           std::cout<< "Command execute move DTD" << std::endl;


           MoveDeckToDeckCommand *dtd = new MoveDeckToDeckCommand {&this->main_card_deck, &this->discard_card_deck};

           std::shared_ptr<Command> p{dtd};

           for (int i = 0; i < 3; ++i) {
            this->command_manager.execute_command(p);
           }

           this->main_card_deck.print();
           this->discard_card_deck.print();

           for (int i = 0; i < 4; ++i) {
            //this->command_manager.undo_command();
           }

           std::cout << "Main\n";
           this->main_card_deck.print();
           std::cout << "Final\n";
           this->discard_card_deck.print();
           std::cout << "First stack\n";
           this->working_card_stacks[0].print();

           MoveDeckToStackCommand *dts = new MoveDeckToStackCommand {&this->discard_card_deck, &this->working_card_stacks[0]};
           std::shared_ptr<Command> f{dts};
           this->command_manager.execute_command(f);
           this->command_manager.execute_command(f);
           this->command_manager.undo_command();
           std::cout << "Exec\n";
           std::cout << "Main\n";
           this->main_card_deck.print();
           std::cout << "Final SRC\n";
           this->discard_card_deck.print();
           std::cout << "First stack DST\n";
           this->working_card_stacks[0].print();

           /*MoveStackToDeckCommand *dts = new MoveStackToDeckCommand {&this->working_card_stacks[6], &this->target_diamonds_deck};

           std::shared_ptr<Command> l{dts};

           this->target_diamonds_deck.print();
           this->working_card_stacks[6].print();

           for (int i = 0; i < 5; ++i) {
            this->command_manager.execute_command(l);
           }

           for (int i = 0; i < 2; ++i) {
            this->command_manager.undo_command();
           }

           this->target_diamonds_deck.print();
           this->working_card_stacks[6].print();*/

        /*for (int i = 0; i < 4; ++i) {
            this->command_manager.undo_command();
           }

           this->discard_card_deck.print();
           this->working_card_stacks[2].print();*/

        /*std::cout<< "Command undo move DTD" << std::endl;

           this->command_manager.undo_command();

           MoveStackToStackCommand *f = new MoveStackToStackCommand {&this->working_card_stacks[4], &this->working_card_stacks[2]};
           std::shared_ptr<Command> s{f};

           std::cout<< "Move from 4 to 2 DTD" << std::endl;

           this->working_card_stacks[2].print();
           this->working_card_stacks[4].print();

           if (this->command_manager.execute_command(s)) {
            std::cout << "MOVE ok\n";
           } else {
            std::cout << "MOVE not ok\n";
           }

           this->working_card_stacks[2].print();
           this->working_card_stacks[4].print();

           std::cout<< "Now UNDO last command" << std::endl;

           this->command_manager.undo_command();

           this->working_card_stacks[2].print();
           this->working_card_stacks[4].print();

           //this->main_card_deck.print();
           //this->discard_card_deck.print();*/

        games_counter++;
}


void Game::undo() {
        this->command_manager.undo_command();
}

bool Game::get_card_from_main_deck_to_discard_deck() {
        MoveMainDeckToDiscardDeckCommand *dtd = new MoveMainDeckToDiscardDeckCommand {&this->main_card_deck, &this->discard_card_deck};
        std::shared_ptr<Command> cmd {dtd};
        return this->command_manager.execute_command(cmd);
}

bool Game::move_card_from_discard_deck_to_working_stack(int stack_index) {
        if (stack_index < 0 || stack_index > 6) {
                return false;
        }
        MoveDeckToStackCommand *dts = new MoveDeckToStackCommand {&this->discard_card_deck, &this->working_card_stacks[stack_index]};
        std::shared_ptr<Command> cmd {dts};
        return this->command_manager.execute_command(cmd);
}

bool Game::move_card_from_discard_deck_to_target_deck(int deck_index) {
        if (deck_index < 0 || deck_index > 3) {
                return false;
        }
        MoveDeckToDeckCommand *dtd = new MoveDeckToDeckCommand {&this->discard_card_deck, &this->target_card_decks[deck_index]};
        std::shared_ptr<Command> cmd {dtd};
        return this->command_manager.execute_command(cmd);
}

bool Game::move_card_from_target_deck_to_working_stack(int deck_index, int stack_index) {
        if (deck_index < 0 || deck_index > DECKS_COUNT - 1) {
                return false;
        }
        if (stack_index < 0 || stack_index > STACKS_COUNT - 1) {
                return false;
        }
        MoveDeckToStackCommand *dts = new MoveDeckToStackCommand {&this->target_card_decks[deck_index], &this->working_card_stacks[stack_index]};
        std::shared_ptr<Command> cmd {dts};
        return this->command_manager.execute_command(cmd);
}

bool Game::move_card_from_working_stack_to_target_deck(int stack_index, int deck_index) {
        if (deck_index < 0 || deck_index > DECKS_COUNT - 1) {
                return false;
        }
        if (stack_index < 0 || stack_index > STACKS_COUNT - 1) {
                return false;
        }
        MoveStackToDeckCommand *std = new MoveStackToDeckCommand {&this->working_card_stacks[stack_index], &this->target_card_decks[deck_index]};
        std::shared_ptr<Command> cmd {std};
        return this->command_manager.execute_command(cmd);
}

bool Game::move_cards_from_working_stack_to_working_stack(int src_stack_index, int dest_stack_index, int card_index) {
        if (src_stack_index < 0 || src_stack_index > STACKS_COUNT - 1) {
                return false;
        }
        if (dest_stack_index < 0 || dest_stack_index > STACKS_COUNT - 1) {
                return false;
        }
        if (card_index < 0 || card_index > CARDS_PER_PACK - 1) {
                return false;
        }

        Card * top = get_working_stack_by_id(src_stack_index)->get(card_index);
        if (top == nullptr) {
            return false;
        }

        FILE *p=fopen("afddj", "w+");
        fprintf(p, "FF %s\n", top->to_string().c_str());
        fclose(p);

        MoveStackToStackCommand *sts = new MoveStackToStackCommand {&this->working_card_stacks[src_stack_index], &this->working_card_stacks[dest_stack_index], top};
        std::shared_ptr<Command> cmd{sts};
        return this->command_manager.execute_command(cmd);
}

CardDeck * Game::get_target_deck_by_id(int index) {
        return &target_card_decks[index];
}

CardStack * Game::get_working_stack_by_id(int index) {
        return &this->working_card_stacks[index];
}

CardDeck * Game::get_main_card_deck() {
        return &this->main_card_deck;
}

CardDeck * Game::get_discard_card_deck() {
        return &this->discard_card_deck;
}

bool Game::save(std::string filename) {
        // todo
}

Game * Game::load(std::string filename) {
        Game *loaded_game = new Game;
        return loaded_game;
}

int Game::get_games_count() {
        return games_counter;
}

int Game::get_score() {
        int score = 0;
        for (int i = 0; i < DECKS_COUNT; ++i) {
                score += this->get_target_deck_by_id(i)->get_size();
        }

        return score;
}

int Game::get_moves_count() {
        return this->command_manager.get_size();
}

void Game::start() {
        this->started_at = std::chrono::high_resolution_clock::now();
        this->paused = false;
}

void Game::pause() {
        if (this->paused) return;
        this->paused_at = std::chrono::high_resolution_clock::now();
        this->paused = true;
}

void Game::resume() {
        if (!this->paused) return;
        this->started_at += std::chrono::high_resolution_clock::now() - this->paused_at;
        this->paused = false;
}

// http://www.informit.com/articles/article.aspx?p=1881386&seqNum=2
std::chrono::seconds Game::get_total_time_in_seconds() {
        if (this->paused) {
                return std::chrono::duration_cast<std::chrono::seconds>(this->paused_at - this->started_at);
        }
        else {
                return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - this->started_at);
        }
}
