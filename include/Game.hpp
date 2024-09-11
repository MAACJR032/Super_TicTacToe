#pragma once

#include <SFML/graphics.hpp>
#include <memory>
#include <vector>
#include "TicTacToe.hpp"
#include "events.hpp"
#include "text.hpp"
#include "buttons.hpp"
#include "menu.hpp"

enum game_state : uint8_t {
    MENU, NAME_INPUT, PLAYING, WAITING_INPUT, GAME_OVER
};

class Game
{
    private:
        // Variables
        std::unique_ptr<sf::RenderWindow> window;
        sf::VideoMode video_mode;
        sf::Event event;

        // Game logic
        TicTacToe tick;
        game_state curr_state = MENU;
        
        // Game objects
        sf::RectangleShape vertical_line;
        sf::RectangleShape Horizontal_line;
        std::vector<sf::RectangleShape> lines;

        // Texts and buttons
        std::pair<std::string, std::string> players;
        text_box players_name_text_box;
        game_text game_over_text;
        std::unique_ptr<menu> game_menu;

        // Initialization functions
        void init_variables();
        void init_window();
        void init_board();
        void set_board();

        // Update and render functions
        void update_poll_events();
        void render_board();
        void state_handler();
    
    public:
        Game();
        ~Game();

        // Getters
        bool running() const;
        game_state get_curr_state() const;

        void update();
        void render();
};