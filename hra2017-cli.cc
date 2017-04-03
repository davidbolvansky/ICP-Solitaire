#include <iostream>
#include <ncurses.h>
#include <unistd.h>
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
        int score_size = 3;



        initscr();
        noecho();
        curs_set(FALSE);

        // set up initial windows
        getmaxyx(stdscr, parent_y, parent_x);

        WINDOW *game_board = newwin(parent_y - score_size, parent_x, 0, 0);
        WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0);

        draw_borders(game_board);
        draw_borders(score);

        while(1) {
                getmaxyx(stdscr, new_y, new_x);

                if (new_y != parent_y || new_x != parent_x) {
                        parent_x = new_x;
                        parent_y = new_y;

                        wresize(game_board, new_y - score_size, new_x);
                        wresize(score, score_size, new_x);
                        mvwin(score, new_y - score_size, 0);

                        wclear(stdscr);
                        wclear(game_board);
                        wclear(score);

                        draw_borders(game_board);
                        draw_borders(score);
                }

                // draw to our windows
                mvwprintw(game_board, 1, LEFT_WINDOW_OFFSET, "Main Deck\tDiscard Deck\t\tClubs  Diamonds  Hearts  Spades");
                draw_line(game_board, parent_x, 2);
                mvwprintw(game_board, 3, LEFT_WINDOW_OFFSET, "   %s\t    %s\t\t %s\t %s\t  %s\t  %s", game->get_main_card_deck().is_empty() ? "<=>" : "==>", game->get_discard_card_deck().is_empty() ? NO_CARD : game->get_discard_card_deck().get()->to_string().c_str(),
                          game->get_target_deck_by_color(Color::CLUBS).is_empty() ? NO_CARD : game->get_target_deck_by_color(Color::CLUBS).get()->to_string().c_str(),
                          game->get_target_deck_by_color(Color::DIAMONDS).is_empty() ? NO_CARD : game->get_target_deck_by_color(Color::DIAMONDS).get()->to_string().c_str(),
                          game->get_target_deck_by_color(Color::HEARTS).is_empty() ? NO_CARD : game->get_target_deck_by_color(Color::HEARTS).get()->to_string().c_str(),
                          game->get_target_deck_by_color(Color::SPADES).is_empty() ? NO_CARD : game->get_target_deck_by_color(Color::SPADES).get()->to_string().c_str());
                draw_line(game_board, parent_x, 4);
                mvwprintw(game_board, 5, LEFT_WINDOW_OFFSET, "Stack 1    Stack 2    Stack 3    Stack 4    Stack 5    Stack 6    Stack 7");
                for (int i = 0; i < CARDS_PER_PACK; ++i) {
                        mvwprintw(game_board, 6 + i, LEFT_WINDOW_OFFSET, "  %s\t%s\t %s\t    %s\t%s\t  %s\t     %s",
                                  game->get_working_stack_by_id(0).get(i) == nullptr ? NO_CARD : game->get_working_stack_by_id(0).get(i)->is_turned_face_up() ? game->get_working_stack_by_id(0).get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(1).get(i) == nullptr ? NO_CARD : game->get_working_stack_by_id(1).get(i)->is_turned_face_up() ? game->get_working_stack_by_id(1).get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(2).get(i) == nullptr ? NO_CARD : game->get_working_stack_by_id(2).get(i)->is_turned_face_up() ? game->get_working_stack_by_id(2).get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(3).get(i) == nullptr ? NO_CARD : game->get_working_stack_by_id(3).get(i)->is_turned_face_up() ? game->get_working_stack_by_id(3).get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(4).get(i) == nullptr ? NO_CARD : game->get_working_stack_by_id(4).get(i)->is_turned_face_up() ? game->get_working_stack_by_id(4).get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(5).get(i) == nullptr ? NO_CARD : game->get_working_stack_by_id(5).get(i)->is_turned_face_up() ? game->get_working_stack_by_id(5).get(i)->to_string().c_str() : FACE_DOWN_CARD,
                                  game->get_working_stack_by_id(6).get(i) == nullptr ? NO_CARD : game->get_working_stack_by_id(6).get(i)->is_turned_face_up() ? game->get_working_stack_by_id(6).get(i)->to_string().c_str() : FACE_DOWN_CARD);
                }
                mvwprintw(score, 1, LEFT_WINDOW_OFFSET, "Moves: %d | Time: %d seconds | Score: %d |", game->get_moves_count(), game->get_total_time_in_seconds(), game->get_score());

                // refresh each window
                wrefresh(game_board);
                wrefresh(score);
        }

        endwin();

        return EXIT_SUCCESS;
}
