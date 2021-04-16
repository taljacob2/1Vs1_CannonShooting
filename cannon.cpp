//
// Created by Tal on 25-Oct-20.
//

#include "board.h"
#include "cannon.h"

const double PI = 3.14159265;

using namespace std;
Cannon::Cannon(const std::string &player) {
    if (player == "Player 1") {
        this->x0 = 7;
        this->y0 = 5;
    } else if (player == "Player 2") {
        this->x0 = 38;
        this->y0 = 5;
    }
    /*-----------initialize-----------*/
    this->player = player;
    this->xt = this->x0;
    this->yt = this->y0;
}
void Cannon::shoot(Board board, bool &foul, bool &round_win) {
//    update_vx(); /*VTODO: there is no need to refresh the update each clock*//*but for some reason there is a need for that */
//    update_vy(); /*VTODO: there is no need to refresh the update each clock*//*but for some reason there is a need for that */
    board.array[yt][xt] = ' ';/*restore previous '*' to be ' '*/
    update_xt();
    update_yt(board);
    if ((yt >= board.get_ROWS()) || (yt <= 0) || (xt >= board.get_COLS()) || (xt <= 0))
        foul = true; /*we lost this round*/
    else if (board.array[yt][xt] != ' ') {/*stop condition*/
        if (board.array[yt][xt] == '-' || board.array[yt][xt] == '|')
            foul = true; /*we lost this round*/
        else if (board.array[yt][xt] != '*') {
            rounds_won++;
            round_win = true; /*we won this round*/ /*TODO: note that, in this way it is possible to win by hitting your own cannon*/
        }
        is_round = false;/*quit the thread any way*/
    }
    board.array[yt][xt] = '*';
}
string Cannon::get_Player() {
    return this->player;
}
void Cannon::set_v_and_alpha() {
    cout << "---------------------------" << endl;
    cout << player << ":" << endl;
    cout << "set 'velocity' [1 pixel / 10^(-1) sec]: ";
    cin >> this->v;
    cout << "set 'alpha' angle: ";
    cin >> this->alpha;
}
void Cannon::update_xt() {
    xt = (int) (x0 + vx * t);
}
void Cannon::update_yt(Board board) {
    yt = (int) (y0 + vy * t -
                0.5 * g * (t * t));/*take note that we need to flip yt because the array is flipped by default*/
    yt = board.get_ROWS() - yt;/*here we flip yt - to count from the bottom*/
}
void Cannon::update_vx() {
    vx = v * cos(alpha * (PI / 180)) + w;
}
void Cannon::update_vy() {
    vy = v * sin(alpha * (PI / 180));
}
