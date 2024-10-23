#include "events.hpp"

/* Return the current mouse position on the window. */
sf::Vector2f get_mouse_position(sf::RenderWindow &window)
{
    return (sf::Vector2f) sf::Mouse::getPosition(window);
}

/* Changes color of valid squares to play on (hoever effect). */
void apply_hoever_effect(subgrid &s, TicTacToe &t, sf::RenderWindow &window)
{
    if (t.get_grid_status(s.get_grid() - 1) == Status::EMPTY && (t.get_next_grid() == -1 || t.get_next_grid() == s.get_grid()))
    {
        if (s.get_rectangle().getGlobalBounds().contains(get_mouse_position(window)) && 
            s.get_status() == Status::EMPTY)
        {
            s.get_rectangle().setFillColor(GREY);
        }
    }

    // make sure that every square affected by the hoever effect get back to it's original color
    if (!s.get_rectangle().getGlobalBounds().contains(get_mouse_position(window)) && 
        s.get_rectangle().getFillColor() == GREY)
    {
        s.get_rectangle().setFillColor(WHITE);
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
void get_player_name(name_input_menu &menu, uint32_t unicode, std::pair<std::string, std::string> &players)
{
    if (unicode != ENTER) return;
    menu.set_error_message_false();

    text_box &box = menu.get_text_box();
    
    std::string str = box.get_text_string();
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char c) { return std::isspace(c); }), str.end());
    
    if (str.length() > 0)
    {
        if (menu.is_player1_turn())
        {
            players.first = box.get_text_string();
            menu.set_player2_turn();
        }
        else if (box.get_text_string() != players.first)
        {   
            players.second = box.get_text_string();
        }
        else
        {
            menu.set_error_message("REPEATED NAME", {1680, 900});
        }
    }
    else
        menu.set_error_message("EMPTY NAME", {1680, 900});

    box.clear(false);
}