#pragma once

#include "Game.hpp"

bool button_click(sf::RectangleShape &square, std::unique_ptr<sf::RenderWindow> &window);
void mouse_valid_square(std::unique_ptr<sf::RenderWindow> &window, TicTacToe &t);