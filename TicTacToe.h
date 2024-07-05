#pragma once

#include <iostream>
#include <vector>
#include <unistd.h>

using std::vector;
using std::cout;
using std::cin;

enum status {EMPTY = 'N', X = 'X', O = 'O'};

class TicTacToe
{
    private:
        vector<status> grids;
        void play_sub(status player, int square, int sub_square, int low_limit_i, int low_limit_j);
        void win_grid(status player, int grid);
        void check_sub(status player, int square, int low_limit_i, int low_limit_j);

    public:
        vector<vector<status>> tic_tac_toe;
        TicTacToe();
        void print_tic_tac_toe();
        void play(status player);
        status win(status player);
};

/* Initializes an empty 9x9 matrix (board). */
TicTacToe::TicTacToe()
{
    tic_tac_toe.resize(9);
    for (size_t i = 0; i < 9; i++)
        tic_tac_toe[i].resize(9, EMPTY);
    
    grids.resize(9, EMPTY);
}

/* Checks if player win the grid he just played */
void TicTacToe::win_grid(status player, int grid)
{
    switch (grid)
    {
        case 1:
            check_sub(player, grid, 0, 0);
            break;
        case 2:
            check_sub(player, grid, 0, 3);
            break;
        case 3:
            check_sub(player, grid, 0, 6);
            break;
        case 4:
            check_sub(player, grid, 3, 0);
            break;
        case 5:
            check_sub(player, grid, 3, 3);
            break;
        case 6:
            check_sub(player, grid, 3, 6);
            break;
        case 7:
            check_sub(player, grid, 6, 0);
            break;
        case 8:
            check_sub(player, grid, 6, 3);
            break;
        case 9:
            check_sub(player, grid, 6, 6);
            break;
        default:
            break;
    }
}

/* Checks all the cases where the player may have scored in a grid */
void TicTacToe::check_sub(status player, int square, int low_limit_i, int low_limit_j)
{
    // Checking the lines
    for (size_t i = low_limit_i; i < low_limit_i + 3; i++)
    {
        if (tic_tac_toe[i][low_limit_j] == player && tic_tac_toe[i][low_limit_j + 1] == player && tic_tac_toe[i][low_limit_j + 2] == player)
            grids[square - 1] = player;
    }

    // Checking the columns
    for (size_t i = low_limit_j; i < low_limit_j + 3; i++)
    {
        if (tic_tac_toe[i][low_limit_j] == player && tic_tac_toe[i + 1][low_limit_j] == player && tic_tac_toe[i + 2][low_limit_j] == player)
            grids[square - 1] = player;
    }
    
    // Diagonals
    if (tic_tac_toe[low_limit_i][low_limit_j] == player && tic_tac_toe[low_limit_i + 1][low_limit_j + 1] == player && tic_tac_toe[low_limit_i + 2][low_limit_j + 2] == player)
        grids[square - 1] = player;

    else if (tic_tac_toe[low_limit_i][low_limit_j + 2] == player && tic_tac_toe[low_limit_i + 1][low_limit_j + 1] == player && tic_tac_toe[low_limit_i + 2][low_limit_j] == player)
        grids[square - 1] = player;
}

/* Checks if the subgrid is valid and if so, it marks in tic_tac_toe.
   Otherwise it will show the available sub grids to play and ask the player to select again. */
