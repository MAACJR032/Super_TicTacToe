#include "../include/player.hpp"

Player::Player()
{
    curr_player = X;
}

void Player::play(TicTacToe &t)
{
    // criar função em tictactoe para checar se o grid/subgrid é valido, e checar isso quando clicar no quadrado
    t.play(curr_player, t.get_next_grid());

    if (curr_player == X)
        curr_player = O;
    else
        curr_player = X;
}