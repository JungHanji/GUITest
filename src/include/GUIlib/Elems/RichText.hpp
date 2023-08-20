//https://github.com/skyrpex/RichText/

/*
Example

sf::Font font;
font.loadFromFile("FreeMono.ttf");

sfe::RichText text(font);
text << sf::Text::Bold       << sf::Color::Cyan  << "This "
        << sf::Text::Italic     << sf::Color::White << "is\nan\n"
        << sf::Text::Regular    << sf::Color::Green << "example"
        << sf::Color::White     << ".\n"
        << sf::Text::Underlined << "It looks good!\n" << sf::Text::StrikeThrough
        << sfe::Outline{ sf::Color::Blue, 3.f } << "Really good!";

text.setCharacterSize(25);
text.setPosition(400, 300);
text.setOrigin(text.getGlobalBounds().width / 2.f, text.getGlobalBounds().height / 2.f);
*/

#pragma once
////////////////////////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////////////////////////
#include <cassert>
#include <cmath>


//////////////////////////////////////////////////////////////////////////
// Headers
//////////////////////////////////////////////////////////////////////////
#include <vector>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics.hpp>

namespace sf
{
class Font;
class String;
template <class T> class Rect;
typedef Rect<float> FloatRect;
}

namespace sfe
{
struct TextStroke
{
    sf::Color fill = sf::Color::White;
    sf::Color outline = sf::Color::Transparent;
    float thickness = 0.f;
};

struct Outline
{
    sf::Color outline = sf::Color::Transparent;
    float thickness = 0.f;
};

class RichText : public sf::Drawable, public sf::Transformable
{
public:
    //////////////////////////////////////////////////////////////////////////
    // Nested class that represents a single line
    //////////////////////////////////////////////////////////////////////////
    class Line : public sf::Transformable, public sf::Drawable
    {
    public:
        //////////////////////////////////////////////////////////////////////
        // Set a character's color.
        // NOTE: Attempting to access a character outside of the line bounds
        // causes a crash.
        //////////////////////////////////////////////////////////////////////
        void setCharacterColor(std::size_t pos, sf::Color color);

        //////////////////////////////////////////////////////////////////////
        // Set a character's style
        // NOTE: Attempting to access a character outside of the line bounds
        // causes a crash.
        //////////////////////////////////////////////////////////////////////
        void setCharacterStyle(std::size_t pos, sf::Text::Style style);

        //////////////////////////////////////////////////////////////////////
        // Set a character
        // NOTE: Attempting to access a character outside of the line bounds
        // causes a crash.
        //////////////////////////////////////////////////////////////////////
        void setCharacter(std::size_t pos, sf::Uint32 character);

        //////////////////////////////////////////////////////////////////////
        // Set character size
        //////////////////////////////////////////////////////////////////////
        void setCharacterSize(unsigned int size);

        //////////////////////////////////////////////////////////////////////
        // Set font
        //////////////////////////////////////////////////////////////////////
        void setFont(const sf::Font &font);

        //////////////////////////////////////////////////////////////////////
        // Get the length of the line
        //////////////////////////////////////////////////////////////////////
        std::size_t getLength() const;

        //////////////////////////////////////////////////////////////////////
        // Get a character's color
        // NOTE: Attempting to access a character outside of the line bounds
        // causes a crash.
        //////////////////////////////////////////////////////////////////////
        sf::Color getCharacterColor(std::size_t pos) const;

        //////////////////////////////////////////////////////////////////////
        // Get a character's style
        // NOTE: Attempting to access a character outside of the line bounds
        // causes a crash.
        //////////////////////////////////////////////////////////////////////
        sf::Uint32 getCharacterStyle(std::size_t pos) const;

        //////////////////////////////////////////////////////////////////////
        // Get a character
        // NOTE: Attempting to access a character outside of the line bounds
        // causes a crash
        //////////////////////////////////////////////////////////////////////
        sf::Uint32 getCharacter(std::size_t pos) const;

        //////////////////////////////////////////////////////////////////////
        // Get texts
        //////////////////////////////////////////////////////////////////////
        const std::vector<sf::Text> &getTexts() const;

        //////////////////////////////////////////////////////////////////////
        // Append text
        //////////////////////////////////////////////////////////////////////
        void appendText(sf::Text text);

        //////////////////////////////////////////////////////////////////////
        // Get local bounds
        //////////////////////////////////////////////////////////////////////
        sf::FloatRect getLocalBounds() const;

        //////////////////////////////////////////////////////////////////////
        // Get global bounds
        //////////////////////////////////////////////////////////////////////
        sf::FloatRect getGlobalBounds() const;

