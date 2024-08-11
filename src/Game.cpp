#include "../include/Game.hpp"
#include <iostream>
#include <ctime>

// Private funtions
void Game::init_variables()
{
    window = nullptr;

    // Game logic
    squares_spawn_timer = 0.f;
    max_squares = 9;
    
    squares.resize(9);
    for (size_t i = 0; i < 9; i++)
        squares[i].reserve(9);
}

void Game::init_window()
{
    video_mode.height = 900;
    video_mode.width = 1680;
    // video_mode.getDesktopMode();

    window = make_unique<sf::RenderWindow>(video_mode, "Super Tic Tac Toe", sf::Style::Close); 
    window->setFramerateLimit(60);
}

void Game::init_square()
{
    square.setSize(sf::Vector2f(75.f, 75.f));
    square.setFillColor(sf::Color::Blue);
    square.setOutlineThickness(2.f);
}


// Constructor / Destructor
Game::Game()
{
    init_variables();
    init_window();
    init_square();
    spawn_squares();
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

/* will set the position of all the 81 squares and insert them into the squares vector */
void Game::spawn_squares()
{
    float x1 = 500.f, y1 = 100.f;
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            square.setPosition({x1 + i * 75, y1 + j * 75});
            squares[i].push_back(square);
        }
    }
}

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

/* update the squares if they were scored or selected */
void Game::update_squares()
{
    
}

/* Updates the mouse position on the game window */
void Game::update_mouse_pos()
{
    mouse_pos = sf::Mouse::getPosition(*window);
}

void Game::update()
{
    update_poll_events();
    update_mouse_pos();
    update_squares();
}

void Game::render_squares()
{
    for (auto &s : squares)
        for (auto &t : s)
            window->draw(t);
}

void Game::render()
{
    window->clear(sf::Color::White); // clear old frame

    // Draw game objects
    render_squares();

    window->display(); // done drawing
}