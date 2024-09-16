#include "menu.hpp"
#include <iostream>
#include <fstream>

menu::menu(sf::RenderWindow &window)
{
    title.set_text("SUPER TIC TAC TOE", 50);

    float half_x = window.getSize().x / 2.f;
    float half_y = window.getSize().y / 2.f;

    sf::FloatRect bounds = title.get_text().getLocalBounds();
    title.set_position({half_x - bounds.width / 2.f, 2 * bounds.height});

    start.set_text("START", 40);
    bounds = start.get_text().getLocalBounds();
    start.set_button_position(
        {half_x - 150.f, half_y / 2.f}, 
        {half_x - bounds.width / 2.f, half_y / 2.f + 10.f}
    );

    credits.set_text("CREDITS", 40);
    bounds = credits.get_text().getLocalBounds();
    credits.set_button_position(
        {half_x - 150.f, half_y / 1.175f}, 
        {half_x - bounds.width / 2.f, half_y / 1.175f + 10.f}
    );

    /*
    sf::Text a;
    std::ifstream b;
    b.open("instructions.txt");
    if (b.fail())
        printf("deu erro\n");

    std::string s;
    std::getline(b, s);

    std::cout << s << '\n';

    exit.set_text("EXIT", 40);
    bounds = exit.get_text().getLocalBounds();
    exit.set_button_position(
        {half_x - 150.f, 1.2f * half_y}, 
        {half_x - bounds.width / 2.f, 1.2f * half_y + 10.f}
    );
    */
}

void menu::draw(sf::RenderWindow &window)
{
    title.draw(window);
    start.draw(window);
    exit.draw(window);
    credits.draw(window);
}

bool menu::start_button_clicked(sf::RenderWindow &window)
{
    return start.button_clicked(window);
}

bool menu::exit_button_clicked(sf::RenderWindow &window)
{
    return exit.button_clicked(window);
}

bool menu::credits_button_clicked(sf::RenderWindow &window)
{
    return credits.button_clicked(window);
}