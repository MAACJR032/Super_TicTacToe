#include "text.hpp"

void game_text::load_font()
{
    open_sans.loadFromFile("Utils/Open_Sans/OpenSans-VariableFont_wdth,wght.ttf");
}

game_text::game_text()
{   
    load_font();
    
    text.setFont(open_sans);
    text.setPosition(15.f, 15.f);
    text.setFillColor(BLACK);
}

sf::Text game_text::get_text()
{
    return text;
}

turn_text::turn_text(std::string player1, std::string player2) : game_text(), player1(player1), player2(player2)
{
    text.setString(player1 + " Turn");
}

void turn_text::change_curr_player(int8_t player)
{
    if (player == 1)
        text.setString(player1 + " Turn");
    else
        text.setString(player2 + " Turn");
}