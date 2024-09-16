#pragma once

#include "buttons.hpp"

class menu
{
    private:
        game_text title;
        button start, exit, credits;

    public:
        menu(sf::RenderWindow &window);

        void draw(sf::RenderWindow &window);
        bool start_button_clicked(sf::RenderWindow &window);
        bool exit_button_clicked(sf::RenderWindow &window);
        bool credits_button_clicked(sf::RenderWindow &window);
};
