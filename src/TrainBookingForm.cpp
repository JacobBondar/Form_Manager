#include "TrainBookingForm.h"
#include "DialogueManager.h"
#include <iostream>
#include <ctime>

//-----------------------------------------------------------------------------

TrainBookingForm::TrainBookingForm(DialogueManager* manager)
    : BookingForm(manager) 
{
    m_fieldLabels.insert(m_fieldLabels.end(), 
                        {
                            "Departure Station:", "Arrival Station:", 
                            "Departure Date:", "Number of Passengers:",
                            "Preferred Time:", "Special Requests:",
                        });

    int yOffset = START_Y;
    createFields(yOffset);
    createTrainButtons(yOffset);
    yOffset = 625;
    createFinishButtons(yOffset);
    setDefaultValues();
}

//-----------------------------------------------------------------------------

void TrainBookingForm::createFields(int yOffset)
{
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidName, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidID, uint32_t>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidLocation, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidEmail, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidName, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidStationComapare, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidDate, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidNumPass, int>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidTime, std::string>>(yOffset, this));
    yOffset += 50;
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidRequest, std::string>>(yOffset, this));
}

//-----------------------------------------------------------------------------

void TrainBookingForm::createTrainButtons(int yOffset)
{
    yOffset += 450;
	createSemiButtons(yOffset, 10, m_timeSelection, { 100 , 30 }, 105);

    yOffset += 100;
    createSemiButtons(yOffset, 10, m_specialSelection, { 150 , 30 }, 160);
}

//-----------------------------------------------------------------------------

void TrainBookingForm::setDefaultValues()
{
    m_inputBoxes[DATE_CELL]->setString(setDefaultDate());
    m_inputBoxes[TIME_CELL]->setString("Don't Care");
    m_inputBoxes[REQUEST_CELL]->setString("None");
}

//-----------------------------------------------------------------------------

void TrainBookingForm::drawButtonsTrain(sf::RenderWindow& window) const
{
    int index = 0;

    drawSemiButtons(window, m_timeSelection, index);
    drawSemiButtons(window, m_specialSelection, index);
}

//-----------------------------------------------------------------------------

void TrainBookingForm::drawRectangles(int yOffset, sf::RenderWindow& window) const
{
    for (std::size_t i = 0; i < m_fieldLabels.size(); ++i, yOffset += 50)
    {
        sf::Text label;
        if (i == m_fieldLabels.size() - 1)
        {
            label = setDefaultText(m_fieldLabels[i], 18, sf::Color(60, 60, 60), 
                                   sf::Vector2f(20, yOffset + 50));
        }
        else label = setDefaultText(m_fieldLabels[i], 18, sf::Color(60, 60, 60), 
                                    sf::Vector2f(20, yOffset));
        window.draw(label);
    }
    drawButtonsTrain(window);
}

//-----------------------------------------------------------------------------

std::string TrainBookingForm::getCompareField() const
{
    return m_inputBoxes[STATION_DEP]->getString();
}

//-----------------------------------------------------------------------------

std::vector<std::string> TrainBookingForm::getNames() const
{
    std::vector<std::string> names;
    
    getSemiNames(names, m_timeSelection);
    names.emplace_back("\0");
    getSemiNames(names, m_specialSelection);

    return names;
}

//-----------------------------------------------------------------------------

std::string TrainBookingForm::getTypeName() const
{
    return "Quiet Zone\nFamily Section";
}

//-----------------------------------------------------------------------------

int TrainBookingForm::getAmount() const
{
    return stoi(m_inputBoxes[PASS_CELL]->getString());
}

//-----------------------------------------------------------------------------

std::string TrainBookingForm::getValidateName() const
{
    return "Family Section\nFirst Class";
}

//-----------------------------------------------------------------------------

void TrainBookingForm::checkClickMouse(sf::Vector2f mousePos)
{
    int index = 0;

    if (checkSemiButtons(m_timeSelection, index, PREFFERED_TIME, mousePos)) return;
    checkSemiButtons(m_specialSelection, index, SPECIAL_REQUEST, mousePos);
}