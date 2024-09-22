#include "text.hpp"

game_text::game_text() : m_open_sans(std::make_shared<sf::Font>())
{   
    load_font();
    
    m_text.setFont(*m_open_sans);
    m_text.setFillColor(BLACK);
}

game_text::game_text(std::string text) : m_open_sans(std::make_shared<sf::Font>())
{   
    load_font();
    
    m_text.setFont(*m_open_sans);
    m_text.setFillColor(BLACK);
    m_text.setString(text);
}

// private function
void game_text::load_font()
{
    if (!m_open_sans->loadFromFile("Utils/Open_Sans/OpenSans.ttf"))
        std::cerr << "Could Not Load Font\n";
}

// setters / getters
void game_text::set_text(const std::string &text, uint32_t char_size)
{
    m_text.setString(text);
    m_text.setCharacterSize(char_size);
}

void game_text::set_text(const std::string &text, uint32_t char_size, const sf::Vector2f position)
{
    m_text.setString(text);
    m_text.setCharacterSize(char_size);
    m_text.setPosition(position);
}

void game_text::set_text_utf_8(const std::string &text, uint32_t char_size, const sf::Vector2f position)
{
    m_text.setString(sf::String::fromUtf8(text.begin(), text.end()));
    m_text.setCharacterSize(char_size);
    m_text.setPosition(position);
}

void game_text::set_position(const sf::Vector2f position)
{
    m_text.setPosition(position);
}

sf::Text game_text::get_text() const
{
    return m_text;
}

// public
void game_text::draw(sf::RenderWindow &window)
{
    window.draw(m_text);
}


// player_turn_text
player_turn_text::player_turn_text() : game_text()
{
    m_text.setPosition(15.f, 15.f);
}

/* set the name of both players */
void player_turn_text::set_names(std::string player1, std::string player2)
{
    m_player1 = player1;
    m_player2 = player2;

    m_text.setString(player1 + " Turn");
}

/* Changes the name of the player after each play*/
void player_turn_text::change_curr_player(Status player)
{
    if (player == Status::X)
        m_text.setString(m_player1 + " Turn");
    else
        m_text.setString(m_player2 + " Turn");
}


// text_box:
text_box::text_box() : game_text()
{
    m_text.setPosition(10.f, 10.f);
    m_box.setFillColor(TRANSPARENT_BLACK);
    m_box.setSize({465.f, 45.f});

    sf::FloatRect bounds = m_box.getLocalBounds();
    m_box.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

// private functions:

/* Returns true If the box was clicked */
bool text_box::check_box_selected(sf::RenderWindow &window) 
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
        m_box.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(window)))
    {
        return true;
    }
    
    return false;
}

/* Used for the backwards key */
void text_box::delete_last_char()
{
    std::string t = m_text_string.str();
    t.pop_back();

    m_text_string.str("");
    m_text_string << t;

    m_text.setString(m_text_string.str());
}

/* Will add or remove text from the screen */
void text_box::input_handler(int typed_char)
{
    if (typed_char == BACKSPACE)
    {
        if (!m_text_string.str().empty())
            delete_last_char();
    }
    else if (typed_char == TAB)
    {
        m_text_string << "    ";
    }
    else
    {
        m_text_string << static_cast<char> (typed_char);
    }
    
    m_text.setString(m_text_string.str() + "_");
}

// public functions:


void text_box::set_box_position(const sf::Vector2f position)
{
    m_box.setPosition(position);
}

/* If the box was clicked then it is selected to write on*/
void text_box::set_selected(sf::RenderWindow &window)
{
    if (check_box_selected(window))
    {
        m_selected = true;
        m_text.setString(m_text_string.str() + "_");
    }
    else
        m_selected = false;

    if (!m_selected)
    {
        std::string t = m_text_string.str();
        m_text.setString(t);
    }
}

/* If the key was typed it will handle the input */
void text_box::typed(sf::Event &input)
{
    if (m_selected)
    {
        int typed_char = input.text.unicode;

        if ((typed_char > 31 && typed_char < 128) || (typed_char == ESC) || (typed_char == TAB) || (typed_char == ENTER) || (typed_char == BACKSPACE))
        {
            if (static_cast<int> (m_text_string.str().length()) <= m_limit || typed_char == BACKSPACE)
                input_handler(typed_char);
        }
    }
}

bool text_box::is_selected()
{
    return m_selected;
}

std::string text_box::get_text_string() const
{
    return m_text_string.str();
}

std::pair<float, float> text_box::get_box_sizes() const
{
    return {m_box.getGlobalBounds().width, m_box.getGlobalBounds().height};
}

void text_box::draw(sf::RenderWindow &window)
{
    window.draw(m_box);
    window.draw(m_text);
}

void text_box::clear()
{
    m_text.setString("_");
    m_text_string.str("_");
}

void text_box::clear_deselect()
{
    m_text.setString("");
    m_text_string.str("");
    m_selected = false;
}