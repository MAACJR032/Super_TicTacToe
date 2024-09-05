#include "../include/events.hpp"
#include "../include/TicTacToe.hpp"

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
            s.rect.setFillColor(GREY);
        }
        else if (s.rect.getFillColor() == GREY)
        {
            s.rect.setFillColor(BLUE);
        }
    }

    // make sure that every square affected by the hoever effect get back to it's original color
    if (!s.rect.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(*window)) && 
        s.rect.getFillColor() == GREY)
    {
        s.rect.setFillColor(BLUE);
    }
}


/* Iterates through the board and Changes color of valid squares to play on. */
void mouse_valid_square(std::unique_ptr<sf::RenderWindow> &window, TicTacToe &t)
{
    t.iterate_board(mouse_update_valid_square, window);
}

enum game_state : uint8_t {
    PLAYING, WAITING_INPUT, MENU, GAME_OVER
};

void handle_square_play(sf::Event &event, std::unique_ptr<sf::RenderWindow> &window, game_state &curr_state, TicTacToe &t)
{
    if (event.mouseButton.button == sf::Mouse::Left && curr_state == WAITING_INPUT)
    {
        curr_state = PLAYING;
        t.play(window);
        curr_state = WAITING_INPUT;

        status result = t.get_victory();
        
        if (result == X || result == O)
        {
            curr_state = GAME_OVER;
            printf("Player %d wins!!\n", result);
        }
        else if (result == TIE)
        {
            curr_state = GAME_OVER;
            printf("It's a TIE\n");
        }
    }
}

void handle_text_box_sel(text_box &t, sf::RenderWindow &window)
{
    t.set_selected(window);
}