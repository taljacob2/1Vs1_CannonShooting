//
// Created by Tal on 25-Oct-20.
//

#include "board.h"
#include "cannon.h"

using namespace std;

const int g = 3; /* 1 pixel per (sec * 10^(-1))^2 */
int w /*wind velocity*//*positive value means wind from left to right, and negative value means wind from right to left.*//*value ranges between (-5) to (+5)*/;
double t /*time elapsed since beginning of movement*/;
int total_rounds;
int curr_round = 1;
bool win = false;
bool is_round = false;
//bool round_win = false;

Board::Board(const std::string &board_txt) {
    gen_array(board_txt);
}
void Board::gen_array(const std::string &board_txt){
    /* !!!!!!!! be aware that every ROW needs to end with a '\n' !!!!!!!! */
    ROWS = 1;/*initialize - VERY IMPORTANT?*/
    COLS = 0;/*initialize - VERY IMPORTANT?*/
    std::ifstream my_file;
    my_file.open("board.txt");
    char c;
    int cols = 0;
    array = (char **) calloc(sizeof(char *), this->ROWS);

    /* !!!!!!!! be aware that every ROW needs to end with a '\n' !!!!!!!! */
    while (my_file.get(c)) {
        if (c == '\r') /*if c == '\r' skip this letter*/
            if (!my_file.get(c))
                break;
        cols++;
        array[this->ROWS - 1] = (char *) realloc(array[this->ROWS - 1], sizeof(char) * cols);
        array[this->ROWS - 1][cols - 1] = c;
        if (cols) /*update COLS*/
            this->COLS = cols;
        if (c == '\n') {
            this->ROWS++;
            array = (char **) realloc(array, sizeof(char *) * this->ROWS);
            cols = 0;
        }
    }
    this->ROWS = this->ROWS - 1; /*remove the last '\n' ROW */
    my_file.close();
}

void Board::print_array() {
    for (int i = 0; i < this->ROWS; i++)
        for (int j = 0; j < this->COLS; j++)
            cout << this->array[i][j];
    cout << endl;
}
void Board::refresh_display(){
    /*system("cls");*//*for windows cmd*/
    system("clear");/*for linux terminal*/
    cout << "wind = " << w << endl;
    cout << "time elapsed (sec) = " << t << endl;
    print_array();
}
int Board::get_ROWS() {
    return this->ROWS;
}
int Board::get_COLS() {
    return this->COLS;
}


void gen_wind() {
    srandom((int) time(nullptr));
    int r = (int) random(), b = r % 2;
    b == 0 ? w = (r % 6) : w = (r % 6) * (-1);/*initialize 'w'*/
}
void set_how_many_rounds_needed() {
    cout << "How many rounds in the game?" << endl;
    cin >> total_rounds;
}

void Board::free_arr(){
    for (int i = 0; i < ROWS; i++)
        free(array[i]);
    free(array);
}
