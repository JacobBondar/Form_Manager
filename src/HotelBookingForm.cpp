#include "HotelBookingForm.h"
#include "DialogueManager.h"
#include <iostream>
#include <ctime>

//-----------------------------------------------------------------------------

HotelBookingForm::HotelBookingForm(sf::RenderWindow& win, DialogueManager* manager)
    : BookingForm(manager) 
{
    m_fieldLabels.insert(m_fieldLabels.end(), 
                         {
                            "Hotel Name:", "Check-in Date:", "Check-out Date:",
                            "Number of Guests:", "Room Type:"
                         });

    int yOffset = START_Y;
    createFields(yOffset);
    createButtons(yOffset, 160, { 150 , 30 });
    createFinishButtons(yOffset);
    setDefaultValues();
}

//-----------------------------------------------------------------------------

void HotelBookingForm::createFields(int& yOffset)
{
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidName, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidID, uint32_t>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidLocation, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidEmail, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidName, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidDate, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidLaterDate, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidNumOfGuests, int>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidType, std::string>>(yOffset, this));
}

//-----------------------------------------------------------------------------

void HotelBookingForm::setDefaultValues() 
{
    std::string date = setDefaultDate();

    m_inputBoxes[FIRST_DATE_DEFAULT]->setString(date);
    m_inputBoxes[SECOND_DATE_DEFAULT]->setString(date);
    m_inputBoxes[ROOM_TYPE]->setString("Single Room");
}

//-----------------------------------------------------------------------------

std::string HotelBookingForm::getFormType() const 
{
    return "Hotel Booking";
}

//-----------------------------------------------------------------------------

std::string HotelBookingForm::getString(int index) const
{
    return m_roomTypeSelection[index];
}

//-----------------------------------------------------------------------------

bool HotelBookingForm::checkSelected(int index) const
{
    return index == m_selectedRoomType;
}

//-----------------------------------------------------------------------------

void HotelBookingForm::doClicked(int index)
{
    m_selectedRoomType = index;
    m_inputBoxes[ROOM_TYPE]->setString(m_inputButtons[index]->getString());
}

//-----------------------------------------------------------------------------

std::string HotelBookingForm::getValidateName() const
{
    return m_inputBoxes[ROOM_TYPE]->getString();
}

//-----------------------------------------------------------------------------

std::string HotelBookingForm::getCompareField() const
{
    return m_inputBoxes[FIRST_DATE_DEFAULT]->getString();
}
