#include "squares.hpp"

/* Sets the configuration that is used for all the squares in the board. */
void set_square(sf::RectangleShape &square)
{
    square.setSize(sf::Vector2f(71.f, 71.f));
    square.setFillColor(WHITE);
    square.setOutlineColor(DARK_GREY);
    square.setOutlineThickness(2.f);
}

/* Returns true if the square was clicked by the mouse. */
bool square_clicked(sf::RectangleShape &square, sf::RenderWindow &window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
        square.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(window)))
    {
        return true;
    }

    return false;
}