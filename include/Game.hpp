#pragma once

#include <SFML/graphics.hpp>
#include <memory>
#include <vector>
#include "player.hpp"
#include "TicTacToe.hpp"

using std::unique_ptr;
using std::vector;

struct Square
{
    pair<int, int> board_pos;
    status stat;
    sf::RectangleShape rect;
};

class Game
{
    private:
        // Variables
        unique_ptr<sf::RenderWindow> window;
        sf::VideoMode video_mode;
        sf::Event event;

        TicTacToe tick;
        Player player;

        // Mouse position
        sf::Vector2i mouse_pos;
        
        // Game logic
        int max_squares;
        
        // Game objects
        sf::RectangleShape square;
        vector<vector<Square>> squares;
        
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