#include "ValidNumPass.h"
#include "ValidName.h"

//-----------------------------------------------------------------------------

bool ValidNumPass::validate(int num, const BookingForm* form)
{
	return num > 0 && num < 100;
}

//-----------------------------------------------------------------------------

std::string ValidNumPass::error()
{
	return "\n	The Num Of Passengers input is invalid!\n";
}