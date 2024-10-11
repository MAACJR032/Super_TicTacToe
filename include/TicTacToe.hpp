#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <numeric>
#include "squares.hpp"
#include "Utils/Text/text.hpp"
#include "Utils/Path/path_utils.hpp"

using std::unique_ptr;

struct Grid
{
    int8_t subgrids_scored; // unavailable subgrids 
    square grid;
};


class TicTacToe
{
    private:
        std::vector<Grid> m_grids;
        std::vector<std::vector<subgrid>> m_board;

        int8_t m_next_grid = -1;
        Status m_current_player = Status::X;
        Status m_victory = Status::EMPTY;

        line m_line;

        std::pair<std::string, std::string> m_players_name;
        game_text m_current_player_text;

        sf::Texture X_texture;
        sf::Texture Big_X_texture;
        sf::Texture O_texture;
        sf::Texture Big_O_texture;

        void update_grid_score(int8_t grid, int8_t low_limit_i, int8_t low_limit_j);
        void grid_score(int8_t grid);
        Status update_grid_tie(int8_t grid);
        void update_square(subgrid &s, sf::RenderWindow &window);
        void iterate_board(sf::RenderWindow &window);
        void set_line_parameters();
        void check_win();

    public:
        TicTacToe();

        void set_players_name(std::string player1, std::string player2);
        
        std::pair<std::string, std::string>& get_players_name();
        int8_t get_next_grid() const;
        Status get_grid_status(uint8_t index) const;
        std::vector<std::vector<subgrid>>& get_board();
        subgrid& get_board_at(uint8_t i, uint8_t j);
        Status get_victory() const;
        Status get_current_player() const;

        bool is_line_max_size() const;
        bool is_drawing_line() const;

        void iterate_board(void (*func) (subgrid&, TicTacToe& , sf::RenderWindow &window), sf::RenderWindow &window);
        void play(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);
        void draw_endline(sf::RenderWindow &window);
        void reset();
};