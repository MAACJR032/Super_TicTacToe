#include "menu.hpp"

#include "Utils/colors.hpp"
#include "Utils/Path/path_utils.hpp"
#include "Utils/Text/keys_unicode.hpp"
#include "Utils/Log/logger.hpp"

Menu::Menu()
{
}

void Menu::_center_button(Button &button, float window_width, float window_height, float y_factor)
{
    float width = button.get_text().getLocalBounds().width;
    button.set_position(
        {window_width / 2.f - BUTTON_WIDTH, window_height / (2.f * y_factor)},
        {window_width / 2.f - width / 2.f, window_height / (2.f * y_factor) + BUTTON_OFFSET}
    );
}

void Menu::_center_text(sf::Text& text, float window_width, float window_height, float y_factor)
{
    float width = text.getLocalBounds().width;
    text.setPosition({window_width / 2.f - width / 2.f, window_height / (2.f * y_factor)});
}

void Menu::draw(sf::RenderWindow &window) const
{
    for (const auto &b : m_buttons)
        b.draw(window);
    for (const auto &t : m_texts)
        t.draw(window);
}

/* Sets the position of the title and all the buttons. */
Main_menu::Main_menu(sf::Vector2u window_size) : Menu(),
    m_title("SUPER TIC TAC TOE", 50)
{
    sf::FloatRect bounds = m_title.get_text().getLocalBounds();
    m_title.set_position({window_size.x / 2.f - bounds.width / 2.f, 2 * bounds.height});

    m_buttons.reserve(3);
    m_buttons.emplace_back("START", 40, square_colors{GREY, DARK_GREY, BLACK, DARK_GREY, 2.f});   // Start button
    m_buttons.emplace_back("CREDITS", 40, square_colors{GREY, DARK_GREY, BLACK, DARK_GREY, 2.f}); // Credits button
    m_buttons.emplace_back("EXIT", 40, square_colors{GREY, DARK_GREY, BLACK, DARK_GREY, 2.f});    // Exit button

    _center_button(m_buttons[0], window_size.x, window_size.y, 2.f);
    _center_button(m_buttons[1], window_size.x, window_size.y, 1.175f);
    _center_button(m_buttons[2], window_size.x, window_size.y, 0.833f);
}

/* Returns true if the start button was clicked.*/
bool Main_menu::_start_button_clicked(sf::RenderWindow &window)
{
    return m_buttons[0].was_clicked(window);
}

/* Returns true if the credits button was clicked.*/
bool Main_menu::_credits_button_clicked(sf::RenderWindow &window)
{
    return m_buttons[1].was_clicked(window);
}

/* Returns true if the exit button was clicked.*/
bool Main_menu::_exit_button_clicked(sf::RenderWindow &window)
{
    return m_buttons[2].was_clicked(window);
}

GameState Main_menu::update(sf::RenderWindow &window)
{
    draw(window);

    if (_start_button_clicked(window))
    {
        LOG_DEBUG("start button clicked");
        return GameState::NAME_INPUT;
    }
    else if (_exit_button_clicked(window))
    {
        LOG_DEBUG("exit button clicked");
        window.close();
    }
    else if (_credits_button_clicked(window))
    {
        LOG_DEBUG("credits button clicked");
        return GameState::CREDITS;
    }

    return GameState::MENU;
}

/* Draws all the buttons and the game title.*/
void Main_menu::draw(sf::RenderWindow &window) const
{
    m_title.draw(window);
    for (const auto &b : m_buttons)
        b.draw(window);
}

static void Center_text(sf::Text& text, float window_width, float y)
{
    auto bounds = text.getLocalBounds();
    text.setPosition(window_width / 2.f - bounds.width / 2.f, y);
}

Credits_menu::Credits_menu(sf::Vector2u window_size) : Menu()
{
    m_sections = {
        {"Super Tic Tac Toe", {"Developed with SFML"}},
        {"Lead Developer:",   {"Márcio Campos Júnior"}},
        {"Game Design:",      {"Márcio Campos Júnior"}},
        {"Programming:",      {"Márcio Campos Júnior"}},
        {"Graphics & Art:",   {"Sprites sourced from the internet"}},
        {"Testing & QA:",     {"Márcio Campos Júnior"}},
        {"Contribution:",     {"Luiz Gustavo Pinheiro", "(for improving cross-platform compatibility and code organization)"}}
    };

    m_buttons.emplace_back("RETURN", 40, square_colors{GREY, DARK_GREY, BLACK, DARK_GREY, 2.f});
    _center_button(m_buttons[0], window_size.x, window_size.y, 0.6f);

    _setup_credits_text(window_size);
}

