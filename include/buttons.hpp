#pragma once

#include "text.hpp"

class button : public game_text
{
    private:
        sf::RectangleShape m_button_rect;
        
    public:
        button();
        button(std::string s);

        void set_button_position(const sf::Vector2f &button_position, const sf::Vector2f &text_position);
        bool button_clicked(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window) override;
};