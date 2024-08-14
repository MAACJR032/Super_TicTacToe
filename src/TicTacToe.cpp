#include "../include/TicTacToe.hpp"

/* Initializes an empty 9x9 matrix (board). */
TicTacToe::TicTacToe()
{
    tic_tac_toe.resize(9);
    for (size_t i = 0; i < 9; i++)
        tic_tac_toe[i].resize(9, EMPTY);
    
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
        if (tic_tac_toe[i][low_limit_j] == player && tic_tac_toe[i][low_limit_j + 1] == player && tic_tac_toe[i][low_limit_j + 2] == player)
        {
            grids[grid - 1].first = player;
            cout << "grid " << grid << " scored\n";
            sleep(1);
            return;
        }
    }

    // Checking the columns
    for (size_t j = low_limit_j; j < low_limit_j + 3; j++)
    {
        if (tic_tac_toe[low_limit_i][j] == player && tic_tac_toe[low_limit_i + 1][j] == player && tic_tac_toe[low_limit_i + 2][j] == player)
        {
            grids[grid - 1].first = player;
            cout << "grid " << grid << " scored\n";
            sleep(1);
            return;
        }
    }
    
    // Checking the Diagonals
    if (tic_tac_toe[low_limit_i][low_limit_j] == player && tic_tac_toe[low_limit_i + 1][low_limit_j + 1] == player && tic_tac_toe[low_limit_i + 2][low_limit_j + 2] == player)
    {
        grids[grid - 1].first = player;
        cout << "grid " << grid << " scored\n";
        sleep(1);
    }
    else if (tic_tac_toe[low_limit_i][low_limit_j + 2] == player && tic_tac_toe[low_limit_i + 1][low_limit_j + 1] == player && tic_tac_toe[low_limit_i + 2][low_limit_j] == player)
    {
        grids[grid - 1].first = player;
        cout << "grid " << grid << " scored\n";
        sleep(1);
    }
}

/* Checks if the subgrid is valid and if so, it plays on the board.
   Otherwise it will show the available sub grids to play and ask the player to select again. */
void TicTacToe::play_subgrid(status player, int grid, int subgrid, int low_limit_i, int low_limit_j)
{
    bool valid = false;
    while (!valid)
    {
        // Play on the subgrid only if it is empty
        switch (subgrid)
        {
            case 1:
                if (tic_tac_toe[low_limit_i][low_limit_j] == EMPTY)
                {
                    tic_tac_toe[low_limit_i][low_limit_j] = player;
                    grids[grid - 1].second++;
                    valid = true;
                }
                break;
            case 2:
                if (tic_tac_toe[low_limit_i][low_limit_j + 1] == EMPTY)
                {
                    tic_tac_toe[low_limit_i][low_limit_j + 1] = player;
                    grids[grid - 1].second++;
                    valid = true;
                }
                break;
            case 3:
                if (tic_tac_toe[low_limit_i][low_limit_j + 2] == EMPTY)
                {
                    tic_tac_toe[low_limit_i][low_limit_j + 2] = player;
                    grids[grid - 1].second++;
                    valid = true;
                }
                break;
            case 4:
                if (tic_tac_toe[low_limit_i + 1][low_limit_j] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 1][low_limit_j] = player;
                    grids[grid - 1].second++;
                    valid = true;
                }
                break;
            case 5:
                if (tic_tac_toe[low_limit_i + 1][low_limit_j + 1] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 1][low_limit_j + 1] = player;
                    grids[grid - 1].second++;
                    valid = true;
                }
                break;
            case 6:
                if (tic_tac_toe[low_limit_i + 1][low_limit_j + 2] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 1][low_limit_j + 2] = player;
                    grids[grid - 1].second++;
                    valid = true;
                }
                break;
            case 7:
                if (tic_tac_toe[low_limit_i + 2][low_limit_j] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 2][low_limit_j] = player;
                    grids[grid - 1].second++;
                    valid = true;
                }
                break;
            case 8:
                if (tic_tac_toe[low_limit_i + 2][low_limit_j + 1] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 2][low_limit_j + 1] = player;
                    grids[grid - 1].second++;
                    valid = true;
                }
                break;
            case 9:
                if (tic_tac_toe[low_limit_i + 2][low_limit_j + 2] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 2][low_limit_j + 2] = player;
                    grids[grid - 1].second++;
                    valid = true;
                }
                break;
            default:
                break;
        }

        // Handling invalid subgrid
        if (!valid)
        {    
            cout << "Invalid sub grid\n";
            cout << "You can play in these sub grids: ";

            for (size_t i = low_limit_i, i_grid = 0; i < low_limit_i + 3; i++, i_grid++)
            {
                for (size_t j = low_limit_j, j_grid = 0; j < low_limit_j + 3; j++, j_grid++)
                {
                    if (tic_tac_toe[i][j] == EMPTY)
                        cout << i * 3 + j + 1 << " ";
                }   
            }
            cout << '\n';
            cout << "sub grid: ";
            cin >> subgrid;
        }
    }

    // Checks if the played scored
    grid_score(player, grid);

    // If the next grid was already scored or is complete (tie) then the player can play at any available grid (next_grid = -1)
    if (grids[subgrid - 1].first == EMPTY)
        next_grid = subgrid;
    else
        next_grid = -1;
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

    return grids[grid - 1].first;
}