void Credits_menu::_setup_credits_text(sf::Vector2u window_size)
{
    const float base_y = 80.f;
    const float paragraph_spacing = 55.f;
    const float window_center = static_cast<float>(window_size.x);

    std::vector<std::string> all_texts;
    for (const auto& section : m_sections)
    {
        all_texts.push_back(section.title);

        for (const auto& entry : section.entries)
            all_texts.push_back(entry);
    }
    
    struct TextConfig
    {
        size_t text_idx;    // index at the vector "all_texts"
        std::string pos;    // "left", "center", "right"
        float y_mult;
        int font_size = 30;
        sf::Text::Style style = sf::Text::Regular;
    };
    
    std::vector<TextConfig> layout =
    {
        // Title and subtitle
        {0, "center", 0, 30, sf::Text::Italic},                // "Super Tic Tac Toe"
        {1, "center", 1, 25},                                  // "Developed with SFML"        
        {2, "left",  4}, {6, "center", 4},  {4, "right", 4},   // Lead Developer, Programming, Game Design
        {3, "left",  5}, {7, "center", 5},  {5, "right", 5},   // Nomes para cada cargo acima
        {8, "left",  7}, {12, "center", 7}, {10, "right", 7},  // Graphics & Art, Contribution, Testing & QA
        {9, "left", 8},  {13, "center", 8}, {11, "right", 8}   // Name for every role above
    };
    
    // Positions
    std::map<std::string, float> pos_map =
    {
        {"left", window_center * 0.405f},
        {"center", window_center},
        {"right", window_center * 1.595f}
    };
    
    // Creating the texts
    for (const auto& config : layout)
    {
        if (config.text_idx < all_texts.size())
        {
            const std::string& text = all_texts[config.text_idx];
            
            m_credits_text.emplace_back(text, config.font_size, sf::Vector2f{0.f, 0.f});
            auto& text_obj = m_credits_text.back().get_text();

            text_obj.setStyle(config.style);
            
            // Titles with ":" are in bold
            if (!text.empty() && text.back() == ':')
                text_obj.setStyle(sf::Text::Bold);
            
            float y_pos = base_y + config.y_mult * paragraph_spacing;
            Center_text(text_obj, pos_map[config.pos], y_pos);
        }
    }
}

/* Returns true if the back button was clicked.*/
bool Credits_menu::_return_button_clicked(sf::RenderWindow &window)
{
    return m_buttons[0].was_clicked(window);
}

GameState Credits_menu::update(sf::RenderWindow &window)
{
    draw(window);

    if (_return_button_clicked(window))
    {
        LOG_DEBUG("return button clicked");
        return GameState::MENU;
    }

    return GameState::CREDITS;
}

/* Draws all the back button and the text.*/
void Credits_menu::draw(sf::RenderWindow &window) const
{
    for (const auto &t : m_credits_text)
        t.draw(window);
    m_buttons[0].draw(window);
}

/* Sets the position of the text box and the type message. */
Name_input_menu::Name_input_menu(sf::Vector2u window_size) : 
    Menu(), 
    m_type_message("X's Name:", 40),
    m_error_message(),
    m_name_box(
        "", 30, square_colors{GREY, GREY, BLACK, DARK_GREY, 2.f}
    )
{
    float half_x = window_size.x / 2.f;
    float half_y = window_size.y / 2.f;

    _center_button(m_name_box.get_box(), (window_size.x - m_name_box.get_box_size().first) * 1.25f, window_size.y, 1.24f);
    _center_text(m_name_box.get_box().get_text(), (window_size.x - m_name_box.get_box_size().first) * 1.2f, window_size.y, 1.24f);

    m_type_message.set_position({half_x - m_name_box.get_box_size().first / 1.1f, half_y / 1.275f});
    m_error_message.get_text().setFillColor(RED);

    m_buttons.emplace_back("RETURN", 40, square_colors{GREY, DARK_GREY, BLACK, DARK_GREY, 2.f}); // Return button
    _center_button(m_buttons[0], window_size.x, window_size.y, 0.833f);
}

