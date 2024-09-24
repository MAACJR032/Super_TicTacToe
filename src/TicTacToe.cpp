#include "TicTacToe.hpp"

/* Initializes an status::empty 9x9 board. */
TicTacToe::TicTacToe()
{
    // Load textures
    std::string exe_dir = get_executable_path();

    std::string pngPath = exe_dir + "Assets/X_sprite.png";
    if (!X_texture.loadFromFile(pngPath))
    {
        std::cerr << "Error loading X_sprite.png\n";
        return;
    }

    pngPath = exe_dir + "Assets/O_sprite.png";
    if (!O_texture.loadFromFile(pngPath))
    {
        std::cerr << "Error loading O_sprite.png\n";
        return;
    }
    
    // init board
    sf::RectangleShape square;
    set_square(square);

    m_board.reserve(9);

    for (int i = 0; i < 9; i++)
    {
        m_board[i].resize(9, Square {.grid = 0, .subgrid = 0, .player = Status::EMPTY, .rect = square});    

        for (int j = 0; j < 9; j++)
        {
            int8_t grid = (i / 3) * 3 + (j / 3) + 1;
            int8_t subgrid = (i % 3) * 3 + (j % 3) + 1;

            m_board[i][j].grid = grid;
            m_board[i][j].subgrid = subgrid;
        }
    }

    m_grids.resize(9, {Status::EMPTY, 0});
}


// Private Functions:

/* Checks all the cases where the player may have scored in a grid. */
void TicTacToe::update_grid_score(int8_t grid, int8_t low_limit_i, int8_t low_limit_j)
{
    // Lines
    for (int i = low_limit_i; i < low_limit_i + 3; i++)
    {
        if (m_board[i][low_limit_j].player == m_current_player && 
            m_board[i][low_limit_j + 1].player == m_current_player && 
            m_board[i][low_limit_j + 2].player == m_current_player)
        {
            m_grids[grid - 1].first = m_current_player;
            return;
        }
    }

    // Ccolumns
    for (int j = low_limit_j; j < low_limit_j + 3; j++)
    {
        if (m_board[low_limit_i][j].player == m_current_player && 
            m_board[low_limit_i + 1][j].player == m_current_player && 
            m_board[low_limit_i + 2][j].player == m_current_player)
        {
            m_grids[grid - 1].first = m_current_player;
            return;
        }
    }
    
    // Diagonals
    if (m_board[low_limit_i][low_limit_j].player == m_current_player && 
        m_board[low_limit_i + 1][low_limit_j + 1].player == m_current_player && 
        m_board[low_limit_i + 2][low_limit_j + 2].player == m_current_player)
    {
        m_grids[grid - 1].first = m_current_player;
    }
    else if (m_board[low_limit_i][low_limit_j + 2].player == m_current_player && 
        m_board[low_limit_i + 1][low_limit_j + 1].player == m_current_player && 
        m_board[low_limit_i + 2][low_limit_j].player == m_current_player)
    {
        m_grids[grid - 1].first = m_current_player;
    }
}

/* Checks if player scored in the grid he just played */
void TicTacToe::grid_score(int8_t grid)
{
    switch (grid)
    {
        case 1:
            update_grid_score(grid, 0, 0);
            break;
        case 2:
            update_grid_score(grid, 0, 3);
            break;
        case 3:
            update_grid_score(grid, 0, 6);
            break;
        case 4:
            update_grid_score(grid, 3, 0);
            break;
        case 5:
            update_grid_score(grid, 3, 3);
            break;
        case 6:
            update_grid_score(grid, 3, 6);
            break;
        case 7:
            update_grid_score(grid, 6, 0);
            break;
        case 8:
            update_grid_score(grid, 6, 3);
            break;
        case 9:
            update_grid_score(grid, 6, 6);
            break;
        default:
            break;
    }
}

/* Checks if the given grid is tied */
Status TicTacToe::update_grid_tie(int8_t grid)
{
    // Grid is tied if all the 9 sub squares where marked but no player could score
    if (m_grids[grid - 1].second == 9 && m_grids[grid - 1].first == Status::EMPTY)
    {
        m_grids[grid - 1].first = Status::TIE;
        return Status::TIE;
    }

    return m_grids[grid - 1].first;
}

/* Will check if the clicked square can be played and will mark it. */
void TicTacToe::update_square(Square &s, sf::RenderWindow &window)
{
    if (m_grids[s.grid - 1].first == Status::EMPTY && 
        square_clicked(s.rect, window) == true && 
       (m_next_grid == -1 || m_next_grid == s.grid) && 
       s.player == Status::EMPTY)
    {
        s.rect.setTexture((m_current_player == Status::X) ? &X_texture : &O_texture);
        s.rect.setFillColor(WHITE);
        
        s.player = m_current_player;
        m_grids[s.grid - 1].second++;
        grid_score(s.grid);
        update_grid_tie(s.grid);
        check_win();
        
        if (m_current_player == Status::X)
            m_current_player_text.set_text(m_players_name.second, 40);
        else
            m_current_player_text.set_text(m_players_name.first, 40);

        m_current_player = (m_current_player == Status::X) ? Status::O : Status::X;
        
        if (m_grids[s.subgrid - 1].first == Status::EMPTY)
            m_next_grid = s.subgrid;
        else
            m_next_grid = -1;
    }
}

