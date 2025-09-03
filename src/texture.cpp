#include "texture.hpp"

#include "Utils/Path/path_utils.hpp"
#include "Utils/Log/logger.hpp"

static const std::string assets_dir = get_assets_path();

void Texture::load_texture(sf::Texture& texture, const std::string& name)
{
    if (!texture.loadFromFile(assets_dir + "Assets/" + name))
        LOG_ERROR("Error loading " + name);
}

void Texture::load_all()
{
    /*
        Sprites taken from here: https://www.pngwing.com/en/free-png-kbndf 
    */ 
    load_texture(s_X_texture,     "X_sprite.png");
    load_texture(s_Big_X_texture, "Big_X_sprite.png");
    load_texture(s_O_texture,     "O_sprite.png");
    load_texture(s_Big_O_texture, "Big_O_sprite.png");
}

void Texture::set_subgrid_texture(sf::RectangleShape &square, Status player)
{
    if (player == Status::X)
        square.setTexture(&s_X_texture);
    else if (player == Status::O)
        square.setTexture(&s_O_texture);
}

void Texture::set_grid_texture(sf::RectangleShape &square, Status player)
{
    if (player == Status::X)
        square.setTexture(&s_Big_X_texture);
    else if (player == Status::O)
        square.setTexture(&s_Big_O_texture);
}

sf::Texture& Texture::get_subgrid_texture(Status player)
{
    return (player == Status::X) ? s_X_texture : s_O_texture;
}

sf::Texture& Texture::get_grid_texture(Status player)
{
    return (player == Status::X) ? s_Big_X_texture : s_Big_O_texture;
}