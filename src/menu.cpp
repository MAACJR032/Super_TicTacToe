#include "menu.hpp"

menu::menu(sf::RenderWindow &window)
{
    title.set_text("SUPER TIC TAC TOE");

    sf::FloatRect bounds = title.get_text().getLocalBounds();
    title.set_position({bounds.width / 2.f + bounds.left, bounds.height / 2.f + bounds.top}, 
                       {window.getSize().x / 2 - (2 * bounds.width / 13.f), 2 * bounds.height});

    start.set_text("START");
    bounds = start.get_text().getLocalBounds();

    start.set_button_position({bounds.width / 2.f + bounds.left, bounds.height / 2.f + bounds.top}, 
                              {window.getSize().x / 2.f - (bounds.width / 1.3f), 8 * bounds.height}, 
                              {window.getSize().x / 2.f - (bounds.width / 2.f), 7.5f * bounds.height});

    exit.set_text("EXIT");
    bounds = exit.get_text().getLocalBounds();
    exit.set_button_position({bounds.width / 2.f + bounds.left, bounds.height / 2.f + bounds.top}, 
                             {window.getSize().x / 2.f - (1.43f * bounds.width), 16 * bounds.height}, 
                             {window.getSize().x / 2.f - (bounds.width / 2.f), 15.5f * bounds.height});
}

void menu::draw(sf::RenderWindow &window)
{
    title.draw(window);
    start.draw(window);
    exit.draw(window);
}

bool menu::start_button_clicked(sf::RenderWindow &window)
{
    return start.button_clicked(window);
}

bool menu::exit_button_clicked(sf::RenderWindow &window)
{
    return exit.button_clicked(window);
}