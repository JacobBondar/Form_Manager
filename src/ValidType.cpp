#include "ValidType.h"
#include "BookingForm.h"

//-----------------------------------------------------------------------------

bool ValidType::validate(const std::string& type, const BookingForm* form)
{
	auto form_vector = form->getVectorTypes();

	bool found = false;
	for (auto& name : form_vector)
	{
		if (name == type) found = true;
	}

	return found;
}

//-----------------------------------------------------------------------------

std::string ValidType::error()
{
	return "\n	The Type input is invalid!\n";
}