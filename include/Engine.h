#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include "UIManager.h"
#include "DialogueManager.h"

class Engine {
private:
    sf::RenderWindow window;
    UIManager uiManager;
    DialogueManager dialogueManager;

public:
    Engine();
    void run();  
};

#endif // ENGINE_H
