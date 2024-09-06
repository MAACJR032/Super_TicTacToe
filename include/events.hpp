#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "../Utils/text.hpp"

class TicTacToe;
enum game_state : uint8_t;

bool button_click(sf::RectangleShape &square, std::unique_ptr<sf::RenderWindow> &window);
void mouse_valid_square(std::unique_ptr<sf::RenderWindow> &window, TicTacToe &t);

void handle_square_play(sf::Event &event, std::unique_ptr<sf::RenderWindow> &window, game_state &curr_state, TicTacToe &t);
void handle_text_box_sel(text_box &t, sf::RenderWindow &window);
void get_player_name(text_box &t, sf::Event &event, std::pair<std::string, std::string> &players, game_state &curr_state);