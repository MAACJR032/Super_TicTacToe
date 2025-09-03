#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "TicTacToe.hpp"

class Board
{
    private:
        TicTacToe m_tic_tac_toe;
        std::array<sf::RectangleShape, 4> m_board_lines;
        
    public:
        Board();

        TicTacToe& get_tic_tac_toe();
        Status get_match_status() const;
        std::pair<std::string, std::string> get_players_name() const;
        
        bool is_drawing_line() const;
        bool is_line_max_size();

        void hover_effect(sf::RenderWindow &window);
        Status play(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);
        void reset(bool reset_names);
};