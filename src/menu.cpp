#include "menu.hpp"
#include <iostream>
#include <fstream>

main_menu::main_menu(sf::RenderWindow &window)
{
    title.set_text("SUPER TIC TAC TOE", 50);

    float half_x = window.getSize().x / 2.f;
    float half_y = window.getSize().y / 2.f;

    sf::FloatRect bounds = title.get_text().getLocalBounds();
    title.set_position({half_x - bounds.width / 2.f, 2 * bounds.height});

    start_button.set_text("START", 40);
    bounds = start_button.get_text().getLocalBounds();
    start_button.set_button_position(
        {half_x - 150.f, half_y / 2.f}, 
        {half_x - bounds.width / 2.f, half_y / 2.f + 10.f}
    );

    credits_button.set_text("CREDITS", 40);
    bounds = credits_button.get_text().getLocalBounds();
    credits_button.set_button_position(
        {half_x - 150.f, half_y / 1.175f}, 
        {half_x - bounds.width / 2.f, half_y / 1.175f + 10.f}
    );

    exit_button.set_text("EXIT", 40);
    bounds = exit_button.get_text().getLocalBounds();
    exit_button.set_button_position(
        {half_x - 150.f, 1.2f * half_y}, 
        {half_x - bounds.width / 2.f, 1.2f * half_y + 10.f}
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
    */
}

void main_menu::draw(sf::RenderWindow &window)
{
    title.draw(window);
    start_button.draw(window);
    exit_button.draw(window);
    credits_button.draw(window);
}

bool main_menu::start_button_clicked(sf::RenderWindow &window)
{
    return start_button.button_clicked(window);
}

bool main_menu::exit_button_clicked(sf::RenderWindow &window)
{
    return exit_button.button_clicked(window);
}

bool main_menu::credits_button_clicked(sf::RenderWindow &window)
{
    return credits_button.button_clicked(window);
}


name_input_menu::name_input_menu(sf::RenderWindow &window)
{
    float half_x = window.getSize().x / 2.f;
    float half_y = window.getSize().y / 2.f;

    player_name_box.set_text(
        "", 30, 
        {half_x - player_name_box.get_box_sizes().first / 2.1f, half_y / 1.24f}
    );

    player_name_box.set_box_position({half_x, half_y / 1.175f});

    type_message.set_text("X's Name:", 40);
    type_message.set_position({half_x - player_name_box.get_box_sizes().first / 1.1f, half_y / 1.275f});
}

void name_input_menu::change_box_text(const std::string s)
{
    player_name_box.set_text(s, 30);
}

void name_input_menu::change_type_message(const std::string s)
{
    type_message.set_text(s, 40);
}

text_box& name_input_menu::get_text_box()
{
    return player_name_box;
}

void name_input_menu::draw(sf::RenderWindow &window)
{
    window.draw(type_message.get_text());
    player_name_box.draw(window);
}


end_screen_menu::end_screen_menu(sf::RenderWindow &window)
{
    float half_x = window.getSize().x / 2.f;
    float half_y = window.getSize().y / 2.f;

    menu_button.set_text("MENU", 40);
    sf::FloatRect bounds = menu_button.get_text().getLocalBounds();
    menu_button.set_button_position(
        {half_x - 150.f, half_y / 2.f}, 
        {half_x - bounds.width / 2.f, half_y / 2.f + 10.f}
    );

    rematch_button.set_text("REMATCH", 40);
    bounds = rematch_button.get_text().getLocalBounds();
    rematch_button.set_button_position(
        {half_x - 150.f, half_y / 1.175f}, 
        {half_x - bounds.width / 2.f, half_y / 1.175f + 10.f}
    );
}

void end_screen_menu::set_result(const std::string result_message, sf::RenderWindow &window)
{
    float half_x = window.getSize().x / 2.f;

    sf::FloatRect bounds = result_text.get_text().getLocalBounds();
    result_text.set_text(
        result_message, 40, 
        {half_x - bounds.width / 2.f, 2 * bounds.height}
    );
}

void end_screen_menu::draw(sf::RenderWindow &window)
{
    window.draw(result_text.get_text());
    menu_button.draw(window);
    rematch_button.draw(window);
}

bool end_screen_menu::menu_button_clicked(sf::RenderWindow &window)
{
    return menu_button.button_clicked(window);
}

bool end_screen_menu::rematch_button_clicked(sf::RenderWindow &window)
{
    return rematch_button.button_clicked(window);
}