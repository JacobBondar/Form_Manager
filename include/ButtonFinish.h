#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class ButtonFinish
{
public:
	ButtonFinish(sf::Vector2f pos, const std::string& str, sf::Color fillColor);
	void drawButton(sf::RenderWindow& window);
	bool contains(sf::Vector2f mousePos);

private:
	sf::Text m_label;
	sf::RectangleShape m_rect;

	void drawLabel(sf::RenderWindow& window) { window.draw(m_rect); };
	void drawText(sf::RenderWindow& window) { window.draw(m_label); };
};