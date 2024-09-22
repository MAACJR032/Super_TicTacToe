#pragma once

#include <SFML/graphics.hpp>
#include <memory>
#include <vector>
#include "TicTacToe.hpp"
#include "events.hpp"
#include "buttons.hpp"
#include "menu.hpp"
#include "game_state.hpp"

class Game
{
    private:
        // Variables
        std::unique_ptr<sf::RenderWindow> m_window;
        sf::VideoMode m_video_mode;
        sf::Event m_event;

        // Game logic
        TicTacToe m_tic_tac_toe;
        GameState m_current_state = GameState::MENU;
        std::pair<std::string, std::string> m_players_name;
        sf::Clock m_timer;

        // Game objects
        sf::RectangleShape m_vertical_line;
        sf::RectangleShape m_horizontal_line;
        std::vector<sf::RectangleShape> m_lines;

        // Menus
        std::unique_ptr<main_menu> m_game_menu;
        std::unique_ptr<credits_menu> m_credits_menu;
        std::unique_ptr<name_input_menu> m_name_input_menu;
        std::unique_ptr<end_screen_menu> m_end_screen_menu;

        // Initialization functions
        void init_variables();
        void init_window();
        void init_board();
        void set_board_position();

        // Update and render functions
        void update_poll_events();
        void draw_board();
        void state_manager();
    
    public:
        Game();

        // Getters
        bool running() const;

        void update();
        void render();
};