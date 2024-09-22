#include "events.hpp"

/* Return the current mouse position on the window. */
sf::Vector2f get_mouse_position(sf::RenderWindow &window)
{
    return (sf::Vector2f) sf::Mouse::getPosition(window);
}

/* Changes color of valid squares to play on (hoever effect). */
void apply_hoever_effect(Square &s, TicTacToe &t, sf::RenderWindow &window)
{
    if (t.get_grid_status(s.grid - 1) == Status::EMPTY && (t.get_next_grid() == -1 || t.get_next_grid() == s.grid))
    {
        if (s.rect.getGlobalBounds().contains(get_mouse_position(window)) && 
            s.player == Status::EMPTY)
        {
            s.rect.setFillColor(GREY);
        }
    }

    // make sure that every square affected by the hoever effect get back to it's original color
    if (!s.rect.getGlobalBounds().contains(get_mouse_position(window)) && 
        s.rect.getFillColor() == GREY)
    {
        s.rect.setFillColor(WHITE);
    }
}

/* Iterates through the board and changes color of valid squares to play on. */
void hoever_effect(sf::RenderWindow &window, TicTacToe &t)
{
    t.iterate_board(apply_hoever_effect, window);
}


/* If a square was clicked the move will be handled. */
void handle_player_move(sf::Event &event, sf::RenderWindow &window, GameState &curr_state, TicTacToe &t)
{
    if (event.mouseButton.button == sf::Mouse::Left && curr_state == GameState::WAITING_INPUT)
    {
        curr_state = GameState::PLAYING;
        t.play(window);
        curr_state = GameState::WAITING_INPUT;

        Status result = t.get_victory();
        
        if (result == Status::X || result == Status::O || result == Status::TIE)
            curr_state = GameState::END_SCREEN;
    }
}

/* Selects the text box to type the player name. */
void handle_text_box_sel(text_box &t, sf::RenderWindow &window)
{
    t.set_selected(window);
}

/* Stores the the player when ENTER is pressed. */
void get_player_name(text_box &t, sf::Event &event, std::pair<std::string, std::string> &players, GameState &curr_state)
{
    if (event.text.unicode == ENTER && t.get_text_string().length() > 0)
    {
        if (players.first.empty())
            players.first = t.get_text_string();
        else
        {
            players.second = t.get_text_string();
            curr_state = GameState::WAITING_INPUT;
        }

        t.clear();
    }
}