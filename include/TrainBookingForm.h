#ifndef TRAINBOOKINGFORM_H
#define TRAINBOOKINGFORM_H

#include "BookingForm.h"
#include "ValidNumPass.h"
#include "ValidTime.h"
#include "ValidRequest.h"

const int STATION_DEP = 4;
const int PREFFERED_TIME = 8;
const int SPECIAL_REQUEST = 9;

enum specialCells 
{
    DATE_CELL = 6,
    PASS_CELL,
    TIME_CELL,
    REQUEST_CELL
};

class TrainBookingForm : public BookingForm 
{
public:
    TrainBookingForm(DialogueManager* manager);
    virtual ~TrainBookingForm() = default;

    virtual std::string getFormType() const override { return "Train Booking"; };
    virtual std::string getCompareField() const override;
    virtual std::vector<std::string> getNames() const override;
    virtual std::string getTypeName() const override;
    virtual std::string getValidateName() const override;
    virtual int getAmount() const override;
    virtual void checkClickMouse(sf::Vector2f mousePos) override;

private:
    std::array<std::pair<std::string, bool>, 5> m_timeSelection = {
            std::make_pair("Morning", false),
            std::make_pair("Noon", false),
            std::make_pair("Evening", false),
            std::make_pair("Night", false),
            std::make_pair("Don't Care", true)
    };
    std::array<std::pair<std::string, bool>, 4> m_specialSelection = {
        std::make_pair("Quiet Zone", false),
        std::make_pair("Family Section", false),
        std::make_pair("First Class", false) ,
        std::make_pair("None", true)
    };

    void createFields(int yOffset);
    void setDefaultValues();
    void drawButtonsTrain(sf::RenderWindow& window) const;
    void createTrainButtons(int yOffset);
	virtual void drawRectangles(int yOffset, sf::RenderWindow& window) const override;

    template<typename T>
    void createSemiButtons(int& yOffset, float buttonX, const T& vec, 
                           sf::Vector2f size, int moveX);
    template<typename T>
    void drawSemiButtons(sf::RenderWindow& window, const T& arr, int& index) const;
    template<typename T>
    void getSemiNames(std::vector<std::string>& names, const T& arr) const;
    template<typename T>
    bool checkSemiButtons(T& arr, int& index, int cell, sf::Vector2f mousePos);
};

//-----------------------------------------------------------------------------

template<typename T>
void TrainBookingForm::createSemiButtons(int& yOffset, float buttonX, 
                                         const T& vec, sf::Vector2f size, int moveX)
{
	for (int i = 0; i < vec.size(); ++i, buttonX += moveX)
	{
		m_inputButtons.emplace_back(std::make_unique<Button>
			(yOffset, buttonX, vec[i].first, size));
	}
}

//-----------------------------------------------------------------------------

template<typename T>
void TrainBookingForm::drawSemiButtons(sf::RenderWindow& window, const T& arr, int& index) const
{
    for (int j = 0; j < arr.size(); ++index, ++j)
    {
        m_inputButtons[index]->drawButton(window, arr[j].second);
    }
}

//-----------------------------------------------------------------------------

template<typename T>
void TrainBookingForm::getSemiNames(std::vector<std::string>& names, const T& arr) const
{
    for (int cell = 0; cell < arr.size(); ++cell)
    {
        names.emplace_back(arr[cell].first);
    }
}

//-----------------------------------------------------------------------------

template<typename T>
bool TrainBookingForm::checkSemiButtons(T& arr, int& index, int cell, sf::Vector2f mousePos)
{
    for (int j = 0; j < arr.size(); ++index, ++j)
    {
        if (m_inputButtons[index]->contains(mousePos))
        {
            checkClick(arr, j, cell);
            return true;
        }
    }
    return false;
}

#endif // TRAINBOOKINGFORM_H