#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "buttons.hpp"
#include "menu.hpp"
#include "types/game_state.hpp"
#include "board.hpp"

class Game
{
    inline static const sf::Vector2u s_window_size = {1680, 900};

    private:
        sf::RenderWindow m_window;
        sf::VideoMode m_video_mode;
        sf::Event m_event;
        sf::Clock m_timer;
        
        Status m_match_status = Status::EMPTY;
        GameState m_current_state = GameState::MENU;
        
        std::shared_ptr<Board> m_board = std::make_shared<Board>();
        Menu_manager m_menu_manager;

        void _update_poll_events();
        void _handle_text_input();
        void _switch_game_state(GameState new_state);        

    public:
        Game();

        bool running() const;

        void update();
        void render();
};