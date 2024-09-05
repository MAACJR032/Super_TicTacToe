#include "text.hpp"

void game_text::load_font()
{
    open_sans.loadFromFile("Utils/Open_Sans/OpenSans.ttf");
}

game_text::game_text()
{   
    load_font();
    
    text.setFont(open_sans);
    text.setFillColor(BLACK);
}

sf::Text game_text::get_text()
{
    return text;
}

player_turn_text::player_turn_text(std::string player1, std::string player2) : game_text(), player1(player1), player2(player2)
{
    text.setPosition(15.f, 15.f);
    text.setString(player1 + " Turn");
}

void player_turn_text::change_curr_player(int8_t player)
{
    if (player == 1)
        text.setString(player1 + " Turn");
    else
        text.setString(player2 + " Turn");
}

text_box::text_box() : game_text()
{
    text.setPosition(10.f, 10.f);
    box.setFillColor(TRANSPARENT_BLACK);
    box.setSize({200.f, 35.f});
    box.setPosition(10.f, 10.f);
}

void text_box::delete_last_char()
{
    std::string t = text_string.str();
    t.pop_back();

    text_string.str("");
    text_string << t;

    text.setString(text_string.str());
}

void text_box::set_selected(bool sel)
{
    selected = sel;

    if (!selected)
    {
        std::string t = text_string.str();
        text.setString(t);
    }
}

void text_box::input_handler(int typed_char)
{
    if (typed_char != BACKSPACE && typed_char != ENTER && typed_char != ESC)
    {
        text_string << static_cast<char> (typed_char);
    }
    else if (typed_char == BACKSPACE)
    {
        if (text_string.str().length() > 0)
            delete_last_char();        
    }
    
    text.setString(text_string.str() + "_");
}

std::string text_box::get_text_string()
{
    return text_string.str();
}

bool text_box::check_mouse_click_button(std::unique_ptr<sf::Window> &window) 
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
        box.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(*window)))
    {
        return true;
    }
    
    return false;
}

void text_box::typed(sf::Event input)
{
    if (selected)
    {
        int typed_char = input.text.unicode;

        if (typed_char < 128)
        {
            if (text_string.str().length() <= limit)
            {
                input_handler(typed_char);
            }
            else if (text_string.str().length() > limit &&
                     typed_char == BACKSPACE)
            {
                delete_last_char();
            }
        }
    }

    text.setString(text_string.str() + "_");
}

void text_box::draw(sf::RenderWindow &window)
{
    window.draw(box);
    window.draw(text);
}