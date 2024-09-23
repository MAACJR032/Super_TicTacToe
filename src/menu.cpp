#include "menu.hpp"
#include <iostream>
#include <locale>
#include <codecvt>

main_menu::main_menu(sf::RenderWindow &window)
{
    m_title.set_text("SUPER TIC TAC TOE", 50);

    float half_x = window.getSize().x / 2.f;
    float half_y = window.getSize().y / 2.f;

    sf::FloatRect bounds = m_title.get_text().getLocalBounds();
    m_title.set_position({half_x - bounds.width / 2.f, 2 * bounds.height});

    m_start_button.set_text("START", 40);
    bounds = m_start_button.get_text().getLocalBounds();
    m_start_button.set_button_position(
        {half_x - 150.f, half_y / 2.f}, 
        {half_x - bounds.width / 2.f, half_y / 2.f + 10.f}
    );

    m_credits_button.set_text("CREDITS", 40);
    bounds = m_credits_button.get_text().getLocalBounds();
    m_credits_button.set_button_position(
        {half_x - 150.f, half_y / 1.175f}, 
        {half_x - bounds.width / 2.f, half_y / 1.175f + 10.f}
    );

    m_exit_button.set_text("EXIT", 40);
    bounds = m_exit_button.get_text().getLocalBounds();
    m_exit_button.set_button_position(
        {half_x - 150.f, 1.2f * half_y}, 
        {half_x - bounds.width / 2.f, 1.2f * half_y + 10.f}
    );
}

bool main_menu::start_button_clicked(sf::RenderWindow &window)
{
    return m_start_button.button_clicked(window);
}

bool main_menu::exit_button_clicked(sf::RenderWindow &window)
{
    return m_exit_button.button_clicked(window);
}

bool main_menu::credits_button_clicked(sf::RenderWindow &window)
{
    return m_credits_button.button_clicked(window);
}

void main_menu::draw(sf::RenderWindow &window)
{
    m_title.draw(window);
    m_start_button.draw(window);
    m_exit_button.draw(window);
    m_credits_button.draw(window);
}


credits_menu::credits_menu(sf::RenderWindow &window)
{
    float half_x = window.getSize().x / 2.f;
    float half_y = window.getSize().y / 2.f;

    m_return_button.set_text("RETURN", 40);

    sf::FloatRect bounds = m_return_button.get_text().getLocalBounds();
    bounds = m_return_button.get_text().getLocalBounds();
    
    m_return_button.set_button_position(
        {half_x - 150.f, 1.2f * half_y}, 
        {half_x - bounds.width / 2.f, 1.2f * half_y + 10.f}
    );

    m_credits_file.open("credits.txt");
    
    if (m_credits_file.fail())
        return;

    std::string s;
    game_text temp;

    float x = 30.f, y = 0.f;
    m_credits_text.reserve(10);
    
    for (int i = 0; std::getline(m_credits_file, s); i++)
    {
        temp.set_text_utf_8(s, 20, {x, y});
        m_credits_text.push_back(temp);
        y +=  30.f;
    }
    
    m_credits_file.close();
}


bool credits_menu::back_button_clicked(sf::RenderWindow &window)
{
    return m_return_button.button_clicked(window);
}

void credits_menu::draw(sf::RenderWindow &window)
{
    for (auto &t : m_credits_text)
        t.draw(window);

    m_return_button.draw(window);
}


name_input_menu::name_input_menu(sf::RenderWindow &window)
{
    float half_x = window.getSize().x / 2.f;
    float half_y = window.getSize().y / 2.f;

    m_player_name_box.set_text(
        "", 30, 
        {half_x - m_player_name_box.get_box_sizes().first / 2.1f, half_y / 1.24f}
    );

    m_player_name_box.set_box_position({half_x, half_y / 1.175f});

    m_type_message.set_text("X's Name:", 40);
    m_type_message.set_position({half_x - m_player_name_box.get_box_sizes().first / 1.1f, half_y / 1.275f});
}

text_box& name_input_menu::get_text_box()
{
    return m_player_name_box;
}

void name_input_menu::set_box_text(const std::string &s)
{
    m_player_name_box.set_text(s, 30);
}

void name_input_menu::set_type_message(const std::string &s)
{
    m_type_message.set_text(s, 40);
}

void name_input_menu::draw(sf::RenderWindow &window)
{
    window.draw(m_type_message.get_text());
    m_player_name_box.draw(window);
}


end_screen_menu::end_screen_menu(sf::RenderWindow &window)
{
    float half_x = window.getSize().x / 2.f;
    float half_y = window.getSize().y / 2.f;

    m_menu_button.set_text("MENU", 40);
    sf::FloatRect bounds = m_menu_button.get_text().getLocalBounds();
    m_menu_button.set_button_position(
        {half_x - 150.f, half_y / 2.f}, 
        {half_x - bounds.width / 2.f, half_y / 2.f + 10.f}
    );

    m_rematch_button.set_text("REMATCH", 40);
    bounds = m_rematch_button.get_text().getLocalBounds();
    m_rematch_button.set_button_position(
        {half_x - 150.f, half_y / 1.175f}, 
        {half_x - bounds.width / 2.f, half_y / 1.175f + 10.f}
    );
}

void end_screen_menu::set_result(const std::string &result_message, sf::RenderWindow &window)
{
    float half_x = window.getSize().x / 2.f;

    sf::FloatRect bounds = m_result_text.get_text().getLocalBounds();
    m_result_text.set_text(
        result_message, 40, 
        {half_x - bounds.width / 2.f, 2 * bounds.height}
    );
}

bool end_screen_menu::menu_button_clicked(sf::RenderWindow &window)
{
    return m_menu_button.button_clicked(window);
}

bool end_screen_menu::rematch_button_clicked(sf::RenderWindow &window)
{
    return m_rematch_button.button_clicked(window);
}

void end_screen_menu::draw(sf::RenderWindow &window)
{
    window.draw(m_result_text.get_text());
    m_menu_button.draw(window);
    m_rematch_button.draw(window);
}