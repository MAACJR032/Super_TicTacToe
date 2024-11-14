#pragma once

#include <SFML/Graphics.hpp>
#include "Utils/colors.hpp"
#include "types/status.hpp"

#ifdef DEBUG
    #include "Utils/Log/logger.hpp"

    static logger l;
#endif

constexpr float GROW_RATE = 0.2f;
constexpr float PI = 3.14159f;
constexpr float speed = 100.f;
constexpr float square_thickness = 2.f;
constexpr float line_thickness = 20.f;
constexpr float square_size = 71.f;
constexpr float big_square_size = 208.f;
constexpr float half_square_size = 35.5f;
constexpr float correction_factor1 = 25.f;
constexpr float correction_factor2 = 50.f;

class square
{
    protected:
        int m_grid;
        Status m_status;
        sf::RectangleShape m_rect;

    public:
        square(int grid);

        bool operator==(Status stat)
        {
            return m_status == stat; 
        }
        bool operator!=(Status stat)
        {
            return m_status != stat; 
        }
        void operator=(Status stat)
        {
            m_status = stat; 
        }

        void set_position(const sf::Vector2f &position);
        Status get_status() const;
        int get_grid() const;
        sf::RectangleShape& get_rectangle();
        bool clicked(sf::RenderWindow &window) const;
        bool is_mouse_on_square(sf::RenderWindow &window) const;
        void draw(sf::RenderWindow &window) const;
};

class subgrid : public square
{
    private:
        int m_sub_grid;

    public:
        subgrid(int sub_grid, int grid);

        using square::operator=;

        int get_subgrid() const;
};

class line
{
    private:
        LineStatus m_line_status = LineStatus::EMPTY;
        sf::RectangleShape m_line;
        sf::Vector2f m_start, m_end;

        float m_total_length = 0.f;
        float m_current_length = 0.f;
        bool m_drawing_line = false;

    public:
        line();

        void operator=(LineStatus stat)
        {
            m_line_status = stat;
        }

        void set_color(sf::Color color);
        void set_start_end_points(sf::Vector2f start_position, sf::Vector2f end_position);
        void set_total_length(float length);
        void set_current_length(float length);
        void set_size(sf::Vector2f size);
        void set_is_drawing_line(bool is_drawing);
        void set_position(sf::Vector2f position, float angle);
        void set_status(LineStatus status);

        LineStatus get_status() const;
        sf::Vector2f get_start() const;
        sf::Vector2f get_end() const;
        float get_current_length() const;
        float get_total_length() const;
        sf::Vector2f get_size() const;

        bool is_drawing_line() const;
        void increment_length();
        void clear();
        void draw(sf::RenderWindow &window) const;
};