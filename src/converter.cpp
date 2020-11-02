/**
 * @file converter.cpp
 * @brief implementation for Converter
 * 
 */

#include <algorithm>

#include "converter.hpp"
#include "conversionrule.hpp"
#include "conversionfunctions.hpp"
#include "helperfunctions.hpp"

size_t Converter::estimatePossibilities(const RuleBook& _rules, std::string_view _string)
{
	size_t totalPossibilities = 0;
	uint8_t stringLength = static_cast<uint8_t>(_string.size()); //TODO do something with strings that are to long somewhere
	uint8_t minPartSize = static_cast<uint8_t>(std::clamp(_rules.getMinInputSize(), 1ULL, 255ULL));
	uint8_t maxPartSize = static_cast<uint8_t>(std::clamp(_rules.getMaxInputSize(), 1ULL, 255ULL));//TODO make these prettier
	for(uint8_t partCount = stringLength; partCount > 0; --partCount)
	{
		auto possiblePartitions = integerPartitions(stringLength, partCount, minPartSize, maxPartSize);
		for(auto& partition : possiblePartitions)
		{
			size_t partitionPossibilities = 1;
			for(uint8_t partSize : partition)
			{
				size_t partSizePossibilities = 0;
				for(auto& rule : _rules)
				{
					//TODO better check here? (e.g. for AsRLE with even size req)
					if( partSize >= ConversionRule::minInputSize(rule) &&
						partSize <= ConversionRule::maxInputSize(rule))
					{
						++partSizePossibilities;
					}
				}
				partitionPossibilities *= partSizePossibilities;
			}
			size_t permutationPossibilities = 1;
			while(std::next_permutation(rbegin(partition), rend(partition)))
			{
				++permutationPossibilities;
			}
			totalPossibilities += partitionPossibilities * permutationPossibilities;
		}
	}
	return totalPossibilities;
}

size_t Converter::calculatePossibilities(const RuleBook& _rules, std::string_view _string)
{
	return 0;
}

std::string Converter::randomConversion(const RuleBook& _rules, std::string_view _string)
{
	return {};
}

std::string Converter::singleConversion(const RuleBook& _rules, std::string_view _string, size_t _number)
{
	return {};
}
