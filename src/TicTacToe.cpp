#include "TicTacToe.hpp"

/* Initializes an EMPTY 9x9 board. */
TicTacToe::TicTacToe()
{
    // Load textures
    std::string assets_dir = get_assets_path();

    /*
        Sprites taken from here: https://www.pngwing.com/en/free-png-kbndf 
    */
    std::string pngPath = assets_dir + "Assets/X_sprite.png";
    if (!X_texture.loadFromFile(pngPath))
    {
        l.Error("could not load X_sprite.png");
        return;
    }

    pngPath = assets_dir + "Assets/Big_X_sprite.png";
    if (!X_texture.loadFromFile(pngPath))
    {
        l.Error("could not load Big_X_sprite.png");
        return;
    }

    pngPath = assets_dir + "Assets/O_sprite.png";
    if (!O_texture.loadFromFile(pngPath))
    {
        l.Error("could not load O_sprite.png");
        return;
    }

    pngPath = assets_dir + "Assets/Big_O_sprite.png";
    if (!O_texture.loadFromFile(pngPath))
    {
        l.Error("could not load Big_O_sprite.png");
        return;
    }
    
    // init board
    m_board.resize(9);

    for (int i = 0; i < 9; i++)
    {
        m_board.reserve(9);

        for (int j = 0; j < 9; j++)
        {
            int grid = (i / 3) * 3 + (j / 3) + 1;
            int subgrid = (i % 3) * 3 + (j % 3) + 1;

            m_board[i].emplace_back(subgrid, grid);
        }
    }

    for (int i = 0; i < 9; i++)
    {
        m_grids.emplace_back(0, i);
        
        int row = i / 3;
        int col = i % 3;
        m_grids[i].m_grid.set_position({505.f + 228.f * col, 105.f + 227.f * row});
    }

    #ifdef DEBUG
        l.Debug("Tic Tac Toe board initialized");
    #endif
}

/* Checks all the cases where the player may have scored in a grid. */
void TicTacToe::update_grid_score(int grid, int low_limit_i, int low_limit_j)
{
    // Rows
    for (int i = low_limit_i; i < low_limit_i + 3; i++)
    {
        if (m_board[i][low_limit_j] == m_current_player && 
            m_board[i][low_limit_j + 1] == m_current_player && 
            m_board[i][low_limit_j + 2] == m_current_player)
        {
            m_grids[grid - 1].m_grid = m_current_player;
            m_grids[grid - 1].m_grid.get_rectangle().setTexture((m_current_player == Status::X) ? &X_texture : &O_texture);

            #ifdef DEBUG
                std::string player_name = (m_current_player == Status::X) ? m_players_name.first : m_players_name.second;
                l.Debugf("Player %s scored in grid %d", player_name.c_str(), grid);
            #endif

            return;
        }
    }

    // Columns
    for (int j = low_limit_j; j < low_limit_j + 3; j++)
    {
        if (m_board[low_limit_i][j] == m_current_player && 
            m_board[low_limit_i + 1][j] == m_current_player && 
            m_board[low_limit_i + 2][j] == m_current_player)
        {
            m_grids[grid - 1].m_grid = m_current_player;
            m_grids[grid - 1].m_grid.get_rectangle().setTexture((m_current_player == Status::X) ? &X_texture : &O_texture);

            #ifdef DEBUG
                std::string player_name = (m_current_player == Status::X) ? m_players_name.first : m_players_name.second;
                l.Debugf("Player %s scored in grid %d", player_name.c_str(), grid);
            #endif

            return;
        }
    }
    
    // Diagonals
    if (m_board[low_limit_i][low_limit_j] == m_current_player && 
        m_board[low_limit_i + 1][low_limit_j + 1] == m_current_player && 
        m_board[low_limit_i + 2][low_limit_j + 2] == m_current_player)
    {
        m_grids[grid - 1].m_grid = m_current_player;
        m_grids[grid - 1].m_grid.get_rectangle().setTexture((m_current_player == Status::X) ? &X_texture : &O_texture);

        #ifdef DEBUG
            std::string player_name = (m_current_player == Status::X) ? m_players_name.first : m_players_name.second;
            l.Debugf("Player %s scored in grid %d", player_name.c_str(), grid);
        #endif
    }
    else if (m_board[low_limit_i][low_limit_j + 2] == m_current_player && 
        m_board[low_limit_i + 1][low_limit_j + 1] == m_current_player && 
        m_board[low_limit_i + 2][low_limit_j] == m_current_player)
    {
        m_grids[grid - 1].m_grid = m_current_player;
        m_grids[grid - 1].m_grid.get_rectangle().setTexture((m_current_player == Status::X) ? &X_texture : &O_texture);

        #ifdef DEBUG
            std::string player_name = (m_current_player == Status::X) ? m_players_name.first : m_players_name.second;
            l.Debugf("Player %s scored in grid %d", player_name.c_str(), grid);
        #endif
    }
}

