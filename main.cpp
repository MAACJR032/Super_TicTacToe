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

enum status victory = EMPTY;

void clear()
{
    system("@cls||clear");
}

void play(TicTacToe &t, status player, string player_name)
{
    clear();

    cout << player_name << " turn\n";
    cout << "Current board:\n\n";
    t.print_tic_tac_toe();
    
    t.play(player, t.get_next_grid());
    victory = t.win(player, player_name);
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
            play(t, X, player1);
            turn = O;
        }
        else
        {
            play(t, O, player2);
            turn = X;
        }

        round++;
        clear();
    }
    
    t.print_tic_tac_toe();
    switch (victory)
    {
        case X:
            cout << player1 << " Win !!!\n";
            break;
        case O:
            cout << player2 << " Win !!!\n";
            break;
        case TIE:
            cout << "Tie\n";
            break;
        default:
            break;
    }
    
    return 0;
}