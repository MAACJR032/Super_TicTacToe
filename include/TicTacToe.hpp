#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../include/squares.hpp"

using std::unique_ptr;

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
        std::vector<std::pair<status, int8_t>> grids; // first - Status, second - how many subgrids where played
        std::vector<std::vector<Square>> board;
        int8_t next_grid = -1; // Next grid to be played
        status curr_player = X;
        status victory;

        void grid_score(int8_t grid);
        void update_grid_score(int8_t grid, int8_t low_limit_i, int8_t low_limit_j);
        status check_tie(int8_t grid);
        void update_square(Square &s, std::unique_ptr<sf::RenderWindow> &window);

    public:
        TicTacToe();

        int8_t get_next_grid();
        status get_grid_i_status(uint8_t index);
        void win();
        void play(std::unique_ptr<sf::RenderWindow> &window);
        status check_win(std::string player_name);
        void iterate_board(void (TicTacToe::*func) (Square&, unique_ptr<sf::RenderWindow> &window), unique_ptr<sf::RenderWindow> &window);
        std::vector<std::vector<Square>>& get_board();
        Square& get_board_at(int i, int j);
};