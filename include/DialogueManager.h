#ifndef DIALOGUEMANAGER_H
#define DIALOGUEMANAGER_H

#include "BookingForm.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

class DialogueManager {
public:
    DialogueManager();
    void setActiveForm(std::unique_ptr<BookingForm> form);
    void handleFormEvents();
    void closeForm();

private:
    std::unique_ptr<BookingForm> activeForm;
    sf::RenderWindow formWindow;
    bool isFormOpen;
};

#endif // DIALOGUEMANAGER_H