    protected:
        //////////////////////////////////////////////////////////////////////
        // Draw
        //////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        //////////////////////////////////////////////////////////////////////
        // Get the index of the sf::Text containing the pos'th character.
        // Also changes pos to the position of the character in the sf::Text.
        //////////////////////////////////////////////////////////////////////
        std::size_t convertLinePosToLocal(std::size_t &pos) const;

        //////////////////////////////////////////////////////////////////////
        // Split a string to isolate the given character
        // into a string of its own for individual formatting
        //////////////////////////////////////////////////////////////////////
        void isolateCharacter(std::size_t pos);

        //////////////////////////////////////////////////////////////////////
        // Update geometry
        //////////////////////////////////////////////////////////////////////
        void updateGeometry() const;

        //////////////////////////////////////////////////////////////////////
        // Update geometry for a given text
        //////////////////////////////////////////////////////////////////////
        void updateTextAndGeometry(sf::Text &text) const;

        //////////////////////////////////////////////////////////////////////
        // Member data
        //////////////////////////////////////////////////////////////////////
        mutable std::vector<sf::Text> m_texts; ///< List of texts
        mutable sf::FloatRect m_bounds;        ///< Local bounds
    };

    //////////////////////////////////////////////////////////////////////////
    // Constructor
    //////////////////////////////////////////////////////////////////////////
    RichText();

    //////////////////////////////////////////////////////////////////////////
    // Constructor
    //////////////////////////////////////////////////////////////////////////
    RichText(const sf::Font &font);

    //////////////////////////////////////////////////////////////////////////
    // Operators
    //////////////////////////////////////////////////////////////////////////
    RichText & operator << (const TextStroke &stroke);
    RichText & operator << (const Outline &outline);
    RichText & operator << (const sf::Color &color);
    RichText & operator << (sf::Text::Style style);
    RichText & operator << (const sf::String &string);

    //////////////////////////////////////////////////////////////////////////
    // Set the color of a character.
    // Attempting to access a character outside of the bounds causes a crash.
    //////////////////////////////////////////////////////////////////////////
    void setCharacterColor(std::size_t line, std::size_t pos, sf::Color color);

    //////////////////////////////////////////////////////////////////////////
    // Set the style of a character.
    // Attempting to access a character outside of the bounds causes a crash.
    //////////////////////////////////////////////////////////////////////////
    void setCharacterStyle(std::size_t line, std::size_t pos, sf::Text::Style style);

    //////////////////////////////////////////////////////////////////////////
    // Set a character
    // Attempting to access a character outside of the bounds causes a crash.
    //////////////////////////////////////////////////////////////////////////
    void setCharacter(std::size_t line, std::size_t pos, sf::Uint32 character);

    //////////////////////////////////////////////////////////////////////////
    // Set character size
    //////////////////////////////////////////////////////////////////////////
    void setCharacterSize(unsigned int size);

    //////////////////////////////////////////////////////////////////////////
    // Set font
    //////////////////////////////////////////////////////////////////////////
    void setFont(const sf::Font &font);

    //////////////////////////////////////////////////////////////////////////
    // Clear
    //////////////////////////////////////////////////////////////////////////
    void clear();

    //////////////////////////////////////////////////////////////////////////
    // Get the color of a character.
    // Attempting to access a character outside of the bounds causes a crash.
    //////////////////////////////////////////////////////////////////////////
    sf::Color getCharacterColor(std::size_t line, std::size_t pos) const;

    //////////////////////////////////////////////////////////////////////////
    // Get the style of a character.
    // Attempting to access a character outside of the bounds causes a crash.
    //////////////////////////////////////////////////////////////////////////
    sf::Uint32 getCharacterStyle(std::size_t line, std::size_t pos) const;

    //////////////////////////////////////////////////////////////////////////
    // Get a character
    // Attempting to access a character outside of the bounds causes a crash.
    //////////////////////////////////////////////////////////////////////////
    sf::Uint32 getCharacter(std::size_t line, std::size_t pos) const;

    //////////////////////////////////////////////////////////////////////////
    // Get text list
    //////////////////////////////////////////////////////////////////////////
    const std::vector<Line> &getLines() const;

    //////////////////////////////////////////////////////////////////////////
    // Get character size
    //////////////////////////////////////////////////////////////////////////
    unsigned int getCharacterSize() const;

    //////////////////////////////////////////////////////////////////////////
    // Get font
    //////////////////////////////////////////////////////////////////////////
    const sf::Font *getFont() const;

    //////////////////////////////////////////////////////////////////////////
    // Get local bounds
    //////////////////////////////////////////////////////////////////////////
    sf::FloatRect getLocalBounds() const;

