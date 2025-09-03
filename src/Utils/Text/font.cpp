#include "font.hpp"
#include "Utils/Path/path_utils.hpp"
#include "Utils/Log/logger.hpp"

sf::Font& Font::get()
{
    static sf::Font font;
    static bool loaded = false;

    if (!loaded)
    {
        std::string fontPath = get_assets_path() + "font/Open_Sans/OpenSans.ttf";
        if (!font.loadFromFile(fontPath))
            LOG_ERROR("ERROR LOADING FONT");
        else
            loaded = true;
    }

    return font;
}