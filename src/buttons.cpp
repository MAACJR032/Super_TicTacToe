#include "buttons.hpp"

#include "Utils/colors.hpp"
#include "Utils/Text/keys_unicode.hpp"

Button::Button(const std::string &s, uint32_t char_size, square_colors colors) : Game_text(s, char_size), m_button_rect(colors)
{
    m_button_rect.get_rectangle().setSize({300.f, 70.f});
}

Button::Button(const std::string &s, uint32_t char_size, square_colors colors, const sf::Vector2f size) : Game_text(s, char_size), m_button_rect(colors)
{
    m_button_rect.get_rectangle().setSize(size);
}

/* Set the the button and it's text position on the window. */
void Button::set_position(const sf::Vector2f &button_position, const sf::Vector2f &text_position)
{
    m_button_rect.set_position(button_position);
    m_text.setPosition(text_position);
}

/* Returns true if the button was was_clicked. */
bool Button::was_clicked(sf::RenderWindow &window)
{
    return m_button_rect.was_clicked(window);
}

sf::RectangleShape& Button::get_rectangle()
{
    return m_button_rect.get_rectangle();
}

sf::RectangleShape Button::get_rectangle() const
{
    return m_button_rect.get_rectangle();
}

/* Draw the button and it's text. */
void Button::draw(sf::RenderWindow &window) const
{
    m_button_rect.draw(window);
    window.draw(m_text);
}

/* Sets the size and color of the box. */
Text_box::Text_box(const std::string &text, uint32_t char_size, square_colors colors)
                   : m_box(text, char_size, colors, {465.f, 45.f})
{
    
}

std::string Text_box::get_string() const
{
    return m_box.get_string();
}

void Text_box::_update_display_text()
{
    if (!m_selected && m_input.empty())
        m_box.get_text().setString(s_default_message);
    else
        m_box.get_text().setString(m_input + (m_selected && m_show_cursor ? "_" : ""));
}

/* Used for the backwards key. */
void Text_box::_delete_last_char()
{
    if (!m_input.empty())
    {
        m_input.pop_back();
        _update_display_text();
    }
}

/* Will handle the keys pressed. */
void Text_box::_handle_input(uint32_t unicode)
{
    if (unicode == BACKSPACE)
        _delete_last_char();
    else if (unicode == TAB && static_cast<uint32_t>(m_input.length()) + 4 <= m_char_limit)
        m_input.append("    ");
    else if (unicode >= 32 && unicode < 128 && static_cast<uint32_t>(m_input.length()) < m_char_limit)
        m_input += static_cast<char>(unicode);
    
    _update_display_text();
}

Button& Text_box::get_box()
{
    return m_box;
}

Button Text_box::get_box() const
{
    return m_box;
}

void Text_box::set_position(const sf::Vector2f &button_position, const sf::Vector2f &text_position)
{
    m_box.set_position(button_position, text_position);
}

void Text_box::set_selected(sf::RenderWindow &window)
{
    bool clicked_inside = m_box.was_clicked(window);
    bool mouse_down = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    static bool was_mouse_down_last_frame = false;

    // Detects if the mouse button was released to avoid multiple triggers
    if (!mouse_down && was_mouse_down_last_frame)
    {
        if (clicked_inside && !m_selected)
            m_selected = true;
        else if (!clicked_inside && m_selected)
            m_selected = false;
    }

    was_mouse_down_last_frame = mouse_down;
    _update_display_text();
}

bool Text_box::is_selected() const
{
    return m_selected;
}


void Text_box::update_cursor()
{
    if (m_cursor_timer.getElapsedTime().asMilliseconds() >= 500)
    {
        m_show_cursor = !m_show_cursor;
        m_cursor_timer.restart();
    }
}

/* If the key was typed it will handle the input. */
void Text_box::typed_key_handler(uint32_t unicode)
{
    if (!m_selected)
        return;
    
    if ((unicode > 31 && unicode < 128) || (unicode == TAB) || (unicode == BACKSPACE))
        _handle_input(unicode);
}

std::pair<float, float> Text_box::get_box_size() const
{
    const auto bounds = m_box.get_rectangle().getGlobalBounds();
    return {bounds.width, bounds.height};
}

/**
 * @brief Updates the state and appearance of the text box.
 *
 * This function handles:
 * - Updating the selection state (focused/unfocused).
 * - Updating the blinking cursor visibility.
 * - Displaying the placeholder text centered inside the box
 *   when no input is provided.
 * - Displaying the user input left-aligned with a 1-character padding,
 *   while keeping it vertically centered inside the box.
 *
 * @param window Reference to the main SFML render window.
 */
void Text_box::update(sf::RenderWindow &window)
{
    set_selected(window);
    update_cursor();

    auto box_bounds = m_box.get_rectangle().getGlobalBounds();
    auto text_bounds = m_box.get_text().getLocalBounds();

    float x = 0.f;

    // Vertically center text using line spacing
    float baseline = m_box.get_text().getFont()->getLineSpacing(m_box.get_text().getCharacterSize());
    float y = box_bounds.top + (box_bounds.height - baseline) / 2.f;

    if (!m_selected && m_input.empty())
    {
        m_box.get_text().setString(s_default_message);
        m_box.get_text().setFillColor(sf::Color(60, 60, 60));

        // Center the placeholder text horizontally
        x = box_bounds.left + (box_bounds.width - text_bounds.width) / 2.f - text_bounds.left;
    }
    else
    {
        m_box.get_text().setFillColor(sf::Color::Black);
        m_box.get_text().setString(m_input + (m_selected && m_show_cursor ? "_" : " "));

        // Measure the width of a single character ("A") for padding
        const sf::Glyph& g = m_box.get_text().getFont()->getGlyph(
            'A', // reference
            m_box.get_text().getCharacterSize(),
            false
        );
        float char_width = g.advance;

        // Left-align the typed text inside the box, with 1 character of padding
        x = box_bounds.left + char_width;
    }

    m_box.get_text().setPosition(x, y);
}

/* Draws the box and the text. */
void Text_box::draw(sf::RenderWindow &window) const
{
    window.draw(m_box.get_rectangle());
    window.draw(m_box.get_text());
}

/* Clears the text written on the box. */
void Text_box::clear(bool deselect)
{
    m_input.clear();
    m_selected = !deselect;
    _update_display_text();
}