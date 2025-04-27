#include "ValidButtonInput.h"
#include "BookingForm.h"

//-----------------------------------------------------------------------------

bool ValidButtonInput::validate(const std::string& type, const BookingForm* form)
{
	std::vector<std::string> names = form->getVectorTypes();
	std::stringstream ss(type);

	return findValidNames(names, ss, 0, names.size());
}

//-----------------------------------------------------------------------------

std::string ValidButtonInput::error()
{
	return "\n	The input is invalid!\n";
}