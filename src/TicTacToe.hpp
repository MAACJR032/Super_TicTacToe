#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "grid.hpp"
#include "Utils/Text/text.hpp"

class TicTacToe
{
    private:
        std::vector<Grid> m_grids;

        int m_next_grid = -1;
        Status m_current_player = Status::X;
        Status m_result = Status::EMPTY;
        Line m_line;

        std::pair<std::string, std::string> m_players_name;
        Game_text m_current_player_text;

        void switch_player();
        Status update_match_status();
        void update_square(Subgrid &s, sf::RenderWindow &window);
        void update_all_squares(sf::RenderWindow &window);

        bool check_line(uint8_t a, uint8_t b, uint8_t c, LineStatus line_status);
        void set_line_dimensions();

    public:
        TicTacToe();

        Status play(sf::RenderWindow &window);
        void hover_effect(sf::RenderWindow &window);
        void set_players_name(std::pair<std::string, std::string> players_name);

        void draw(sf::RenderWindow &window) const;

        Status get_match_status() const;
        Line& get_result_line();
        Line get_result_line() const;

        std::pair<std::string, std::string>& get_players_name();
        std::pair<std::string, std::string> get_players_name() const;

        void reset(bool reset_names);
};