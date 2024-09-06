#include "text.hpp"
#include <iostream>

game_text::game_text()
{   
    load_font();
    
    text.setFont(open_sans);
    text.setFillColor(BLACK);
}

game_text::game_text(std::string s)
{   
    load_font();
    
    text.setFont(open_sans);
    text.setFillColor(BLACK);
    text.setString(s);
}

// private function
void game_text::load_font()
{
    open_sans.loadFromFile("Utils/Open_Sans/OpenSans.ttf");
}

// setters / getters
void game_text::set_text(const std::string s)
{
    text.setString(s);
}

sf::Text game_text::get_text()
{
    return text;
}

// public
void game_text::draw(sf::RenderWindow &window)
{
    window.draw(text);
}



// player_turn_text
player_turn_text::player_turn_text() : game_text()
{
    text.setPosition(15.f, 15.f);
}

/* Changes the name of the player after each play*/
void player_turn_text::change_curr_player(int8_t player)
{
    if (player == 1)
        text.setString(player1 + " Turn");
    else
        text.setString(player2 + " Turn");
}

/* set the name of both players */
void player_turn_text::set_names(std::string player1, std::string player2)
{
    this->player1 = player1;
    this->player2 = player2;
}

// text_box:
text_box::text_box() : game_text()
{
    text.setPosition(10.f, 10.f);
    
    box.setFillColor(TRANSPARENT_BLACK);
    box.setOutlineColor(BLACK);
    box.setSize({200.f, 35.f});
    box.setPosition(10.f, 10.f);
}

// private functions:

/* Returns true If the box was clicked */
bool text_box::check_mouse_click_button(sf::Window &window) 
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
        box.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(window)))
    {
        return true;
    }
    
    return false;
}

/* Used for the backwards key */
void text_box::delete_last_char()
{
    std::string t = text_string.str();
    t.pop_back();

    text_string.str("");
    text_string << t;

    text.setString(text_string.str());
}

/* Will add or remove text from the screen */
void text_box::input_handler(int typed_char)
{
    if (typed_char != BACKSPACE && typed_char != ENTER && typed_char != ESC)
    {
        text_string << static_cast<char> (typed_char);
    }
    else if (typed_char == BACKSPACE)
    {
        if (!text_string.str().empty())
            delete_last_char();        
    }
    
    text.setString(text_string.str() + "_");
}

// public functions:

/* If the box was clicked then it is selected to write on*/
void text_box::set_selected(sf::RenderWindow &window)
{
    if (check_mouse_click_button(window))
    {
        selected = true;
        text.setString(text_string.str() + "_");
    }
    else
        selected = false;

    if (!selected)
    {
        std::string t = text_string.str();
        text.setString(t);
    }
}

bool text_box::is_selected()
{
    return selected;
}

std::string text_box::get_text_string()
{
    return text_string.str();
}

/* If the key was typed it will handle the input */
void text_box::typed(sf::Event input)
{
    if (selected)
    {
        int typed_char = input.text.unicode;

        if (typed_char > 0 && typed_char < 128)
        {
            if (static_cast<int> (text_string.str().length()) <= limit || typed_char == BACKSPACE)
                input_handler(typed_char);
        }
    }
}

void text_box::draw(sf::RenderWindow &window)
{
    window.draw(box);
    window.draw(text);
}

void text_box::clear()
{
    text.setString("_");
    text_string.str("_");
}