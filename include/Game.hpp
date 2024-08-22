#pragma once

#include <SFML/graphics.hpp>
#include <memory>
#include <vector>
#include "player.hpp"
// #include "TicTacToe.hpp"
#include "TicTacToe.hpp"

using std::unique_ptr;
using std::vector;

class Game
{
    private:
        friend class TicTacToe;
        // Variables
        unique_ptr<sf::RenderWindow> window;
        sf::VideoMode video_mode;
        sf::Event event;

        // Mouse position
        sf::Vector2i mouse_pos;
        
        // Game logic
        int max_squares;
        TicTacToe tick;
        Player player;
        
        // Game objects
        sf::RectangleShape square;
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