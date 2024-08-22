#pragma once

#include "TicTacToe.hpp"

class Player
{
    public:
        status curr_player;

        Player();

        void play(TicTacToe &t);
};

