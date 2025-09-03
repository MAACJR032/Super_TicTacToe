#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "buttons.hpp"
#include "board.hpp"
#include "types/game_state.hpp"


class Menu
{
    private:
        static constexpr float BUTTON_WIDTH = 150.f;
        static constexpr float BUTTON_OFFSET = 10.f;
        
    protected:
        std::vector<Button> m_buttons;
        std::vector<Game_text> m_texts;

        void _center_button(Button &button, float window_width, float window_height, float y_factor);
        void _center_text(sf::Text& text, float window_width, float window_height, float y_factor);
        
    public:
        Menu();

        virtual GameState update(sf::RenderWindow&) = 0;
        virtual void draw(sf::RenderWindow &window) const;
};

class Main_menu : public Menu
{
    private:
        Game_text m_title;

        bool _start_button_clicked(sf::RenderWindow &window);
        bool _exit_button_clicked(sf::RenderWindow &window);
        bool _credits_button_clicked(sf::RenderWindow &window);

    public:
        Main_menu(sf::Vector2u window_size);

        GameState update(sf::RenderWindow &window) override;
        void draw(sf::RenderWindow &window) const override;
};

class Credits_menu : public Menu
{
    private:
        struct CreditSection
        {
            std::string title;
            std::vector<std::string> entries;
        };
        
        std::vector<CreditSection> m_sections;
        std::vector<Game_text> m_credits_text;

        void _setup_credits_text(sf::Vector2u window_size);
        bool _return_button_clicked(sf::RenderWindow &window);

    public:
        Credits_menu(sf::Vector2u window_size);

        GameState update(sf::RenderWindow &window) override;
        void draw(sf::RenderWindow &window) const override;
};

class Name_input_menu : public Menu
{
    private:
        std::string m_player1_name;
        std::string m_player2_name;
        Game_text m_type_message;
        Game_text m_error_message;
        Text_box m_name_box;
        Status m_player_turn = Status::X;
        bool m_display_error_message = false;

        void _update_prompt_message(const std::string &message);
        void _set_error_message(const std::string &error_message, const sf::Vector2u window_size);
        void _set_player_turn(Status player);
        void _display_error_message(bool display);
        bool _return_button_clicked(sf::RenderWindow &window);

    public:
        Name_input_menu(sf::Vector2u window_size);

        Text_box& get_text_box();
        Status get_player_turn() const;
        GameState get_player_name(uint32_t unicode, TicTacToe &tictactoe);

        GameState update(sf::RenderWindow &window) override;
        void draw(sf::RenderWindow &window) const override;
        void reset();
};

class End_screen_menu : public Menu
{
    private:
        Game_text m_result_text;
        std::shared_ptr<Board> m_board = nullptr;
        
        bool _rematch_button_clicked(sf::RenderWindow &window);
        bool _menu_button_clicked(sf::RenderWindow &window);
    
    public:
        End_screen_menu(sf::Vector2u window_size, std::shared_ptr<Board> board);

        void set_result(const std::string &result_message, const sf::Vector2u window_size);
        GameState update(sf::RenderWindow &window) override;
        void draw(sf::RenderWindow &window) const override;
};

class Menu_manager
{
    private:
        Main_menu m_main_menu;
        Credits_menu m_credits_menu;
        Name_input_menu m_name_input_menu;
        End_screen_menu m_end_screen_menu;

        GameState m_curr_state = GameState::MENU;
        Menu *m_curr_menu = nullptr;

        bool m_mouse_ready_for_click = true;

    public:
        Menu_manager(sf::Vector2u window_size, std::shared_ptr<Board> board);

        void switch_menu(GameState curr_state);
        GameState update(sf::RenderWindow &window);
        GameState get_players_name(uint32_t unicode, TicTacToe &tictactoe);
        void draw(sf::RenderWindow &window) const;
};