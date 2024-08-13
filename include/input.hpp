#pragma once

#include <SFML/graphics.hpp>
#include <memory>

void button_click(sf::Mouse::Button button, sf::RectangleShape &square, std::unique_ptr<sf::RenderWindow> &window);