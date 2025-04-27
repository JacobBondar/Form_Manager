#include "FlightBookingForm.h"
#include "DialogueManager.h"
#include <iostream>
#include <ctime>

FlightBookingForm::FlightBookingForm(sf::RenderWindow& win, DialogueManager* manager)
    : BookingForm(manager) 
{ 
    m_fieldLabels.insert(m_fieldLabels.end(), 
                        { 
                            "Departure Airport:", "Arrival Airport:",
                            "Departure Date:",
                            "Preferred Time:" 
                        });
    int yOffset = START_Y;
    createFields(yOffset);
    createButtons(yOffset);
    createFinishButtons(yOffset);
    setDefaultFields();
}

//-----------------------------------------------------------------------------

void FlightBookingForm::createFields(int& yOffset)
{
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidName, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidID, uint32_t>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidLocation, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidEmail, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidName, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidStationComapare, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidDate, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidButtonInput, std::string>>(yOffset, this));
}

//-----------------------------------------------------------------------------

void FlightBookingForm::setDefaultFields() const
{
    m_inputBoxes[SECOND_DATE_DEFAULT]->setString(setDefaultDate());
    m_inputBoxes[PREFFERD_TIME]->setString("Don't Care");
}

//-----------------------------------------------------------------------------

bool FlightBookingForm::checkSelected(int index) const
{
    return m_timeSelection[index].second;
}

//-----------------------------------------------------------------------------

std::string FlightBookingForm::getFormType() const 
{
    return "Flight Booking";
}

//-----------------------------------------------------------------------------

void FlightBookingForm::doClicked(int index)
{
    checkClick(m_timeSelection, index, PREFFERD_TIME);
}

//-----------------------------------------------------------------------------

std::string FlightBookingForm::getString(int index) const
{
    return m_timeSelection[index].first;
}

//-----------------------------------------------------------------------------

std::string FlightBookingForm::getCompareField() const
{
    return m_inputBoxes[DEPARTURE]->getString();
}