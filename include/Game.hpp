#pragma once

#include <SFML/graphics.hpp>
#include <memory>
#include <vector>
#include "input.hpp"

using std::unique_ptr;
using std::vector;

class Game
{
    private:
        // Variables
        unique_ptr<sf::RenderWindow> window;
        sf::VideoMode video_mode;
        sf::Event event;

        // Mouse position
        sf::Vector2i mouse_pos;
        
        // Game logic
        float squares_spawn_timer;
        float squares_spawn_timer_max;
        int max_squares;
        
        // Game objects
        sf::RectangleShape square;
        vector<vector<sf::RectangleShape>> squares;
        
        sf::RectangleShape vertical_line;
        sf::RectangleShape Horizontal_line;
        vector<sf::RectangleShape> lines;

        void init_variables();
        void init_window();
        void init_board();

    public:
        Game();
        ~Game();

        // Accessors
        const bool running() const;

        // Functions
        void spawn_board();
        void update_poll_events();
        void update_squares();
        void update_mouse_pos();
        void update();
        void render_squares();
        void render();
};