/* Prints the tic tac toe board. N = empty, T - tie, X = player 1 and O = player 2. */
void TicTacToe::print_tic_tac_toe() const
{
    for (size_t i = 0; i < 9; i++)
    {
        for (size_t j = 0; j < 9; j++)
        {
            printf(" %c", tic_tac_toe[i][j]);

            if (j == 2 || j == 5)
                cout << "  | ";
        }

        if (i == 2 || i == 5)
            cout << "\n---------------------------";
        cout << "\n";
    }

    cout << "Score:\n";
    for (size_t i = 0; i < 9; i += 3)
        printf("%c %c %c\n", grids[i].first, grids[i+1].first, grids[i+2].first);    
}

/* Checks if the choosen grid is valid and calls play_subgrid to play on the board. */
void TicTacToe::play(status player, int next_grid)
{
    int subgrid = 0;

    // if next_grid == -1 then the player must choose any available grid to play
    while (next_grid < 0 || next_grid > 9 || grids[next_grid - 1].first != EMPTY)
    {
        cout << "You can choose any of theese grids to play: ";
        for (size_t i = 0; i < 9; i++)
            if (grids[i].first == EMPTY)
                cout << i + 1 << " ";
        cout << '\n';
        cin >> next_grid;

        if (next_grid < 0 || next_grid > 9 || grids[next_grid - 1].first != EMPTY)
            cout << "Invalid grid\n";
    }

    cout << "You must play on grid " << next_grid << '\n';
    
    // play_subgrid checks will handle if subgrid is invalid.
    cout << "Sub grid: ";
    cin >> subgrid;

    switch (next_grid)
    {
        case 1:
            play_subgrid(player, next_grid, subgrid, 0, 0);
            break;
        case 2:
            play_subgrid(player, next_grid, subgrid, 0, 3);
            break;
        case 3:
            play_subgrid(player, next_grid, subgrid, 0, 6);
            break;
        case 4:
            play_subgrid(player, next_grid, subgrid, 3, 0);
            break;
        case 5:
            play_subgrid(player, next_grid, subgrid, 3, 3);
            break;
        case 6:
            play_subgrid(player, next_grid, subgrid, 3, 6);
            break;
        case 7:
            play_subgrid(player, next_grid, subgrid, 6, 0);
            break;
        case 8:
            play_subgrid(player, next_grid, subgrid, 6, 3);
            break;
        case 9:
            play_subgrid(player, next_grid, subgrid, 6, 6);
            break;
        default:
            break;
    }

    // Check if the played grid is a tie
    check_tie(next_grid);
}

/* Checks if the player won or if it's a tie, else the game hasn't finished and it will return EMPTY. */
status TicTacToe::check_win(status player, string player_name)
{
    // Checking the lines
    for (size_t i = 0; i < 7; i += 3)
    {
        if (grids[i].first == player && grids[i+1].first == player && grids[i+2].first == player)
            return player;
    }

    // Checking the columns
    for (size_t i = 0; i < 3; i++)
    {
        if (grids[i].first == player && grids[i+3].first == player && grids[i+6].first == player)
            return player;
    }
    
    // Diagonals
    if (grids[0].first == player && grids[4].first == player && grids[8].first == player)
        return player;
    else if (grids[2].first == player && grids[4].first == player && grids[6].first == player)
        return player;

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