/* Updates victory if the player won or if it's a tie, else the game hasn't finished. */
void TicTacToe::check_win()
{
    // Checking the lines
    for (int i = 0; i < 7; i += 3)
    {
        if (m_grids[i].first == m_current_player && 
            m_grids[i+1].first == m_current_player && 
            m_grids[i+2].first == m_current_player)
        {
            m_victory = m_current_player;
        }
    }

    // Checking the columns
    for (int i = 0; i < 3; i++)
    {
        if (m_grids[i].first == m_current_player && 
            m_grids[i+3].first == m_current_player && 
            m_grids[i+6].first == m_current_player)
        {
            m_victory = m_current_player;
        }
    }
    
    // Diagonals
    if (m_grids[0].first == m_current_player && 
        m_grids[4].first == m_current_player && 
        m_grids[8].first == m_current_player)
    {
        m_victory = m_current_player;
    }
    else if (m_grids[2].first == m_current_player && 
        m_grids[4].first == m_current_player && 
        m_grids[6].first == m_current_player)
    {
        m_victory = m_current_player;
    }

    // If neither of the players won and all the grids where marked, then it is a tie
    uint8_t complete_grids = 0;
    for (int i = 0; i < 9; i++)
        if (m_grids[i].first != Status::EMPTY)
            complete_grids++;
        
    if (complete_grids == 9)
        m_victory = Status::TIE;
}

/* will iterate the board and call func for each square. */
void TicTacToe::iterate_board(void (TicTacToe::*func) (Square&, sf::RenderWindow &window), sf::RenderWindow &window)
{
    // Update squares that were played 
    for (auto &g : m_board)
        for (auto &s : g)
            (this->*func)(s, window);
}

/* Sets the name of both players. */
void TicTacToe::set_players_name(std::string player1, std::string player2)
{
    m_players_name.first = player1;
    m_players_name.second = player2;

    m_current_player_text.set_text(player1, 40);
}

/* Returns a reference to players_name pair. */
std::pair<std::string, std::string>& TicTacToe::get_players_name()
{
    return m_players_name;
}

/* Returns the next grid that must be played.
 * If it returns -1, then any status::EMPTY grid can be played.
 */
int8_t TicTacToe::get_next_grid() const
{
    return m_next_grid;
}

/* Returns the grid status at the specified index. */
Status TicTacToe::get_grid_status(uint8_t index) const
{
    if (index >= 9)
        throw std::out_of_range("Grid index is out of range\n");
    
    return m_grids[index].first;
}

/* Returns a refference to the board. */
std::vector<std::vector<Square>>& TicTacToe::get_board()
{
    return m_board;
}

/* Returns a refference to a square of the board. */
Square& TicTacToe::get_board_at(uint8_t i, uint8_t j)
{
    if (i >= 9 || j >= 9)
        throw std::out_of_range("Board index is out of range\n");
    
    return m_board[i][j];
}

/* Returns the current result of the game. */
Status TicTacToe::get_victory() const
{
    return m_victory;
}

/* Returns whose player is the current turn. */
Status TicTacToe::get_current_player()
{
    return m_current_player;
}

/* will iterate the board and call func for each square. */
void TicTacToe::iterate_board(void (*func) (Square &s, TicTacToe &t, sf::RenderWindow &window), sf::RenderWindow &window)
{
    // Changes color of valid squares that can be played 
    for (auto &g : m_board)
        for (auto &s : g)
            func(s, *this, window);
}

/* Will iterate through the board and call update_square to handle the player's move. */
void TicTacToe::play(sf::RenderWindow &window)
{
    iterate_board(update_square, window);    
}

/* Draws the text of whose player is the turn. */
void TicTacToe::draw_current_player_text(sf::RenderWindow &window)
{
    m_current_player_text.draw(window);
}

void TicTacToe::reset()
{
    sf::RectangleShape square;
    set_square(square);

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            m_board[i][j].player = Status::EMPTY;
            m_board[i][j].rect.setFillColor(WHITE);
            m_board[i][j].rect.setTexture(nullptr);
        }
    }

    m_grids.assign(m_grids.size(), {Status::EMPTY, 0});
    m_current_player_text.set_text(m_players_name.first, 40);
    m_victory = Status::EMPTY;
    m_current_player = Status::X;
    m_next_grid = -1;
}