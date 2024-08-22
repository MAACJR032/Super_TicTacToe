#pragma once

#include "Game.hpp"
#include "player.hpp"

void button_click(sf::Mouse::Button button, Square &square, std::unique_ptr<sf::RenderWindow> &window, TicTacToe &t, Player &player);