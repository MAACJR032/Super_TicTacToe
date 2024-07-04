#pragma once

#include <iostream>
#include <vector>
#include <unistd.h>

using std::vector;
using std::cout;
using std::cin;

enum status {EMPTY = 'N', X = 'X', O = 'O'};

void valid_sub()
{
    for (size_t i = 0; i < 3; i++)
    {
        // if (sub[i][0] != EMPTY && sub[i][0] == sub[i][1] && sub[i][0] == sub[i][2])
        //     curr_status = sub[i][0];
            
        // else if (sub[0][i] != EMPTY && sub[0][i] == sub[1][i] && sub[0][i] == sub[2][i])
        //     curr_status = sub[i][0];
        
        // else if (sub[i][0] != EMPTY && sub[i][0] == sub[1][1] && sub[i][0] == sub[2][2])
        //     curr_status = sub[i][0];
    }
}

class TicTacToe
{
    private:
        vector<vector<status>> tic_tac_toe;
        vector<status> grids;
        void play_sub(status player, int sub_square, int low_limit_i, int low_limit_j);

    public:
        TicTacToe();
        void print_tic_tac_toe();
        void play(status player, int square, int sub_square);
        status win(status player);
};

TicTacToe::TicTacToe()
{
    tic_tac_toe.resize(9);
    for (size_t i = 0; i < 9; i++)
        tic_tac_toe[i].resize(9, EMPTY);
    
    grids.resize(9, EMPTY);
}

void TicTacToe::play_sub(status player, int sub_square, int low_limit_i, int low_limit_j)
{
    switch (sub_square)
    {
        case 1:
            tic_tac_toe[low_limit_i][low_limit_j] = player;
            break;
        case 2:
            tic_tac_toe[low_limit_i][low_limit_j + 1] = player;
            break;
        case 3:
            tic_tac_toe[low_limit_i][low_limit_j + 2] = player;
            break;
        case 4:
            tic_tac_toe[low_limit_i + 1][low_limit_j] = player;
            break;
        case 5:
            tic_tac_toe[low_limit_i + 1][low_limit_j + 1] = player;
            break;
        case 6:
            tic_tac_toe[low_limit_i + 1][low_limit_j + 2] = player;
            break;
        case 7:
            tic_tac_toe[low_limit_i + 2][low_limit_j] = player;
            break;
        case 8:
            tic_tac_toe[low_limit_i + 2][low_limit_j + 1] = player;
            break;
        case 9:
            tic_tac_toe[low_limit_i + 2][low_limit_j + 2] = player;
            break;
        default:
            break;
    }
}

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
}

void TicTacToe::play(status player, int square, int sub_square)
{
    // if the square to play is occupied, than the player can play in any free grid
    // while (grids[square] != EMPTY)
    // {
    //     print_tic_tac_toe();
    //     cin >> square;
    // }

    cout << "Grid: ";
    cin >> square;
    
    while (square < 0 || square > 8 || grids[square] != EMPTY) 
    {
        cout << "Invalid grid\n";
        cout << "You can play in these grids: ";

        for (size_t i = 0; i < 9; i++)
            if (grids[i] == EMPTY)
                cout << i << " ";
        cout << '\n';
    }
    
    cout << "Sub grid: ";
    cin >> sub_square;

    sleep(2);

    switch (square)
    {
        case 1:
            play_sub(player, sub_square, 0, 0);
            break;
        case 2:
            play_sub(player, sub_square, 0, 3);
            break;
        case 3:
            play_sub(player, sub_square, 0, 6);
            break;
        case 4:
            play_sub(player, sub_square, 3, 0);
            break;
        case 5:
            play_sub(player, sub_square, 3, 3);
            break;
        case 6:
            play_sub(player, sub_square, 3, 6);
            break;
        case 7:
            play_sub(player, sub_square, 6, 0);
            break;
        case 8:
            play_sub(player, sub_square, 6, 3);
            break;
        case 9:
            play_sub(player, sub_square, 6, 6);
            break;
        default:
            break;
    }
    
    /* Criar função para checar se o quadrado já foi completado, para não jogar em local já dominado */
    /* Criar função para checar se os quadrados selecionados são válidos */
   
}

status TicTacToe::win(status player)
{
/*
    0 1 2
    3 4 5
    6 7 8
            */

    // Lines
    for (size_t i = 0; i < 7; i += 3)
    {
        if (grids[i] == player && grids[i+1] == player && grids[i+2] == player)
        {
            cout << "Player " << player << "Win !!!";

            // flag de fim
            return player;
        }
    }

    // Columns
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