#pragma once

#include "Game.hpp"
#include "player.hpp"

bool button_click(sf::Mouse::Button button, sf::RectangleShape square, std::unique_ptr<sf::RenderWindow> &window, Player &player);