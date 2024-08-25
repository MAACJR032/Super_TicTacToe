#include "../include/events.hpp"

/* Returns true if the square was clicked by the mouse. */
bool button_click(sf::RectangleShape &square, std::unique_ptr<sf::RenderWindow> &window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
        square.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(*window)))
    {
        return true;
    }

    return false;
}

/* Changes color of valid squares to play on. */
void mouse_update_valid_square(Square &s, TicTacToe &t, std::unique_ptr<sf::RenderWindow> &window)
{
    if (t.get_grid_status(s.grid - 1) == EMPTY && (t.get_next_grid() == -1 || t.get_next_grid() == s.grid))
    {
        if (s.rect.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(*window)) && 
            s.player == EMPTY)
        {
            s.rect.setFillColor(sf::Color::Magenta);
        }
        else if (s.rect.getFillColor() == sf::Color::Magenta)
        {
            s.rect.setFillColor(sf::Color::Blue);
        }
    }
}

/* Iterates through the board and Changes color of valid squares to play on. */
void mouse_valid_square(std::unique_ptr<sf::RenderWindow> &window, TicTacToe &t)
{
    t.iterate_board(mouse_update_valid_square, window);
}