#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <SFML/Graphics.hpp>
#include "DialogueManager.h"

class UIManager {
private:
    sf::RenderWindow& window;
    DialogueManager& formManager;

    // ✅ Fix: Declare buttons and texts
    sf::Font font;
    sf::RectangleShape buttonFlight, buttonHotel, buttonCar, buttonEvent, buttonTrain;
    sf::Text textFlight, textHotel, textCar, textEvent, textTrain;

    // ✅ Fix: Declare setupButton
    void setupButton(sf::RectangleShape& button, sf::Text& text, const std::string& label, float y);

public:
    UIManager(sf::RenderWindow& win, DialogueManager& dManager);
    void handleEvent(const sf::Event& event);
    void render();
};

#endif // UIMANAGER_H
