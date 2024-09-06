#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <memory>

#include "colors.hpp"
#include "keys_unicode.hpp"

class game_text
{
    protected:
        sf::Text text;
        sf::Font open_sans;

        void load_font();

    public:
        game_text();
        sf::Text get_text();
};

class player_turn_text : public game_text
{
    private:
        std::string player1, player2;
        
    public:
        player_turn_text(std::string player1, std::string player2);
        void change_curr_player(int8_t player);
};

class text_box : public game_text
{
    private:
        sf::RectangleShape box;
        std::ostringstream text_string;
        int char_size = 10;
        int limit = 15;
        bool selected = false;

        bool check_mouse_click_button(sf::Window &window);
        void delete_last_char();
        void input_handler(int typed_char);

    public:
        text_box();

        std::string get_text_string();
        
        bool is_selected();
        void set_selected(sf::RenderWindow &window);
        void typed(sf::Event input);
        void draw(sf::RenderWindow &window);
        void clear();
};