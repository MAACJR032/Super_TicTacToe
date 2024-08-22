#include "../include/events.hpp"

void button_click(sf::Mouse::Button button, Square &square, std::unique_ptr<sf::RenderWindow> &window, TicTacToe &t, Player &player)
{
    if (sf::Mouse::isButtonPressed(button) && square.rect.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(*window)))
    {
        // if (t.get_next_grid() == -1)
        // {
            square.rect.setFillColor(sf::Color::Red);
            // square.stat = X;
            
            // player.play(t);
            // t.set_next_grid(square.board_pos.first);
            
            // t.print_tic_tac_toe();
            // Create logic to check wich square was clicked
        // }
        // else if (t.get_next_grid() == pressed square)
        // {
        //     /* code */
        // }
        
    } 
}