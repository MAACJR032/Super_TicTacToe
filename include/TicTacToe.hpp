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
    status player;
    sf::RectangleShape rect;
};

class TicTacToe
{
    private:
        vector<pair<status, int8_t>> grids; // first - Status, second - how many subgrids where played
        int8_t next_grid; // Next grid to be played
        status curr_player;

        void grid_score(int8_t grid);
        void update_grid_score(int8_t grid, int8_t low_limit_i, int8_t low_limit_j);
        status check_tie(int8_t grid);

    public:
        TicTacToe();
        vector<vector<Square>> board;
        status victory;

        void win();
        void play(std::unique_ptr<sf::RenderWindow> &window);
        status check_win(string player_name);
};