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
                handle_text_box_sel(name_input->get_text_box(), *window);
                break;
                
            case sf::Event::TextEntered:
                name_input->get_text_box().typed(event);
                get_player_name(name_input->get_text_box(), event, players, curr_state);
                
                if (!players.second.empty())
                    tick.set_players_name(players);
                else if (!players.first.empty())
                    name_input->change_type_message("O's Name:");                
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

void Game::state_manager()
{
    switch (curr_state)
    {
        case game_state::MENU:
            game_menu->draw(*window);

            if (game_menu->start_button_clicked(*window))
                curr_state = game_state::NAME_INPUT;
            else if (game_menu->exit_button_clicked(*window))
                window->close();
            else if (game_menu->credits_button_clicked(*window))
                curr_state = game_state::CREDITS;
            break;
        
        case game_state::CREDITS:
            credits->draw_text(*window);
            // printf("chegou aqui\n");
            break;
        
        case game_state::NAME_INPUT:
            name_input->draw(*window);
            break;
        
        case game_state::WAITING_INPUT: case game_state::PLAYING:
            render_board();
            tick.get_text().draw(*window);
            break;

        case game_state::END_SCREEN:
            if (tick.get_victory() == 1)
            {
                end_screen->set_result(players.first + " Win!!!", *window);
                end_screen->draw(*window);
            }            
            else if (tick.get_victory() == 2)
            {
                end_screen->set_result(players.second + " Win!!!", *window);
                end_screen->draw(*window);
            }
            else if (tick.get_victory() == 3)
            {
                end_screen->set_result("It's a Tie!!!", *window);
                end_screen->draw(*window);
            }

            if (end_screen->menu_button_clicked(*window))
            {
                players.first.clear();
                players.second.clear();

                name_input->change_type_message("X's Name:");
                name_input->get_text_box().clear_deselect();
                
                tick.reset();
                timer.restart();
                while (timer.getElapsedTime().asMilliseconds() < 200) {};

                curr_state = game_state::MENU;
            }
            else if (end_screen->rematch_button_clicked(*window))
            {
                tick.reset();
                timer.restart();
                while (timer.getElapsedTime().asMilliseconds() < 200) {};

                curr_state = game_state::WAITING_INPUT;
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

    game_menu = std::make_unique<main_menu>(*window);
    name_input = std::make_unique<name_input_menu>(*window);
    end_screen = std::make_unique<end_screen_menu>(*window);
    credits = std::make_unique<credits_menu>();
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
    if (curr_state == game_state::WAITING_INPUT)
        mouse_valid_square(window, tick);
}

/* Will render and display the objects in the screen. */
void Game::render()
{
    window->clear(WHITE); // clear old frame

    // Draw game objects
    state_manager();
    
    window->display(); // done drawing
}