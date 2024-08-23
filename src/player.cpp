#include "../include/player.hpp"

Player::Player()
{
    curr_player = X;
}

void Player::play(TicTacToe &t, std::unique_ptr<sf::RenderWindow> &window)
{
    t.play(curr_player, window);

    // if (curr_player == X)
    //     curr_player = O;
    // else
    //     curr_player = X;
}