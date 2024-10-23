#include "text.hpp"

/* Loads and sets the font and color of the text. */
game_text::game_text()
{
    load_font();
    m_text.setFont(m_open_sans);
    m_text.setFillColor(BLACK);
}

/* Loads and sets the font and sets the text and it's color. */
game_text::game_text(const std::string &text, uint32_t char_size)
{
    load_font();
    m_text.setFont(m_open_sans);
    
    m_text.setFillColor(BLACK);
    m_text.setString(sf::String::fromUtf8(text.begin(), text.end()));
    m_text.setCharacterSize(char_size);
}

game_text::game_text(const std::string &text, uint32_t char_size, const sf::Vector2f &position)
{
    load_font();
    m_text.setFont(m_open_sans);

    str = text;
    m_text.setString(sf::String::fromUtf8(text.begin(), text.end()));
    m_text.setFillColor(BLACK);
    m_text.setCharacterSize(char_size);
    m_text.setPosition(position);
}

/* Finds the path of the font and loads it. */
void game_text::load_font()
{    
    std::string assets_dir = get_assets_path();
    std::string fontPath = assets_dir + "font/Open_Sans/OpenSans.ttf";

    if (!m_open_sans.loadFromFile(fontPath))
    {
        std::cerr << "Could Not Load Font\n";
        std::exit(EXIT_FAILURE);
    }
}

void game_text::set_text(const std::string &text)
{
    str = text;
    m_text.setString(sf::String::fromUtf8(text.begin(), text.end()));
}

/* Sets the text and the character size. */
void game_text::set_text(const std::string &text, uint32_t char_size)
{
    str = text;
    m_text.setString(sf::String::fromUtf8(text.begin(), text.end()));
    m_text.setCharacterSize(char_size);
}

/* Sets the text, the character size and the position of the text. */
void game_text::set_text(const std::string &text, uint32_t char_size, const sf::Vector2f &position)
{
    str = text;
    m_text.setString(sf::String::fromUtf8(text.begin(), text.end()));
    m_text.setCharacterSize(char_size);
    m_text.setPosition(position);
}

void game_text::set_char_size(uint32_t char_size)
{
    m_text.setCharacterSize(char_size);
}

void game_text::set_position(const sf::Vector2f &position)
{
    m_text.setPosition(position);
}

sf::Text game_text::get_text() const
{
    return m_text;
}

sf::Text& game_text::get_text()
{
    return m_text;
}

std::string game_text::get_string() const
{
    return str;
}

std::string& game_text::get_string()
{
    return str;
}

/* Draws the text. */
void game_text::draw(sf::RenderWindow &window) const
{
    window.draw(m_text);
}


/* Sets the size and color of the box. */
/* adicionar mais coisa*/
text_box::text_box(const std::string &text, uint32_t char_size, const sf::Vector2f &position) : game_text(text, char_size, position)
{
    m_box.setFillColor(TRANSPARENT_BLACK);
    m_box.setSize({465.f, 45.f});

    sf::FloatRect bounds = m_box.getLocalBounds();
    m_box.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

/* Returns true if the box was clicked. */
bool text_box::is_box_clicked(sf::RenderWindow &window) const
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
        m_box.getGlobalBounds().contains((sf::Vector2f) sf::Mouse::getPosition(window)))
    {
        return true;
    }
    
    return false;
}

/* Used for the backwards key. */
void text_box::delete_last_char()
{
    std::string t = m_text_string;
    t.pop_back();

    m_text_string.clear();
    m_text_string = t;

    m_text.setString(m_text_string);
}

/* Will handle the keys pressed. */
void text_box::input_handler(uint32_t typed_char)
{
    if (typed_char == BACKSPACE)
    {
        if (!m_text_string.empty())
            delete_last_char();
    }
    else if (typed_char == TAB)
    {
        for (int i = 0; i < 4; i++)
            m_text_string.push_back(' ');
    }
    else
    {
        m_text_string.push_back(static_cast<char> (typed_char));
    }
    
    m_text.setString(m_text_string + "_");
}

void text_box::set_box_position(const sf::Vector2f &position)
{
    m_box.setPosition(position);
}

/* If the box was clicked then it is selected to write on. */
void text_box::set_selected(sf::RenderWindow &window)
{
    if (is_box_clicked(window))
    {
        m_selected = true;
        m_text.setString(m_text_string + "_");
    }
    else
        m_selected = false;

    if (!m_selected)
    {
        std::string t = m_text_string;
        m_text.setString(t);
    }
}

/* If the key was typed it will handle the input. */
void text_box::typed(uint32_t unicode)
{
    if (m_selected)
    {
        if ((unicode > 31 && unicode < 128) || (unicode == TAB) || (unicode == BACKSPACE))
        {
            if (static_cast<int> (m_text_string.length()) < m_limit || unicode == BACKSPACE)
                input_handler(unicode);
        }
    }
}

/* Returns true if the box is selected to write on. */
bool text_box::is_selected() const
{
    return m_selected;
}

std::string text_box::get_text_string() const
{
    return m_text_string;
}

std::pair<float, float> text_box::get_box_sizes() const
{
    return {m_box.getGlobalBounds().width, m_box.getGlobalBounds().height};
}

/* Draws the box and the text. */
void text_box::draw(sf::RenderWindow &window) const
{
    window.draw(m_box);
    window.draw(m_text);
}

/* Clears the text written on the box. */
void text_box::clear(bool deselect)
{
    if (deselect)
    {
        m_selected = !deselect;
        m_text.setString("");
    }
    else
        m_text.setString("_");

    m_text_string.clear();
}