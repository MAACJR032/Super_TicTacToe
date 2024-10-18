#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>

#include "../colors.hpp"
#include "keys_unicode.hpp"
#include "types/status.hpp"
#include "Utils/Path/path_utils.hpp"

class game_text
{
    protected:
        sf::Text m_text;
        std::string str;
        sf::Font m_open_sans;

        void load_font();

    public:
        game_text();
        game_text(const std::string &text, uint32_t char_size);
        game_text(const std::string &text, uint32_t char_size, const sf::Vector2f &position);

        void set_text(const std::string &text);
        void set_text(const std::string &text, uint32_t char_size);
        void set_text(const std::string &text, uint32_t char_size, const sf::Vector2f &position);
        void set_text_utf_8(const std::string &text, uint32_t char_size, const sf::Vector2f &position);
        void set_char_size(uint32_t char_size);
        void set_position(const sf::Vector2f &position);

        sf::Text get_text() const;
        sf::Text& get_text();
        std::string get_string() const;
        std::string& get_string();
        
        virtual void draw(sf::RenderWindow &window) const;
};

class text_box : public game_text
{
    private:
        sf::RectangleShape m_box;
        std::ostringstream m_text_string;
        int m_limit = 15;
        bool m_selected = false;

        bool check_box_selected(sf::RenderWindow &window) const;
        void delete_last_char();
        void input_handler(uint32_t typed_char);

    public:
        text_box(const std::string &text, uint32_t char_size, const sf::Vector2f &position);

        void set_box_position(const sf::Vector2f &position);
        void set_selected(sf::RenderWindow &window);
        bool is_selected() const;
        void typed(uint32_t unicode);
        
        std::string get_text_string() const;
        std::pair<float, float> get_box_sizes() const;

        void draw(sf::RenderWindow &window) const override;
        void clear();
        void clear_deselect();
};