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
{//TODO make this not as wasteful as this currently is
	size_t totalPossibilities = 0;
	uint8_t stringLength = static_cast<uint8_t>(_string.size()); //TODO do something with strings that are to long somewhere
	uint8_t minPartSize = static_cast<uint8_t>(std::clamp(_rules.getMinInputSize(), 1ULL, 255ULL));
	uint8_t maxPartSize = static_cast<uint8_t>(std::clamp(_rules.getMaxInputSize(), 1ULL, 255ULL));//TODO make these prettier
	for(uint8_t partCount = stringLength; partCount > 0; --partCount)
	{
		auto possiblePartitions = integerPartitions(stringLength, partCount, minPartSize, maxPartSize);
		for(auto& partition : possiblePartitions)
		{
			do
			{
				size_t partitionPossibilities = 1;
				size_t partOffset = 0;
				for(uint8_t partSize : partition)
				{
					size_t partSizePossibilities = 0;
					std::string_view stringPart = _string.substr(partOffset, partSize);
					partOffset += partSize;
					for(auto& rule : _rules)
					{
						//TODO better check here? (e.g. for AsRLE with even size req)
						if(!ConversionRule::convert(rule, stringPart).empty())
						{
							++partSizePossibilities;
						}
					}
					partitionPossibilities *= partSizePossibilities;
				}
				totalPossibilities += partitionPossibilities;
			}while(std::next_permutation(rbegin(partition), rend(partition)));
		}
	}
	return totalPossibilities;
}

std::string Converter::randomConversion(const RuleBook& _rules, std::string_view _string)
{
	return {};
}

std::string Converter::singleConversion(const RuleBook& _rules, std::string_view _string, size_t _number)
{
	if(auto possibilities = calculatePossibilities(_rules, _string);
		_number > possibilities) _number %= possibilities; //TODO have this cached somehow
	uint8_t stringLength = static_cast<uint8_t>(_string.size()); //TODO do something with strings that are to long somewhere
	uint8_t minPartSize = static_cast<uint8_t>(std::clamp(_rules.getMinInputSize(), 1ULL, 255ULL));
	uint8_t maxPartSize = static_cast<uint8_t>(std::clamp(_rules.getMaxInputSize(), 1ULL, 255ULL));//TODO make these prettier
	for(uint8_t partCount = stringLength; partCount > 0; --partCount)
	{
		auto possiblePartitions = integerPartitions(stringLength, partCount, minPartSize, maxPartSize);
		for(auto& partition : possiblePartitions)
		{
			do{
				std::vector<uint8_t> ruleIndices(partCount, 0);
				auto incrementIndices = [&](uint8_t _index = 0) -> bool
				{
					auto impl = [&](auto& _impl) -> bool
					{
						if(_index == ruleIndices.size()) return false;
						++ruleIndices[_index];
						if(ruleIndices[_index] == _rules.size())
						{
							ruleIndices[_index] = 0;
							++_index;
							return _impl(_impl);
						}
						return true;
					};
					return impl(impl);
				};
				do
				{
					std::string converted;
					size_t partOffset = 0;
					for(uint8_t i = 0; i < partCount; ++i)
					{
						std::string_view stringPart = _string.substr(partOffset, partition[i]);
						partOffset += partition[i];
						std::string convertedPart = ConversionRule::convert(_rules[ruleIndices[i]], stringPart);
						if(convertedPart.empty() == true) break;
						converted.append(convertedPart).append(" ");
					}
					if(partOffset == stringLength)
					{
						if(_number != 0) --_number;
						if(auto size = converted.size(); size > 0) converted.erase(size-1);
						if(_number == 0) return converted;
					}
				}while(incrementIndices());
			}while(std::next_permutation(rbegin(partition), rend(partition)));
		}
	}
	return {};//TODO handle number > calculatePossibilities
}
