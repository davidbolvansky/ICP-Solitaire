#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "board.h"

const int LEFT_WINDOW_OFFSET = 2;
const char * NO_CARD = " -- ";
const char * FACE_DOWN_CARD = "-(-)";

void draw_borders(WINDOW *screen) {
        int x, y, i;

        getmaxyx(screen, y, x);

        // 4 corners
        mvwprintw(screen, 0, 0, "+");
        mvwprintw(screen, y - 1, 0, "+");
        mvwprintw(screen, 0, x - 1, "+");
        mvwprintw(screen, y - 1, x - 1, "+");

        // sides
        for (i = 1; i < (y - 1); i++) {
                mvwprintw(screen, i, 0, "|");
                mvwprintw(screen, i, x - 1, "|");
        }

        // top and bottom
        for (i = 1; i < (x - 1); i++) {
                mvwprintw(screen, 0, i, "-");
                mvwprintw(screen, y - 1, i, "-");
        }
}

void draw_line(WINDOW *screen, int x, int y) {
        for (int i = 1; i < (x - 1); i++) {
                mvwprintw(screen, y, i, "-");
        }
}

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

        //draw_borders(game_board);
        //draw_borders(game_info);

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

                        draw_borders(game_board);
                        draw_borders(game_info);
                }

                // draw to our windows
                mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Main Deck\tDiscard Deck\t\tSpades  Diamonds  Hearts  Clubs");
                draw_line(game_board, parent_x, 2);
                mvwprintw(game_board, 3, LEFT_WINDOW_OFFSET, "   %s\t    %s\t\t %s\t %s\t  %s\t  %s",
                          game->get_main_card_deck()->is_empty() ? "<=>" : "==>", game->get_discard_card_deck()->is_empty() ? NO_CARD : game->get_discard_card_deck()->get()->to_string().c_str(),
                          game->get_target_deck_by_id(Color::SPADES)->is_empty() ? NO_CARD : game->get_target_deck_by_id(Color::SPADES)->get()->to_string().c_str(),
                          game->get_target_deck_by_id(Color::DIAMONDS)->is_empty() ? NO_CARD : game->get_target_deck_by_id(Color::DIAMONDS)->get()->to_string().c_str(),
                          game->get_target_deck_by_id(Color::HEARTS)->is_empty() ? NO_CARD : game->get_target_deck_by_id(Color::HEARTS)->get()->to_string().c_str(),
                          game->get_target_deck_by_id(Color::CLUBS)->is_empty() ? NO_CARD : game->get_target_deck_by_id(Color::CLUBS)->get()->to_string().c_str());
                draw_line(game_board, parent_x, 4);
                mvwprintw(game_board, 5, LEFT_WINDOW_OFFSET, "Stack 1    Stack 2    Stack 3    Stack 4    Stack 5    Stack 6    Stack 7");
                for (int i = 0; i <  13; ++i) {

                        int offset = i + 1 >= 10 ? 1 : 2;
                        mvwprintw(game_board, 6 + i, offset, "%d %s\t%s\t %s\t    %s\t%s\t  %s\t     %s", i + 1,
                                  game->get_working_stack_by_id(0)->get(i) == nullptr ? NO_CARD : game->get_working_stack_by_id(0)->get(i)->is_turned_face_up() ? game->get_working_stack_by_id(0)->get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(1)->get(i)  == nullptr ? NO_CARD : game->get_working_stack_by_id(1)->get(i)->is_turned_face_up() ? game->get_working_stack_by_id(1)->get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(2)->get(i)  == nullptr ? NO_CARD : game->get_working_stack_by_id(2)->get(i)->is_turned_face_up() ? game->get_working_stack_by_id(2)->get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(3)->get(i) == nullptr ? NO_CARD : game->get_working_stack_by_id(3)->get(i)->is_turned_face_up() ? game->get_working_stack_by_id(3)->get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(4)->get(i)  == nullptr ? NO_CARD : game->get_working_stack_by_id(4)->get(i)->is_turned_face_up() ? game->get_working_stack_by_id(4)->get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(5)->get(i)  == nullptr ? NO_CARD : game->get_working_stack_by_id(5)->get(i)->is_turned_face_up() ? game->get_working_stack_by_id(5)->get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(6)->get(i)  == nullptr ? NO_CARD : game->get_working_stack_by_id(6)->get(i)->is_turned_face_up() ? game->get_working_stack_by_id(6)->get(i)->to_string().c_str() : FACE_DOWN_CARD);
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

                mvwprintw(game_info, 1, LEFT_WINDOW_OFFSET, "Moves: %d | Time: %s | Score: %d", game->get_moves_count(), game_time.data(), game->get_score());

                if (game->get_total_time_in_seconds().count() <  20) {

                }

                int c = getch();
                if (c == 'c') {
                        std::string command;
                        std::cin >> command;

                        if (command == "g") {
                                game->get_card_from_main_deck_to_discard_deck();
                        } else if (command.substr(0, 3) == "dds") {
                                int i = atoi(command.substr(3, 4).data()) - 1;
                                if (!game->move_card_from_discard_deck_to_working_stack(i)) {
                                        wclear(game_board);
                                        mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Invalid move.");
                                        wrefresh(game_board);
                                        sleep(1);
                                }
                        } else if (command.substr(0, 3) == "ddd") {
                                int i = atoi(command.substr(3, 4).data()) - 1;
                                if (!game->move_card_from_discard_deck_to_target_deck(i)) {
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
                                if (!game->move_card_from_working_stack_to_target_deck(stack_index , deck_index)) {
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

                                if (!(game->move_cards_from_working_stack_to_working_stack(src_stack_index , dest_stack_index, card_index))) {
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

                                if (!(game->move_cards_from_working_stack_to_working_stack(src_stack_index , dest_stack_index, card_index))) {
                                        wclear(game_board);
                                        wclear(game_info);
                                        mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Invalid move.");
                                        wrefresh(game_board);
                                        sleep(1);
                                        wrefresh(game_info);
                                }
                        } else if (command == "u") {
                                game->undo();
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

                    mvwprintw(game_board, 9, LEFT_WINDOW_OFFSET, "Control mode:");
                    mvwprintw(game_board, 10, LEFT_WINDOW_OFFSET, "g - Get card from main deck to discard deck");
                    mvwprintw(game_board, 11, LEFT_WINDOW_OFFSET, "dds[1-7] - Take card from discard deck to stack 1 - 7");
                    mvwprintw(game_board, 12, LEFT_WINDOW_OFFSET, "ddd[1-4] - Take card from discard deck to deck 1 - 4");
                    mvwprintw(game_board, 13, LEFT_WINDOW_OFFSET, "d[1-4]s[1-7] - Take card from deck 1 - 4 to stack 1 - 7");
                    mvwprintw(game_board, 14, LEFT_WINDOW_OFFSET, "s[1-7]d[1-4] - Take card from stack 1 - 7 to deck 1 - 4");
                    mvwprintw(game_board, 15, LEFT_WINDOW_OFFSET, "s[1-7]s[1-7]c[1-13] - Take card 1 - 13 from stack 1 - 7 to stack 1 - 7");

                    mvwprintw(game_board, 17, LEFT_WINDOW_OFFSET, "Press Enter to return to game board...");

                    wrefresh(game_board);
                    wrefresh(game_info);
                    std::cin.ignore();
                } else if (c == 'p') {
                    game->pause();
                } else if (c == 'r') {
                    game->resume();
                } else if (c == 'n') {
                    if((game = main.create_new_game()) == nullptr) {
                        wclear(game_board);
                        wclear(game_info);
                        mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Cannot not start new game.");
                        wrefresh(game_board);
                        wrefresh(game_info);
                        sleep(1);
                        endwin();
                        exit(EXIT_FAILURE);
                    }
                    game->start();
                } else if (c == 'g') {
                    game->pause();
                    int id = std::getchar();
                    int game_index = id - '0' - 1;
                    if((game = main.get_game(game_index)) == nullptr) {
                        wclear(game_board);
                        wclear(game_info);
                        mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Cannot not switch to game.");
                        wrefresh(game_board);
                        wrefresh(game_info);
                        sleep(1);
                        endwin();
                        exit(EXIT_FAILURE);
                    } else {
                        game->start();
                    }
                } else if (c == 'e') {
                    break;
                }

                wrefresh(game_board);
                wrefresh(game_info);
        }

        endwin();

        return EXIT_SUCCESS;
}
