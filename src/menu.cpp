#include "menu.hpp"

/* Sets the position of the title and all the buttons. */
main_menu::main_menu(sf::Vector2u window_size) : 
    m_title("SUPER TIC TAC TOE", 50), m_start_button("START", 40), 
    m_exit_button("EXIT", 40), m_credits_button("CREDITS", 40) 
{
    float half_x = window_size.x / 2.f;
    float half_y = window_size.y / 2.f;

    sf::FloatRect bounds = m_title.get_text().getLocalBounds();
    m_title.set_position({half_x - bounds.width / 2.f, 2 * bounds.height});

    bounds = m_start_button.get_text().getLocalBounds();
    m_start_button.set_button_position(
        {half_x - 150.f, half_y / 2.f}, 
        {half_x - bounds.width / 2.f, half_y / 2.f + 10.f}
    );

    bounds = m_credits_button.get_text().getLocalBounds();
    m_credits_button.set_button_position(
        {half_x - 150.f, half_y / 1.175f}, 
        {half_x - bounds.width / 2.f, half_y / 1.175f + 10.f}
    );

    bounds = m_exit_button.get_text().getLocalBounds();
    m_exit_button.set_button_position(
        {half_x - 150.f, 1.2f * half_y}, 
        {half_x - bounds.width / 2.f, 1.2f * half_y + 10.f}
    );
}

/* Returns true if the start button was clicked.*/
bool main_menu::start_button_clicked(sf::RenderWindow &window) const
{
    return m_start_button.button_clicked(window);
}

/* Returns true if the exit button was clicked.*/
bool main_menu::exit_button_clicked(sf::RenderWindow &window) const
{
    return m_exit_button.button_clicked(window);
}

/* Returns true if the credits button was clicked.*/
bool main_menu::credits_button_clicked(sf::RenderWindow &window) const
{
    return m_credits_button.button_clicked(window);
}

/* Draws all the buttons and the game title.*/
void main_menu::draw(sf::RenderWindow &window) const
{
    m_title.draw(window);
    m_start_button.draw(window);
    m_exit_button.draw(window);
    m_credits_button.draw(window);
}


/* Sets the position of the text and all the buttons. */
credits_menu::credits_menu(sf::Vector2u window_size) : m_return_button("RETURN", 40)
{
    float half_x = window_size.x / 2.f;
    float half_y = window_size.y / 2.f;

    sf::FloatRect bounds = m_return_button.get_text().getLocalBounds();
    bounds = m_return_button.get_text().getLocalBounds();
    m_return_button.set_button_position(
        {half_x - 150.f, 1.5f * half_y}, 
        {half_x - bounds.width / 2.f, 1.5f * half_y + 10.f}
    );

    std::string assets_dir = get_assets_path();
    std::string credits_path = assets_dir + "texts/credits.txt";

    m_credits_file.open(credits_path);
    
    if (m_credits_file.fail())
        return;

    std::string s;
    m_credits_text.reserve(22);
    float x = window_size.y / 1.5f, y = 90.f;
    int i = 0;
    
    while (std::getline(m_credits_file, s))
    {
        m_credits_text.emplace_back(s, 30, sf::Vector2f(x, y));
        if (s.back() == ':')
        {
            m_credits_text[i].get_text().setStyle(sf::Text::Bold);
            x = (window_size.y / 1.5f) + m_credits_text[i].get_text().getLocalBounds().width + 20.f;
        }
        else
            x = window_size.y / 1.5f;

        if (s.empty())
            y +=  60.f;
        i++;
    }

    m_credits_text[0].set_position({window_size.y / 1.25f, 30.f});
    m_credits_text[0].get_text().setStyle(sf::Text::Italic);

    m_credits_text[1].set_position({window_size.y / 1.25f, 80.f});
    m_credits_text[1].set_char_size(25.f);

    m_credits_text[i-1].set_position({window_size.y / 1.5f, y - 30.f});

    m_credits_file.close();
}


/* Returns true if the back button was clicked.*/
bool credits_menu::return_button_clicked(sf::RenderWindow &window) const
{
    return m_return_button.button_clicked(window);
}

/* Draws all the back button and the text.*/
void credits_menu::draw(sf::RenderWindow &window) const
{
    for (auto &t : m_credits_text)
        t.draw(window);

    m_return_button.draw(window);
}


