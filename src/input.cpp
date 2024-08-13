#include "../include/input.hpp"

void button_click(sf::Mouse::Button button, sf::RectangleShape &square, std::unique_ptr<sf::RenderWindow> &window)
{
    if (sf::Mouse::isButtonPressed(button) && square.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(*window)))
    {
        square.setFillColor(sf::Color::Red);
    } 
}

