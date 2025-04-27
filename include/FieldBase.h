#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class BookingForm;

const int MAX_LENGTH = 28;

class FieldBase 
{
public:
    FieldBase() : m_rect(sf::Vector2f(350, 35)) {}
    virtual ~FieldBase() = default;
    virtual bool validate() const = 0;
    virtual std::string getError() const = 0;
    virtual std::string getString() const = 0;

    bool contains(sf::Vector2f mousePos) const;
    void checkUserInput(sf::Event event);
    void drawLabel(sf::RenderWindow& window, bool activeRect);
    void drawText(sf::RenderWindow& window, bool activeText) const;
    void setString(const std::string& str) { m_label = str; };
    void addToString(std::string txt) { m_label += txt; };

protected:
    std::string m_label;
    sf::RectangleShape m_rect;

private:
    sf::Text setText(std::string str, int size, sf::Color color, sf::Vector2f pos) const;
};