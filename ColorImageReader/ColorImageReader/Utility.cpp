#include "Utility.h"
#include <sstream>

std::string Utility::ltos(long l, std::string inputString)
{
	std::ostringstream os;
	os << l;
	return inputString + os.str() + "\n";
}