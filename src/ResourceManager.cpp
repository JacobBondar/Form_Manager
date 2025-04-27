#include "ResourceManager.h"

//-----------------------------------------------------------------------------

ResourceManager& ResourceManager::instance()
{
    static ResourceManager instance;
    return instance;
}

//-----------------------------------------------------------------------------

ResourceManager::ResourceManager()
{
	sf::Font font;
	m_font.loadFromFile("C:/Windows/Fonts/arialbd.ttf");	
}

//-----------------------------------------------------------------------------

sf::Text ResourceManager::getTextFont()
{
    sf::Text textReturn("", m_font);
    textReturn.setOutlineColor(sf::Color::White);
    textReturn.setFillColor(sf::Color::Black);

    return textReturn;
}