    //////////////////////////////////////////////////////////////////////////
    // Get global bounds
    //////////////////////////////////////////////////////////////////////////
    sf::FloatRect getGlobalBounds() const;

protected:
    //////////////////////////////////////////////////////////////////////////
    // Render
    //////////////////////////////////////////////////////////////////////////
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    //////////////////////////////////////////////////////////////////////////
    // Delegate constructor
    //////////////////////////////////////////////////////////////////////////
    RichText(const sf::Font *font);

    //////////////////////////////////////////////////////////////////////////
    // Creates a sf::Text instance using the current styles
    //////////////////////////////////////////////////////////////////////////
    sf::Text createText(const sf::String &string) const;

    //////////////////////////////////////////////////////////////////////////
    // Update geometry
    //////////////////////////////////////////////////////////////////////////
    void updateGeometry() const;

    //////////////////////////////////////////////////////////////////////////
    // Member data
    //////////////////////////////////////////////////////////////////////////
    mutable std::vector<Line> m_lines; ///< List of lines
    const sf::Font *m_font;            ///< Font
    unsigned int m_characterSize;      ///< Character size
    mutable sf::FloatRect m_bounds;    ///< Local bounds
    TextStroke m_currentStroke;        ///< Last used stroke
    sf::Text::Style m_currentStyle;    ///< Last style used
};

}

namespace sfe
{

////////////////////////////////////////////////////////////////////////////////
void RichText::Line::setCharacterColor(std::size_t pos, sf::Color color)
{
    assert(pos < getLength());
    isolateCharacter(pos);
    std::size_t stringToFormat = convertLinePosToLocal(pos);
    m_texts[stringToFormat].setFillColor(color);
    updateGeometry();
}

////////////////////////////////////////////////////////////////////////////////
void RichText::Line::setCharacterStyle(std::size_t pos, sf::Text::Style style)
{
    assert(pos < getLength());
    isolateCharacter(pos);
    std::size_t stringToFormat = convertLinePosToLocal(pos);
    m_texts[stringToFormat].setStyle(style);
    updateGeometry();
}
////////////////////////////////////////////////////////////////////////////////
void RichText::Line::setCharacter(std::size_t pos, sf::Uint32 character)
{
    assert(pos < getLength());
    sf::Text& text = m_texts[convertLinePosToLocal(pos)];
    sf::String string = text.getString();
    string[pos] = character;
    text.setString(string);
    updateGeometry();
}


////////////////////////////////////////////////////////////////////////////////
void RichText::Line::setCharacterSize(unsigned int size)
{
    for (sf::Text &text : m_texts)
        text.setCharacterSize(size);

    updateGeometry();
}


////////////////////////////////////////////////////////////////////////////////
void RichText::Line::setFont(const sf::Font &font)
{
    for (sf::Text &text : m_texts)
        text.setFont(font);

    updateGeometry();
}


////////////////////////////////////////////////////////////////////////////////
std::size_t RichText::Line::getLength() const
{
    std::size_t count = 0;
    for (sf::Text &text : m_texts)
    {
        count += text.getString().getSize();
    }
    return count;
}


////////////////////////////////////////////////////////////////////////////////
sf::Color RichText::Line::getCharacterColor(std::size_t pos) const
{
    assert(pos < getLength());
    return m_texts[convertLinePosToLocal(pos)].getFillColor();
}


////////////////////////////////////////////////////////////////////////////////
sf::Uint32 RichText::Line::getCharacterStyle(std::size_t pos) const
{
    assert(pos < getLength());
    return m_texts[convertLinePosToLocal(pos)].getStyle();
}


////////////////////////////////////////////////////////////////////////////////
sf::Uint32 RichText::Line::getCharacter(std::size_t pos) const
{
    assert(pos < getLength());
    sf::Text& text = m_texts[convertLinePosToLocal(pos)];
    return text.getString()[pos];
}


////////////////////////////////////////////////////////////////////////////////
const std::vector<sf::Text> &RichText::Line::getTexts() const
{
    return m_texts;
}

////////////////////////////////////////////////////////////////////////////////
void RichText::Line::appendText(sf::Text text)
{
    updateTextAndGeometry(text);
    m_texts.push_back(std::move(text));
}


////////////////////////////////////////////////////////////////////////////////
sf::FloatRect RichText::Line::getLocalBounds() const
{
    return m_bounds;
}


////////////////////////////////////////////////////////////////////////////////
sf::FloatRect RichText::Line::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}


