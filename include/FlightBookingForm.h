#ifndef FLIGHTBOOKINGFORM_H
#define FLIGHTBOOKINGFORM_H
#include <SFML/Graphics.hpp>

#include "BookingForm.h"
#include "ValidButtonInput.h"

const int PREFFERD_TIME = 7;
const int DEPARTURE = 4;

class FlightBookingForm : public BookingForm 
{
public:
    FlightBookingForm(sf::RenderWindow& win, DialogueManager* manager);
	virtual ~FlightBookingForm() = default;

    virtual int getSize() const override { return m_timeSelection.size(); }
    virtual std::string getFormType() const override;
    virtual std::string getString(int index) const override;
    virtual std::string getCompareField() const override;

private:
    std::array<std::pair<std::string, bool>, 5> m_timeSelection = {
        std::make_pair("Morning", false),
        std::make_pair("Noon", false),
        std::make_pair("Evening", false),
        std::make_pair("Night", false),
        std::make_pair("Don't Care", true)
    };

	void createFields(int& yOffset);
    void setDefaultFields() const;
    virtual bool checkSelected(int index) const override;
    virtual void doClicked(int index) override;
};

#endif // FLIGHTBOOKINGFORM_H