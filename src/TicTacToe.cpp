#include "TicTacToe.hpp"

#include <cmath>
#include "Utils/colors.hpp"
#include "texture.hpp"
#include "Utils/Log/logger.hpp"

/* Initializes an EMPTY 9x9 board. */
TicTacToe::TicTacToe() : m_line(), m_current_player_text()
{
    for (int i = 0; i < 9; i++)
    {
        m_grids.emplace_back(i);

        int row = i / 3;
        int col = i % 3;
        
        m_grids[i].set_position({505.f + (Square::big_square_size + 20.f) * col, 105.f + (Square::big_square_size + 19.f) * row});
    }

    LOG_DEBUG("Tic Tac Toe board initialized");
}

void TicTacToe::switch_player()
{
    m_current_player  = (m_current_player == Status::X) ? Status::O : Status::X;
    std::string &name = (m_current_player == Status::X) ? m_players_name.first : m_players_name.second;
    m_current_player_text.set_text(name, 40);
}

struct Pattern
{
    uint8_t a, b, c;
    LineStatus status;
};

static constexpr Pattern patterns[] = {
    {0,1,2, LineStatus::ROW1},      {3,4,5, LineStatus::ROW2},     {6,7,8, LineStatus::ROW3},
    {0,3,6, LineStatus::COLUMN1},   {1,4,7, LineStatus::COLUMN2},  {2,5,8, LineStatus::COLUMN3},
    {0,4,8, LineStatus::DIAGONAL1}, {2,4,6, LineStatus::DIAGONAL2}
};

/* Updates victory if the player won or if it's a tie, else the game hasn't finished. */
Status TicTacToe::update_match_status()
{
    for (const auto& p : patterns)
    {
        if (check_line(p.a, p.b, p.c, p.status))
        {
            m_result = m_current_player;
            return m_result;
        }
    }

    // If neither of the players won and all the grids where filled, then it is a tie
    uint8_t complete_grids = 0;

    for (int i = 0; i < 9; i++)
        if (m_grids[i].get_status() != Status::EMPTY)
            complete_grids++;
        
    if (complete_grids == 9)
    {
        m_result = Status::TIE;

        static sf::Clock timer;
        timer.restart();
        while (timer.getElapsedTime().asSeconds() < 2.f);
    }
    return m_result;
}

/* Will check if the clicked square can be played and will mark it. */
void TicTacToe::update_square(Subgrid &s, sf::RenderWindow &window)
{
    if (s.get_status() == Status::EMPTY && s.was_clicked(window) &&
        m_grids[s.get_grid()].get_status() == Status::EMPTY && 
        (m_next_grid == -1 || m_next_grid == s.get_grid()))
    {
        // updates the subgrid
        s.fill(m_current_player);

        // updates the grid
        m_grids[s.get_grid()].update_grid_score(m_current_player);
        
        if (m_grids[s.get_subgrid()].get_status() == Status::EMPTY)
            m_next_grid = s.get_subgrid();
        else
            m_next_grid = -1;
  
        if (update_match_status() == Status::EMPTY)
            switch_player();
    }
}

// /* will iterate the board and call update_square for each square. */
void TicTacToe::update_all_squares(sf::RenderWindow &window)
{
    for (auto &g : m_grids)
        for (uint8_t i = 0; i < 9; i++)
            update_square(g.get_subgrid(i), window);
}

/* Will iterate through the board and call update_square to handle the player's move. */
Status TicTacToe::play(sf::RenderWindow &window)
{
    update_all_squares(window);
    return update_match_status();
}

