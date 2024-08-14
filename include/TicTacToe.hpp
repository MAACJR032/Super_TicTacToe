#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

using std::vector;
using std::cout;
using std::cin;
using std::string;
using std::pair;

enum status {EMPTY = 'N', X = 'X', O = 'O', TIE = 'T'};

class TicTacToe
{
    private:
        vector<pair<status, int>> grids; // first - Status, second - how many subgrids where played
        vector<vector<status>> tic_tac_toe; // 9x9 board divided in 9 3x3 grids 
        int next_grid; // Next grid to be played

        void grid_score(status player, int grid);
        void check_grid_score(status player, int grid, int low_limit_i, int low_limit_j);
        void play_subgrid(status player, int grid, int subgrid, int low_limit_i, int low_limit_j);
        status check_tie(int grid);

    public:
        TicTacToe();
        int get_next_grid() const;
        void set_next_grid(int next);
        void print_tic_tac_toe() const;
        void play(status player, int next_grid);
        status check_win(status player, string player_name);
};