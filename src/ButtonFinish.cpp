#include "ButtonFinish.h"

//-----------------------------------------------------------------------------

ButtonFinish::ButtonFinish(sf::Vector2f pos, const std::string& str, 
                           sf::Color fillColor) : m_rect(sf::Vector2f(140, 40))
{
    m_rect.setPosition(pos);
    m_rect.setFillColor(fillColor);
    m_rect.setOutlineColor(fillColor);

    m_label = ResourceManager::instance().getTextFont();
    m_label.setString(str);
    m_label.setCharacterSize(20);
    m_label.setFillColor(sf::Color::White);
    m_label.setPosition(pos + sf::Vector2f( 35 , 10 ));
}

//-----------------------------------------------------------------------------

void ButtonFinish::drawButton(sf::RenderWindow& window)
{
	drawLabel(window);
	drawText(window);
}

//-----------------------------------------------------------------------------

bool ButtonFinish::contains(sf::Vector2f mousePos)
{
	return m_rect.getGlobalBounds().contains(mousePos);
}