/* Returns a reference to text_box. */ 
Text_box& Name_input_menu::get_text_box()
{
    return m_name_box;
}

/* Returns true if the return button was clicked. */
bool Name_input_menu::_return_button_clicked(sf::RenderWindow &window)
{
    return m_buttons[0].was_clicked(window);
}

/* Returns true if it is player 1's turn to write their name. */
Status Name_input_menu::get_player_turn() const
{
    return m_player_turn;
}

/* Wil set player 1's turn to write their name. */
void Name_input_menu::_set_player_turn(Status player)
{
    m_player_turn = player;
}

void Name_input_menu::_display_error_message(bool display)
{
    m_display_error_message = display;
}

/* Sets the message of which player turn is to type the name. */
void Name_input_menu::_update_prompt_message(const std::string &s)
{
    m_type_message.set_text(s, 40);
}

void Name_input_menu::_set_error_message(const std::string &error_message, const sf::Vector2u window_size)
{
    float half_x = window_size.x / 2.f;
    float half_y = window_size.y / 2.f;

    m_error_message.set_text(
        error_message, 40,
        {half_x - m_name_box.get_box_size().first / 2.1f, half_y / 1.48f}
    );

    m_display_error_message = true;
}

GameState Name_input_menu::get_player_name(uint32_t unicode, TicTacToe &tictactoe)
{
    if (unicode != ENTER || !m_name_box.is_selected())
        return GameState::NAME_INPUT;
    _display_error_message(false);

    Text_box &box = get_text_box();
    std::string str = box.get_string();
    
    str.erase(
        std::remove_if(
            str.begin(),
            str.end(),
            [](unsigned char c)
            {
                return std::isspace(c) || c == '_';
            }
        ),
        str.end()
    );
    
    if (str.length() > 0)
    {
        switch (m_player_turn)
        {
            case Status::X:
                m_player1_name = str;
                _set_player_turn(Status::O);
                _update_prompt_message("O's Name:");
                m_display_error_message = false;
                break;

            case Status::O:
                if (str != m_player1_name)  
                {
                    m_player2_name = str;
                    tictactoe.set_players_name({m_player1_name, m_player2_name});
                    return GameState::WAITING_INPUT;
                }
                else
                {
                    _set_error_message("REPEATED NAME", {1680, 900});
                    box.clear(false);

                    return GameState::NAME_INPUT;
                }
                break;

            default:
                break;
        }
    }
    else
    {
        _set_error_message("EMPTY NAME", {1680, 900});
    }

    box.clear(false);
    return GameState::NAME_INPUT;
}

GameState Name_input_menu::update(sf::RenderWindow &window)
{
    m_name_box.update(window);
    draw(window);
    
    if (_return_button_clicked(window))
    {
        LOG_DEBUG("return button clicked");

        m_name_box.clear(true);
        _update_prompt_message("X's Name:");
        _set_player_turn(Status::X);
        return GameState::MENU;
    }

    return GameState::NAME_INPUT;
}

void Name_input_menu::reset()
{
    m_name_box.clear(true);
    _update_prompt_message("X's Name:");
    _set_player_turn(Status::X);
    m_display_error_message = false;
    m_player1_name = "";
    m_player2_name = "";
}

/* Draws the type message and the text_box. */
void Name_input_menu::draw(sf::RenderWindow &window) const
{
    window.draw(m_type_message.get_text());
    m_name_box.draw(window);
    m_buttons[0].draw(window);

    if (m_display_error_message)
        m_error_message.draw(window);
}

/* Sets the position of all the buttons. */
End_screen_menu::End_screen_menu(sf::Vector2u window_size, std::shared_ptr<Board> board) : Menu()
{
    m_board = board;
    m_buttons.reserve(2);
    m_buttons.emplace_back("REMATCH", 40, square_colors{GREY, DARK_GREY, BLACK, DARK_GREY, 2.f});
    m_buttons.emplace_back("MENU", 40, square_colors{GREY, DARK_GREY, BLACK, DARK_GREY, 2.f});
    _center_button(m_buttons[0], window_size.x, window_size.y, 2.f);
    _center_button(m_buttons[1], window_size.x, window_size.y, 1.175f);
}

