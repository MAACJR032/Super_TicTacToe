#include <SFML/graphics.hpp>
#include <memory>
#include <vector>

using std::unique_ptr;
using std::make_unique;
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

        void init_variables();
        void init_window();
        void init_square();

    public:
        Game();
        ~Game();

        // Accessors
        const bool running() const;

        // Functions
        void spawn_squares();
        void update_poll_events();
        void update_squares();
        void update_mouse_pos();
        void update();
        void render_squares();
        void render();
};