////////////////////////////////////////////////////////////////////////////////
void RichText::Line::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (const sf::Text &text : m_texts)
        target.draw(text, states);
}


////////////////////////////////////////////////////////////////////////////////
std::size_t RichText::Line::convertLinePosToLocal(std::size_t& pos) const
{
    assert(pos < getLength());
    std::size_t arrayIndex = 0;
    for (; pos >= m_texts[arrayIndex].getString().getSize(); ++arrayIndex)
    {
        pos -= m_texts[arrayIndex].getString().getSize();
    }
    return arrayIndex;
}


////////////////////////////////////////////////////////////////////////////////
void RichText::Line::isolateCharacter(std::size_t pos)
{
    std::size_t localPos = pos;
    std::size_t index = convertLinePosToLocal(localPos);
    sf::Text temp = m_texts[index];

    sf::String string = temp.getString();
    if (string.getSize() == 1)
        return;

    m_texts.erase(m_texts.begin() + index);
    if (localPos != string.getSize() - 1)
    {
        temp.setString(string.substring(localPos+1));
        m_texts.insert(m_texts.begin() + index, temp);
    }

    temp.setString(string.substring(localPos, 1));
    m_texts.insert(m_texts.begin() + index, temp);
    
    if (localPos != 0)
    {
        temp.setString(string.substring(0, localPos));
        m_texts.insert(m_texts.begin() + index, temp);
    }
}


////////////////////////////////////////////////////////////////////////////////
void RichText::Line::updateGeometry() const
{
    m_bounds = sf::FloatRect();

    for (sf::Text& text : m_texts)
        updateTextAndGeometry(text);
}


////////////////////////////////////////////////////////////////////////////////
void RichText::Line::updateTextAndGeometry(sf::Text& text) const
{
    // Set text offset
    text.setPosition(m_bounds.width, 0.f);

    // Update bounds
    float lineSpacing = std::floor(text.getFont()->getLineSpacing(text.getCharacterSize()));
    m_bounds.height = std::max(m_bounds.height, lineSpacing);
    m_bounds.width += text.getGlobalBounds().width;
}


////////////////////////////////////////////////////////////////////////////////
RichText::RichText()
    : RichText(nullptr)
{

}


////////////////////////////////////////////////////////////////////////////////
RichText::RichText(const sf::Font& font)
    : RichText(&font)
{

}

////////////////////////////////////////////////////////////////////////////////
RichText& RichText::operator << (const TextStroke& stroke)
{
    m_currentStroke = stroke;
    return *this;
}

