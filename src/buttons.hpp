#pragma once

#include "Utils/Text/text.hpp"
#include "squares.hpp"

class Button : public Game_text
{
    private:
        Clickable_square m_button_rect;

        void _update_mouse_state();
        
    public:
        Button(const std::string &s, uint32_t char_size, square_colors colors);
        Button(const std::string &s, uint32_t char_size, square_colors colors, const sf::Vector2f size);

        void set_position(const sf::Vector2f &button_position, const sf::Vector2f &text_position);
        bool was_clicked(sf::RenderWindow &window);
        sf::RectangleShape& get_rectangle();
        sf::RectangleShape get_rectangle() const;
        void draw(sf::RenderWindow &window) const override;
};

class Text_box
{
    private:
        Button m_box;
        sf::Clock m_cursor_timer;
        std::string m_input;
        const char* s_default_message = "Type your name";

        Status m_curr_player = Status::X;
        bool m_show_cursor = false;
        bool m_selected = false;
        uint32_t m_char_limit = 15;

        void _update_display_text();
        void _delete_last_char();
        void _handle_input(uint32_t unicode);

    public:
        Text_box(const std::string &text, uint32_t char_size, square_colors colors);

        std::string get_string() const;
        Button& get_box();
        Button get_box() const;

        void set_position(const sf::Vector2f& box_position, const sf::Vector2f& text_position);
        void set_selected(sf::RenderWindow &window);
        bool is_selected() const;

        void update_cursor();
        void typed_key_handler(uint32_t unicode);
        
        std::pair<float, float> get_box_size() const;

        void update(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window) const;
        void clear(bool deselect);
};