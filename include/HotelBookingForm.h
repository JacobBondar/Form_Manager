#ifndef HOTELBOOKINGFORM_H
#define HOTELBOOKINGFORM_H

#include "BookingForm.h"
#include "ValidLaterDate.h"
#include "ValidNumOfGuests.h"

const int ROOM_TYPE = 8;

class HotelBookingForm : public BookingForm 
{
public:
    HotelBookingForm(sf::RenderWindow& win, DialogueManager* manager);
	virtual ~HotelBookingForm() = default;

    virtual std::string getFormType() const override;
    virtual std::string getValidateName() const override;
    virtual std::string getCompareField() const override;

private:
    std::array<std::string, 4> m_roomTypeSelection = 
                    {"Single Room","Double Room","Family Room","Presidential Suite"};
	int m_selectedRoomType = 0;

    void setDefaultValues();
    void createFields(int& yOffset);

    virtual int getSize() const override { return m_roomTypeSelection.size(); }
    virtual bool checkSelected(int index) const override;
    virtual void doClicked(int index);
    virtual std::string getString(int index) const override;
};

#endif // HOTELBOOKINGFORM_H