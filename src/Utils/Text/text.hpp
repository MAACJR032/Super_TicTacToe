#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Game_text
{
    protected:
        mutable sf::Text m_text;

    public:
        Game_text();
        Game_text(const std::string& text, uint32_t char_size);
        Game_text(const std::string& text, uint32_t char_size, const sf::Vector2f& position);

        void set_text(const std::string& text);
        void set_text(const std::string& text, uint32_t char_size);
        void set_text(const std::string& text, uint32_t char_size, const sf::Vector2f& position);

        void set_char_size(uint32_t char_size);
        void set_position(const sf::Vector2f& position);

        const sf::Text& get_text() const;
        sf::Text& get_text();
        const std::string get_string() const;
        
        virtual void draw(sf::RenderWindow &window) const;
};