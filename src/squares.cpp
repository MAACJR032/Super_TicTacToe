#include "squares.hpp"

/* Sets the size of the rectangle and the status as EMPTY */
square::square(int8_t grid)
{
    m_grid = grid;
    m_rect.setSize(sf::Vector2f(big_square_size, big_square_size));
    m_rect.setFillColor(WHITE);
    m_status = Status::EMPTY;
}

void square::set_position(const sf::Vector2f &position)
{
    m_rect.setPosition(position);
}

int8_t square::get_grid() const
{
    return m_grid;
}

Status square::get_status() const
{
    return m_status;
}

/* Returns a reference to sf::RectangleShape. */
sf::RectangleShape& square::get_rectangle()
{
    return m_rect;
}

/* Returns true if the square was clicked by the mouse. */
bool square::square_clicked(sf::RenderWindow &window) const
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
        m_rect.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(window)))
    {
        return true;
    }

    return false;
}

/* Draws the square. */
void square::draw(sf::RenderWindow &window) const
{
    window.draw(m_rect);
}


/* Sets the outline. */
subgrid::subgrid(int8_t sub_grid, int8_t grid) : square(0)
{
    m_sub_grid = sub_grid;
    m_grid = grid;

    m_rect.setSize({square_size, square_size});
    m_rect.setOutlineColor(DARK_GREY);
    m_rect.setOutlineThickness(square_thickness);
}

void subgrid::set_subgrid(int8_t sub_grid)
{
    m_sub_grid = sub_grid;
}

void subgrid::set_subgrid(int8_t sub_grid, int8_t grid)
{
    m_sub_grid = sub_grid;
    m_grid = grid;
}

int8_t subgrid::get_subgrid() const
{
    return m_sub_grid;
}

line::line()
{
    m_line.setSize(sf::Vector2f(0.f, line_thickness));
    m_line.setOrigin(0.f, line_thickness / 2.f);
}

void line::set_color(sf::Color color)
{
    m_line.setFillColor(color);
}

void line::set_start_end_points(sf::Vector2f start_position, sf::Vector2f end_position)
{
    m_start = start_position;
    m_end = end_position;
}

void line::set_total_length(float length)
{
    m_total_length = length;
}

void line::set_current_length(float length)
{
    m_current_length = length;
}

void line::set_size(sf::Vector2f size)
{
    m_line.setSize(size);
}

void line::set_is_drawing_line(bool is_drawing)
{
    m_drawing_line = is_drawing;
}

void line::set_position(sf::Vector2f position, float angle)
{
    m_line.setPosition(position);
    m_line.setRotation(angle);
}

void line::set_status(LineStatus status)
{
    m_line_status = status;
}

LineStatus line::get_status() const
{
    return m_line_status;
}

sf::Vector2f line::get_start() const
{
    return m_start;
}

sf::Vector2f line::get_end() const
{
    return m_end;
}

float line::get_current_length() const
{
    return m_current_length;
}

float line::get_total_length() const
{
    return m_total_length;
}

sf::Vector2f line::get_size() const
{
    return m_line.getSize();
}

bool line::is_drawing_line() const
{
    return m_drawing_line;
}

void line::increment_length()
{
    m_current_length += speed * GROW_RATE;
}

void line::clear()
{
    m_drawing_line = false;
    m_total_length = 0.f;
    m_current_length = 0.f;
    m_line_status = LineStatus::EMPTY;
    m_line.setSize({0.f, line_thickness});

    m_start = {0.f, 0.f};
    m_end = {0.f, 0.f};
}

void line::draw(sf::RenderWindow &window) const
{
    window.draw(m_line);
}