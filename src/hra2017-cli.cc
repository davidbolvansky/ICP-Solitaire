/**
* @file: hra2017-cli.cc
* @brief: implementation of command line version of Solitaire
* @author: Dávid Bolvanský xbolva00
*/

#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <vector>
#include "board.h"

// Left offset of cli window
const int LEFT_WINDOW_OFFSET = 2;
// Placeholder for not existing card in deck
const char * NO_DECK_CARD = " -- ";
// Placeholder for not existing card in stack
const char * NO_STACK_CARD = "    ";
// Placeholder for card which is turned face down
const char * FACE_DOWN_CARD = "-(-)";

/**
* Get name of target deck
* @game: pointer to game
* @index index of target deck
* @return: target deck name
*/
const char * get_target_deck_name(Game * game, int index) {
        switch (game->get_target_deck_by_id(index)->get_color()) {
        case SPADES: return "Spades  ";
        case DIAMONDS: return "Diamonds";
        case HEARTS: return "Hearts  ";
        case CLUBS: return "Clubs   ";
        }
        return "        ";
}

/**
* Show hints about possible moves
* @game: pointer to game
* @screen: show hints to this screen
*/
void show_hints(Game *game, WINDOW *screen) {
        std::vector<Move> moves = MoveFinder::get_available_moves(game);
        std::string hint;
        mvwprintw(screen, 1, LEFT_WINDOW_OFFSET, "Hints:");
        for (int i = 0; i < moves.size(); ++i) {
                Move move = moves[i];
                switch (move.get_move_type()) {
                case STOCK_DECK_TO_WASTE_DECK:
                        hint = "Card from stock deck to waste deck";
                        break;
                case WASTE_DECK_TO_TARGET_DECK:
                        hint = "Card from waste deck to " + std::to_string(move.get_destination_index() + 1)  + ". target deck";
                        break;
                case WASTE_DECK_TO_WORKING_STACK:
                        hint = "Card from waste deck to " + std::to_string(move.get_destination_index() + 1) + ". working pack";
                        break;
                case TARGET_DECK_TO_WORKING_STACK:
                        hint = "Card from " + std::to_string(move.get_source_index() + 1) + ". target deck to " + std::to_string(move.get_destination_index() + 1) + ". working stack";
                        break;
                case WORKING_STACK_TO_TARGET_DECK:
                        hint = "Card from " + std::to_string(move.get_source_index() + 1) + ". working stack to " + std::to_string(move.get_destination_index() + 1) + ". target deck";
                        break;
                case WORKING_STACK_TO_WORKING_STACK:
                        hint = "Card from " + std::to_string(move.get_source_index() + 1) + ". working stack to " + std::to_string(move.get_destination_index() + 1) + ". working stack since " + std::to_string(move.get_card_index() + 1) + ". card";
                        break;
                }

                mvwprintw(screen, i + 2, LEFT_WINDOW_OFFSET, hint.c_str());
        }

        mvwprintw(screen, moves.size() + 3, LEFT_WINDOW_OFFSET, "Press Enter to return to game board...");
}

