#include "../include/events.hpp"

bool button_click(sf::RectangleShape square, std::unique_ptr<sf::RenderWindow> &window)
{
    sf::Mouse::Button button;
    if (sf::Mouse::isButtonPressed(button) && 
        square.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(*window)))
    {
        return true;
    }

    return false;
}