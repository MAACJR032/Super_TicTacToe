#include "../include/events.hpp"

bool button_click(sf::Mouse::Button button, sf::RectangleShape square, std::unique_ptr<sf::RenderWindow> &window, Player &player)
{
    if (sf::Mouse::isButtonPressed(button) && 
        square.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(*window)))
    {
        return true;
    }

    return false;
}