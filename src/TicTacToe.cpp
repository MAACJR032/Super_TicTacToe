#include "../include/TicTacToe.hpp"

/* Initializes an empty 9x9 board. */
TicTacToe::TicTacToe() : text("Player 1", "Player 2")
{
    sf::RectangleShape square;
    set_square(square);
    
    board.resize(9);

    for (int i = 0; i < 9; i++)
    {
        board[i].resize(9, Square {.grid = 0, .subgrid = 0, .player = EMPTY, .rect = square});    

        for (int j = 0; j < 9; j++)
        {
            int8_t grid = (i / 3) * 3 + (j / 3) + 1;
            int8_t subgrid = (i % 3) * 3 + (j % 3) + 1;

            board[i][j].grid = grid;
            board[i][j].subgrid = subgrid;
        }
    }

    grids.resize(9, {EMPTY, 0});
}


// Private Functions:

/* Checks all the cases where the player may have scored in a grid. */
void TicTacToe::update_grid_score(int8_t grid, int8_t low_limit_i, int8_t low_limit_j)
{
    // Checking the lines
    for (int i = low_limit_i; i < low_limit_i + 3; i++)
    {
        if (board[i][low_limit_j].player == curr_player && 
            board[i][low_limit_j + 1].player == curr_player && 
            board[i][low_limit_j + 2].player == curr_player)
        {
            grids[grid - 1].first = curr_player;
            return;
        }
    }

    // Checking the columns
    for (int j = low_limit_j; j < low_limit_j + 3; j++)
    {
        if (board[low_limit_i][j].player == curr_player && 
            board[low_limit_i + 1][j].player == curr_player && 
            board[low_limit_i + 2][j].player == curr_player)
        {
            grids[grid - 1].first = curr_player;
            return;
        }
    }
    
    // Checking the Diagonals
    if (board[low_limit_i][low_limit_j].player == curr_player && 
        board[low_limit_i + 1][low_limit_j + 1].player == curr_player && 
        board[low_limit_i + 2][low_limit_j + 2].player == curr_player)
    {
        grids[grid - 1].first = curr_player;
    }
    else if (board[low_limit_i][low_limit_j + 2].player == curr_player && 
        board[low_limit_i + 1][low_limit_j + 1].player == curr_player && 
        board[low_limit_i + 2][low_limit_j].player == curr_player)
    {
        grids[grid - 1].first = curr_player;
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
status TicTacToe::update_grid_tie(int8_t grid)
{
    // Grid is tied if all the 9 sub squares where marked but no player could score
    if (grids[grid - 1].second == 9 && grids[grid - 1].first == EMPTY)
    {
        grids[grid - 1].first = TIE;
        return TIE;
    }

    // pode ser redundante por causa de check_win
    // considerar retornar empty
    return grids[grid - 1].first;
}

/* Will check if the clicked square can be played and will mark it. */
void TicTacToe::update_square(Square &s, unique_ptr<sf::RenderWindow> &window)
{
    if (grids[s.grid - 1].first == EMPTY && 
        button_click(s.rect, window) == true && 
       (next_grid == -1 || next_grid == s.grid) && 
       s.player == EMPTY)
    {
        s.rect.setFillColor((curr_player == X) ? RED : GREEN);
        
        s.player = curr_player;
        grids[s.grid - 1].second++;
        grid_score(s.grid);
        update_grid_tie(s.grid);
        check_win();
        
        if (curr_player == X)
            text.change_curr_player(O);
        else
            text.change_curr_player(X);

        curr_player = (curr_player == X) ? O : X;
        
        if (grids[s.subgrid - 1].first == EMPTY)
            next_grid = s.subgrid;
        else
            next_grid = -1;
    }
}

/* Updates victory if the player won or if it's a tie, else the game hasn't finished. */
void TicTacToe::check_win()
{
    // Checking the lines
    for (int i = 0; i < 7; i += 3)
    {
        if (grids[i].first == curr_player && 
            grids[i+1].first == curr_player && 
            grids[i+2].first == curr_player)
        {
            victory = curr_player;
        }
    }

    // Checking the columns
    for (int i = 0; i < 3; i++)
    {
        if (grids[i].first == curr_player && 
            grids[i+3].first == curr_player && 
            grids[i+6].first == curr_player)
        {
            victory = curr_player;
        }
    }
    
    // Diagonals
    if (grids[0].first == curr_player && 
        grids[4].first == curr_player && 
        grids[8].first == curr_player)
    {
        victory = curr_player;
    }
    else if (grids[2].first == curr_player && 
        grids[4].first == curr_player && 
        grids[6].first == curr_player)
    {
        victory = curr_player;
    }

    // If neither of the players won and all the grids where marked, then it is a tie
    uint8_t complete_grids = 0;
    for (int i = 0; i < 9; i++)
        if (grids[i].first != EMPTY)
            complete_grids++;
        
    if (complete_grids == 9)
        victory = TIE;
}

/* will iterate the board and call func for each square. */
void TicTacToe::iterate_board(void (TicTacToe::*func) (Square&, unique_ptr<sf::RenderWindow> &window), unique_ptr<sf::RenderWindow> &window)
{
    // Update squares that were played 
    for (auto &g : board)
        for (auto &s : g)
            (this->*func)(s, window);
}

// Getters:

/* Returns the next grid that must be played.
 * If it returns -1, then any EMPTY grid can be played.
 */
int8_t TicTacToe::get_next_grid()
{
    return next_grid;
}

/* Returns the grid status at the specified index. */
status TicTacToe::get_grid_status(uint8_t index)
{
    if (index >= 9)
        throw std::out_of_range("index of grid is out of range\n");
    
    return grids[index].first;
}

/* Returns a refference to the board. */
std::vector<std::vector<Square>>& TicTacToe::get_board()
{
    return board;
}

/* Returns a refference to a square of the board. */
Square& TicTacToe::get_board_at(int i, int j)
{
    return board[i][j];
}

status TicTacToe::get_victory()
{
    return victory;
}


// Public Functions:

/* will iterate the board and call func for each square. */
void TicTacToe::iterate_board(void (*func) (Square &s, TicTacToe &t, unique_ptr<sf::RenderWindow> &window), unique_ptr<sf::RenderWindow> &window)
{
    // Changes color of valid squares that can be played 
    for (auto &g : board)
        for (auto &s : g)
            func(s, *this, window);
}

/* Will iterate through the board and call update_square to handle the player's play. */
void TicTacToe::play(unique_ptr<sf::RenderWindow> &window)
{
    iterate_board(update_square, window);    
}