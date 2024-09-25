#include "TicTacToe.hpp"

/* Initializes an an EMPTY 9x9 board. */
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
    m_board.resize(9);

    for (int i = 0; i < 9; i++)
    {
        m_board[i].resize(9, subgrid(0, 0));    

        for (int j = 0; j < 9; j++)
        {
            int8_t grid = (i / 3) * 3 + (j / 3) + 1;
            int8_t subgrid = (i % 3) * 3 + (j % 3) + 1;

            m_board[i][j].set_subgrid(subgrid, grid);
        }
    }

    for (auto i = 0; i < 9; i++)
        m_grids.push_back({0, square(i)});
}

/* Checks all the cases where the player may have scored in a grid. */
void TicTacToe::update_grid_score(int8_t grid, int8_t low_limit_i, int8_t low_limit_j)
{
    // Lines
    for (int i = low_limit_i; i < low_limit_i + 3; i++)
    {
        if (m_board[i][low_limit_j].get_status() == m_current_player && 
            m_board[i][low_limit_j + 1].get_status() == m_current_player && 
            m_board[i][low_limit_j + 2].get_status() == m_current_player)
        {
            m_grids[grid - 1].grid.set_status(m_current_player);
            m_grids[grid - 1].grid.get_rectangle().setTexture((m_current_player == Status::X) ? &X_texture : &O_texture);
            return;
        }
    }

    // Ccolumns
    for (int j = low_limit_j; j < low_limit_j + 3; j++)
    {
        if (m_board[low_limit_i][j].get_status() == m_current_player && 
            m_board[low_limit_i + 1][j].get_status() == m_current_player && 
            m_board[low_limit_i + 2][j].get_status() == m_current_player)
        {
            m_grids[grid - 1].grid.set_status(m_current_player);
            m_grids[grid - 1].grid.get_rectangle().setTexture((m_current_player == Status::X) ? &X_texture : &O_texture);
            return;
        }
    }
    
    // Diagonals
    if (m_board[low_limit_i][low_limit_j].get_status() == m_current_player && 
        m_board[low_limit_i + 1][low_limit_j + 1].get_status() == m_current_player && 
        m_board[low_limit_i + 2][low_limit_j + 2].get_status() == m_current_player)
    {
        m_grids[grid - 1].grid.set_status(m_current_player);
        m_grids[grid - 1].grid.get_rectangle().setTexture((m_current_player == Status::X) ? &X_texture : &O_texture);
    }
    else if (m_board[low_limit_i][low_limit_j + 2].get_status() == m_current_player && 
        m_board[low_limit_i + 1][low_limit_j + 1].get_status() == m_current_player && 
        m_board[low_limit_i + 2][low_limit_j].get_status() == m_current_player)
    {
        m_grids[grid - 1].grid.set_status(m_current_player);
        m_grids[grid - 1].grid.get_rectangle().setTexture((m_current_player == Status::X) ? &X_texture : &O_texture);
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
    if (m_grids[grid - 1].subgrids_scored == 9 && m_grids[grid - 1].grid.get_status() == Status::EMPTY)
    {
        m_grids[grid - 1].grid.set_status(Status::TIE);
        return Status::TIE;
    }

    return m_grids[grid - 1].grid.get_status();
}

/* Will check if the clicked square can be played and will mark it. */
void TicTacToe::update_square(subgrid &s, sf::RenderWindow &window)
{
    if (m_grids[s.get_grid() - 1].grid.get_status() == Status::EMPTY && 
        s.square_clicked(window) == true && 
       (m_next_grid == -1 || m_next_grid == s.get_grid()) && 
       s.get_status() == Status::EMPTY)
    {
        s.get_rectangle().setTexture((m_current_player == Status::X) ? &X_texture : &O_texture);
        s.get_rectangle().setFillColor(WHITE);
        
        s.set_status(m_current_player);
        m_grids[s.get_grid() - 1].subgrids_scored++;
        grid_score(s.get_grid());
        update_grid_tie(s.get_grid());
        check_win();
        
        if (m_current_player == Status::X)
            m_current_player_text.set_text(m_players_name.second, 40);
        else
            m_current_player_text.set_text(m_players_name.first, 40);

        m_current_player = (m_current_player == Status::X) ? Status::O : Status::X;
        
        if (m_grids[s.get_subgrid() - 1].grid.get_status() == Status::EMPTY)
            m_next_grid = s.get_subgrid();
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
        if (m_grids[i].grid.get_status() == m_current_player && 
            m_grids[i+1].grid.get_status() == m_current_player && 
            m_grids[i+2].grid.get_status() == m_current_player)
        {
            m_victory = m_current_player;
        }
    }

    // Checking the columns
    for (int i = 0; i < 3; i++)
    {
        if (m_grids[i].grid.get_status() == m_current_player && 
            m_grids[i+3].grid.get_status() == m_current_player && 
            m_grids[i+6].grid.get_status() == m_current_player)
        {
            m_victory = m_current_player;
        }
    }
    
    // Diagonals
    if (m_grids[0].grid.get_status() == m_current_player && 
        m_grids[4].grid.get_status() == m_current_player && 
        m_grids[8].grid.get_status() == m_current_player)
    {
        m_victory = m_current_player;
    }
    else if (m_grids[2].grid.get_status() == m_current_player && 
        m_grids[4].grid.get_status() == m_current_player && 
        m_grids[6].grid.get_status() == m_current_player)
    {
        m_victory = m_current_player;
    }

    // If neither of the players won and all the grids where marked, then it is a tie
    uint8_t complete_grids = 0;
    for (int i = 0; i < 9; i++)
        if (m_grids[i].grid.get_status() != Status::EMPTY)
            complete_grids++;
        
    if (complete_grids == 9)
        m_victory = Status::TIE;
}

/* will iterate the board and call func for each square. */
void TicTacToe::iterate_board(void (TicTacToe::*func) (subgrid&, sf::RenderWindow &window), sf::RenderWindow &window)
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
    
    return m_grids[index].grid.get_status();
}

/* Returns a refference to the board. */
std::vector<std::vector<subgrid>>& TicTacToe::get_board()
{
    return m_board;
}

/* Returns a refference to a square of the board. */
subgrid& TicTacToe::get_board_at(uint8_t i, uint8_t j)
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
void TicTacToe::iterate_board(void (*func) (subgrid &s, TicTacToe &t, sf::RenderWindow &window), sf::RenderWindow &window)
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
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            m_board[i][j].set_status(Status::EMPTY);
            m_board[i][j].get_rectangle().setFillColor(WHITE);
            m_board[i][j].get_rectangle().setTexture(nullptr);
        }
    }

    for (auto &g : m_grids)
    {
        g.grid.set_status(Status::EMPTY);
        g.subgrids_scored = 0;
    }
    
    m_current_player_text.set_text(m_players_name.first, 40);
    m_victory = Status::EMPTY;
    m_current_player = Status::X;
    m_next_grid = -1;
}