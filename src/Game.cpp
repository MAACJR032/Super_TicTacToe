#include "Game.hpp"

void Game::init_variables()
{
    m_window = nullptr;
    m_lines.reserve(4);
    init_board();
    init_window();
}

void Game::init_window()
{
    m_video_mode.height = 900;
    m_video_mode.width = 1680;
    // video_mode.getDesktopMode();

    m_window = std::make_unique<sf::RenderWindow>(m_video_mode, "Super Tic Tac Toe", sf::Style::Close);
    m_window->setFramerateLimit(60);
}

void Game::init_board()
{
    m_vertical_line.setSize(sf::Vector2f(10.f, 790.f));
    m_vertical_line.setFillColor(BLACK);

    m_horizontal_line.setSize(sf::Vector2f(790.f, 10.f));
    m_horizontal_line.setFillColor(BLACK);
}

/* will set the position of all the 9x9 board. */
void Game::set_board_position()
{
    // seting the board's position
    float x = 500.f, y = 100.f;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            m_tic_tac_toe.get_board_at(i, j).rect.setPosition({x + j * 75, y + i * 75});
    
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
    while (m_window->pollEvent(m_event))
    {
        switch (m_event.type)
        {
            case sf::Event::Closed:
                m_window->close();
                break;
            
            // pressing Esc to close
            case sf::Event::KeyPressed:
                if (m_event.key.code == sf::Keyboard::Escape)
                    m_window->close();
                break;
            
            // Click on available squares to play
            case sf::Event::MouseButtonPressed:
                handle_player_move(m_event, *m_window, m_current_state, m_tic_tac_toe);
                handle_text_box_sel(m_name_input_menu->get_text_box(), *m_window);
                break;
                
            case sf::Event::TextEntered:
                if (m_current_state == GameState::NAME_INPUT)
                {
                    m_name_input_menu->get_text_box().typed(m_event);
                    get_player_name(m_name_input_menu->get_text_box(), m_event, m_players_name, m_current_state, *m_window);
                    
                    if (!m_players_name.second.empty())
                        m_tic_tac_toe.set_players_name(m_players_name);
                    else if (!m_players_name.first.empty())
                        m_name_input_menu->set_type_message("O's Name:");
                    break;
                }

            default:
                break;
        }   
    }
}

/* Renders all the squares and lines of the board. */
void Game::draw_board()
{
    for (const auto &i : m_tic_tac_toe.get_board())
        for (const auto &s : i)
            m_window->draw(s.rect);
    
    for (const auto &l : m_lines)
        m_window->draw(l);
}

void Game::state_manager()
{
    switch (m_current_state)
    {
        case GameState::MENU:
            m_game_menu->draw(*m_window);

            if (m_game_menu->start_button_clicked(*m_window))
                m_current_state = GameState::NAME_INPUT;
            else if (m_game_menu->exit_button_clicked(*m_window))
                m_window->close();
            else if (m_game_menu->credits_button_clicked(*m_window))
                m_current_state = GameState::CREDITS;
            break;
        
        case GameState::CREDITS:
            m_credits_menu->draw(*m_window);
            
            if (m_credits_menu->back_button_clicked(*m_window))
            {
                m_timer.restart();
                while (m_timer.getElapsedTime().asMilliseconds() < 300) {};

                m_current_state = GameState::MENU;
            }
            break;
        
        case GameState::NAME_INPUT:
            m_name_input_menu->draw(*m_window);
            break;
        
        case GameState::WAITING_INPUT: case GameState::PLAYING:
            draw_board();
            m_tic_tac_toe.get_text().draw(*m_window);
            break;

        case GameState::END_SCREEN:
            if (m_tic_tac_toe.get_victory() == Status::X)
            {
                m_end_screen_menu->set_result(m_players_name.first + " Win!!!", *m_window);
                m_end_screen_menu->draw(*m_window);
            }            
            else if (m_tic_tac_toe.get_victory() == Status::X)
            {
                m_end_screen_menu->set_result(m_players_name.second + " Win!!!", *m_window);
                m_end_screen_menu->draw(*m_window);
            }
            else if (m_tic_tac_toe.get_victory() == Status::X)
            {
                m_end_screen_menu->set_result("It's a Tie!!!", *m_window);
                m_end_screen_menu->draw(*m_window);
            }

            if (m_end_screen_menu->menu_button_clicked(*m_window))
            {
                m_players_name = {"", ""};

                m_name_input_menu->set_type_message("X's Name:");
                m_name_input_menu->get_text_box().clear_deselect();
                
                m_tic_tac_toe.reset();
                m_timer.restart();
                while (m_timer.getElapsedTime().asMilliseconds() < 300) {};

                m_current_state = GameState::MENU;
            }
            else if (m_end_screen_menu->rematch_button_clicked(*m_window))
            {
                m_tic_tac_toe.reset();
                m_timer.restart();
                while (m_timer.getElapsedTime().asMilliseconds() < 300) {};

                m_current_state = GameState::WAITING_INPUT;
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
    set_board_position();

    m_game_menu = std::make_unique<main_menu>(*m_window);
    m_name_input_menu = std::make_unique<name_input_menu>(*m_window);
    m_end_screen_menu = std::make_unique<end_screen_menu>(*m_window);
    m_credits_menu = std::make_unique<credits_menu>(*m_window);
}

// Accessors
bool Game::running() const
{
    return m_window->isOpen();
}

// Public Functions:

void Game::update()
{
    update_poll_events();

    // hoever effect
    if (m_current_state == GameState::WAITING_INPUT)
        hoever_effect(*m_window, m_tic_tac_toe);
}

/* Will render and display the objects in the screen. */
void Game::render()
{
    m_window->clear(WHITE); // clear old frame

    // Draw game objects
    state_manager();
    
    m_window->display(); // done drawing
}