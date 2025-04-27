#include "EventBookingForm.h"
#include "DialogueManager.h"
#include <iostream>
#include <ctime>  // For getting current date

EventBookingForm::EventBookingForm(sf::RenderWindow& win, DialogueManager* manager)
    : BookingForm(manager) {  // ✅ Calls base constructor
    m_fieldLabels.insert(m_fieldLabels.end(), {
        "Event Name:", "Venue:", "Event Date:",
        "Number of Tickets:","Wheelchair Accessibility?", "Seating Preference:"
        });

    userInput.resize(m_fieldLabels.size(), "");  // ✅ Resize input fields
    setDefaultValues();
}

void EventBookingForm::setDefaultValues() {
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);  // ✅ Safe alternative to localtime()

    userInput[6] = std::to_string(1900 + ltm.tm_year) + "-" +
        std::to_string(1 + ltm.tm_mon) + "-" +
        std::to_string(ltm.tm_mday);
    userInput[9] = "General Admission";
}

std::string EventBookingForm::getFormType() const {
    return "Event Booking";
}

void EventBookingForm::render(sf::RenderWindow& window) const {
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arialbd.ttf");

    window.clear(sf::Color(235, 235, 235));

    // ✅ Title
    sf::Text title("Event Booking Form", font, 26);
    title.setFillColor(sf::Color(20, 20, 20));
    title.setStyle(sf::Text::Bold);
    title.setPosition(20, 10);
    window.draw(title);

    bool cursorVisible = (m_cursorTimer.getElapsedTime().asMilliseconds() % 1000 < 500);

    // ✅ Render input fields dynamically
    int yOffset = 60;
    for (std::size_t i = 0; i < m_fieldLabels.size(); ++i) {
        sf::Text label(m_fieldLabels[i], font, 18);
        label.setFillColor(sf::Color(60, 60, 60));
        label.setPosition(20, yOffset);
        window.draw(label);

        sf::RectangleShape inputBox(sf::Vector2f(250, 35));
        inputBox.setPosition(250, yOffset - 5);
        inputBox.setFillColor(sf::Color::White);
        inputBox.setOutlineThickness(2);
        inputBox.setOutlineColor(i == m_activeField ? sf::Color(0, 120, 255) : sf::Color(160, 160, 160));
        window.draw(inputBox);

        std::string displayText = userInput[i];
        if (i == m_activeField && cursorVisible) {
            displayText += "|";
        }

        sf::Text inputText(displayText, font, 16);
        inputText.setFillColor(sf::Color::Black);
        inputText.setPosition(255, yOffset);
        window.draw(inputText);

        yOffset += 50;
    }
    yOffset -= 10;
    float seatingTypeButtonX = 10;
    for (int i = 0; i < SeatingTypeSelection.size(); ++i) {
        sf::RectangleShape seatButton(sf::Vector2f(150, 30));
        seatButton.setPosition(seatingTypeButtonX, yOffset);
        seatButton.setFillColor(selectedSeatingType == i ? sf::Color(0, 120, 255) : sf::Color::White);  // ✅ Highlight selected
        seatButton.setOutlineThickness(2);
        seatButton.setOutlineColor(sf::Color(160, 160, 160));
        window.draw(seatButton);

        sf::Text roomText(SeatingTypeSelection[i], font, 16);
        roomText.setFillColor(selectedSeatingType == i ? sf::Color::White : sf::Color::Black);
        roomText.setPosition(seatingTypeButtonX + 5, yOffset + 5);
        window.draw(roomText);

        seatingTypeButtonX += 160;  // ✅ Increased spacing
    }
    // ✅ "Done" and "Cancel" Buttons (positioned dynamically)
     yOffset += 50;

    sf::RectangleShape submitButton(sf::Vector2f(140, 40));
    submitButton.setPosition(20, yOffset);
    submitButton.setFillColor(sf::Color(50, 150, 50));
    window.draw(submitButton);

    sf::Text submitText("DONE", font, 20);
    submitText.setFillColor(sf::Color::White);
    submitText.setPosition(50, yOffset + 10);
    window.draw(submitText);

    sf::RectangleShape cancelButton(sf::Vector2f(140, 40));
    cancelButton.setPosition(200, yOffset);
    cancelButton.setFillColor(sf::Color(180, 0, 0));
    window.draw(cancelButton);

    sf::Text cancelText("CANCEL", font, 20);
    cancelText.setFillColor(sf::Color::White);
    cancelText.setPosition(230, yOffset + 10);
    window.draw(cancelText);
}

void EventBookingForm::handleInput(sf::Event event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b' && !userInput[m_activeField].empty()) {
            userInput[m_activeField].pop_back();
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 128) {
            userInput[m_activeField] += static_cast<char>(event.text.unicode);
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Tab) {
            m_activeField = (m_activeField + 1) % userInput.size();
        }
        if (event.key.code == sf::Keyboard::Return) {
            std::cout << "Entered Data: ";
            for (const auto& field : userInput) std::cout << field << " ";
            std::cout << std::endl;
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        int yOffset = 60;

        for (std::size_t i = 0; i < m_fieldLabels.size(); ++i) {
            sf::FloatRect inputBoxBounds(250, yOffset - 5, 250, 35);
            if (inputBoxBounds.contains(mousePos)) {
                m_activeField = i;
                return;
            }
            yOffset += 50;
        }
        // ✅ Handle Seating Type Button Click     
        yOffset -= 10;    
        float seatingButtonX = 10;
        for (int i = 0; i < SeatingTypeSelection.size(); ++i) {
            sf::FloatRect timeButtonBounds(seatingButtonX, yOffset, 150, 30);
            if (timeButtonBounds.contains(mousePos)) {
                selectedSeatingType = i;
                //Update the "Room Type" input box
                userInput[9] = SeatingTypeSelection[i];

                return;
            }
            seatingButtonX += 160;  // Move to next button
        }

        yOffset += 50;

        if (mousePos.x >= 20 && mousePos.x <= 160 && mousePos.y >= yOffset && mousePos.y <= yOffset + 40) {
            std::cout << "Event Booking Confirmed!\n";
            
            WindowConfirmation confirmWindow(getFormType(), this, std::vector<std::string>());
            confirmWindow.openWindow();
            return;
        }

        if (mousePos.x >= 200 && mousePos.x <= 340 && mousePos.y >= yOffset && mousePos.y <= yOffset + 40) {
            std::cout << "Cancelled Event Booking\n";
            closeFormManager();
            return;
        }
    }
}