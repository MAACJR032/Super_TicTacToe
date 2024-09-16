#include "Game.hpp"
#include <iostream>

void Game::init_variables()
{
    window = nullptr;
    lines.reserve(4);
}

void Game::init_window()
{
    video_mode.height = 900;
    video_mode.width = 1680;
    // video_mode.getDesktopMode();

    window = std::make_unique<sf::RenderWindow>(video_mode, "Super Tic Tac Toe", sf::Style::Close);
    window->setFramerateLimit(60);
}

void Game::init_board()
{
    vertical_line.setSize(sf::Vector2f(10.f, 790.f));
    vertical_line.setFillColor(BLACK);

    Horizontal_line.setSize(sf::Vector2f(790.f, 10.f));
    Horizontal_line.setFillColor(BLACK);
}

/* will set the position of all the 9x9 board. */
void Game::set_board()
{
    // seting the board's position
    float x = 500.f, y = 100.f;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            tick.get_board_at(i, j).rect.setPosition({x + j * 75, y + i * 75});
    
    // vertical lines
    for (int i = 0; i < 2; i++)
    {
        vertical_line.setPosition({720 + static_cast<float>(225 * i), y-60});
        lines.push_back(vertical_line);
    }
    
    // horizontal lines
    for (int i = 0; i < 2; i++)
    {
        Horizontal_line.setPosition({x-55, y + 220 + static_cast<float>(225 * i)});
        lines.push_back(Horizontal_line);
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
            
            // Click on available squares to play
            case sf::Event::MouseButtonPressed:
                handle_square_play(event, window, curr_state, tick);
                handle_text_box_sel(players_name_text_box, *window);
                break;
                
            case sf::Event::TextEntered:
                players_name_text_box.typed(event);
                get_player_name(players_name_text_box, event, players, curr_state);
                
                if (!players.second.empty())
                    tick.set_players_name(players);
                break;

            default:
                break;
        }   
    }
}

/* Renders all the squares and lines of the board. */
void Game::render_board()
{
    for (auto &i : tick.get_board())
        for (auto &s : i)
            window->draw(s.rect);
    
    for (auto &l : lines)
        window->draw(l);
}

void Game::state_handler()
{
    switch (curr_state)
    {
        case MENU:
            game_menu->draw(*window);

            if (game_menu->start_button_clicked(*window))
                curr_state = NAME_INPUT;
            break;
        
        case NAME_INPUT:
            players_name_text_box.draw(*window);
            break;
        
        case WAITING_INPUT: case PLAYING:
            render_board();
            tick.get_text().draw(*window);
            break;

        case GAME_OVER:
            if (tick.get_victory() == 1)
            {
                game_over_text.set_text(players.first + " Win!!!", 40);
                game_over_text.draw(*window);
            }            
            else if (tick.get_victory() == 2)
            {
                game_over_text.set_text(players.second + " Win!!!", 40);
                game_over_text.draw(*window);
            }
            else if (tick.get_victory() == 3)
            {
                game_over_text.set_text("It's a Tie!!!", 40);
                game_over_text.draw(*window);
            }
            break;

        default:
            break;
    }
}

// Constructor / Destructor
Game::Game()
{
    init_variables(); // init game objects
    init_window();
    init_board();
    set_board();

    game_menu = std::make_unique<menu>(*window);
}

Game::~Game()
{
}

// Accessors
bool Game::running() const
{
    return window->isOpen();
}

// Public Functions:

void Game::update()
{
    update_poll_events();

    // hoever effect
    if (curr_state == WAITING_INPUT)
        mouse_valid_square(window, tick);
}

/* Will render and display the objects in the screen. */
void Game::render()
{
    window->clear(WHITE); // clear old frame

    // Draw game objects
    state_handler();
    
    window->display(); // done drawing
}
