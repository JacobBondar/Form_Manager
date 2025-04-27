#include "UIManager.h"
#include <iostream>
#include "FlightBookingForm.h"
#include "HotelBookingForm.h"
#include "CarRentalForm.h"
#include "EventBookingForm.h"
#include "TrainBookingForm.h"

UIManager::UIManager(sf::RenderWindow& win, DialogueManager& dManager)
    : window(win), formManager(dManager) {

 
    font.loadFromFile("C:/Windows/Fonts/arialbd.ttf");
    

    // ✅ Fix: Setup all buttons using setupButton()
    setupButton(buttonFlight, textFlight, "Flight Booking", 150);
    setupButton(buttonHotel, textHotel, "Hotel Booking", 220);
    setupButton(buttonCar, textCar, "Car Rental", 290);
    setupButton(buttonEvent, textEvent, "Event Booking", 360);
    setupButton(buttonTrain, textTrain, "Train Booking", 430);

}

// ✅ Fix: Define `setupButton()`
void UIManager::setupButton(sf::RectangleShape& button, sf::Text& text, const std::string& label, float y) {
    button.setSize(sf::Vector2f(300, 50));
    button.setFillColor(sf::Color::Blue);
    button.setPosition(100, y);

    text.setFont(font);  // ✅ Fix: Use class member `font`
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(120, y + 10);
}

// ✅ Fix: Ensure render() uses class member buttons
void UIManager::render() {
    sf::Text title("Travel Booking System", font, 30);
    title.setFillColor(sf::Color::Black);
    title.setStyle(sf::Text::Bold);
    title.setPosition(80, 20);
    window.draw(title);

    // ✅ Draw all buttons
    window.draw(buttonFlight);
    window.draw(textFlight);
    window.draw(buttonHotel);
    window.draw(textHotel);
    window.draw(buttonCar);
    window.draw(textCar);
    window.draw(buttonEvent);
    window.draw(textEvent);
    window.draw(buttonTrain);
    window.draw(textTrain);
}


void UIManager::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        std::cout << "Mouse Clicked at: " << mousePos.x << ", " << mousePos.y << std::endl;  // ✅ Debug log
        
        if (buttonFlight.getGlobalBounds().contains(mousePos)) {
            std::cout << "Flight Booking Button Clicked!" << std::endl;  // ✅ Debug
            formManager.setActiveForm(std::make_unique<FlightBookingForm>(window, &formManager));
        }
        
        if (buttonHotel.getGlobalBounds().contains(mousePos)) {
            std::cout << "Hotel Booking Button Clicked!" << std::endl;
            formManager.setActiveForm(std::make_unique<HotelBookingForm>(window, &formManager));
        }

        if (buttonCar.getGlobalBounds().contains(mousePos)) {
            std::cout << "Car Rental Button Clicked!" << std::endl;
            formManager.setActiveForm(std::make_unique<CarRentalForm>(&formManager));
        }
        
        if (buttonEvent.getGlobalBounds().contains(mousePos)) {
            std::cout << "Event Booking Button Clicked!" << std::endl;
            formManager.setActiveForm(std::make_unique<EventBookingForm>(window, &formManager));
        }
        
        if (buttonTrain.getGlobalBounds().contains(mousePos)) {
            std::cout << "Train Booking Button Clicked!" << std::endl;
            formManager.setActiveForm(std::make_unique<TrainBookingForm>(&formManager));
        }
        
    }
}
