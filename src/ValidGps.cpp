#include "ValidGps.h"
#include "BookingForm.h"

//-----------------------------------------------------------------------------

bool ValidGps::validate(const std::string& gps, const BookingForm* form)
{
	if (gps != "Yes" && gps != "No") return false;

	auto name = form->getTypeName();
	auto namesValid = form->getNames();

	if (name != namesValid[0] && name != namesValid[1] && 
		name != namesValid[2] && gps != "No") return false;

	return true;
}

//-----------------------------------------------------------------------------

std::string ValidGps::error()
{
	return "\n	The Gps input is invalid!\n";
}