/* Checks if current player scored in the grid just played */
void TicTacToe::grid_score(int grid)
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
Status TicTacToe::update_grid_tie(int grid)
{
    // The grid is tied if all the 9 sub squares where marked but no player could score
    if (m_grids[grid - 1].m_subgrids_scored == 9 && m_grids[grid - 1].m_grid == Status::EMPTY)
    {
        m_grids[grid - 1].m_grid = Status::TIE;
        return Status::TIE;
    }

    return m_grids[grid - 1].m_grid.get_status();
}

/* Will check if the clicked square can be played and will mark it. */
void TicTacToe::update_square(subgrid &s, sf::RenderWindow &window)
{
    if (m_grids[s.get_grid() - 1].m_grid == Status::EMPTY && 
        s.clicked(window) == true && 
       (m_next_grid == -1 || m_next_grid == s.get_grid()) && 
       s == Status::EMPTY)
    {
        s.get_rectangle().setTexture((m_current_player == Status::X) ? &X_texture : &O_texture);
        s.get_rectangle().setFillColor(WHITE);
        
        s = m_current_player;
        m_grids[s.get_grid() - 1].m_subgrids_scored++;
        grid_score(s.get_grid());
        update_grid_tie(s.get_grid());
        check_win();
        
        if (m_current_player == Status::X)
            m_current_player_text.set_text(m_players_name.second, 40);
        else
            m_current_player_text.set_text(m_players_name.first, 40);

        m_current_player = (m_current_player == Status::X) ? Status::O : Status::X;
        
        if (m_grids[s.get_subgrid() - 1].m_grid == Status::EMPTY)
            m_next_grid = s.get_subgrid();
        else
            m_next_grid = -1;
    }
}

/* will iterate the board and call update_square for each square. */
void TicTacToe::update_all_squares(sf::RenderWindow &window)
{
    // Changes color of valid squares that can be played 
    for (auto &g : m_board)
        for (auto &s : g)
            update_square(s, window);
}

