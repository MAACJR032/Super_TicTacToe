#include "buttons.hpp"

button::button() : game_text()
{
    m_button_rect.setFillColor(DARK_GREY);
    m_button_rect.setOutlineColor(BLACK);
    m_button_rect.setSize({300.f, 70.f});
}

button::button(std::string s) : game_text(s)
{
    m_button_rect.setFillColor(DARK_GREY);
    m_button_rect.setOutlineColor(BLACK);
    m_button_rect.setSize({300.f, 70.f});
    m_text.setCharacterSize(40);
}

void button::set_button_position(const sf::Vector2f &button_position, const sf::Vector2f &text_position)
{
    m_button_rect.setPosition(button_position);
    m_text.setPosition(text_position);
}

bool button::button_clicked(sf::RenderWindow &window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
        m_button_rect.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(window)))
    {
        return true;
    }
    
    return false;
}

void button::draw(sf::RenderWindow &window)
{
    window.draw(m_button_rect);
    window.draw(m_text);
}