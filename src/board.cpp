#include "board.hpp"
#include "Utils/colors.hpp"

Board::Board() : m_tic_tac_toe()
{
    float x = 500.f, y = 100.f;
    
    for (auto &l : m_board_lines)
        l.setFillColor(BLACK);    
    
    // vertical lines
    m_board_lines[0].setSize(sf::Vector2f(10.f, 790.f));
    m_board_lines[0].setPosition({505.f + Square::big_square_size + 10.f, y - 60});

    m_board_lines[1].setSize(sf::Vector2f(10.f, 790.f));
    m_board_lines[1].setPosition({733.f + Square::big_square_size + 10.f, y - 60});
    
    // horizontal lines
    m_board_lines[2].setSize(sf::Vector2f(790.f, 10.f));
    m_board_lines[2].setPosition({x - 55, 105.f + Square::big_square_size + 10.f});

    m_board_lines[3].setSize(sf::Vector2f(790.f, 10.f));
    m_board_lines[3].setPosition({x - 55, 332.f + Square::big_square_size + 10.f});
}

Status Board::get_match_status() const
{
    return m_tic_tac_toe.get_match_status();
}

std::pair<std::string, std::string> Board::get_players_name() const
{
    return m_tic_tac_toe.get_players_name();
}

bool Board::is_drawing_line() const
{
    return m_tic_tac_toe.get_result_line().is_drawing_line();
}

bool Board::is_line_max_size()
{
    return m_tic_tac_toe.get_result_line().is_line_max_size();
}

TicTacToe& Board::get_tic_tac_toe()
{
    return m_tic_tac_toe;
}

void Board::hover_effect(sf::RenderWindow &window)
{
    m_tic_tac_toe.hover_effect(window);
}

Status Board::play(sf::RenderWindow &window)
{
    return m_tic_tac_toe.play(window);
}

void Board::draw(sf::RenderWindow &window)
{
    m_tic_tac_toe.draw(window);

    for (const auto &line : m_board_lines)
        window.draw(line);
    
    if (m_tic_tac_toe.get_result_line().is_drawing_line())
        m_tic_tac_toe.get_result_line().draw(window);
}

/*
Resets the board 
If reset_names is false, the player names will be the same as last match
*/
void Board::reset(bool reset_names)
{
    m_tic_tac_toe.reset(reset_names);
}