#include "squares.hpp"

/* Sets the configuration that is used for all the squares in the board. */
void set_square(sf::RectangleShape &square)
{
    square.setSize(sf::Vector2f(71.f, 71.f));
    square.setFillColor(WHITE);
    square.setOutlineColor(DARK_GREY);
    square.setOutlineThickness(2.f);
}