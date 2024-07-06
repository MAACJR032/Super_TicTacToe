#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

using std::vector;
using std::cout;
using std::cin;
using std::string;
using std::pair;

enum status {EMPTY = 'N', X = 'X', O = 'O', TIE = 'T'};

class TicTacToe
{
    private:
        vector<pair<status, int>> grids; // 1 - Status, 2 - size of marked sub grids
        vector<vector<status>> tic_tac_toe;
        int next_grid;
        void win_grid(status player, int grid);
        void check_sub_score(status player, int square, int low_limit_i, int low_limit_j);
        void play_sub_grid(status player, int square, int sub_square, int low_limit_i, int low_limit_j);
        status tie(int square);

    public:
        TicTacToe();
        int get_next_grid() const;
        void print_tic_tac_toe() const;
        void play(status player, int next_grid);
        status win(status player, string player_name);
};

/* Initializes an empty 9x9 matrix (board). */
TicTacToe::TicTacToe()
{
    tic_tac_toe.resize(9);
    for (size_t i = 0; i < 9; i++)
        tic_tac_toe[i].resize(9, EMPTY);
    
    grids.resize(9, {EMPTY, 0});

    next_grid = -1;
}

// Return the index of the next grid that the player must play
int TicTacToe::get_next_grid() const
{
    return next_grid;
}

/* Checks if player win the grid he just played */
void TicTacToe::win_grid(status player, int grid)
{
    switch (grid)
    {
        case 1:
            check_sub_score(player, grid, 0, 0);
            break;
        case 2:
            check_sub_score(player, grid, 0, 3);
            break;
        case 3:
            check_sub_score(player, grid, 0, 6);
            break;
        case 4:
            check_sub_score(player, grid, 3, 0);
            break;
        case 5:
            check_sub_score(player, grid, 3, 3);
            break;
        case 6:
            check_sub_score(player, grid, 3, 6);
            break;
        case 7:
            check_sub_score(player, grid, 6, 0);
            break;
        case 8:
            check_sub_score(player, grid, 6, 3);
            break;
        case 9:
            check_sub_score(player, grid, 6, 6);
            break;
        default:
            break;
    }
}

/* Checks all the cases where the player may have scored in a grid */
void TicTacToe::check_sub_score(status player, int square, int low_limit_i, int low_limit_j)
{
    // Checking the lines
    for (size_t i = low_limit_i; i < low_limit_i + 3; i++)
    {
        if (tic_tac_toe[i][low_limit_j] == player && tic_tac_toe[i][low_limit_j + 1] == player && tic_tac_toe[i][low_limit_j + 2] == player)
        {
            grids[square - 1].first = player;
            cout << "grid " << square << " occupied\n";
            return;
        }
    }

    // Checking the columns
    for (size_t j = low_limit_j; j < low_limit_j + 3; j++)
    {
        if (tic_tac_toe[low_limit_i][j] == player && tic_tac_toe[low_limit_i + 1][j] == player && tic_tac_toe[low_limit_i + 2][j] == player)
        {
            grids[square - 1].first = player;
            cout << "grid " << square << " occupied\n";
            return;
        }
    }
    
    // Diagonals
    if (tic_tac_toe[low_limit_i][low_limit_j] == player && tic_tac_toe[low_limit_i + 1][low_limit_j + 1] == player && tic_tac_toe[low_limit_i + 2][low_limit_j + 2] == player)
    {
        grids[square - 1].first = player;
        cout << "grid " << square << " occupied\n";
    }

    else if (tic_tac_toe[low_limit_i][low_limit_j + 2] == player && tic_tac_toe[low_limit_i + 1][low_limit_j + 1] == player && tic_tac_toe[low_limit_i + 2][low_limit_j] == player)
    {
        grids[square - 1].first = player;
        cout << "grid " << square << " occupied\n";
    }
}

/* Checks if the subgrid is valid and if so, it marks in tic_tac_toe.
   Otherwise it will show the available sub grids to play and ask the player to select again. */
