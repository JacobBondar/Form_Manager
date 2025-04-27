#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class Button
{
public:
	Button(int yOffset, int carTypeButtonX, const std::string& str, sf::Vector2f size);
	void drawButton(sf::RenderWindow& window, bool active);
	bool contains(sf::Vector2f mousePos);
	std::string getString() const { return m_label.getString(); }

private:
	sf::Text m_label;
	sf::RectangleShape m_rect;

	void drawLabel(sf::RenderWindow& window, bool active);
	void drawText(sf::RenderWindow& window, bool active);
};