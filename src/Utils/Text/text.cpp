#include "text.hpp"

#include "Utils/colors.hpp"
#include "types/status.hpp"
#include "Utils/Text/font.hpp"
#include "Utils/Log/logger.hpp"

/* Loads and sets the font and color of the text. */
Game_text::Game_text()
{
    m_text.setFont(Font::get());
    m_text.setFillColor(BLACK);
}

/* Loads and sets the font and sets the text and it's color. */
Game_text::Game_text(const std::string &text, uint32_t char_size) : Game_text()
{
    set_text(text, char_size);
}

Game_text::Game_text(const std::string &text, uint32_t char_size, const sf::Vector2f &position) : Game_text(text, char_size)
{
    m_text.setPosition(position);
}

void Game_text::set_text(const std::string &text)
{
    m_text.setString(sf::String::fromUtf8(text.begin(), text.end()));
}

/* Sets the text and the character size. */
void Game_text::set_text(const std::string &text, uint32_t char_size)
{
    set_text(text);
    set_char_size(char_size);
}

/* Sets the text, the character size and the position of the text. */
void Game_text::set_text(const std::string &text, uint32_t char_size, const sf::Vector2f &position)
{
    set_text(text, char_size);
    set_position(position);
}

void Game_text::set_char_size(uint32_t char_size)
{
    m_text.setCharacterSize(char_size);
}

void Game_text::set_position(const sf::Vector2f &position)
{
    m_text.setPosition(position);
}

const sf::Text& Game_text::get_text() const
{
    return m_text;
}

sf::Text& Game_text::get_text()
{
    return m_text;
}

const std::string Game_text::get_string() const
{
    return m_text.getString();
}

/* Draws the text. */
void Game_text::draw(sf::RenderWindow &window) const
{
    window.draw(m_text);
}