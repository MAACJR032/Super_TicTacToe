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
void get_player_name(name_input_menu &menu, uint32_t unicode, std::pair<std::string, std::string> &players, GameState &curr_state, sf::RenderWindow &window)
{
    if (unicode != ENTER) return;

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
            std::cout << str << " " << str.length() << '\n';
            players.second = box.get_text_string();
        }
        
        // TODO: Error message if press ENTER for empty name or repeated name

        // else if (t.get_text_string() != players.first)
        // {
        //     players.second = t.get_text_string();
        //     curr_state = GameState::WAITING_INPUT;
        // }
        // else
        // {
        //     game_text error_message;
            
        //     float half_x = window.getSize().x / 2.f;
        //     float half_y = window.getSize().y / 2.f;

        //     if (t.get_text_string().empty())
        //     {
        //         error_message.set_text("EMPTY NAME", 40);
        //         sf::FloatRect bounds = error_message.get_text().getLocalBounds();
                
        //         error_message.set_position({half_x - bounds.width, half_y / 1.5f});
        //         error_message.draw(window);
        //     }
        // }

        box.clear();
    }
}