//
// Created by Tal on 25-Oct-20.
//

#ifndef MY_T1_BOARD_H
#define MY_T1_BOARD_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

extern int w;
extern double t;
extern const int g;
/*extern bool win;*/
extern int total_rounds;
extern bool is_round;
//extern bool round_win;

class Board {
    int ROWS/* = 1*/;
    int COLS/* = 0*/;
public:
    char **array;
    explicit Board(const std::string &board_txt);
    void gen_array(const std::string &board_txt);
    void print_array();
    void refresh_display();
    int get_ROWS();
    int get_COLS();
    void free_arr();
};

void gen_wind();
void set_how_many_rounds_needed();

#endif //MY_T1_BOARD_H
