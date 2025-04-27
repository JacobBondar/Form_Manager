#include "Button.h"

//-----------------------------------------------------------------------------

Button::Button(int yOffset, int carTypeButtonX, 
			   const std::string& str, sf::Vector2f size) : m_rect(size)
{
	m_rect.setPosition(sf::Vector2f(carTypeButtonX, yOffset));
	m_rect.setOutlineThickness(2);
	m_rect.setOutlineColor(sf::Color(160, 160, 160));

	m_label = ResourceManager::instance().getTextFont();
	m_label.setString(str);
	m_label.setCharacterSize(16);
	m_label.setFillColor(sf::Color::Black);
	m_label.setPosition(carTypeButtonX + 10, yOffset + 5);
}

//-----------------------------------------------------------------------------

void Button::drawButton(sf::RenderWindow& window, bool active)
{
	drawLabel(window, active);
	drawText(window, active);
}

//-----------------------------------------------------------------------------

void Button::drawText(sf::RenderWindow& window, bool active)
{
	m_rect.setFillColor(active ? sf::Color(0, 120, 255) : sf::Color::White);
	window.draw(m_label);
}

//-----------------------------------------------------------------------------

void Button::drawLabel(sf::RenderWindow& window, bool active)
{
	m_label.setFillColor(active ? sf::Color::White : sf::Color::Black);
	window.draw(m_rect);
}

//-----------------------------------------------------------------------------

bool Button::contains(sf::Vector2f mousePos)
{
	return m_rect.getGlobalBounds().contains(mousePos);
}