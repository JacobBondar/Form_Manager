#include "FieldBase.h"

//-----------------------------------------------------------------------------

void FieldBase::checkUserInput(sf::Event event)
{
    if (event.text.unicode == '\b' && !m_label.empty()) m_label.pop_back();

    else if (event.text.unicode >= 32 && event.text.unicode < 128) 
    {
        m_label += static_cast<char>(event.text.unicode);

        if (m_label.length() > MAX_LENGTH) 
        {
            m_label.resize(MAX_LENGTH); // keep only the first MAX_LENGTH characters
        }
    }
}

//-----------------------------------------------------------------------------

bool FieldBase::contains(sf::Vector2f mousePos) const
{
    return m_rect.getGlobalBounds().contains(mousePos);
}

//-----------------------------------------------------------------------------

void FieldBase::drawLabel(sf::RenderWindow& window, bool activeRect)
{
    if (activeRect) m_rect.setOutlineColor(sf::Color(0, 120, 255));
    else m_rect.setOutlineColor(sf::Color(160, 160, 160));
    window.draw(m_rect);
}

//-----------------------------------------------------------------------------

void FieldBase::drawText(sf::RenderWindow& window, bool activeText) const
{
    std::string displayText = m_label;
    if (activeText) displayText += "|";

    sf::Text inputText = setText(displayText, 16, sf::Color::Black, 
                                 m_rect.getPosition() + sf::Vector2f{ 5, 5 });
    window.draw(inputText);
}

//-----------------------------------------------------------------------------

sf::Text FieldBase::setText(std::string str, int size, sf::Color color, 
                            sf::Vector2f pos) const
{
    sf::Text text = ResourceManager::instance().getTextFont();
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(pos);

    return text;
}