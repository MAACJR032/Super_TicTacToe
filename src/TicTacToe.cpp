#include "../include/tic.hpp"

/* Initializes an empty 9x9 matrix (board). */
TicTacToe::TicTacToe()
{
    sf::RectangleShape square;
    set_square(square);
    
    board.resize(9);

    for (int i = 0; i < 9; i++)
    {
        board[i].resize(9, Square {.grid = i, .subgrid = 0, .stat = EMPTY, .rect = square});

        for (int j = 0; j < 9; j++)
            board[i][j].subgrid = j;
    }
    
    grids.resize(9, {EMPTY, 0});

    next_grid = -1;
}

/* Return the index of the next grid that the player must play. */
int TicTacToe::get_next_grid() const
{
    return next_grid;
}

void TicTacToe::set_next_grid(int next)
{
    next_grid = next;
}

/* Checks if player scored in the grid he just played */
void TicTacToe::grid_score(status player, int grid)
{
    switch (grid)
    {
        case 1:
            check_grid_score(player, grid, 0, 0);
            break;
        case 2:
            check_grid_score(player, grid, 0, 3);
            break;
        case 3:
            check_grid_score(player, grid, 0, 6);
            break;
        case 4:
            check_grid_score(player, grid, 3, 0);
            break;
        case 5:
            check_grid_score(player, grid, 3, 3);
            break;
        case 6:
            check_grid_score(player, grid, 3, 6);
            break;
        case 7:
            check_grid_score(player, grid, 6, 0);
            break;
        case 8:
            check_grid_score(player, grid, 6, 3);
            break;
        case 9:
            check_grid_score(player, grid, 6, 6);
            break;
        default:
            break;
    }
}

/* Checks all the cases where the player may have scored in a grid. */
void TicTacToe::check_grid_score(status player, int grid, int low_limit_i, int low_limit_j)
{
    // Checking the lines
    for (size_t i = low_limit_i; i < low_limit_i + 3; i++)
    {
        if (board[i][low_limit_j].stat == player && 
            board[i][low_limit_j + 1].stat == player && 
            board[i][low_limit_j + 2].stat == player)
        {
            grids[grid - 1].first = player;
            return;
        }
    }

    // Checking the columns
    for (size_t j = low_limit_j; j < low_limit_j + 3; j++)
    {
        if (board[low_limit_i][j].stat == player && 
            board[low_limit_i + 1][j].stat == player && 
            board[low_limit_i + 2][j].stat == player)
        {
            grids[grid - 1].first = player;
            return;
        }
    }
    
    // Checking the Diagonals
    if (board[low_limit_i][low_limit_j].stat == player && 
        board[low_limit_i + 1][low_limit_j + 1].stat == player && 
        board[low_limit_i + 2][low_limit_j + 2].stat == player)
    {
        grids[grid - 1].first = player;
    }
    else if (board[low_limit_i][low_limit_j + 2].stat == player && 
        board[low_limit_i + 1][low_limit_j + 1].stat == player && 
        board[low_limit_i + 2][low_limit_j].stat == player)
    {
        grids[grid - 1].first = player;
    }
}

/* Checks if the given grid is a tie */
status TicTacToe::check_tie(int grid)
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

/* Checks if the player won or if it's a tie, else the game hasn't finished and it will return EMPTY. */
status TicTacToe::check_win(status player, string player_name)
{
    // Checking the lines
    for (size_t i = 0; i < 7; i += 3)
    {
        if (grids[i].first == player && 
            grids[i+1].first == player && 
            grids[i+2].first == player)
            return player;
    }

    // Checking the columns
    for (size_t i = 0; i < 3; i++)
    {
        if (grids[i].first == player && 
            grids[i+3].first == player && 
            grids[i+6].first == player)
        {
            return player;
        }
    }
    
    // Diagonals
    if (grids[0].first == player && 
        grids[4].first == player && 
        grids[8].first == player)
    {
        return player;
    }
    else if (grids[2].first == player && 
        grids[4].first == player && 
        grids[6].first == player)
    {
        return player;
    }

    // If neither of the players won and all the grids where marked, then it is a tie
    int complete_grids = 0;
    for (size_t i = 0; i < 9; i++)
        if (grids[i].first != EMPTY)
            complete_grids++;
        
    if (complete_grids == 9)
        return TIE;
    
    // Game is not over
    return EMPTY;
}

void TicTacToe::win(status player)
{
    switch (check_win(player, ""))
    {
        case X:
            if (player == X)
                victory = X;
            break;
        
        case O:
            if (player == O)
                victory = O;
            break;

        case TIE:
            victory = TIE;
            break;
        
        case EMPTY:
            break;
    }
}

/* Checks if the choosen grid is valid and calls play_subgrid to play on the board. */
void TicTacToe::play(status player)
{
    int subgrid = 0;

    for (auto &g : board)
    {
        for (auto &s : g)
        {
            // passou mouse em cima
            if (next_grid == -1)
            {
                // fica cinza
                // se apertar marca 
            }
            else if (next_grid == s.grid)
            {
                // fica cinza
                // se apertar muda a cor
                s.stat = player;
                next_grid = s.subgrid;

                // checar vitória, ponto, etc
                grid_score(player, s.grid);
                win(s.stat);
                if (victory == EMPTY)
                    victory = check_tie(s.grid);
            }
        }   
    }

    // Check if the played grid is a tie
    check_tie(next_grid);
}