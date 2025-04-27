#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

enum CHARACTAR_SIZE
{
	USER_INPUT = 12,
	LABALE = 18,
	LARGE = 24,
	EXTRA_LARGE = 36
};

class ResourceManager
{
public:
	~ResourceManager() = default;

	static ResourceManager& instance();
	sf::Text getTextFont();

private:
	ResourceManager();
	ResourceManager(const ResourceManager& other) = default;
	ResourceManager& operator=(const ResourceManager&) = default;

	sf::Font m_font;
};