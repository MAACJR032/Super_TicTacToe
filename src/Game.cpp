#include "../include/Game.hpp"

// Private funtions
void Game::init_variables()
{
    window = nullptr;
}

void Game::init_window()
{
    video_mode.height = 900;
    video_mode.width = 1680;
    // video_mode.getDesktopMode();

    window = make_unique<sf::RenderWindow>(video_mode, "Super Tic Tac Toe", sf::Style::Close); 
}

// Constructor / Destructor
Game::Game()
{
    init_variables();
    init_window();
}

Game::~Game()
{
}

// Accessors
const bool Game::running() const
{
    return window->isOpen();
}

// Functions
void Game::update_poll_events()
{
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window->close();
                break;
            
            // pressing Esc to close
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window->close();
                break;

            default:
                break;
        }   
    }
}

void Game::update()
{
    update_poll_events();
}

void Game::render()
{
    window->clear(sf::Color::White); // clear old frame

    window->display(); // done drawing
}
