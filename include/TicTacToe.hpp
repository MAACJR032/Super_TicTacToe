#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../include/squares.hpp"

using std::vector;
using std::string;
using std::pair;

enum status : uint8_t {
    EMPTY, X, O, TIE
};

struct Square
{
    int8_t grid;
    int8_t subgrid;
    status stat;
    sf::RectangleShape rect;
};

class TicTacToe
{
    private:
        vector<pair<status, int>> grids; // first - Status, second - how many subgrids where played
        int8_t next_grid; // Next grid to be played

        void grid_score(status player, int grid);
        void check_grid_score(status player, int grid, int low_limit_i, int low_limit_j);
        status check_tie(int grid);

    public:
        TicTacToe();
        vector<vector<Square>> board;
        status victory;
        void win(status player);
        void play(status player, std::unique_ptr<sf::RenderWindow> &window);
        status check_win(status player, string player_name);
};