/**
* Run CLI version of Solitaire game
* @argc: number of arguments
* @argv: arguments
* @return: 0 if no error, 1 if any error when playing game
*/
int main(int argc, char *argv[]) {
        Board main {};
        Game * game = main.create_new_game();
        game->start();

        int parent_x, parent_y, new_x, new_y;
        int game_info_size =  3;



        initscr();
        noecho();
        curs_set(FALSE);
        nodelay(stdscr, TRUE);

        // set up initial windows
        getmaxyx(stdscr, parent_y, parent_x);

        WINDOW *game_board = newwin(parent_y - game_info_size, parent_x, 0, 0);
        WINDOW *game_info = newwin(game_info_size, parent_x, parent_y - game_info_size, 0);
        while(1) {
                getmaxyx(stdscr, new_y, new_x);

                if (new_y != parent_y || new_x != parent_x) {
                        parent_x = new_x;
                        parent_y = new_y;

                        wresize(game_board, new_y - game_info_size, new_x);
                        wresize(game_info, game_info_size, new_x);
                        mvwin(game_info, new_y - game_info_size, 0);

                        wclear(stdscr);
                        wclear(game_board);
                        wclear(game_info);
                }

                // draw to our windows
                werase(game_board);
                mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "  Stock\t   Waste\t\t%s  %s  %s  %s", get_target_deck_name(game, 0), get_target_deck_name(game, 1), get_target_deck_name(game, 2), get_target_deck_name(game, 3));
                mvwprintw(game_board, 3, LEFT_WINDOW_OFFSET, "   %s\t    %s\t\t  %s\t   %s      %s      %s",
                          game->get_stock_deck()->is_empty() ? "<=>" : "==>", game->get_waste_deck()->is_empty() ? NO_DECK_CARD : game->get_waste_deck()->get()->to_string().c_str(),
                          game->get_target_deck_by_id(Color::SPADES)->is_empty() ? NO_DECK_CARD : game->get_target_deck_by_id(Color::SPADES)->get()->to_string().c_str(),
                          game->get_target_deck_by_id(Color::DIAMONDS)->is_empty() ? NO_DECK_CARD : game->get_target_deck_by_id(Color::DIAMONDS)->get()->to_string().c_str(),
                          game->get_target_deck_by_id(Color::HEARTS)->is_empty() ? NO_DECK_CARD : game->get_target_deck_by_id(Color::HEARTS)->get()->to_string().c_str(),
                          game->get_target_deck_by_id(Color::CLUBS)->is_empty() ? NO_DECK_CARD : game->get_target_deck_by_id(Color::CLUBS)->get()->to_string().c_str());
                mvwprintw(game_board, 5, LEFT_WINDOW_OFFSET, "Stack 1    Stack 2    Stack 3    Stack 4    Stack 5    Stack 6    Stack 7");
                for (int i = 0; i <  13; ++i) {

                        int offset = i + 1 >= 10 ? 1 : 2;
                        mvwprintw(game_board, 6 + i, offset, "%d %s\t%s\t %s\t    %s\t%s\t  %s\t     %s", i + 1,
                                  game->get_working_stack_by_id(0)->get(i) == nullptr ? NO_STACK_CARD : game->get_working_stack_by_id(0)->get(i)->is_turned_face_up() ? game->get_working_stack_by_id(0)->get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(1)->get(i)  == nullptr ? NO_STACK_CARD : game->get_working_stack_by_id(1)->get(i)->is_turned_face_up() ? game->get_working_stack_by_id(1)->get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(2)->get(i)  == nullptr ? NO_STACK_CARD : game->get_working_stack_by_id(2)->get(i)->is_turned_face_up() ? game->get_working_stack_by_id(2)->get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(3)->get(i) == nullptr ? NO_STACK_CARD : game->get_working_stack_by_id(3)->get(i)->is_turned_face_up() ? game->get_working_stack_by_id(3)->get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(4)->get(i)  == nullptr ? NO_STACK_CARD : game->get_working_stack_by_id(4)->get(i)->is_turned_face_up() ? game->get_working_stack_by_id(4)->get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(5)->get(i)  == nullptr ? NO_STACK_CARD : game->get_working_stack_by_id(5)->get(i)->is_turned_face_up() ? game->get_working_stack_by_id(5)->get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(6)->get(i)  == nullptr ? NO_STACK_CARD : game->get_working_stack_by_id(6)->get(i)->is_turned_face_up() ? game->get_working_stack_by_id(6)->get(i)->to_string().c_str() : FACE_DOWN_CARD);
                }

                int total_time = game->get_total_time_in_seconds().count();
                std::string game_time;
                int minutes = total_time / 60;
                int seconds = total_time % 60;
                if (minutes == 1) {
                        game_time += "1 minute ";
                } else if (minutes > 1) {
                        game_time += std::to_string(minutes) + " minutes ";
                }

                if (seconds == 1) {
                        game_time += "1 second";
                } else if (seconds > 1) {
                        game_time += std::to_string(seconds) + " seconds";
                }

                werase(game_info);
                mvwprintw(game_info, 1, LEFT_WINDOW_OFFSET, "Moves: %d | Time: %s | Score: %d | Game: %d / %d", game->get_moves_count(), game_time.data(), game->get_score(), main.get_game_id(game) + 1, main.get_games_count());

                if (game->get_total_time_in_seconds().count() <  20) {

                }

                int c = getch();
                if (c == 'c') {
                        std::string command;
                        std::cin >> command;

                        if (command == "g") {
                                game->move_card_from_stock_deck_to_waste_deck();
                        } else if (command.substr(0, 2) == "ws") {
                                int i = atoi(command.substr(2,3).data()) - 1;
                                if (!game->move_card_from_waste_deck_to_working_stack(i)) {
                                        wclear(game_board);
                                        mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Invalid move.");
                                        wrefresh(game_board);
                                        sleep(1);
                                }
                        } else if (command.substr(0, 2) == "wd") {
                                int i = atoi(command.substr(2,3).data()) - 1;
                                if (!game->move_card_from_waste_deck_to_target_deck(i)) {
                                        wclear(game_board);
                                        mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Invalid move.");
                                        wrefresh(game_board);
                                        sleep(1);
                                }
                        } else if (command.size() == 4 && command[0] == 'd' && command[2] == 's') {
                                int deck_index = command[1] - '0' - 1;
                                int stack_index = command[3]- '0' - 1;
                                if (!game->move_card_from_target_deck_to_working_stack(deck_index, stack_index)) {
                                        wclear(game_board);
                                        mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Invalid move.");
                                        wrefresh(game_board);
                                        sleep(1);
                                }
                        } else if (command.size() == 4 && command[0] == 's' && command[2] == 'd') {
                                int stack_index  = command[1] - '0' - 1;
                                int deck_index = command[3]- '0' - 1;
                                if (!game->move_card_from_working_stack_to_target_deck(stack_index, deck_index)) {
                                        wclear(game_board);
                                        wclear(game_info);
                                        mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Invalid move.");
                                        wrefresh(game_board);
                                        sleep(1);
                                        wrefresh(game_info);
                                }
                        } else if (command.size() == 6 && command[0] == 's' && command[2] == 's') {
                                int src_stack_index  = command[1] - '0' - 1;
                                int dest_stack_index = command[3]- '0' - 1;
                                int card_index = command[5]- '0' - 1;

                                if (!(game->move_cards_from_working_stack_to_working_stack(src_stack_index, dest_stack_index, card_index))) {
                                        wclear(game_board);
                                        wclear(game_info);
                                        mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Invalid move.");
                                        wrefresh(game_board);
                                        sleep(1);
                                        wrefresh(game_info);
                                }
                        } else if (command.size() == 7 && command[0] == 's' && command[2] == 's' && command[4] == 'c') {
                                int src_stack_index  = command[1] - '0' - 1;
                                int dest_stack_index = command[3]- '0' - 1;
                                int card_index = atoi(command.substr(5, 7).data()) - 1;

                                if (!(game->move_cards_from_working_stack_to_working_stack(src_stack_index, dest_stack_index, card_index))) {
                                        wclear(game_board);
                                        wclear(game_info);
                                        mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Invalid move.");
                                        wrefresh(game_board);
                                        sleep(1);
                                        wrefresh(game_info);
                                }
                        }

                } else if (c == 'h') {
                        wclear(game_board);
                        wclear(game_info);
                        mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Help:");
                        mvwprintw(game_board, 2, LEFT_WINDOW_OFFSET, "c - Control mode");
                        mvwprintw(game_board, 3, LEFT_WINDOW_OFFSET, "e - Exit game");
                        mvwprintw(game_board, 4, LEFT_WINDOW_OFFSET, "p - Pause game");
                        mvwprintw(game_board, 5, LEFT_WINDOW_OFFSET, "r - Resume game");
                        mvwprintw(game_board, 6, LEFT_WINDOW_OFFSET, "n - New game");
                        mvwprintw(game_board, 7, LEFT_WINDOW_OFFSET, "g[1-4] - Switch game");
                        mvwprintw(game_board, 8, LEFT_WINDOW_OFFSET, "s - Save game");
                        mvwprintw(game_board, 9, LEFT_WINDOW_OFFSET, "l - Load game");
                        mvwprintw(game_board, 10, LEFT_WINDOW_OFFSET, "u - Undo");
                        mvwprintw(game_board, 11, LEFT_WINDOW_OFFSET, "m - Move hint");

                        mvwprintw(game_board, 13, LEFT_WINDOW_OFFSET, "Control mode:");
                        mvwprintw(game_board, 14, LEFT_WINDOW_OFFSET, "g - Get card from stock deck to waste deck");
                        mvwprintw(game_board, 15, LEFT_WINDOW_OFFSET, "ws[1-7] - Take card from waste deck stack 1 - 7");
                        mvwprintw(game_board, 16, LEFT_WINDOW_OFFSET, "wd[1-4] - Take card from waste deck to deck 1 - 4");
                        mvwprintw(game_board, 17, LEFT_WINDOW_OFFSET, "d[1-4]s[1-7] - Take card from deck 1 - 4 to stack 1 - 7");
                        mvwprintw(game_board, 18, LEFT_WINDOW_OFFSET, "s[1-7]d[1-4] - Take card from stack 1 - 7 to deck 1 - 4");
                        mvwprintw(game_board, 19, LEFT_WINDOW_OFFSET, "s[1-7]s[1-7]c[1-13] - Take card 1 - 13 from stack 1 - 7 to stack 1 - 7");

                        mvwprintw(game_info, 1, LEFT_WINDOW_OFFSET, "Press Enter to return to game board...");

                        wrefresh(game_board);
                        wrefresh(game_info);
                        std::cin.ignore();
                } else if (c == 'p') {
                        game->pause();
                } else if (c == 'r') {
                        game->resume();
                } else if (c == 'n') {
                        Game * backup = game;
                        if((game = main.create_new_game()) == nullptr) {
                                wclear(game_board);
                                wclear(game_info);
                                mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Cannot not start new game. Reached maximum number of games (%d).", main.get_games_count_limit());
                                wrefresh(game_board);
                                wrefresh(game_info);
                                sleep(1);

                                if (backup == nullptr) {
                                        endwin();
                                        exit(EXIT_FAILURE);
                                } else {
                                        game = backup;
                                }
                        } else {
                                if (backup != nullptr) {
                                        backup->pause();
                                }
                        }
                        game->start();
                } else if (c == 'g') {
                        game->pause();
                        std::string id;
                        std::cin >> id;
                        if (id.size() > 1) {
                                continue;
                        }
                        int game_index = id[0] - '0' - 1;
                        Game * backup = game;
                        if((game = main.get_game(game_index)) == nullptr) {
                                wclear(game_board);
                                wclear(game_info);
                                mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Cannot not switch to game.");
                                wrefresh(game_board);
                                wrefresh(game_info);
                                sleep(1);

                                if (backup == nullptr) {
                                        endwin();
                                        exit(EXIT_FAILURE);
                                } else {
                                        game = backup;
                                }
                        } else {
                                if (backup != nullptr) {
                                        backup->pause();
                                }
                        }
                        game->resume();
                } else if (c == 'e') {
                        break;
                } else if (c == 's') {
                        wclear(game_board);
                        wclear(game_info);
                        mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Enter file name:");
                        wrefresh(game_board);
                        wrefresh(game_info);
                        std::string filename;
                        std::cin >> filename;
                        if(!main.export_game(main.get_game_id(game), filename)) {
                                wclear(game_board);
                                wclear(game_info);
                                mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Cannot not save game.");
                                wrefresh(game_board);
                                wrefresh(game_info);
                                sleep(1);
                        }
                } else if (c == 'l') {
                        wclear(game_board);
                        wclear(game_info);
                        mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Enter file name:");
                        wrefresh(game_board);
                        wrefresh(game_info);
                        std::string filename;
                        std::cin >> filename;
                        Game * backup = game;
                        if(!(game = main.import_game(filename))) {
                                wclear(game_board);
                                wclear(game_info);
                                mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Cannot not load game.");
                                wrefresh(game_board);
                                wrefresh(game_info);
                                sleep(1);

                                if (backup == nullptr) {
                                        endwin();
                                        exit(EXIT_FAILURE);
                                } else {
                                        game = backup;
                                }
                        } else {
                                if (backup != nullptr) {
                                        backup->pause();
                                }
                        }
                        game->start();
                } else if (c  == 'u') {
                        game->undo();
                } else if (c  == 'm') {
                        wclear(game_board);
                        wclear(game_info);
                        show_hints(game, game_board);
                        wrefresh(game_board);
                        wrefresh(game_info);
                        std::cin.ignore();
                } else if (c  == 'x') {
                        main.cancel_game(game);
                        if (main.get_games_count() == 0) {
                            break;
                        }
                        game = main.get_game(0);
                }

                wrefresh(game_board);
                wrefresh(game_info);
        }

        endwin();

        return EXIT_SUCCESS;
}
