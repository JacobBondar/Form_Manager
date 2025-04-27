#ifndef CARRENTALFORM_H
#define CARRENTALFORM_H
#include <array>

#include "BookingForm.h"
#include "ValidRentDays.h"
#include "ValidGPS.h"
#include "ValidChildSeat.h"

const int BUTTON_CHOICE = 9;

class CarRentalForm : public BookingForm
{
public:
    CarRentalForm(DialogueManager* manager);
    virtual ~CarRentalForm() = default;

    virtual std::string getFormType() const override { return "Car Rental"; };
    virtual std::string getValidateName() const override { return "SUV\nSedan"; };
    virtual std::string getTypeName() const override;
    virtual std::vector<std::string> getNames() const override;

private:
    std::array<std::string, 5> m_carTypeSelection = 
                                { "Economy","Compact","Sedan","SUV","Luxury"};
    int m_selectedCarType = 0;

    void setDefaultFields() const;
    void createFields(int& yOffset);
    virtual int getSize() const override { return m_carTypeSelection.size(); }
    virtual bool checkSelected(int index) const override;
    virtual void doClicked(int index) override;
    virtual std::string getString(int index) const override;
};

#endif // CARRENTALFORM_H
