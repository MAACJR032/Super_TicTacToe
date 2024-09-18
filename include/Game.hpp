#pragma once

#include <SFML/graphics.hpp>
#include <memory>
#include <vector>
#include "TicTacToe.hpp"
#include "events.hpp"
#include "text.hpp"
#include "buttons.hpp"
#include "menu.hpp"

enum class game_state : uint8_t {
    MENU, NAME_INPUT, PLAYING, WAITING_INPUT, END_SCREEN
};

class Game
{
    private:
        // Variables
        std::unique_ptr<sf::RenderWindow> window;
        sf::VideoMode video_mode;
        sf::Event event;
        std::pair<std::string, std::string> players;

        // Game logic
        TicTacToe tick;
        game_state curr_state = game_state::MENU;
        
        // Game objects
        sf::RectangleShape vertical_line;
        sf::RectangleShape Horizontal_line;
        std::vector<sf::RectangleShape> lines;

        // Menus
        std::unique_ptr<main_menu> game_menu;
        std::unique_ptr<name_input_menu> name_input;
        std::unique_ptr<end_screen_menu> end_screen;

        // Initialization functions
        void init_variables();
        void init_window();
        void init_board();
        void set_board();

        // Update and render functions
        void update_poll_events();
        void render_board();
        void state_manager();
    
    public:
        Game();
        ~Game();

        // Getters
        bool running() const;
        game_state get_curr_state() const;

        void update();
        void render();
};