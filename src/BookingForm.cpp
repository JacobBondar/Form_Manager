#include "BookingForm.h"
#include "DialogueManager.h"
#include <iostream>
#include <ctime>

//-----------------------------------------------------------------------------

BookingForm::BookingForm(DialogueManager* manager) : m_formManager(manager) {
    m_fieldLabels = { "Name:", "ID:", "Address:", "Email:" };
}

//-----------------------------------------------------------------------------

sf::Text BookingForm::setDefaultText(std::string str, int size, sf::Color color, 
                                     sf::Vector2f pos) const
{
	sf::Text text = ResourceManager::instance().getTextFont();
    text.setString(str);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setPosition(pos);

	return text;
}

//-----------------------------------------------------------------------------

sf::RectangleShape BookingForm::setDefaultRectangle(sf::Vector2f size, sf::Vector2f pos, 
                                                    sf::Color fillColor, float outlineThickness, 
                                                    sf::Color outlineColor) const
{
	sf::RectangleShape rect(size);
	rect.setPosition(pos);
	rect.setFillColor(fillColor);
	rect.setOutlineThickness(outlineThickness);
	rect.setOutlineColor(outlineColor);

	return rect;
}

//-----------------------------------------------------------------------------

void BookingForm::createFinishButtons(int& yOffset)
{
	m_finishButtons.emplace_back(std::make_unique<ButtonFinish>
                                (sf::Vector2f(20, yOffset + 50), "DONE", 
                                 sf::Color(50, 150, 50)));

    m_finishButtons.emplace_back(std::make_unique<ButtonFinish>
                                (sf::Vector2f(200, yOffset + 50), "CANCEL", 
                                 sf::Color(180, 0, 0)));
}

//-----------------------------------------------------------------------------

void BookingForm::drawFinishButtons(sf::RenderWindow& window) const
{
	for (std::size_t i = 0; i < m_finishButtons.size(); ++i)
	{
		m_finishButtons[i]->drawButton(window);
	}
}

//-----------------------------------------------------------------------------

void BookingForm::drawLabelsAndInputFields(sf::RenderWindow& window, int& yOffset,
                                           bool cursorVisible) const
{
    drawLabels(window);

    for (std::size_t i = 0; i < m_inputBoxes.size(); ++i)
    {
        m_inputBoxes[i]->drawText(window, i == m_activeField && cursorVisible);
    }
}

//-----------------------------------------------------------------------------

void BookingForm::drawLabels(sf::RenderWindow& window) const
{
    for (std::size_t i = 0; i < m_inputBoxes.size(); ++i)
    {
        m_inputBoxes[i]->drawLabel(window, i == m_activeField);
    }
}

//-----------------------------------------------------------------------------

void BookingForm::drawButtons(sf::RenderWindow& window) const
{
    for (int i = 0; i < m_inputButtons.size(); ++i)
    {
        m_inputButtons[i]->drawButton(window, checkSelected(i));
    }
}

//-----------------------------------------------------------------------------

void BookingForm::drawTitle(sf::RenderWindow& window) const
{
    sf::Text title = setDefaultText(getFormType() + " Form", 26, 
                                    sf::Color(20, 20, 20), sf::Vector2f(20, 10));
    title.setStyle(sf::Text::Bold);
    window.draw(title);
}

//-----------------------------------------------------------------------------

bool BookingForm::checkUserClick(sf::Vector2f mousePos)
{
    for (std::size_t i = 0; i < m_inputBoxes.size(); ++i) 
    {
        if (m_inputBoxes[i]->contains(mousePos)) 
        {
            m_activeField = i;
            return true;
        }
    }

    for (std::size_t i = 0; i < m_finishButtons.size(); ++i) 
    {
        if (m_finishButtons[i]->contains(mousePos)) 
        {
            if (i == 0) // "DONE" button
            {
                if(isValidInfo()) openConfirmationWindow();
            }
            else if (i == 1) // "CANCEL" button
            {
                closeFormManager();
            }
            return true;
        }
    }
    return false;
}

//-----------------------------------------------------------------------------

bool BookingForm::isValidInfo() const
{
	for (std::size_t index = 0; index < m_inputBoxes.size(); ++index)
	{
		if (m_inputBoxes[index]->getString().empty())
		{
			std::cout << "Please fill in all fields." << std::endl;
			return false;
		}
	}
	return true;
}

//-----------------------------------------------------------------------------

