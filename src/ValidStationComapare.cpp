#include "ValidStationComapare.h"
#include "ValidName.h"
#include "BookingForm.h"

//-----------------------------------------------------------------------------

bool ValidStationComapare::validate(const std::string& type, const BookingForm* form)
{
	if (!ValidName::validate(type, form)) return false;

	auto prev = form->getCompareField();

	return prev != type;
}

//-----------------------------------------------------------------------------

std::string ValidStationComapare::error()
{
	return "\n	The Arrival Station input is invalid!\n";
}