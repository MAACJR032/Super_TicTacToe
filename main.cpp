#include <SFML/graphics.hpp>
#include <fstream>
#include "include/TicTacToe.hpp"
#include "include/Game.hpp"

using std::ifstream;

// enum status victory = EMPTY;

// void play(TicTacToe &t, status player, string player_name)
// {
//     clear();

//     cout << player_name << " turn\n";
//     cout << "Current board:\n\n";
//     t.print_tic_tac_toe();
    
//     t.play(player, t.get_next_grid());
//     victory = t.check_win(player, player_name);
// }

int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init game
    Game game;

    // Game loop
    while (game.running())
    {
        // Update
        game.update();

        // Render
        game.render();
    }

    // TicTacToe t;
    // string player1, player2;

    // cout << "Player 1 (X) name: ";
    // cin >> player1;
    // cout << "Player 2 (O) name: ";
    // cin >> player2;

    // /* Instructions */
    // clear_buffer();
    // cout << "\nDo you wanna read the instructions ? [Y/N]: ";

    // if (tolower(getchar()) == 'y')
    // {
    //     ifstream file;
    //     file.open("instructions.txt");

    //     if (file.fail())
    //         cout << "Error opening file\n";

    //     cout << file.rdbuf();
    //     file.close();
        
    //     clear_buffer();
    //     cout << "\n\nPress Enter to close\n";
    // }
    // clear_buffer();

    // /* Game Loop */ 
    // status turn = X;
    // int round = 1;

    // while (victory == EMPTY)
    // {
    //     cout << "Round " << round << '\n';
    //     sleep(2);

    //     if (turn == X)
    //     {
    //         play(t, X, player1);
    //         turn = O; // Change turn
    //     }
    //     else
    //     {
    //         play(t, O, player2);
    //         turn = X; // Change turn
    //     }

    //     round++;
    //     clear();
    // }
    
    // /* Game result */
    // t.print_tic_tac_toe();
    // switch (victory)
    // {
    //     case X:
    //         cout << player1 << " Win !!!\n";
    //         break;
    //     case O:
    //         cout << player2 << " Win !!!\n";
    //         break;
    //     case TIE:
    //         cout << "It's a Tie\n";
    //         break;
    //     default:
    //         break;
    // }

    return 0;
}