/**
 * @file conversionstates.hpp
 * @brief implementation file for conversion state functions
 */

#include "conversionstates.hpp"
#include "helperfunctions.hpp"

namespace ConversionStates
{
	bool Nums_validate(std::string_view _sequence) 
	{
		return isValidNumberSequence(_sequence);
	}
}