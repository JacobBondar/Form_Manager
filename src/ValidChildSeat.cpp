#include "ValidChildSeat.h"
#include "BookingForm.h"

//-----------------------------------------------------------------------------

bool ValidChildSeat::validate(const std::string& childSit, const BookingForm* form)
{
	if (childSit != "Yes" && childSit != "No") return false;

	std::string name = form->getTypeName();
	std::istringstream iss(form->getValidateName());

	std::string firstString, secondString;
	std::getline(iss, firstString);
	std::getline(iss, secondString);

	if (name != firstString && name != secondString && childSit != "No") return false;
	return true;
}

//-----------------------------------------------------------------------------

std::string ValidChildSeat::error()
{
	return "\n	The child seat input is invalid!\n";
}