RichText& RichText::operator << (const Outline& outline)
{
    m_currentStroke.outline = outline.outline;
    m_currentStroke.thickness = outline.thickness;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
RichText & RichText::operator << (const sf::Color& color)
{
    m_currentStroke.fill = color;
    return *this;
}


////////////////////////////////////////////////////////////////////////////////
RichText & RichText::operator << (sf::Text::Style style)
{
    m_currentStyle = style;
    return *this;
}


////////////////////////////////////////////////////////////////////////////////
std::vector<sf::String> explode(const sf::String& string, sf::Uint32 delimiter)
{
    if (string.isEmpty())
        return std::vector<sf::String>();

    // For each character in the string
    std::vector<sf::String> result;
    sf::String buffer;
    for (sf::Uint32 character : string) {
        // If we've hit the delimiter character
        if (character == delimiter) {
            // Add them to the result vector
            result.push_back(buffer);
            buffer.clear();
        } else {
            // Accumulate the next character into the sequence
            buffer += character;
        }
    }

    // Add to the result if buffer still has contents or if the last character is a delimiter
    if (!buffer.isEmpty() || string[string.getSize() - 1] == delimiter)
        result.push_back(buffer);

    return result;
}


////////////////////////////////////////////////////////////////////////////////
RichText & RichText::operator << (const sf::String& string)
{
    // Maybe skip
    if (string.isEmpty())
        return *this;

    // Explode into substrings
    std::vector<sf::String> subStrings = explode(string, '\n');

    // Append first substring using the last line
    auto it = subStrings.begin();
    if (it != subStrings.end()) {
        // If there isn't any line, just create it
        if (m_lines.empty())
            m_lines.resize(1);

        // Remove last line's height
        Line &line = m_lines.back();
        m_bounds.height -= line.getGlobalBounds().height;

        // Append text
        line.appendText(createText(*it));

        // Update bounds
        m_bounds.height += line.getGlobalBounds().height;
        m_bounds.width = std::max(m_bounds.width, line.getGlobalBounds().width);
    }

    // Append the rest of substrings as new lines
    while (++it != subStrings.end()) {
        Line line;
        line.setPosition(0.f, m_bounds.height);
        line.appendText(createText(*it));
        m_lines.push_back(std::move(line));

        // Update bounds
        m_bounds.height += line.getGlobalBounds().height;
        m_bounds.width = std::max(m_bounds.width, line.getGlobalBounds().width);
    }

    // Return
    return *this;
}


////////////////////////////////////////////////////////////////////////////////
void RichText::setCharacterColor(std::size_t line, std::size_t pos, sf::Color color)
{
    assert(line < m_lines.size());
    m_lines[line].setCharacterColor(pos, color);
    updateGeometry();
}


////////////////////////////////////////////////////////////////////////////////
void RichText::setCharacterStyle(std::size_t line, std::size_t pos, sf::Text::Style style)
{
    assert(line < m_lines.size());
    m_lines[line].setCharacterStyle(pos, style);
    updateGeometry();
}


////////////////////////////////////////////////////////////////////////////////
void RichText::setCharacter(std::size_t line, std::size_t pos, sf::Uint32 character)
{
    assert(line < m_lines.size());
    m_lines[line].setCharacter(pos, character);
    updateGeometry();
}

////////////////////////////////////////////////////////////////////////////////
void RichText::setCharacterSize(unsigned int size)
{
    // Maybe skip
    if (m_characterSize == size)
        return;

    // Update character size
    m_characterSize = size;

    // Set texts character size
    for (Line &line : m_lines)
        line.setCharacterSize(size);

    updateGeometry();
}


////////////////////////////////////////////////////////////////////////////////
void RichText::setFont(const sf::Font& font)
{
    // Maybe skip
    if (m_font == &font)
        return;

    // Update font
    m_font = &font;

    // Set texts font
    for (Line &line : m_lines)
        line.setFont(font);

    updateGeometry();
}


////////////////////////////////////////////////////////////////////////////////
void RichText::clear()
{
    // Clear texts
    m_lines.clear();

    // Reset bounds
    m_bounds = sf::FloatRect();
}


////////////////////////////////////////////////////////////////////////////////
sf::Color RichText::getCharacterColor(std::size_t line, std::size_t pos) const
{
    assert(line < m_lines.size());
    return m_lines[line].getCharacterColor(pos);
}


////////////////////////////////////////////////////////////////////////////////
sf::Uint32 RichText::getCharacterStyle(std::size_t line, std::size_t pos) const
{
    assert(line < m_lines.size());
    return m_lines[line].getCharacterStyle(pos);
}


////////////////////////////////////////////////////////////////////////////////
sf::Uint32 RichText::getCharacter(std::size_t line, std::size_t pos) const
{
    assert(line < m_lines.size());
    return m_lines[line].getCharacter(pos);
}


////////////////////////////////////////////////////////////////////////////////
const std::vector<RichText::Line> &RichText::getLines() const
{
    return m_lines;
}


////////////////////////////////////////////////////////////////////////////////
unsigned int RichText::getCharacterSize() const
{
    return m_characterSize;
}


////////////////////////////////////////////////////////////////////////////////
const sf::Font *RichText::getFont() const
{
    return m_font;
}


////////////////////////////////////////////////////////////
sf::FloatRect RichText::getLocalBounds() const
{
    return m_bounds;
}


////////////////////////////////////////////////////////////
sf::FloatRect RichText::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}


////////////////////////////////////////////////////////////////////////////////
void RichText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (const Line &line : m_lines)
        target.draw(line, states);
}


////////////////////////////////////////////////////////////////////////////////
RichText::RichText(const sf::Font* font)
    : m_font(font),
      m_characterSize(30),
      m_currentStroke{ sf::Color::White, sf::Color::Transparent },
      m_currentStyle(sf::Text::Regular)
{

}


////////////////////////////////////////////////////////////////////////////////
sf::Text RichText::createText(const sf::String& string) const
{
    sf::Text text;
    text.setString(string);
    text.setFillColor(m_currentStroke.fill);
    text.setOutlineColor(m_currentStroke.outline);
    text.setOutlineThickness(m_currentStroke.thickness);
    text.setStyle(m_currentStyle);
    text.setCharacterSize(m_characterSize);
    if (m_font)
        text.setFont(*m_font);

    return text;
}


////////////////////////////////////////////////////////////////////////////////
void RichText::updateGeometry() const
{
    m_bounds = sf::FloatRect();

    for (Line &line : m_lines) {
        line.setPosition(0.f, m_bounds.height);

        m_bounds.height += line.getGlobalBounds().height;
        m_bounds.width = std::max(m_bounds.width, line.getGlobalBounds().width);
    }
}

}
