#include "events.hpp"
#include "TicTacToe.hpp"
#include "Game.hpp"

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
            s.rect.setFillColor(WHITE);
        }
    }

    // make sure that every square affected by the hoever effect get back to it's original color
    if (!s.rect.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(*window)) && 
        s.rect.getFillColor() == GREY)
    {
        s.rect.setFillColor(WHITE);
    }
}


/* Iterates through the board and Changes color of valid squares to play on. */
void mouse_valid_square(std::unique_ptr<sf::RenderWindow> &window, TicTacToe &t)
{
    t.iterate_board(mouse_update_valid_square, window);
}

void handle_square_play(sf::Event &event, std::unique_ptr<sf::RenderWindow> &window, game_state &curr_state, TicTacToe &t)
{
    if (event.mouseButton.button == sf::Mouse::Left && curr_state == game_state::WAITING_INPUT)
    {
        curr_state = game_state::PLAYING;
        t.play(window);
        curr_state = game_state::WAITING_INPUT;

        status result = t.get_victory();
        
        if (result == X || result == O || result == TIE)
            curr_state = game_state::END_SCREEN;
    }
}

void handle_text_box_sel(text_box &t, sf::RenderWindow &window)
{
    t.set_selected(window);
}

void get_player_name(text_box &t, sf::Event &event, std::pair<std::string, std::string> &players, game_state &curr_state)
{
    if (event.text.unicode == ENTER && t.get_text_string().length() > 0)
    {
        if (players.first.empty())
            players.first = t.get_text_string();
        else
        {
            players.second = t.get_text_string();
            curr_state = game_state::WAITING_INPUT;
        }

        t.clear();
    }
}