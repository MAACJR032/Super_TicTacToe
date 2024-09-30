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

constexpr float GROW_RATE = 0.2f;
constexpr float PI = 3.14159f;
constexpr float speed = 100.f;
constexpr float thickness = 10.f;

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
        Status m_victory;

        Line m_result_line = Line::EMPTY;

        std::pair<std::string, std::string> m_players_name;
        game_text m_current_player_text;

        sf::Texture X_texture;
        sf::Texture Big_X_texture;
        sf::Texture O_texture;
        sf::Texture Big_O_texture;

        sf::RectangleShape line;
        sf::Vector2f start, end;
        float totalLength;
        float currentLength = 0.f;

        void update_grid_score(int8_t grid, int8_t low_limit_i, int8_t low_limit_j);
        void grid_score(int8_t grid);
        Status update_grid_tie(int8_t grid);
        void update_square(subgrid &s, sf::RenderWindow &window);
        void check_win();
        void iterate_board_private(sf::RenderWindow &window);
        
    public:
        TicTacToe();

        void set_players_name(std::string player1, std::string player2);
        void set_line_parameters();
        
        std::pair<std::string, std::string>& get_players_name();
        int8_t get_next_grid() const;
        Status get_grid_status(uint8_t index) const;
        std::vector<std::vector<subgrid>>& get_board();
        subgrid& get_board_at(uint8_t i, uint8_t j);
        Status get_victory() const;
        Status get_current_player() const;

        
        void iterate_board_public(void (*func) (subgrid&, TicTacToe& , sf::RenderWindow &window), sf::RenderWindow &window);
        void play(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);
        void draw_endline(sf::RenderWindow &window);
        void reset();
};