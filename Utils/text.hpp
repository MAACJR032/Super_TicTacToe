#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>

#include "colors.hpp"
#include "keys_unicode.hpp"
#include "status.hpp"

class game_text
{
    protected:
        sf::Text m_text;
        std::shared_ptr<sf::Font> m_open_sans;

        void load_font();

    public:
        game_text();
        game_text(std::string text);

        void set_text(const std::string &text, uint32_t char_size);
        void set_text(const std::string &text, uint32_t char_size, const sf::Vector2f position);
        void set_text_utf_8(const std::string &text, uint32_t char_size, const sf::Vector2f position);
        void set_position(const sf::Vector2f position);

        sf::Text get_text() const;
        
        virtual void draw(sf::RenderWindow &window);
};

class player_turn_text : public game_text
{
    private:
        std::string m_player1, m_player2;
        
    public:
        player_turn_text();

        void set_names(std::string player1, std::string player2);
        void change_curr_player(Status player);
};

class text_box : public game_text
{
    private:
        sf::RectangleShape m_box;
        std::ostringstream m_text_string;
        int m_limit = 15;
        bool m_selected = false;

        bool check_box_selected(sf::RenderWindow &window);
        void delete_last_char();
        void input_handler(int typed_char);

    public:
        text_box();

        void set_box_position(const sf::Vector2f position);
        void set_selected(sf::RenderWindow &window);
        bool is_selected();
        void typed(sf::Event &input);
        
        std::string get_text_string() const;
        std::pair<float, float> get_box_sizes() const;

        void draw(sf::RenderWindow &window) override;
        void clear();
        void clear_deselect();
};