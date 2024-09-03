#include <SFML/Graphics.hpp>
#include <string>
#include "colors.hpp"

class game_text
{
    protected:
        sf::Text text;
        sf::Font open_sans;

        void load_font();

    public:
        game_text();
        sf::Text get_text();
};

class turn_text : public game_text
{
    private:
        std::string player1, player2;
        
    public:
        turn_text(std::string player1, std::string player2);
        void change_curr_player(int8_t player);
};