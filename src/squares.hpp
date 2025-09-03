#pragma once

#include <SFML/Graphics.hpp>
#include "types/status.hpp"

struct square_colors
{
    sf::Color main_color;
    sf::Color clicked_color;
    sf::Color outline_color;
    sf::Color text_color;
    float     outline_thickness;
};

class Square
{
    protected:
        Status m_status = Status::EMPTY;
        sf::RectangleShape m_rect;
        sf::RectangleShape m_hitbox;

    public:
        Square();

        static constexpr float square_thickness = 2.f;
        static constexpr float square_size = 71.f;
        static constexpr float big_square_size = 208.f;
        static constexpr float half_square_size = 35.5f;

        sf::RectangleShape& get_rectangle();
        sf::RectangleShape get_rectangle() const;
        sf::RectangleShape& get_hitbox();
        
        Status get_status() const;
        void set_status(Status status);
        
        void set_position(const sf::Vector2f &position);
        bool is_mouse_on_square(sf::RenderWindow &window) const;
        void draw(sf::RenderWindow &window) const;
};

class Clickable_square : public Square
{
    private:
        bool m_pressed = false;
        square_colors m_colors;

    public:
        Clickable_square(square_colors colors);

        bool was_clicked(sf::RenderWindow &window);
};

class Line
{
    private:
        LineStatus m_result_status = LineStatus::EMPTY;
        sf::RectangleShape m_line;
        sf::Vector2f m_start, m_end;

        float m_total_length = 0.f;
        float m_current_length = 0.f;
        bool m_drawing_line = false;

        void _increment_length();

    public:
        Line();

        static constexpr float line_thickness     = 20.f;
        static constexpr float GROW_RATE          = 0.2f;
        static constexpr float speed              = 100.f;
        static constexpr float PI                 = 3.14159f;
        static constexpr float correction_factor1 = 25.f;
        static constexpr float correction_factor2 = 50.f;

        void set_color(sf::Color color);
        void set_start_end_points(sf::Vector2f start_position, sf::Vector2f end_position);
        void set_total_length(float length);
        void set_is_drawing_line(bool is_drawing);
        void set_position(sf::Vector2f position, float angle);
        void set_status(LineStatus status);

        LineStatus get_status() const;
        sf::Vector2f get_start() const;
        sf::Vector2f get_end() const;

        bool is_drawing_line() const;
        bool is_line_max_size();
        void reset();
        void draw(sf::RenderWindow &window);
};