void BookingForm::openConfirmationWindow()
{
    std::vector<std::string> fieldValid;

    for (int index = 0; index < m_inputBoxes.size(); ++index)
    {
        fieldValid.push_back("");
        if (!m_inputBoxes[index]->validate()) fieldValid[index] = m_inputBoxes[index]->getError();
    }

	WindowConfirmation confirmWindow(getFormType(), this, fieldValid);
	confirmWindow.openWindow();
}

//-----------------------------------------------------------------------------

void BookingForm::closeFormManager() const
{
    m_formManager->closeForm();
}

//-----------------------------------------------------------------------------

std::string BookingForm::getField(int index) const
{
    return m_fieldLabels[index] + " " + m_inputBoxes[index]->getString() + "\n";
}

//-----------------------------------------------------------------------------

std::string BookingForm::setDefaultDate() const
{
    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);
    std::string day = "-", month = "-";

    if (1 + ltm.tm_mon < 10)  month += "0";
    if (ltm.tm_mday < 10)  day += "0";

    return std::to_string(1900 + ltm.tm_year) + month +
        std::to_string(1 + ltm.tm_mon) + day +
        std::to_string(ltm.tm_mday);
}

//-----------------------------------------------------------------------------

std::vector<std::string> BookingForm::getVectorTypes() const
{
    std::vector<std::string> temp;
    for (auto& input : m_inputButtons)
    {
        temp.push_back(input->getString());
    }
    return temp;
}

//-----------------------------------------------------------------------------

void BookingForm::checkUserSpecial(sf::Event event)
{
    if (event.key.code == sf::Keyboard::Tab)
    {
        m_activeField = (m_activeField + 1) % m_inputBoxes.size();
    }
    if (event.key.code == sf::Keyboard::Return)
    {
        std::cout << "Entered Data: ";

        for (int i = 0; i < m_inputBoxes.size(); ++i)
        {
            std::cout << m_inputBoxes[i]->getString() << " ";
        }
        std::cout << std::endl;
    }
}

//-----------------------------------------------------------------------------

void BookingForm::createButtons(int& yOffset, float addX, sf::Vector2f sizeRec)
{
    float typeButtonX = 10;
	int size = getSize();

    for (int i = 0; i < size; ++i, typeButtonX += addX) //105
    {
        m_inputButtons.emplace_back(std::make_unique<Button>
            (yOffset, typeButtonX, getString(i), sizeRec));
    }
}

//-----------------------------------------------------------------------------

void BookingForm::updateFieldString(std::string text, bool active,
                                    int index, int value) const
{
    if (active)
    {
        if (m_inputBoxes[value]->getString() != "") m_inputBoxes[value]->addToString("|");
        m_inputBoxes[value]->addToString(text);
    }
}

//-----------------------------------------------------------------------------

void BookingForm::handleInput(sf::Event event)
{
    if (event.type == sf::Event::TextEntered) m_inputBoxes[m_activeField]->checkUserInput(event);

    else if (event.type == sf::Event::KeyPressed) checkUserSpecial(event);

    else if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        if (checkUserClick(mousePos)) return;

        checkClickMouse(mousePos);
    }
}

//-----------------------------------------------------------------------------

void BookingForm::checkClickMouse(sf::Vector2f mousePos)
{
    for (std::size_t i = 0; i < m_inputButtons.size(); ++i)
    {
        if (m_inputButtons[i]->contains(mousePos)) 
        {
            doClicked(i);
            return;
        }
    }
}

//-----------------------------------------------------------------------------

void BookingForm::render(sf::RenderWindow& window) const
{
    window.clear(sf::Color(235, 235, 235));
    bool cursorVisible = (m_cursorTimer.getElapsedTime().asMilliseconds() % 1000 < 500);
    int yOffset = START_Y;

    drawTitle(window);
    drawLabelsAndInputFields(window, yOffset, cursorVisible);

    drawRectangles(yOffset, window);
    drawFinishButtons(window);
}

//-----------------------------------------------------------------------------

void BookingForm::drawRectangles(int yOffset, sf::RenderWindow& window) const
{
    for (std::size_t i = 0; i < m_fieldLabels.size(); ++i, yOffset += 50)
    {
        sf::Text label = setDefaultText(m_fieldLabels[i], 18, sf::Color(60, 60, 60), 
                                        sf::Vector2f(20, yOffset));
        window.draw(label);
    }
    drawButtons(window);
}