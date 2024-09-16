#include "buttons.hpp"

button::button() : game_text()
{
    button_shape.setFillColor(DARK_GREY);
    button_shape.setOutlineColor(BLACK);
    button_shape.setSize({300.f, 70.f});

    text.setPosition({300.f, 200.f});
}

button::button(std::string s) : game_text(s)
{
    button_shape.setFillColor(DARK_GREY);
    button_shape.setOutlineColor(BLACK);
    button_shape.setSize({300.f, 70.f});
    text.setCharacterSize(40);
}

bool button::button_clicked(sf::RenderWindow &window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
        button_shape.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(window)))
    {
        return true;
    }
    
    return false;
}

void button::set_button_position(const sf::Vector2f &button_position, const sf::Vector2f &text_position)
{
    button_shape.setPosition(button_position);
    text.setPosition(text_position);
}

void button::draw(sf::RenderWindow &window)
{
    window.draw(button_shape);
    window.draw(text);
}