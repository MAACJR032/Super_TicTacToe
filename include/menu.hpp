#pragma once

#include "buttons.hpp"

class main_menu
{
    private:
        game_text title;
        button start, exit, credits;

    public:
        main_menu(sf::RenderWindow &window);

        void draw(sf::RenderWindow &window);
        bool start_button_clicked(sf::RenderWindow &window);
        bool exit_button_clicked(sf::RenderWindow &window);
        bool credits_button_clicked(sf::RenderWindow &window);
};

class name_input_menu
{
    private:
        player_turn_text type_message;
        text_box player_name_box;
        std::pair<std::string, std::string> box_message;

    public:
        name_input_menu(sf::RenderWindow &window);

        text_box& get_text_box();
        void change_type_message();
        void change_box_text(const std::string s);
        void draw(sf::RenderWindow &window);
};

class end_screen_menu
{
    private:
        game_text result_text;
        button play_again, menu_button;

    public:
        end_screen_menu(sf::RenderWindow &window);
        void set_result(const std::string result_message);
        void draw(sf::RenderWindow &window);
};