void TicTacToe::play_sub_grid(status player, int square, int sub_square, int low_limit_i, int low_limit_j)
{
    bool valid = false;
    while (!valid)
    {
        // Marks the subgrid if it is empty
        switch (sub_square)
        {
            case 1:
                if (tic_tac_toe[low_limit_i][low_limit_j] == EMPTY)
                {
                    tic_tac_toe[low_limit_i][low_limit_j] = player;
                    grids[square - 1].second++;
                    valid = true;
                }
                break;
            case 2:
                if (tic_tac_toe[low_limit_i][low_limit_j + 1] == EMPTY)
                {
                    tic_tac_toe[low_limit_i][low_limit_j + 1] = player;
                    grids[square - 1].second++;
                    valid = true;
                }
                break;
            case 3:
                if (tic_tac_toe[low_limit_i][low_limit_j + 2] == EMPTY)
                {
                    tic_tac_toe[low_limit_i][low_limit_j + 2] = player;
                    grids[square - 1].second++;
                    valid = true;
                }
                break;
            case 4:
                if (tic_tac_toe[low_limit_i + 1][low_limit_j] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 1][low_limit_j] = player;
                    grids[square - 1].second++;
                    valid = true;
                }
                break;
            case 5:
                if (tic_tac_toe[low_limit_i + 1][low_limit_j + 1] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 1][low_limit_j + 1] = player;
                    grids[square - 1].second++;
                    valid = true;
                }
                break;
            case 6:
                if (tic_tac_toe[low_limit_i + 1][low_limit_j + 2] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 1][low_limit_j + 2] = player;
                    grids[square - 1].second++;
                    valid = true;
                }
                break;
            case 7:
                if (tic_tac_toe[low_limit_i + 2][low_limit_j] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 2][low_limit_j] = player;
                    grids[square - 1].second++;
                    valid = true;
                }
                break;
            case 8:
                if (tic_tac_toe[low_limit_i + 2][low_limit_j + 1] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 2][low_limit_j + 1] = player;
                    grids[square - 1].second++;
                    valid = true;
                }
                break;
            case 9:
                if (tic_tac_toe[low_limit_i + 2][low_limit_j + 2] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 2][low_limit_j + 2] = player;
                    grids[square - 1].second++;
                    valid = true;
                }
                break;
        }

        // Checking if the subgrid is invalid
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
            cin >> sub_square;
        }
    }

    // Checks if the played scored
    win_grid(player, square);

    // If the next grid was scored then the player can play at any available grid 
    if (grids[sub_square - 1].first == EMPTY)
        next_grid = sub_square;
    else
        next_grid = -1;
}

status TicTacToe::tie(int square)
{
    // Grid is tied if all the 9 sub squares where marked but no player could score
    if (grids[square - 1].second == 9 && grids[square - 1].first == EMPTY)
    {
        grids[square - 1].first = TIE;
        return TIE;
    }

    return grids[square - 1].first;
}

/* Prints the tic tac toe board. N = empty, X = player 1 and O = player 2. */
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

/* Checks if the choosen grid is valid and calls play_sub_grid to handle the subgrid. */
void TicTacToe::play(status player, int next_grid)
{
    int square = 0, sub_square = 0;

    if (next_grid == -1)
    {
        cout << "You can choose any of theese grids to play: ";
        for (size_t i = 0; i < 9; i++)
            if (grids[i].first == EMPTY)
                cout << i + 1 << " ";
        cout << '\n';
        cin >> square;

        while (square < 0 || square > 9 || grids[square - 1].first != EMPTY) 
        {
            cout << "Invalid grid\n";
            cout << "You can play in these grids: ";

            for (size_t i = 0; i < 9; i++)
                if (grids[i].first == EMPTY)
                    cout << i + 1 << " ";
            cout << '\n';

            cout << "grid: ";
            cin >> square;
        }
    }
    else
        square = next_grid;
    
    // play_sub_grid checks if subgrid is valid and if so it marks in the matrix (board).
    cout << "Sub grid: ";
    cin >> sub_square;

    switch (square)
    {
        case 1:
            play_sub_grid(player, square, sub_square, 0, 0);
            break;
        case 2:
            play_sub_grid(player, square, sub_square, 0, 3);
            break;
        case 3:
            play_sub_grid(player, square, sub_square, 0, 6);
            break;
        case 4:
            play_sub_grid(player, square, sub_square, 3, 0);
            break;
        case 5:
            play_sub_grid(player, square, sub_square, 3, 3);
            break;
        case 6:
            play_sub_grid(player, square, sub_square, 3, 6);
            break;
        case 7:
            play_sub_grid(player, square, sub_square, 6, 0);
            break;
        case 8:
            play_sub_grid(player, square, sub_square, 6, 3);
            break;
        case 9:
            play_sub_grid(player, square, sub_square, 6, 6);
            break;
        default:
            break;
    }

    tie(square);
}

/* Checks if the player won or if it's a tie. If the player didn't win and it's not a tie it will return EMPTY. */
status TicTacToe::win(status player, string player_name)
{
    /* VER QUESTÃO DE EMPATE */

    // Checking the lines
    for (size_t i = 0; i < 7; i += 3)
    {
        if (grids[i].first == player && grids[i+1].first == player && grids[i+2].first == player)
            return player;
        else if (grids[i].first == TIE && grids[i+1].first == TIE && grids[i+2].first == TIE)
            return TIE;
    }

    // Checking the columns
    for (size_t i = 0; i < 3; i++)
    {
        if (grids[i].first == player && grids[i+3].first == player && grids[i+6].first == player)
            return player;
        else if (grids[i].first == TIE && grids[i+3].first == TIE && grids[i+6].first == TIE)
            return TIE;
    }
    
    // Diagonals
    if (grids[0].first == player && grids[4].first == player && grids[8].first == player)
        return player;
    else if (grids[0].first == TIE && grids[4].first == TIE && grids[8].first == TIE)
        return TIE;
    else if (grids[2].first == player && grids[4].first == player && grids[6].first == player)
        return player;
    else if (grids[2].first == TIE && grids[4].first == TIE && grids[6].first == TIE)
        return TIE;

    int complete_grids = 0;
    for (size_t i = 0; i < 9; i++)
        if (grids[i].first != EMPTY)
            complete_grids++;
        
    if (complete_grids == 9)
        return TIE;
    
    return EMPTY;
}