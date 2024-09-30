#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "TicTacToe.hpp"
#include "events.hpp"
#include "buttons.hpp"
#include "menu.hpp"
#include "types/game_state.hpp"

class Game
{
    private:
        // Variables
        sf::RenderWindow m_window;
        sf::VideoMode m_video_mode;
        sf::Event m_event;

        // Game logic
        TicTacToe m_tic_tac_toe;
        GameState m_current_state = GameState::MENU;
        sf::Clock m_timer;

        // Game objects
        sf::RectangleShape m_vertical_line;
        sf::RectangleShape m_horizontal_line;
        std::vector<sf::RectangleShape> m_lines;

        // Menus
        main_menu m_game_menu;
        credits_menu m_credits_menu;
        name_input_menu m_name_input_menu;
        end_screen_menu m_end_screen_menu;

        // Initialization functions
        void set_board_position();

        // Update and render functions
        void update_poll_events();
        void draw_board();
        void state_manager();

        void handle_mouse_button_pressed();
        void handle_text_input();

        void handle_main_menu();
        void handle_credits_menu();
        void handle_name_input_menu();
        void handle_end_screen_menu();

    public:
        Game();

        // Getters
        bool running() const;

        void update();
        void render();
};