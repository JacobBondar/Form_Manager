#include "ValidRentDays.h"

//-----------------------------------------------------------------------------

bool ValidRentDays::validate(int rentDays, const BookingForm* form)
{
	return rentDays > 0 && rentDays < 1000;
}

//-----------------------------------------------------------------------------

std::string ValidRentDays::error()
{
	return "\n	The input has exceeded the limits!\n";
}