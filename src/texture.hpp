#pragma once

#include <SFML/Graphics.hpp>
#include "types/status.hpp"

class Texture
{
    private:
        static inline sf::Texture s_X_texture;
        static inline sf::Texture s_Big_X_texture;
        static inline sf::Texture s_O_texture;
        static inline sf::Texture s_Big_O_texture;

    public:
        static void load_texture(sf::Texture& texture, const std::string& name);
        static void load_all();

        static void set_subgrid_texture(sf::RectangleShape &square, Status player);
        static void set_grid_texture(sf::RectangleShape &square, Status player);

        static sf::Texture& get_subgrid_texture(Status player);
        static sf::Texture& get_grid_texture(Status player);
};