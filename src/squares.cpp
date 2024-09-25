#include "squares.hpp"

/* Sets the size of the rectangle and the status as EMPTY */
square::square(int8_t grid)
{
    m_grid = grid;
    m_rect.setSize(sf::Vector2f(208.f, 208.f));
    m_rect.setFillColor(WHITE);
    m_status = Status::EMPTY;
}

void square::set_status(Status status)
{
    m_status = status;
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
bool square::square_clicked(sf::RenderWindow &window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
        m_rect.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(window)))
    {
        return true;
    }

    return false;
}

/* Draws the square. */
void square::draw(sf::RenderWindow &window)
{
    window.draw(m_rect);
}


/* Sets the outline. */
subgrid::subgrid(int8_t sub_grid, int8_t grid) : square(0)
{
    m_sub_grid = sub_grid;
    m_grid = grid;

    m_rect.setSize({71.f, 71.f});
    m_rect.setOutlineColor(DARK_GREY);
    m_rect.setOutlineThickness(2.f);
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