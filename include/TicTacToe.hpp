#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "squares.hpp"
#include "text.hpp"

using std::unique_ptr;

class TicTacToe
{
    private:
        std::vector<std::pair<Status, int8_t>> m_grids; // first - Status, second - how many subgrids where played
        std::vector<std::vector<Square>> m_board;

        int8_t m_next_grid = -1;
        Status m_current_player = Status::X;
        Status m_victory;
        player_turn_text m_current_player_text;

        sf::Texture X_texture;
        sf::Texture O_texture;

        void update_grid_score(int8_t grid, int8_t low_limit_i, int8_t low_limit_j);
        void grid_score(int8_t grid);
        Status update_grid_tie(int8_t grid);
        void update_square(Square &s, sf::RenderWindow &window);
        void check_win();
        void iterate_board(void (TicTacToe::*func) (Square&, sf::RenderWindow &window), sf::RenderWindow &window);
        
    public:
        TicTacToe();

        void set_players_name(const std::pair<std::string, std::string> &players);
        
        player_turn_text get_text() const;
        int8_t get_next_grid() const;
        Status get_grid_status(uint8_t index) const;
        std::vector<std::vector<Square>>& get_board();
        Square& get_board_at(uint8_t i, uint8_t j);
        Status get_victory() const;

        void iterate_board(void (*func) (Square &s, TicTacToe &t, sf::RenderWindow &window), sf::RenderWindow &window);
        void play(sf::RenderWindow &window);
        void reset();
};