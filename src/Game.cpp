#include "Game.hpp"

#include "Utils/Log/logger.hpp"
#include "Utils/colors.hpp"
#include "squares.hpp"
#include "texture.hpp"

Game::Game() : m_window(sf::VideoMode(1680, 900), "Super Tic Tac Toe", sf::Style::Close), 
               m_menu_manager(s_window_size, m_board)
{
    m_window.setFramerateLimit(60);

    Texture::load_all();
    
    LOG_DEBUG("window initialized");
}

void Game::_update_poll_events()
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

            case sf::Event::TextEntered:
                _handle_text_input();
                break;

            default:
                break;
        }   
    }
}

void Game::_switch_game_state(GameState new_state)
{
    if (m_current_state != new_state)
        m_current_state = new_state;
}

void Game::_handle_text_input()
{
    if (m_current_state == GameState::NAME_INPUT)
        _switch_game_state(m_menu_manager.get_players_name(m_event.text.unicode, m_board->get_tic_tac_toe()));
}

// Accessors
bool Game::running() const
{
    return m_window.isOpen();
}

/* Update poll events and hover effect. */
void Game::update()
{
    _update_poll_events();
    
    if (m_current_state == GameState::WAITING_INPUT)
        m_board->hover_effect(m_window);
}

/* Will render and display the objects in the screen. */
void Game::render()
{
    m_window.clear(WHITE);

    if (m_current_state != GameState::PLAYING && m_current_state != GameState::WAITING_INPUT)
    {
        _switch_game_state(m_menu_manager.update(m_window));
    }
    else
    {
        m_match_status = m_board->play(m_window);
        m_board->draw(m_window);
        
        if (m_match_status != Status::EMPTY)
        {
            _switch_game_state(GameState::END_SCREEN);
            m_menu_manager.switch_menu(m_current_state);
        }
    }
    m_window.display();
}