void TicTacToe::play_sub(status player, int square, int sub_square, int low_limit_i, int low_limit_j)
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
                    valid = true;
                }
                break;
            case 2:
                if (tic_tac_toe[low_limit_i][low_limit_j + 1] == EMPTY)
                {
                    tic_tac_toe[low_limit_i][low_limit_j + 1] = player;
                    valid = true;
                }
                break;
            case 3:
                if (tic_tac_toe[low_limit_i][low_limit_j + 2] == EMPTY)
                {
                    tic_tac_toe[low_limit_i][low_limit_j + 2] = player;
                    valid = true;
                }
                break;
            case 4:
                if (tic_tac_toe[low_limit_i + 1][low_limit_j] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 1][low_limit_j] = player;
                    valid = true;
                }
                break;
            case 5:
                if (tic_tac_toe[low_limit_i + 1][low_limit_j + 1] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 1][low_limit_j + 1] = player;
                    valid = true;
                }
                break;
            case 6:
                if (tic_tac_toe[low_limit_i + 1][low_limit_j + 2] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 1][low_limit_j + 2] = player;
                    valid = true;
                }
                break;
            case 7:
                if (tic_tac_toe[low_limit_i + 2][low_limit_j] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 2][low_limit_j] = player;
                    valid = true;
                }
                break;
            case 8:
                if (tic_tac_toe[low_limit_i + 2][low_limit_j + 1] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 2][low_limit_j + 1] = player;
                    valid = true;
                }
                break;
            case 9:
                if (tic_tac_toe[low_limit_i + 2][low_limit_j + 2] == EMPTY)
                {
                    tic_tac_toe[low_limit_i + 2][low_limit_j + 2] = player;
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
}

/* Prints the tic tac toe board. N = empty, X = player 1 and O = player 2. */
void TicTacToe::print_tic_tac_toe()
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

    cout << "Available grids:\n\n";
    for (size_t i = 0; i < 9; i += 3)
        printf("%c %c %c\n", grids[i], grids[i+1], grids[i+2]);    
}

/* Checks if the choosen grid is valid and calls play_sub to handle the subgrid. */
void TicTacToe::play(status player)
{
    // if the square to play is occupied, than the player can play in any free grid
    // while (grids[square] != EMPTY)
    // {
    //     print_tic_tac_toe();
    //     cin >> square;
    // }
    int square = 1, sub_square = 1;
    cout << "Grid: ";
    cin >> square;
    
    while (square < 0 || square > 9 || grids[square - 1] != EMPTY) 
    {
        cout << "Invalid grid\n";
        cout << "You can play in these grids: ";

        for (size_t i = 0; i < 9; i++)
            if (grids[i] == EMPTY)
                cout << i + 1 << " ";
        cout << '\n';

        cout << "grid: ";
        cin >> square;
    }
    
    // play_sub checks if subgrid is valid and if so it marks in the matrix (board).
    cout << "Sub grid: ";
    cin >> sub_square;

    switch (square)
    {
        case 1:
            play_sub(player, square, sub_square, 0, 0);
            break;
        case 2:
            play_sub(player, square, sub_square, 0, 3);
            break;
        case 3:
            play_sub(player, square, sub_square, 0, 6);
            break;
        case 4:
            play_sub(player, square, sub_square, 3, 0);
            break;
        case 5:
            play_sub(player, square, sub_square, 3, 3);
            break;
        case 6:
            play_sub(player, square, sub_square, 3, 6);
            break;
        case 7:
            play_sub(player, square, sub_square, 6, 0);
            break;
        case 8:
            play_sub(player, square, sub_square, 6, 3);
            break;
        case 9:
            play_sub(player, square, sub_square, 6, 6);
            break;
        default:
            break;
    }
}

/* Checks if the player won. If the player didn't win it will return EMPTY. */
status TicTacToe::win(status player)
{
    /* CHECAR CADA QUADRADO P/ CASO ALGUM GRID SEJA MARCADO */
    /* VER QUESTÃO DE EMPATE */
    
/*
    0 1 2
    3 4 5
    6 7 8
            */

    // Checking the lines
    for (size_t i = 0; i < 7; i += 3)
    {
        if (grids[i] == player && grids[i+1] == player && grids[i+2] == player)
        {
            cout << "Player " << player << "Win !!!";

            // flag de fim
            return player;
        }
    }

    // Checking the columns
    for (size_t i = 0; i < 3; i++)
    {
        if (grids[i] == player && grids[i+3] == player && grids[i+6] == player)
        {
            cout << "Player " << player << "Win !!!";

            // flag de fim
            return player;
        }
    }
    
    // Diagonals
    if (grids[0] == player && grids[4] == player && grids[8] == player)
    {
        cout << "Player " << player << "Win !!!";
        // flag de fim
        return player;
    }
    else if (grids[2] == player && grids[4] == player && grids[6] == player)
    {
        cout << "Player " << player << "Win !!!";
        // flag de fim
        return player;
    }
    
    return EMPTY;
}