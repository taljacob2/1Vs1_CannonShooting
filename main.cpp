/* My Notes:
 * VTODO: need to represent w on the screen.
 * VTODO: Remember to free the board.array.
 *
 *
 * */

#include "cannon.h"
#include "board.h"
#include <thread>
#include <chrono>

using namespace std;

bool thread_cannon_fn(Board &board, Cannon &cannon1);/*open a thread to refresh - begins with false*/
void set_this_cannon_and_update_is_round(Board board, Cannon &cannon);
void check_who_won_and_display(Cannon cannon1, Cannon cannon2);
void play(Board &board, Cannon &cannon1, Cannon &cannon2);
void play_round_p1_first(Board &board, Cannon &cannon1, Cannon &cannon2, int &round_count, int &total_rounds_won_player1, int& total_rounds_won_player2);
void play_round_p2_first(Board &board, Cannon &cannon1, Cannon &cannon2, int &round_count, int &total_rounds_won_player1, int& total_rounds_won_player2);
void check_round_score_and_choose_who_begins(Board board, Cannon cannon1, Cannon cannon2, int &round_count, int &total_rounds_won_player1, int& total_rounds_won_player2);

int main() {
    Board board("board.txt");
    Cannon cannon1("Player 1"), cannon2("Player 2");
    gen_wind();
    set_how_many_rounds_needed();
    /*---------------------------------------------*/
    board.refresh_display();/*initial display*/
    play(board, cannon1, cannon2);
    return 0;
}

bool thread_cannon_fn(Board &board, Cannon &cannon) {
    /*this function opens a thread*/
    bool round_win = false;
    bool foul = false;
//    board.free_arr();/*free old arr*/ /*<<<-TODO: for some reason these two lines are making a SIGSEGV, so i disabled them*/
//    board.gen_array("board.txt");/*refresh array from txt*/ /*<<<-TODO: for some reason these two lines are making a SIGSEGV, so i disabled them*/
    for (; is_round && !foul;) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));/*this is the physical screen Hz refresh rate. adjust as you wish!*/
        /* call your functions here: */
        cannon.shoot(board, foul, round_win);
        board.refresh_display();
        cout << cannon.get_Player() << " score is: " << cannon.rounds_won << endl;
        t += (1.0 / 10);/*1/10 of a second has elapsed, so we update 't'*/
    }
    return round_win;
}
void set_this_cannon_and_update_is_round(Board board, Cannon &cannon) {
    /*------set initializers------*/
    t = 0;/*reset time*/
    cannon.set_v_and_alpha();
    cannon.update_vx();
    cannon.update_vy();
    cannon.update_xt(); /*initialize xt*/
    cannon.update_yt(board); /*initialize yt*/
    is_round = true;
}
void check_who_won_and_display(Cannon cannon1, Cannon cannon2, int total_rounds_won_player1, int total_rounds_won_player2) {
    cout << "Total Scores: " << cannon1.get_Player() <<  " [" << total_rounds_won_player1 << "]" << " : " << cannon2.get_Player() << " [" << total_rounds_won_player2 << "]" << endl;/*print both scores*/
    if (total_rounds_won_player1 > total_rounds_won_player2)
        cout << cannon1.get_Player() << " has won with the score of " << total_rounds_won_player1 << "!" << endl;
    else if (cannon1.rounds_won < cannon2.rounds_won)
        cout << cannon2.get_Player() << " has won with the score of " << total_rounds_won_player2 << "!" << endl;
    else cout << "Good Game! its a tie!" << endl;
}
void play(Board &board, Cannon &cannon1, Cannon &cannon2) {
    int round_count = 1; /*display what round is it*/
    int total_rounds_won_player1 = 0, total_rounds_won_player2 = 0;
    while (total_rounds >= 1) {
        check_round_score_and_choose_who_begins(board, cannon1, cannon2, round_count, total_rounds_won_player1, total_rounds_won_player2);
        total_rounds--;
    }
    check_who_won_and_display(cannon1, cannon2, total_rounds_won_player1, total_rounds_won_player2);
    board.free_arr();/*free array*/
}
void check_round_score_and_choose_who_begins(Board board, Cannon cannon1, Cannon cannon2, int &round_count, int &total_rounds_won_player1, int& total_rounds_won_player2) {
    if (cannon1.rounds_won > cannon2.rounds_won) {
        cout << cannon1.get_Player() << " begins:" << endl;
        play_round_p1_first(board, cannon1, cannon2, round_count, total_rounds_won_player1, total_rounds_won_player2);
    } else if (cannon1.rounds_won < cannon2.rounds_won) {
        cout << cannon2.get_Player() << " begins:" << endl;
        play_round_p2_first(board, cannon1, cannon2, round_count, total_rounds_won_player1, total_rounds_won_player2);
    } else {
        /*randomise scores and try again:*/
        cannon1.rounds_won = (int) random();
        cannon2.rounds_won = (int) random();
        check_round_score_and_choose_who_begins(board, cannon1, cannon2, round_count, total_rounds_won_player1, total_rounds_won_player2);
    }
}
void play_round_p1_first(Board &board, Cannon &cannon1, Cannon &cannon2, int &round_count, int &total_rounds_won_player1, int& total_rounds_won_player2) {
    /*new round:*/
    bool player_is_alive;
    cout << "Round " << round_count << ":" << endl;/*display round number on screen*/
    cannon1.rounds_won = 0, cannon2.rounds_won = 0;/*reset scores*/
    /*player 1 begins:*/
    for (player_is_alive = true; player_is_alive;) {
        set_this_cannon_and_update_is_round(board, cannon1);
        player_is_alive = thread_cannon_fn(board, cannon1);/*open a thread to refresh - begins with false*/
    }
    /*switch to player 2*/
    for (player_is_alive = true; player_is_alive;) {
        set_this_cannon_and_update_is_round(board, cannon2);
        player_is_alive = thread_cannon_fn(board, cannon2);/*open a thread to refresh - begins with false*/
    }
    /*------always------*/
    if (cannon1.rounds_won > cannon2.rounds_won)
        total_rounds_won_player1++;
    else if (cannon1.rounds_won < cannon2.rounds_won)
        total_rounds_won_player2++;
    round_count++;
}
void play_round_p2_first(Board &board, Cannon &cannon1, Cannon &cannon2, int &round_count, int &total_rounds_won_player1, int& total_rounds_won_player2) {
    /*new round:*/
    cout << "Round " << round_count << ":" << endl;
    /*player 2 begins:*/
    set_this_cannon_and_update_is_round(board, cannon1);
    thread_cannon_fn(board, cannon2);/*open a thread to refresh - begins with false*/
    /*switch to player 1*/
    set_this_cannon_and_update_is_round(board, cannon2);
    thread_cannon_fn(board, cannon1);/*open a thread to refresh - begins with false*/
    /*------always------*/
    round_count++;
}