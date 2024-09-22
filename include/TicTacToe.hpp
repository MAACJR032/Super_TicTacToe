#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "events.hpp"
#include "squares.hpp"
#include "text.hpp"

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

        int8_t next_grid = -1;
        status curr_player = X;
        status victory;
        player_turn_text text;

        sf::Texture X_texture;
        sf::Texture O_texture;

        void update_grid_score(int8_t grid, int8_t low_limit_i, int8_t low_limit_j);
        void grid_score(int8_t grid);
        status update_grid_tie(int8_t grid);
        void check_win();

        void update_square(Square &s, std::unique_ptr<sf::RenderWindow> &window);
        void iterate_board(void (TicTacToe::*func) (Square&, unique_ptr<sf::RenderWindow> &window), unique_ptr<sf::RenderWindow> &window);
        
    public:
        TicTacToe();

        void set_players_name(std::pair<std::string, std::string> &players);
        
        player_turn_text get_text();
        int8_t get_next_grid();
        status get_grid_status(uint8_t index);
        std::vector<std::vector<Square>>& get_board();
        Square& get_board_at(uint8_t i, uint8_t j);
        status get_victory();

        void iterate_board(void (*func) (Square &s, TicTacToe &t, unique_ptr<sf::RenderWindow> &window), unique_ptr<sf::RenderWindow> &window);
        void play(unique_ptr<sf::RenderWindow> &window);
        void reset();
};