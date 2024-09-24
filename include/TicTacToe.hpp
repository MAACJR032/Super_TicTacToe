#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "squares.hpp"
#include "Utils/Text/text.hpp"
#include "Utils/Path/path_utils.hpp"

using std::unique_ptr;

class TicTacToe
{
    private:
        std::vector<std::pair<Status, int8_t>> m_grids; // first - Status, second - how many subgrids where played
        std::vector<std::vector<Square>> m_board;

        int8_t m_next_grid = -1;
        Status m_current_player = Status::X;
        Status m_victory;
        std::pair<std::string, std::string> m_players_name;
        game_text m_current_player_text;

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

        void set_players_name(std::string player1, std::string player2);
        
        std::pair<std::string, std::string>& get_players_name();
        int8_t get_next_grid() const;
        Status get_grid_status(uint8_t index) const;
        std::vector<std::vector<Square>>& get_board();
        Square& get_board_at(uint8_t i, uint8_t j);
        Status get_victory() const;
        Status get_current_player();

        void iterate_board(void (*func) (Square &s, TicTacToe &t, sf::RenderWindow &window), sf::RenderWindow &window);
        void play(sf::RenderWindow &window);
        void draw_current_player_text(sf::RenderWindow &window);
        void reset();
};