void TicTacToe::set_line_dimensions()
{
    if (m_result == Status::X)
        m_line.set_color(RED);
    else if (m_result == Status::O)
        m_line.set_color(BLUE);
    
    switch (m_line.get_status())
    {
        case LineStatus::ROW1:
            m_line.set_start_end_points(
                m_grids[0].get_subgrid(3).get_rectangle().getPosition() + sf::Vector2f(-Line::correction_factor1, Square::half_square_size), 
                m_grids[2].get_subgrid(5).get_rectangle().getPosition() + sf::Vector2f(0.f, Square::half_square_size)
            );

            m_line.set_total_length(720.f);
            break;
    
        case LineStatus::ROW2:
            m_line.set_start_end_points(
                m_grids[3].get_subgrid(3).get_rectangle().getPosition() + sf::Vector2f(-Line::correction_factor1, Square::half_square_size), 
                m_grids[5].get_subgrid(5).get_rectangle().getPosition() + sf::Vector2f(0.f, Square::half_square_size)
            );

            m_line.set_total_length(720.f);
            break;
    
        case LineStatus::ROW3:
            m_line.set_start_end_points(
                m_grids[6].get_subgrid(3).get_rectangle().getPosition() + sf::Vector2f(-Line::correction_factor1, Square::half_square_size), 
                m_grids[6].get_subgrid(5).get_rectangle().getPosition() + sf::Vector2f(0.f, Square::half_square_size)
            );

            m_line.set_total_length(720.f);
            break;
    
        case LineStatus::COLUMN1:
            m_line.set_start_end_points(
                m_grids[0].get_subgrid(1).get_rectangle().getPosition() + sf::Vector2f(Square::half_square_size, -Line::correction_factor1), 
                m_grids[6].get_subgrid(7).get_rectangle().getPosition() + sf::Vector2f(Square::half_square_size, 0.f)
            );

            m_line.set_total_length(720.f);
            break;
    
        case LineStatus::COLUMN2:
            m_line.set_start_end_points(
                m_grids[1].get_subgrid(1).get_rectangle().getPosition() + sf::Vector2f(Square::half_square_size, -Line::correction_factor1), 
                m_grids[7].get_subgrid(7).get_rectangle().getPosition() + sf::Vector2f(Square::half_square_size, 0.f)
            );

            m_line.set_total_length(720.f);
            break;
    
        case LineStatus::COLUMN3:
            m_line.set_start_end_points(
                m_grids[2].get_subgrid(1).get_rectangle().getPosition() + sf::Vector2f(Square::half_square_size, -Line::correction_factor1), 
                m_grids[8].get_subgrid(7).get_rectangle().getPosition() + sf::Vector2f(Square::half_square_size, 0.f)
            );

            m_line.set_total_length(720.f);
            break;
    
        case LineStatus::DIAGONAL1:
            m_line.set_start_end_points(
                m_grids[0].get_subgrid(0).get_rectangle().getPosition() + sf::Vector2f(-Line::correction_factor2, -Line::correction_factor2), 
                m_grids[8].get_subgrid(8).get_rectangle().getPosition()
            );

            m_line.set_total_length(1100.f);
            break;
    
        case LineStatus::DIAGONAL2:
            m_line.set_start_end_points(
                m_grids[2].get_subgrid(2).get_rectangle().getPosition() + sf::Vector2f(-Line::correction_factor2, Line::correction_factor2 + Square::square_size), 
                m_grids[6].get_subgrid(6).get_rectangle().getPosition() + sf::Vector2f(Square::square_size, 0.f)
            );

            m_line.set_total_length(1100.f);
            break;

        default:
            break;
    }

    float angle = std::atan2(m_line.get_end().y - m_line.get_start().y, m_line.get_end().x - m_line.get_start().x) * 180 / Line::PI;

    m_line.set_position(m_line.get_start(), angle);
    m_line.set_is_drawing_line(true);
}

bool TicTacToe::check_line(uint8_t a, uint8_t b, uint8_t c, LineStatus line_status)
{
    if (m_grids[a].get_status() == m_current_player &&
        m_grids[b].get_status() == m_current_player &&
        m_grids[c].get_status() == m_current_player) 
    {
        m_result = m_current_player;
        m_line.set_status(line_status);
        set_line_dimensions();
        return true;
    }
    return false;
}

/* Sets the name of both players. */
void TicTacToe::set_players_name(std::pair<std::string, std::string> players_name)
{
    m_players_name.first  = players_name.first;
    m_players_name.second = players_name.second;
    m_current_player_text.set_text(players_name.first, 40, {10.f, 10.f});
}

/* Returns a reference to m_players_name pair. */
std::pair<std::string, std::string>& TicTacToe::get_players_name()
{
    return m_players_name;
}

std::pair<std::string, std::string> TicTacToe::get_players_name() const
{
    return m_players_name;
}

/* Returns the current result of the game. */
Status TicTacToe::get_match_status() const
{
    return m_result;
}

Line& TicTacToe::get_result_line()
{
    return m_line;
}

Line TicTacToe::get_result_line() const
{
    return m_line;
}

void TicTacToe::hover_effect(sf::RenderWindow &window)
{
    for (auto &g : m_grids)
        g.hover_effect(window, m_next_grid);
}

/* Draws the text of whose player is the turn, the squares and the textures. */
void TicTacToe::draw(sf::RenderWindow &window) const
{
    m_current_player_text.draw(window);

    for (const auto &s : m_grids)
        s.draw(window);
}

void TicTacToe::reset(bool reset_names)
{
    for (auto &g : m_grids)
        g.reset();
    
    m_next_grid      = -1;
    m_result         = Status::EMPTY;
    m_current_player = Status::X;
    
    if (reset_names)
        m_players_name = {"", ""};

    m_current_player_text.set_text(m_players_name.first, 40);
    m_line.reset();

    LOG_DEBUG("board reset");
}