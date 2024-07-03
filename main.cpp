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

void play(TicTacToe t, status player, string player_name, int next_grid)
{
    sleep(2);
    clear();

    cout << player_name << " turn\n\n";
    t.print_tic_tac_toe();

    if (next_grid == -1)
    {
        cout << "You can play at any grid\n";
        cout << "Choose the grid and the sub grid to play\n";
    }
    

    /* Lógica para checar qual o grid a se jogar */
    t.play(player, 0, 0);
    t.win(player); // Checks if the player won
}

int main()
{
    TicTacToe t;
    
    string player1, player2;

    cout << "Player 1 (X) name: ";
    cin >> player1;
    cout << "Player 1 (O) name: ";
    cin >> player2;

    char turn[2] = {'X', 'O'};
    int turn_index = 0;
    int round = 1;
    int next_grid = -1;

    while (victory == EMPTY)
    {
        sleep(2);
        clear();

        cout << "Round " << round << '\n';
        if (turn[turn_index] == 'X')
        {
            play(t, X, player1, next_grid);
        }
        else
        {
            play(t, O, player1, next_grid);
        }

        round++;

        if (turn_index == 1)
        {
            turn_index = 0;
            continue;
        }

        turn_index++;
    }
    
    return 0;
}