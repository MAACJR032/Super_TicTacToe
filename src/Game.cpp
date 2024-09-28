#include "Game.hpp"

static const sf::Vector2u s_window_size(1680, 900);

/* Constructor */
Game::Game() : m_window(sf::VideoMode(1680, 900), "Super Tic Tac Toe", sf::Style::Close), 
               m_game_menu(s_window_size), m_credits_menu(s_window_size), m_name_input_menu(s_window_size),
               m_end_screen_menu(s_window_size)
{
    m_window.setFramerateLimit(60);
 
    m_lines.reserve(4);
    m_vertical_line.setSize(sf::Vector2f(10.f, 790.f));
    m_vertical_line.setFillColor(BLACK);

    m_horizontal_line.setSize(sf::Vector2f(790.f, 10.f));
    m_horizontal_line.setFillColor(BLACK);

    set_board_position();
}

/* will set the position of all the board objects. */
void Game::set_board_position()
{
    // seting the board's position
    float x = 500.f, y = 100.f;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            m_tic_tac_toe.get_board_at(i, j).get_rectangle().setPosition({x + j * 75, y + i * 75});
    
    // vertical lines
    for (int i = 0; i < 2; i++)
    {
        m_vertical_line.setPosition({720 + static_cast<float>(225 * i), y-60});
        m_lines.push_back(m_vertical_line);
    }
    
    // horizontal lines
    for (int i = 0; i < 2; i++)
    {
        m_horizontal_line.setPosition({x-55, y + 220 + static_cast<float>(225 * i)});
        m_lines.push_back(m_horizontal_line);
    }
}

void Game::update_poll_events()
{
    while (m_window.pollEvent(m_event))
    {
        switch (m_event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;
            
            // pressing Esc to close
            case sf::Event::KeyPressed:
                if (m_event.key.code == sf::Keyboard::Escape)
                    m_window.close();
                break;
            
            // Click on available squares to play
            case sf::Event::MouseButtonPressed:
                handle_mouse_button_pressed();
                break;
                
            case sf::Event::TextEntered:
                handle_text_input();
                break;

            default:
                break;
        }   
    }
}

void Game::handle_mouse_button_pressed()
{
    if (m_current_state == GameState::WAITING_INPUT || m_current_state == GameState::PLAYING)
        handle_player_move(m_event, m_window, m_current_state, m_tic_tac_toe);
    else if (m_current_state == GameState::NAME_INPUT)
        handle_text_box_sel(m_name_input_menu.get_text_box(), m_window);
}

void Game::handle_text_input()
{
    if (m_current_state == GameState::NAME_INPUT)
    {
        m_name_input_menu.get_text_box().typed(m_event.text.unicode);
        get_player_name(m_name_input_menu, m_event.text.unicode, m_tic_tac_toe.get_players_name());
        
        if (!m_name_input_menu.is_player1_turn())
        {
            m_name_input_menu.set_type_message("O's Name:");
        }
        if (!m_tic_tac_toe.get_players_name().second.empty())
        {
            m_tic_tac_toe.set_players_name(m_tic_tac_toe.get_players_name().first, m_tic_tac_toe.get_players_name().second);
            m_current_state = GameState::WAITING_INPUT;
        }
    }
}

/* Draws all the squares and lines of the board. */
void Game::draw_board()
{
    m_tic_tac_toe.draw(m_window);
    
    for (const auto &l : m_lines)
        m_window.draw(l);
}

/* Draws and handle events from the current game state. */
void Game::state_manager()
{
    switch (m_current_state)
    {
        case GameState::MENU:
            handle_main_menu();
            break;
        
        case GameState::CREDITS:
            handle_credits_menu();
            break;
        
        case GameState::NAME_INPUT:
            handle_name_input_menu();
            break;
        
        case GameState::WAITING_INPUT: case GameState::PLAYING:
            draw_board();
            break;

        case GameState::END_SCREEN:
            handle_end_screen_menu();
            break;

        default:
            break;
    }
}

void Game::handle_main_menu()
{
    m_game_menu.draw(m_window);

    if (m_game_menu.start_button_clicked(m_window))
        m_current_state = GameState::NAME_INPUT;
    else if (m_game_menu.exit_button_clicked(m_window))
        m_window.close();
    else if (m_game_menu.credits_button_clicked(m_window))
        m_current_state = GameState::CREDITS;
}

void Game::handle_credits_menu()
{
    m_credits_menu.draw(m_window);

    if (m_credits_menu.return_button_clicked(m_window))
    {
        m_timer.restart();
        while (m_timer.getElapsedTime().asMilliseconds() < 300) {};

        m_current_state = GameState::MENU;
    }
}

void Game::handle_name_input_menu()
{
    m_name_input_menu.draw(m_window);

    if (m_credits_menu.return_button_clicked(m_window))
    {
        m_tic_tac_toe.set_players_name("", "");
        m_name_input_menu.get_text_box().clear_deselect();
        m_name_input_menu.set_type_message("X's Name:");
        m_name_input_menu.set_player1_turn();

        m_timer.restart();
        while (m_timer.getElapsedTime().asMilliseconds() < 300) {};

        m_current_state = GameState::MENU;
    }
}

void Game::handle_end_screen_menu()
{
    if (m_tic_tac_toe.get_victory() == Status::X)
    {
        m_end_screen_menu.set_result(m_tic_tac_toe.get_players_name().first + " Win!!!", m_window.getSize());
        m_end_screen_menu.draw(m_window);
    }            
    else if (m_tic_tac_toe.get_victory() == Status::O)
    {
        m_end_screen_menu.set_result(m_tic_tac_toe.get_players_name().second + " Win!!!", m_window.getSize());
        m_end_screen_menu.draw(m_window);
    }
    else if (m_tic_tac_toe.get_victory() == Status::TIE)
    {
        m_end_screen_menu.set_result("It's a Tie!!!", m_window.getSize());
        m_end_screen_menu.draw(m_window);
    }

    if (m_end_screen_menu.menu_button_clicked(m_window))
    {
        m_tic_tac_toe.set_players_name("", "");
        m_name_input_menu.set_type_message("X's Name:");
        m_name_input_menu.get_text_box().clear_deselect();
        
        m_tic_tac_toe.reset();
        m_timer.restart();
        while (m_timer.getElapsedTime().asMilliseconds() < 300) {};

        m_current_state = GameState::MENU;
    }
    else if (m_end_screen_menu.rematch_button_clicked(m_window))
    {
        m_tic_tac_toe.reset();
        m_timer.restart();
        while (m_timer.getElapsedTime().asMilliseconds() < 300) {};

        m_current_state = GameState::WAITING_INPUT;
    }
}

// Accessors
bool Game::running() const
{
    return m_window.isOpen();
}

// Public Functions:

/* Update poll events and hoever effect. */
void Game::update()
{
    update_poll_events();

    if (m_current_state == GameState::WAITING_INPUT)
        hoever_effect(m_window, m_tic_tac_toe);
}

/* Will render and display the objects in the screen. */
void Game::render()
{
    m_window.clear(WHITE); // clear old frame

    // Draw game objects
    state_manager();
    
    m_window.display(); // done drawing
}