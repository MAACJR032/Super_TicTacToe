#pragma once

#include <vector>
#include <fstream>
#include "buttons.hpp"

class main_menu
{
    private:
        game_text m_title;
        button m_start_button, m_exit_button, m_credits_button;

    public:
        main_menu(sf::Vector2u window_size);

        bool start_button_clicked(sf::RenderWindow &window);
        bool exit_button_clicked(sf::RenderWindow &window);
        bool credits_button_clicked(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);
};

class credits_menu
{
    private:
        button m_return_button;
        std::ifstream m_credits_file;
        std::vector<game_text> m_credits_text;

    public:
        credits_menu(sf::Vector2u window_size);

        bool back_button_clicked(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);
};

class name_input_menu
{
    private:
        game_text m_type_message;
        text_box m_player_name_box;
        bool player1_turn = true;

    public:
        name_input_menu(sf::Vector2u window_size);

        text_box& get_text_box();
        bool is_player1_turn() const;
        void set_player2_turn();
        void set_type_message(const std::string &message);
        void set_box_text(const std::string &text);
        void draw(sf::RenderWindow &window);
};

class end_screen_menu
{
    private:
        game_text m_result_text;
        button m_rematch_button, m_menu_button;

    public:
        end_screen_menu(sf::Vector2u window_size);

        void set_result(const std::string &result_message, sf::Vector2u window_size);
        bool menu_button_clicked(sf::RenderWindow &window);
        bool rematch_button_clicked(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);
};