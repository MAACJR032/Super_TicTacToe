#include <SFML/graphics.hpp>
#include <memory>

using std::unique_ptr;
using std::make_unique;

class Game
{
    private:
        // Variables
        unique_ptr<sf::RenderWindow> window;
        sf::VideoMode video_mode;
        sf::Event event;

        void init_variables();
        void init_window();

    public:
        Game();
        ~Game();

        // Accessors
        const bool running() const;

        // Functions
        void update_poll_events();
        void update();
        void render();
};