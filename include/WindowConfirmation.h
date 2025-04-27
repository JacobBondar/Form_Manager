#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ResourceManager.h"

class BookingForm;
class WindowConfirmation
{
public:
	WindowConfirmation(const std::string& formTitle, BookingForm* bookingForm, 
					   std::vector<std::string> fieldError);
	~WindowConfirmation() = default;

	void openWindow();

private:
	std::vector<std::string> m_fieldError;
	sf::RenderWindow m_confirmWindow;
	BookingForm* m_bookingForm;
	std::string m_formTitle;

	void setConfirmation(sf::RectangleShape& approveButton, sf::RectangleShape& cancelButton);
	void setRectangle(sf::RectangleShape& approveButton, sf::Vector2f pos, sf::Color color) const;
	sf::Text setText(int size, std::string txt, sf::Color color, sf::Vector2f pos) const;
	void getStrings(std::string& bookingInfo, std::string& errorText) const;
	void drawConfirmation(sf::Text details, sf::Text errors, sf::Text title,
						  sf::RectangleShape cancelButton, sf::Text cancelText,
						  sf::RectangleShape approveButton, sf::Text approveText);
	void waitForEvent(sf::RectangleShape approveButton,
					  sf::RectangleShape cancelButton, bool valid);
	void checkPressed(sf::RectangleShape approveButton,
					  sf::RectangleShape cancelButton,
					  bool valid, sf::Vector2f mousePos);
	void setTexts(sf::Text& title, sf::Text& approveText,
				  sf::Text& cancelText, sf::Text& errors,
				  sf::Text& details, std::string bookingInfo,
				  std::string errorText) const;
};