void TicTacToe::set_line_parameters()
{
    if (m_victory == Status::X)
        m_line.set_color(RED);
    else if (m_victory == Status::O)
        m_line.set_color(BLUE);
    
    switch (m_line.get_status())
    {
        case LineStatus::ROW1:
            m_line.set_start_end_points(
                m_board[1][0].get_rectangle().getPosition() + sf::Vector2f(-correction_factor1, half_square_size), 
                m_board[1][8].get_rectangle().getPosition() + sf::Vector2f(0.f, half_square_size)
            );

            m_line.set_total_length(720.f);
            break;
    
        case LineStatus::ROW2:
            m_line.set_start_end_points(
                m_board[5][0].get_rectangle().getPosition() + sf::Vector2f(-correction_factor1, -half_square_size), 
                m_board[5][8].get_rectangle().getPosition() + sf::Vector2f(0.f, -half_square_size)
            );

            m_line.set_total_length(720.f);
            break;
    
        case LineStatus::ROW3:
            m_line.set_start_end_points(
                m_board[7][0].get_rectangle().getPosition() + sf::Vector2f(-correction_factor1, half_square_size), 
                m_board[7][8].get_rectangle().getPosition() + sf::Vector2f(0.f, half_square_size)
            );

            m_line.set_total_length(720.f);
            break;
    
        case LineStatus::COLUMN1:
            m_line.set_start_end_points(
                m_board[0][1].get_rectangle().getPosition() + sf::Vector2f(half_square_size, -correction_factor1), 
                m_board[8][1].get_rectangle().getPosition() + sf::Vector2f(half_square_size, 0.f)
            );

            m_line.set_total_length(720.f);
            break;
    
        case LineStatus::COLUMN2:
            m_line.set_start_end_points(
                m_board[0][5].get_rectangle().getPosition() + sf::Vector2f(-half_square_size, -correction_factor1), 
                m_board[8][5].get_rectangle().getPosition() + sf::Vector2f(-half_square_size, 0.f)
            );

            m_line.set_total_length(720.f);
            break;
    
        case LineStatus::COLUMN3:
            m_line.set_start_end_points(
                m_board[0][7].get_rectangle().getPosition() + sf::Vector2f(half_square_size, -correction_factor1), 
                m_board[8][7].get_rectangle().getPosition() + sf::Vector2f(half_square_size, 0.f)
            );

            m_line.set_total_length(720.f);
            break;
    
        case LineStatus::DIAGONAL1:
            m_line.set_start_end_points(
                m_board[0][0].get_rectangle().getPosition() + sf::Vector2f(-correction_factor2, -correction_factor2), 
                m_board[8][8].get_rectangle().getPosition()
            );

            m_line.set_total_length(1100.f);
            break;
    
        case LineStatus::DIAGONAL2:
            m_line.set_start_end_points(
                m_board[8][0].get_rectangle().getPosition() + sf::Vector2f(-correction_factor2, correction_factor2 + square_size), 
                m_board[0][8].get_rectangle().getPosition() + sf::Vector2f(square_size, 0.f)
            );

            m_line.set_total_length(1100.f);
            break;

        default:
            break;
    }

    float angle = std::atan2(m_line.get_end().y - m_line.get_start().y, m_line.get_end().x - m_line.get_start().x) * 180 / PI;

    m_line.set_position(m_line.get_start(), angle);
    m_line.set_is_drawing_line(true);
}

/* Updates victory if the player won or if it's a tie, else the game hasn't finished. */
void TicTacToe::check_win()
{
    // Rows
    for (int i = 0; i < 7; i += 3)
    {
        if (m_grids[i].m_grid == m_current_player && 
            m_grids[i+1].m_grid == m_current_player && 
            m_grids[i+2].m_grid == m_current_player)
        {
            m_victory = m_current_player;
            
            if (i == 0)
                m_line = LineStatus::ROW1;
            else if (i == 3)
                m_line = LineStatus::ROW2;
            else if (i == 6)
                m_line = LineStatus::ROW3;

            set_line_parameters();
            return;
        }
    }

    // Columns
    for (int i = 0; i < 3; i++)
    {
        if (m_grids[i].m_grid == m_current_player && 
            m_grids[i+3].m_grid == m_current_player && 
            m_grids[i+6].m_grid == m_current_player)
        {
            m_victory = m_current_player;

            if (i == 0)
                m_line = LineStatus::COLUMN1;
            else if (i == 1)
                m_line = LineStatus::COLUMN2;
            else if (i == 2)
                m_line = LineStatus::COLUMN3;
            
            set_line_parameters();
            return;
        }
    }
    
    // Diagonals
    if (m_grids[0].m_grid == m_current_player && 
        m_grids[4].m_grid == m_current_player && 
        m_grids[8].m_grid == m_current_player)
    {
        m_victory = m_current_player;
        m_line = LineStatus::DIAGONAL1;
        set_line_parameters();
        return;
    }
    else if (m_grids[2].m_grid == m_current_player && 
        m_grids[4].m_grid == m_current_player && 
        m_grids[6].m_grid == m_current_player)
    {
        m_victory = m_current_player;
        m_line = LineStatus::DIAGONAL2;
        set_line_parameters();
        return;
    }

    // If neither of the players won and all the grids where marked, then it is a tie
    int complete_grids = 0;
    for (int i = 0; i < 9; i++)
        if (m_grids[i].m_grid != Status::EMPTY)
            complete_grids++;
        
    if (complete_grids == 9)
        m_victory = Status::TIE;
}


