#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "menu.hpp"
#include "TicTacToe.hpp"
#include "types/game_state.hpp"

sf::Vector2f get_mouse_position(sf::RenderWindow &window);

void apply_hoever_effect(subgrid &s, TicTacToe &t, sf::RenderWindow &window);
void hoever_effect(sf::RenderWindow &window, TicTacToe &t);

void handle_player_move(sf::Event &event, sf::RenderWindow &window, GameState &curr_state, TicTacToe &t);
void handle_text_box_sel(text_box &t, sf::RenderWindow &window);
void get_player_name(name_input_menu &menu, uint32_t unicode, std::pair<std::string, std::string> &players, GameState &curr_state, sf::RenderWindow &window);