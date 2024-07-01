#pragma once

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;

enum status {EMPTY = 0, X = 1, O = 2};

class sub_TicTacToe
{
    public:
        vector<vector<status>> sub;
        enum status curr_status;
    
        sub_TicTacToe();

        void print_sub(void)
        {   
            for (size_t i = 0; i < 3; i++)
            {
                for (size_t j = 0; j < 3; j++)
                    cout << sub[i][j] << " ";
                cout << '\n';
            }
        }

        void valid_sub();
};

sub_TicTacToe::sub_TicTacToe()
{
    sub.resize(3);
    for (size_t i = 0; i < 3; i++)
    {
        sub[i].resize(3, EMPTY);
        curr_status = EMPTY;
    }
}

void sub_TicTacToe::valid_sub()
{
    for (size_t i = 0; i < 3; i++)
    {
        if (sub[i][0] != EMPTY && sub[i][0] == sub[i][1] && sub[i][0] == sub[i][2])
            curr_status = sub[i][0];
            
        else if (sub[0][i] != EMPTY && sub[0][i] == sub[1][i] && sub[0][i] == sub[2][i])
            curr_status = sub[i][0];
        
        else if (sub[i][0] != EMPTY && sub[i][0] == sub[1][1] && sub[i][0] == sub[2][2])
            curr_status = sub[i][0];
    }
}

class TicTacToe
{
    private:
        vector<vector<sub_TicTacToe>> tic_tac_toe;
    public:
        TicTacToe();
        void print_tic_tac_toe();
        void play(enum status player, int square, int sub_square);
        void valid();
};

TicTacToe::TicTacToe()
{
    tic_tac_toe.resize(3);
    for (size_t i = 0; i < 3; i++)
        tic_tac_toe[i].resize(3);
}

void TicTacToe::print_tic_tac_toe()
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            tic_tac_toe[i][j].print_sub();
            cout << '\n';
        }
    }
}

void TicTacToe::play(enum status player, int square, int sub_square)
{
    /* Criar função para checar se o quadrado já foi completado, para não jogar e local já dominado */
    /* Criar função para checar se os quadrados selecionados são válidos */
    do
    {
        cout << "Square: ";
        cin >> square;

        cout << "Sub square: ";
        cin >> sub_square;

    } while (square < 0 || square > 9 || sub_square < 0 || sub_square > 9);
    
    switch (square)
    {
        case 1:
            
            break;
    }
}

void TicTacToe::valid()
{
    for (size_t i = 0; i < 3; i++)
    {
        if (tic_tac_toe[i][0].curr_status != EMPTY && tic_tac_toe[i][0].curr_status == tic_tac_toe[i][1].curr_status && tic_tac_toe[i][0].curr_status == tic_tac_toe[i][2].curr_status)
            cout << "Player " << tic_tac_toe[i][0].curr_status << " Won !!!\n";
        
        else if (tic_tac_toe[0][i].curr_status != EMPTY && tic_tac_toe[0][i].curr_status == tic_tac_toe[1][i].curr_status && tic_tac_toe[0][i].curr_status == tic_tac_toe[2][i].curr_status)
            cout << "Player " << tic_tac_toe[i][0].curr_status << " Won !!!\n";
        
        else if (tic_tac_toe[i][0].curr_status != EMPTY && tic_tac_toe[i][0].curr_status == tic_tac_toe[1][1].curr_status && tic_tac_toe[i][0].curr_status == tic_tac_toe[2][2].curr_status)
            cout << "Player " << tic_tac_toe[i][0].curr_status << " Won !!!\n";
    }
}