/* Sets the name of both players. */
void TicTacToe::set_players_name(std::string player1, std::string player2)
{
    m_players_name.first = player1;
    m_players_name.second = player2;

    m_current_player_text.set_text(player1, 40);
}


/* Returns a reference to m_players_name pair. */
std::pair<std::string, std::string>& TicTacToe::get_players_name()
{
    return m_players_name;
}

/* Returns the next grid that must be played.
 * If it returns -1, then any status::EMPTY grid can be played.
 */
int TicTacToe::get_next_grid() const
{
    return m_next_grid;
}

/* Returns the grid status at the specified index. */
Status TicTacToe::get_grid_status(int index) const
{
    if (index >= 9)
        throw std::out_of_range("Grid index is out of range\n");
    
    return m_grids[index].m_grid.get_status();
}

/* Returns a refference to the board. */
std::vector<std::vector<subgrid>>& TicTacToe::get_board()
{
    return m_board;
}

/* Returns a refference to a square of the board. */
subgrid& TicTacToe::get_board_at(int i, int j)
{
    if (i >= 9 || i < 0|| j >= 9 || j < 0)
        throw std::out_of_range("Board index is out of range\n");
    
    return m_board[i][j];
}

/* Returns the current result of the game. */
Status TicTacToe::get_victory() const
{
    return m_victory;
}

/* Returns whose player is the current turn. */
Status TicTacToe::get_current_player() const
{
    return m_current_player;
}

bool TicTacToe::is_line_max_size() const
{
    return m_line.get_size().x == m_line.get_total_length();
}

bool TicTacToe::is_drawing_line() const
{
    return m_line.is_drawing_line();
}

/* will iterate the board and call func for each square. */
void TicTacToe::iterate_board(void (*func) (subgrid&, TicTacToe& , sf::RenderWindow&), sf::RenderWindow &window)
{
    for (auto &g : m_board)
        for (auto &s : g)
            (*func)(s, *this, window);
}

/* Will iterate through the board and call update_square to handle the player's move. */
void TicTacToe::play(sf::RenderWindow &window)
{
    update_all_squares(window);    
}

/* Draws the text of whose player is the turn, the squares and the textures. */
void TicTacToe::draw(sf::RenderWindow &window)
{
    m_current_player_text.draw(window);

    for (const auto &g : m_board)
        for (const auto &s : g)
            s.draw(window);

    for (auto &s : m_grids)
    {
        if (s.m_grid == Status::X) 
        {
            s.m_grid.get_rectangle().setFillColor(TRANSPARENT_RED);
            s.m_grid.draw(window);
        }
        else if (s.m_grid == Status::O)
        {
            s.m_grid.get_rectangle().setFillColor(TRANSPARENT_BLUE);
            s.m_grid.draw(window);
        }
    }
}

void TicTacToe::draw_endline(sf::RenderWindow &window)
{
    m_line.increment_length();
    if (m_line.get_current_length() > m_line.get_total_length())
    {
        m_line.set_current_length(m_line.get_total_length());
        m_line.set_is_drawing_line(false);
    }
    
    m_line.set_size(sf::Vector2f(m_line.get_current_length(), line_thickness));

    m_line.draw(window);
}

void TicTacToe::reset()
{
    for (auto &squares : m_board)
    {
        for (auto &s : squares)
        {
            s = Status::EMPTY;
            s.get_rectangle().setFillColor(WHITE);
            s.get_rectangle().setTexture(nullptr);
        }
    }

    for (auto &g : m_grids)
    {
        g.m_grid = Status::EMPTY;
        g.m_subgrids_scored = 0;
    }
    
    m_current_player_text.set_text(m_players_name.first, 40);
    m_victory = Status::EMPTY;
    m_current_player = Status::X;
    m_line.clear();
    m_next_grid = -1;

    #ifdef DEBUG
        l.Debug("board reset");
    #endif
}
