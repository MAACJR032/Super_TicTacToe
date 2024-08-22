#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../include/squares.hpp"

using std::vector;
using std::string;
using std::pair;

enum status {EMPTY, X, O, TIE};

struct Square
{
    int grid;
    int subgrid;
    status stat;
    sf::RectangleShape rect;
};

class TicTacToe
{
    private:
        vector<pair<status, int>> grids; // first - Status, second - how many subgrids where played
        int next_grid; // Next grid to be played

        void grid_score(status player, int grid);
        void check_grid_score(status player, int grid, int low_limit_i, int low_limit_j);
        status check_tie(int grid);

    public:
        TicTacToe();
        vector<vector<Square>> board;
        status victory;
        void win(status player);
        int get_next_grid() const;
        void set_next_grid(int next);
        void play(status player);
        status check_win(status player, string player_name);
};