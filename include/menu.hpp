#pragma once

#include <vector>
#include <fstream>
#include <locale>
#include <codecvt>
#include "buttons.hpp"

class main_menu
{
    private:
        game_text m_title;
        button m_start_button, m_exit_button, m_credits_button;

    public:
        main_menu(sf::Vector2u window_size);

        bool start_button_clicked(sf::RenderWindow &window) const;
        bool exit_button_clicked(sf::RenderWindow &window) const;
        bool credits_button_clicked(sf::RenderWindow &window) const;
        void draw(sf::RenderWindow &window) const;
};

class credits_menu
{
    private:
        button m_return_button;
        std::ifstream m_credits_file;
        std::vector<game_text> m_credits_text;

    public:
        credits_menu(sf::Vector2u window_size);

        bool back_button_clicked(sf::RenderWindow &window) const;
        void draw(sf::RenderWindow &window) const;
};

class name_input_menu
{
    private:
        game_text m_type_message;
        game_text m_error_message;
        text_box m_player_name_box;
        bool player1_turn = true;
        bool display_error_message = false;

    public:
        name_input_menu(sf::Vector2u window_size);

        text_box& get_text_box();
        bool is_player1_turn() const;
        void set_player2_turn();
        void set_error_message_false();
        void set_box_text(const std::string &text);
        void set_type_message(const std::string &message);
        void set_error_message(const std::string &error_message, const sf::Vector2u window_size);
        void draw(sf::RenderWindow &window) const;
};

class end_screen_menu
{
    private:
        game_text m_result_text;
        button m_rematch_button, m_menu_button;

    public:
        end_screen_menu(sf::Vector2u window_size);

        void set_result(const std::string &result_message, const sf::Vector2u window_size);
        bool menu_button_clicked(sf::RenderWindow &window) const;
        bool rematch_button_clicked(sf::RenderWindow &window) const;
        void draw(sf::RenderWindow &window) const;
};