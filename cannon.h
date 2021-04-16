//
// Created by Tal on 25-Oct-20.
//

#ifndef MY_T1_Cannon_H
#define MY_T1_Cannon_H

#include <iostream>
#include "board.h"/*included*/

extern const double PI;

class Cannon {
    std::string player;
    int x0 /*col_pos*/, y0 /*row_pos*/;
    double v, alpha;
    double vx = 0, vy = 0;

public:
    int xt /*col_pos at time 't'*/, yt /*row_pos at time 't'*/;
    int rounds_won = 0;
    explicit Cannon(const std::string &player);
    void shoot(Board board, bool &foul, bool &round_win);
    void set_v_and_alpha();
    void update_xt();
    void update_yt(Board board);
    void update_vx();
    void update_vy();
    std::string get_Player();
};

#endif //MY_T1_Cannon_H