/* Sets the position of the text box and the type message. */
name_input_menu::name_input_menu(sf::Vector2u window_size) : 
    m_return_button("RETURN", 40), m_type_message("X's Name:", 40), m_error_message(), m_player_name_box("", 30, {0.f, 0.f})
{
    float half_x = window_size.x / 2.f;
    float half_y = window_size.y / 2.f;

    m_player_name_box.set_position({half_x - m_player_name_box.get_box_sizes().first / 2.1f, half_y / 1.24f});
    m_player_name_box.set_box_position({half_x, half_y / 1.175f});

    m_type_message.set_position({half_x - m_player_name_box.get_box_sizes().first / 1.1f, half_y / 1.275f});
    m_error_message.get_text().setFillColor(RED);

    sf::FloatRect bounds = m_return_button.get_text().getLocalBounds();
    m_return_button.set_button_position(
        {half_x - 150.f, 1.2f * half_y}, 
        {half_x - bounds.width / 2.f, 1.2f * half_y + 10.f}
    );
}

/* Returns a reference to text_box. */ 
text_box& name_input_menu::get_text_box()
{
    return m_player_name_box;
}

/* Returns true if the return button was clicked. */
bool name_input_menu::return_button_clicked(sf::RenderWindow &window) const
{
    return m_return_button.button_clicked(window);
}

/* Returns true if it is player 1's turn to write their name. */
bool name_input_menu::is_player1_turn() const
{
    return player1_turn;
}

/* Wil set player 1's turn to write their name. */
void name_input_menu::set_player1_turn()
{
    player1_turn = true;
}

/* Wil set player 2's turn to write their name. */
void name_input_menu::set_player2_turn()
{
    player1_turn = false;
}

void name_input_menu::set_error_message_false()
{
    display_error_message = false;
}

/* Sets the text of the text_box. */
void name_input_menu::set_box_text(const std::string &s)
{
    m_player_name_box.set_text(s, 30);
}

/* Sets the message of which player turn is to type the name. */
void name_input_menu::set_type_message(const std::string &s)
{
    m_type_message.set_text(s, 40);
}

void name_input_menu::set_error_message(const std::string &error_message, const sf::Vector2u window_size)
{
    float half_x = window_size.x / 2.f;
    float half_y = window_size.y / 2.f;

    m_error_message.set_text(
        error_message, 40,
        {half_x - m_player_name_box.get_box_sizes().first / 2.1f, half_y / 1.48f}
    );

    display_error_message = true;
}

/* Draws the type message and the text_box. */
void name_input_menu::draw(sf::RenderWindow &window) const
{
    window.draw(m_type_message.get_text());
    m_player_name_box.draw(window);
    m_return_button.draw(window);

    if (display_error_message)
        m_error_message.draw(window);
}


/* Sets the position of all the buttons. */
end_screen_menu::end_screen_menu(sf::Vector2u window_size) : 
    m_rematch_button("REMATCH", 40), m_menu_button("MENU", 40)
{
    float half_x = window_size.x / 2.f;
    float half_y = window_size.y / 2.f;

    // m_menu_button.set_text("MENU", 40);
    sf::FloatRect bounds = m_menu_button.get_text().getLocalBounds();
    m_menu_button.set_button_position(
        {half_x - 150.f, half_y / 2.f}, 
        {half_x - bounds.width / 2.f, half_y / 2.f + 10.f}
    );

    // m_rematch_button.set_text("REMATCH", 40);
    bounds = m_rematch_button.get_text().getLocalBounds();
    m_rematch_button.set_button_position(
        {half_x - 150.f, half_y / 1.175f}, 
        {half_x - bounds.width / 2.f, half_y / 1.175f + 10.f}
    );
}

/* Sets the position of the result message. */
void end_screen_menu::set_result(const std::string &result_message, sf::Vector2u window_size)
{
    float half_x = window_size.x / 2.f;

    sf::FloatRect bounds = m_result_text.get_text().getLocalBounds();
    m_result_text.set_text(
        result_message, 40, 
        {half_x - bounds.width / 2.f, 2 * bounds.height}
    );
}

/* Returns true if the menu button was clicked.*/
bool end_screen_menu::menu_button_clicked(sf::RenderWindow &window) const
{
    return m_menu_button.button_clicked(window);
}

/* Returns true if the rematch button was clicked.*/
bool end_screen_menu::rematch_button_clicked(sf::RenderWindow &window) const
{
    return m_rematch_button.button_clicked(window);
}

/* Draws all the buttons and the result text.*/
void end_screen_menu::draw(sf::RenderWindow &window) const
{
    window.draw(m_result_text.get_text());
    m_menu_button.draw(window);
    m_rematch_button.draw(window);
}