/* Sets the position of the result message. */
void End_screen_menu::set_result(const std::string &result_message, sf::Vector2u window_size)
{
    float half_x = window_size.x / 2.f;

    sf::FloatRect bounds = m_result_text.get_text().getLocalBounds();
    m_result_text.set_text(
        result_message, 40, 
        {half_x - bounds.width / 2.f, 2 * bounds.height}
    );
}

bool End_screen_menu::_rematch_button_clicked(sf::RenderWindow &window)
{
    return m_buttons[0].was_clicked(window);
}

bool End_screen_menu::_menu_button_clicked(sf::RenderWindow &window)
{
    return m_buttons[1].was_clicked(window);
}

GameState End_screen_menu::update(sf::RenderWindow &window)
{
    if (m_board->is_drawing_line())
    {
        if (m_board->is_line_max_size())
        {
            static sf::Clock timer;
            timer.restart();

            while (timer.getElapsedTime().asSeconds() < 2.f);
        }

        m_board->draw(window);
    }
    else
    {
        Status status = m_board->get_match_status();

        if (status == Status::X)
            set_result(m_board->get_players_name().first + " Win!!!", window.getSize());
        else if (status == Status::O)
            set_result(m_board->get_players_name().second + " Win!!!", window.getSize());
        else if (status == Status::TIE)
            set_result("It's a Tie!!!", window.getSize());
        
        draw(window);

        if (_menu_button_clicked(window))
        {
            LOG_DEBUG("menu button clicked");
            m_board->reset(true);
            return GameState::MENU;
        }
        else if (_rematch_button_clicked(window))
        {
            LOG_DEBUG("rematch button clicked");
            m_board->reset(false);
            return GameState::WAITING_INPUT;
        }
    }

    return GameState::END_SCREEN;
}

/* Draws all the buttons and the result text.*/
void End_screen_menu::draw(sf::RenderWindow &window) const
{
    window.draw(m_result_text.get_text());
    for (const auto &b : m_buttons)
        b.draw(window);
}

Menu_manager::Menu_manager(sf::Vector2u window_size, std::shared_ptr<Board> board) : 
    m_main_menu(window_size),
    m_credits_menu(window_size), 
    m_name_input_menu(window_size),
    m_end_screen_menu(window_size, board)
{
    m_curr_menu = &m_main_menu;
}

void Menu_manager::switch_menu(GameState curr_state)
{
    switch (curr_state)
    {
        case GameState::MENU:
            m_curr_menu = &m_main_menu;
            break;
        
        case GameState::CREDITS:
            m_curr_menu = &m_credits_menu;
            break;
            
        case GameState::NAME_INPUT:
            m_curr_menu = &m_name_input_menu;
            break;

        case GameState::END_SCREEN:
            m_curr_menu = &m_end_screen_menu;
            break;
        
        case GameState::WAITING_INPUT:
        case GameState::PLAYING:
            m_curr_menu = nullptr;
            break;
        default:
            break;
    }

    m_curr_state = curr_state;
}

GameState Menu_manager::update(sf::RenderWindow &window)
{
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        m_mouse_ready_for_click = true;

    if (m_curr_menu)
    {
        GameState new_state = m_curr_menu->update(window);

        if (new_state != m_curr_state && m_mouse_ready_for_click)
        {
            if (new_state == GameState::MENU)
                m_name_input_menu.reset();

            LOG_DEBUGF("Switching from state %d to %d", (int)m_curr_state, (int)new_state);
            switch_menu(new_state);
            m_mouse_ready_for_click = false;
        }
    }

    return m_curr_state;
}

GameState Menu_manager::get_players_name(uint32_t unicode, TicTacToe &tictactoe)
{
    m_name_input_menu.get_text_box().typed_key_handler(unicode);
    return m_name_input_menu.get_player_name(unicode, tictactoe);
}

void Menu_manager::draw(sf::RenderWindow &window) const
{
    if (m_curr_menu)
        m_curr_menu->draw(window);
}