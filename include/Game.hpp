#pragma once

#include <SFML/graphics.hpp>
#include <memory>
#include <vector>
#include "TicTacToe.hpp"

enum game_state : uint8_t {
    PLAYING, WAITING_INPUT, MENU, GAME_OVER
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
        game_state curr_state = WAITING_INPUT;
        
        // Game objects
        sf::RectangleShape vertical_line;
        sf::RectangleShape Horizontal_line;
        std::vector<sf::RectangleShape> lines;

        // Initialization functions
        void init_variables();
        void init_window();
        void init_board();
        void set_board();

        // Update and render functions
        void update_poll_events();
        void render_board();
    
    public:
        Game();
        ~Game();

        // Getters
        const bool running() const;
        const game_state get_curr_state() const;

        void update();
        void render();
};