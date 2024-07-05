/*
                   |                     |
 ____|____|____|   |   ____|____|____|   |   ____|____|____|
 ____|____|____|   |   ____|____|____|   |   ____|____|____|
 ____|____|____|   |   ____|____|____|   |   ____|____|____|
___________________|_____________________|____________________

 ____|____|____|   |   ____|____|____|   |   ____|____|____|
 ____|____|____|   |   ____|____|____|   |   ____|____|____|
 ____|____|____|   |   ____|____|____|   |   ____|____|____|
___________________|_____________________|____________________

 ____|____|____|   |   ____|____|____|   |   ____|____|____|
 ____|____|____|   |   ____|____|____|   |   ____|____|____|
 ____|____|____|   |   ____|____|____|   |   ____|____|____|
                   |                     |
*/

#include "TicTacToe.h"
#include <string>

using std::string;

enum status victory = EMPTY;

void clear()
{
    system("@cls||clear");
}

void play(TicTacToe &t, status player, string player_name, int next_grid)
{
    clear();

    cout << player_name << " turn\n";
    cout << "Current board:\n\n";
    t.print_tic_tac_toe();

    // if (next_grid == -1)
    // {
    //     cout << "You can play at any grid\n";
    //     cout << "Choose the grid and the sub grid to play\n";
    // }
    
    /* Lógica para checar qual o grid a se jogar */
    t.play(player);
    sleep(1);
    t.win(player); // Checks if the player won
}

int main()
{
    TicTacToe t;
    
    string player1, player2;

    cout << "Player 1 (X) name: ";
    cin >> player1;
    cout << "Player 2 (O) name: ";
    cin >> player2;

    /* Instructions */
    
    status turn = X;
    int round = 1;
    int next_grid = -1;

    while (victory == EMPTY)
    {
        cout << "Round " << round << '\n';
        sleep(2);

        if (turn == X)
        {
            play(t, X, player1, next_grid);
            turn = O;
        }
        else
        {
            play(t, O, player2, next_grid);
            turn = X;
        }

        round++;
        clear();
    }
    
    return 0;
}