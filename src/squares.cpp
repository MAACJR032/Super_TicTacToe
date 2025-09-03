#include "squares.hpp"

#include "texture.hpp"
#include "Utils/colors.hpp"
#include "Utils/Log/logger.hpp"

// MUDAR PARA TER MAIS ARGUMENTO NO CONTRUTOR DE SQUARE
/* Sets the size of the rectangle and the status as EMPTY */
Square::Square()
{
    m_rect.setSize(sf::Vector2f(big_square_size, big_square_size));
    m_rect.setFillColor(sf::Color::Transparent);
    m_hitbox.setSize(sf::Vector2f(big_square_size - 2.f, big_square_size - 2.f));
}

/* Returns a reference to sf::RectangleShape. */
sf::RectangleShape& Square::get_rectangle()
{
    return m_rect;
}

sf::RectangleShape Square::get_rectangle() const
{
    return m_rect;
}

sf::RectangleShape& Square::get_hitbox()
{
    return m_hitbox;
}

Status Square::get_status() const
{
    return m_status;
}

void Square::set_status(Status status)
{
    m_status = status;
}

void Square::set_position(const sf::Vector2f &position)
{
    m_rect.setPosition(position);
    m_hitbox.setPosition(position);
}

/* Returns true if the mouse is over the square. */
bool Square::is_mouse_on_square(sf::RenderWindow &window) const
{
    return m_hitbox.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(window));
}

/* Draws the square. */
void Square::draw(sf::RenderWindow &window) const
{
    window.draw(m_rect);
}

Clickable_square::Clickable_square(square_colors colors) : Square()
{
    m_colors = colors;
    m_rect.setFillColor(colors.main_color);
    m_rect.setFillColor(colors.main_color);
    m_rect.setOutlineColor(colors.outline_color);
    m_rect.setOutlineThickness(colors.outline_thickness);
}

bool Clickable_square::was_clicked(sf::RenderWindow &window)
{
    bool mouseDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);

    if (mouseDown)
    {
        if (!m_pressed && m_rect.getGlobalBounds().contains(mousePos))
        {
            m_pressed = true;
            m_rect.setFillColor(m_colors.clicked_color);
        }
    }
    else
    {
        // On release, if press started inside and release is inside, it's a click
        if (m_pressed)
        {
            m_pressed = false;
            m_rect.setFillColor(m_colors.main_color);
            if (m_rect.getGlobalBounds().contains(mousePos))
                return true;
        }
    }

    return false;
}

/* Initializes the result line. */
Line::Line()
{
    m_line.setSize(sf::Vector2f(0.f, line_thickness));
    m_line.setOrigin(0.f, line_thickness / 2.f);

    LOG_DEBUG("line initialized");
}

void Line::set_color(sf::Color color)
{
    m_line.setFillColor(color);
}

/* Sets the starting and ending position of the line. */
void Line::set_start_end_points(sf::Vector2f start_position, sf::Vector2f end_position)
{
    m_start = start_position;
    m_end = end_position;
}

void Line::set_total_length(float length)
{
    m_total_length = length;
}

void Line::set_is_drawing_line(bool is_drawing)
{
    m_drawing_line = is_drawing;
}

void Line::set_position(sf::Vector2f position, float angle)
{
    m_line.setPosition(position);
    m_line.setRotation(angle);
}

void Line::set_status(LineStatus status)
{
    m_result_status = status;
}

LineStatus Line::get_status() const
{
    return m_result_status;
}

/* Returns the starting point of the line. */
sf::Vector2f Line::get_start() const
{
    return m_start;
}

/* Returns the ending point of the line. */
sf::Vector2f Line::get_end() const
{
    return m_end;
}

bool Line::is_drawing_line() const
{
    return m_drawing_line;
}

bool Line::is_line_max_size()
{
    if (m_line.getSize().x == m_total_length)
    {
        m_drawing_line = false;
        return true;
    }

    return false;
}

void Line::_increment_length()
{
    m_current_length += speed * GROW_RATE;
}

/* Resets the line methods. */
void Line::reset()
{
    m_drawing_line   = false;
    m_total_length   = 0.f;
    m_current_length = 0.f;
    m_result_status  = LineStatus::EMPTY;
    m_line.setSize({0.f, line_thickness});

    m_start = {0.f, 0.f};
    m_end   = {0.f, 0.f};
    LOG_DEBUG("line reset");
}

void Line::draw(sf::RenderWindow &window)
{
    _increment_length();
    if (m_current_length > m_total_length)
        m_current_length = m_total_length;
    
    m_line.setSize(sf::Vector2f(m_current_length, Line::line_thickness));

    window.draw(m_line);
}