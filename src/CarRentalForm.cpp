#include "CarRentalForm.h"
#include "DialogueManager.h"
#include <iostream>
#include <ctime>

//-----------------------------------------------------------------------------

CarRentalForm::CarRentalForm(DialogueManager* manager)
    : BookingForm(manager)
{
    m_fieldLabels.insert(m_fieldLabels.end(), 
                        {
                            "Pickup Location:",
                            "Pickup Date:", "Rent total days:",
                            "GPS needed?", "Child Seat needed?",
                            "Car Type:"
                        });

	int yOffset = START_Y;
    createFields(yOffset);
	createButtons(yOffset);
    createFinishButtons(yOffset);
    setDefaultFields();
}

//-----------------------------------------------------------------------------

void CarRentalForm::setDefaultFields() const
{
   m_inputBoxes[FIRST_DATE_DEFAULT]->setString(setDefaultDate());
   m_inputBoxes[BUTTON_CHOICE]->setString("Economy");
}

//-----------------------------------------------------------------------------

std::string CarRentalForm::getTypeName() const
{
    return m_inputBoxes[BUTTON_CHOICE]->getString();
}

//-----------------------------------------------------------------------------

std::vector<std::string> CarRentalForm::getNames() const
{
    std::vector<std::string> vecReturn;

    vecReturn.emplace_back("SUV");
    vecReturn.emplace_back("Sedan");
    vecReturn.emplace_back("Luxury");

    return vecReturn;
}

//-----------------------------------------------------------------------------

std::string CarRentalForm::getString(int index) const
{
    return m_carTypeSelection[index];
}

//-----------------------------------------------------------------------------

bool CarRentalForm::checkSelected(int index) const
{
    return index == m_selectedCarType;
}

//-----------------------------------------------------------------------------

void CarRentalForm::doClicked(int index)
{
    m_selectedCarType = index;
    m_inputBoxes[BUTTON_CHOICE]->setString(m_inputButtons[index]->getString());
}

//-----------------------------------------------------------------------------

void CarRentalForm::createFields(int& yOffset)
{
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidName, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidID, uint32_t>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidLocation, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidEmail, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidLocation, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidDate, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidRentDays, int>>(yOffset, this));  
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidGps, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidChildSeat, std::string>>(yOffset, this));
    m_inputBoxes.emplace_back(std::make_unique<Field<ValidType, std::string>>(yOffset, this));
}