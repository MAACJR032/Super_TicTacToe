#include "grid.hpp"

#include "texture.hpp"
#include "types/status.hpp"
#include "Utils/colors.hpp"
#include "Utils/Log/logger.hpp"

/* Initializes a square with grid and subgrid. */
Subgrid::Subgrid(int grid, int subgrid) : m_rect(square_colors{WHITE, WHITE, BLACK, sf::Color::Transparent, Square::square_thickness})
{
    m_subgrid = subgrid;
    m_grid    = grid;

    m_rect.get_hitbox().setSize({Square::square_size - 2.f, Square::square_size - 2.f});
    m_rect.get_rectangle().setSize({Square::square_size, Square::square_size});
    m_rect.set_status(Status::EMPTY);

    LOG_DEBUGF("square of subgrid %d %d initialized", m_grid, m_subgrid);
}

int Subgrid::get_grid() const
{
    return m_grid;
}

int Subgrid::get_subgrid() const
{
    return m_subgrid;
}

sf::RectangleShape& Subgrid::get_rectangle()
{
    return m_rect.get_rectangle();
}

sf::RectangleShape Subgrid::get_rectangle() const
{
    return m_rect.get_rectangle();
}

bool Subgrid::is_mouse_on_square(sf::RenderWindow &window) const
{
    return m_rect.is_mouse_on_square(window);
}

void Subgrid::set_position(const sf::Vector2f &position)
{
    m_rect.set_position(position);
}

void Subgrid::set_status(Status status)
{
    m_rect.set_status(status);
}

bool Subgrid::was_clicked(sf::RenderWindow &window)
{
    return m_rect.was_clicked(window);
}

void Subgrid::fill(Status player)
{
    Texture::set_subgrid_texture(m_rect.get_rectangle(), player);
    m_rect.set_status(player);
    m_rect.get_rectangle().setFillColor(WHITE);
}

Status Subgrid::get_status() const
{
    return m_rect.get_status();
}

void Subgrid::reset()
{
    m_rect.get_rectangle().setTexture(nullptr);
    m_rect.set_status(Status::EMPTY);
}

void Subgrid::draw(sf::RenderWindow &window) const
{
    window.draw(m_rect.get_rectangle());
}


Grid::Grid(int grid) : m_background()
{
    m_grid = grid;
    m_subgrids.reserve(9);    
    
    for (int i = 0; i < 9; i++)
        m_subgrids.emplace_back(m_grid, i);

    LOG_DEBUGF("Grid %d initialized", m_grid);
}

void Grid::set_position(const sf::Vector2f& position)
{
    m_background.set_position(position);

    const float offset_x = position.x;
    const float offset_y = position.y;

    for (int i = 0; i < 9; i++)
    {
        int row = i / 3;
        int col = i % 3;

        float x = offset_x + col * (Square::square_size + Square::square_thickness);
        float y = offset_y + row * (Square::square_size + Square::square_thickness);

        m_subgrids[i].set_position({x, y});
    }
}

void Grid::draw(sf::RenderWindow& window) const
{
    for (const auto &sub : m_subgrids)
        sub.draw(window);
 
    m_background.draw(window);
}

Subgrid& Grid::get_subgrid(int index)
{
    return m_subgrids.at(index);
}

const Subgrid& Grid::get_subgrid(int index) const
{
    return m_subgrids.at(index);
}

Status Grid::get_status() const
{
    return m_status;
}

void Grid::set_status(Status status)
{
    m_status = status;
}

void Grid::fill(Status player)
{
    Texture::set_grid_texture(m_background.get_rectangle(), player);
    m_background.get_rectangle().setFillColor(WHITE);
    m_status = player;
}

void Grid::reset()
{
    m_status = Status::EMPTY;
    m_background.get_rectangle().setTexture(nullptr);
    m_background.get_rectangle().setFillColor(sf::Color::Transparent);

    for (int i = 0; i < 9; i++)
        m_subgrids[i].reset();
}

/* Updates the status if the given grid is tied */
void Grid::check_for_tie()
{
    uint8_t filled_cells = 0;
    for (uint8_t i = 0; i < m_subgrids.size(); i++)
    {
        if (m_subgrids[i].get_status() != Status::EMPTY)
            filled_cells++;
    }

    if (filled_cells == 9 && m_status == Status::EMPTY)
        m_status = Status::TIE;
}

/* Checks all the cases where the player may have scored in a grid. */
void Grid::update_grid_score(Status current_player)
{
    // Rows
    for (uint8_t i = 0; i < 9; i += 3)
    {
        if (m_subgrids[i].get_status()   == current_player && 
            m_subgrids[i+1].get_status() == current_player && 
            m_subgrids[i+2].get_status() == current_player)
        {
            fill(current_player);
            LOG_DEBUGF(
                "Player %s scored in grid %d",
                (current_player == Status::X) ? "player X" : "player O",
                m_grid
            );
            return;
        }
    }

    // Columns
    for (uint8_t i = 0; i < 3; i++)
    {
        if (m_subgrids[i].get_status()   == current_player && 
            m_subgrids[i+3].get_status() == current_player && 
            m_subgrids[i+6].get_status() == current_player)
        {
            fill(current_player);
            LOG_DEBUGF(
                "Player %s scored in grid %d",
                (current_player == Status::X) ? "player X" : "player O",
                m_grid
            );

            return;
        }
    }
    
    // Diagonals
    if (m_subgrids[0].get_status() == current_player && 
        m_subgrids[4].get_status() == current_player && 
        m_subgrids[8].get_status() == current_player)
    {
        fill(current_player);
        LOG_DEBUGF(
            "Player %s scored in grid %d",
            (current_player == Status::X) ? "player X" : "player O",
            m_grid
        );
    }
    else if (m_subgrids[2].get_status() == current_player && 
             m_subgrids[4].get_status() == current_player && 
             m_subgrids[6].get_status() == current_player)
    {
        fill(current_player);
        LOG_DEBUGF(
            "Player %s scored in grid %d",
            (current_player == Status::X) ? "player X" : "player O",
            m_grid
        );
    }

    check_for_tie();
}

void Grid::hover_effect(sf::RenderWindow &window, int8_t next_grid)
{
    if ((m_grid == next_grid || next_grid == -1) && m_status == Status::EMPTY)
    {
        for (uint8_t i = 0; i < 9; i++)
        {
            if (m_subgrids[i].is_mouse_on_square(window) && 
                m_subgrids[i].get_status() == Status::EMPTY)
            {
                m_subgrids[i].get_rectangle().setFillColor(GREY);
            }
        }
    }

    for (uint8_t i = 0; i < 9; i++)
    {
        if (!m_subgrids[i].is_mouse_on_square(window) && 
            m_subgrids[i].get_rectangle().getFillColor() == GREY)
        {
            m_subgrids[i].get_rectangle().setFillColor(WHITE);
        }
    }
}