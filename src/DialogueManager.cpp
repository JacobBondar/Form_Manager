#include "DialogueManager.h"

DialogueManager::DialogueManager() : activeForm(nullptr), isFormOpen(false) {}

void DialogueManager::setActiveForm(std::unique_ptr<BookingForm> form) {
    if (isFormOpen) return;  // Prevent multiple openings
    isFormOpen = true;

    activeForm = std::move(form);
    std::cout << "Opening " << activeForm->getFormType() << " form...\n";

    if (!formWindow.isOpen()) {  // ✅ Fix: Prevent reopening if already open

        formWindow.create(sf::VideoMode(650, 850), activeForm->getFormType());
    }
}

void DialogueManager::closeForm() {
    if (formWindow.isOpen()) {
        formWindow.close();   // ✅ Close the window
    }

    if (activeForm) {
        activeForm.reset();  // ✅ Properly delete the form
        activeForm = nullptr; // ✅ Explicitly set to nullptr to prevent dangling pointer
    }

    isFormOpen = false;   // ✅ Allow opening a new form later
    std::cout << "Returned to Main Menu.\n";
}


void DialogueManager::handleFormEvents() {
    if (!isFormOpen || !formWindow.isOpen() || !activeForm) {
        return; // ✅ Avoid handling events if form is closed
    }

    sf::Event event;
    while (formWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            closeForm();  // ✅ Use closeForm() instead of just closing the window
            return;
        }

        if (activeForm) {  // ✅ Check again before accessing
            activeForm->handleInput(event);
        }
    }

    if (activeForm) {  // ✅ Prevent access if deleted
        formWindow.clear(sf::Color::White);
        activeForm->render(formWindow);
        formWindow.display();
    }
}

