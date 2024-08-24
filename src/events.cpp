#include "../include/events.hpp"

bool button_click(sf::RectangleShape &square, std::unique_ptr<sf::RenderWindow> &window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
        square.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(*window)))
    {
        return true;
    }

    return false;
}