#include <algorithm>
#include <random>

#include "conversionfunctions.hpp"
#include "conversionrule.hpp"
#include "converter.hpp"
#include "helperfunctions.hpp"

// TODO remove the massive amount of code duplication
// TODO use "static" buffer string for conversions to reduce allocations?

size_t Converter::estimatePossibilities(const RuleBook& rules, std::string_view string)
{
	size_t totalPossibilities = 0;
	const size_t stringLength = string.size();
	const size_t minPartSize = std::clamp(rules.getMinInputSize(), 1ULL, 255ULL);
	const size_t maxPartSize = std::clamp(rules.getMaxInputSize(), 1ULL, 255ULL);

	for(size_t partCount = stringLength; partCount > 0; --partCount)
	{
		auto possiblePartitions = integerPartitions(stringLength, partCount, minPartSize, maxPartSize);
		for(auto& partition : possiblePartitions)
		{
			size_t partitionPossibilities = 1;
			for(const size_t partSize : partition)
			{
				partitionPossibilities *= std::count_if(std::begin(rules), std::end(rules),
				    [partSize](const RuleType& rule)
				    {
					    return partSize >= ConversionRule::minInputSize(rule) &&
					           partSize <= ConversionRule::maxInputSize(rule);
				    });
			}

			size_t permutationPossibilities = 1;
			while(std::next_permutation(rbegin(partition), rend(partition)))
			{
				++permutationPossibilities; // TODO number of possible permutations should be static for each length
				                            // (can make psblPrtns const)
			}
			totalPossibilities += partitionPossibilities * permutationPossibilities;
		}
	}

	return totalPossibilities;
}

size_t Converter::calculatePossibilities(const RuleBook& rules, std::string_view string)
{
	size_t totalPossibilities = 0;
	const size_t stringLength = string.size();
	const size_t minPartSize = std::clamp(rules.getMinInputSize(), 1ULL, 255ULL);
	const size_t maxPartSize = std::clamp(rules.getMaxInputSize(), 1ULL, 255ULL);

	for(size_t partCount = stringLength; partCount > 0; --partCount)
	{
		auto possiblePartitions = integerPartitions(stringLength, partCount, minPartSize, maxPartSize);
		for(auto& partition : possiblePartitions)
		{
			do
			{
				size_t partitionPossibilities = 1;
				size_t partOffset = 0;
				for(const size_t partSize : partition)
				{
					const std::string_view stringPart = string.substr(partOffset, partSize);
					partitionPossibilities *= std::count_if(std::begin(rules), std::end(rules),
					    [&](const RuleType& rule)
					    {
						    return !ConversionRule::convert(rule, stringPart).empty();
					    });
					if(partitionPossibilities == 0)
					{
						break;
					}
					partOffset += partSize;
				}
				totalPossibilities += partitionPossibilities;
			} while(std::next_permutation(rbegin(partition), rend(partition)));
		}
	}

	return totalPossibilities;
}

std::string Converter::randomConversion(const RuleBook& rules, std::string_view string)
{
	const size_t possibilities = calculatePossibilities(rules, string);
	if(possibilities == 0)
	{
		return {};
	}
	std::uniform_int_distribution<size_t> dist(1, possibilities);
	std::random_device rd;
	std::mt19937_64 mt(rd()); // TODO have this cached somehow?
	return singleConversion(rules, string, dist(mt));
}

std::string Converter::singleConversion(const RuleBook& rules, std::string_view string, size_t number)
{
	if(auto possibilities = calculatePossibilities(rules, string); number > possibilities && possibilities != 0)
	{
		number %= possibilities;
	}
	if(number == 0)
	{
		number = 1;
	}

	const size_t stringLength = string.size();
	const size_t minPartSize = std::clamp(rules.getMinInputSize(), 1ULL, 255ULL);
	const size_t maxPartSize = std::clamp(rules.getMaxInputSize(), 1ULL, 255ULL);

	for(size_t partCount = stringLength; partCount > 0; --partCount)
	{
		auto possiblePartitions = integerPartitions(stringLength, partCount, minPartSize, maxPartSize);
		for(auto& partition : possiblePartitions)
		{
			do
			{
				std::vector<size_t> ruleIndices(partCount, 0);
				auto incrementIndices = [&](size_t _index = 0) -> bool
				{
					auto impl = [&](auto& _impl) -> bool
					{
						if(_index == ruleIndices.size())
						{
							return false;
						}
						++ruleIndices[_index];
						if(ruleIndices[_index] == rules.size())
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
					for(size_t i = 0; i < partCount; ++i)
					{
						const std::string_view stringPart = string.substr(partOffset, partition[i]);
						const std::string convertedPart = ConversionRule::convert(rules[ruleIndices[i]], stringPart);
						if(convertedPart.empty())
						{
							break;
						}
						partOffset += partition[i];
						converted.append(convertedPart).append(" ");
					}

					if(partOffset == stringLength)
					{
						--number;
						converted.erase(converted.size() - 1);
						if(number == 0)
						{
							return converted;
						}
					}
				} while(incrementIndices());
			} while(std::next_permutation(rbegin(partition), rend(partition)));
		}
	}

	return {};
}

size_t Converter::allConversions(
    const RuleBook& rules, std::string_view string, std::function<void(std::string&&)> outputFunc)
{ // TODO replace placeholder impl
	size_t conversions = 0;
	const size_t stringLength = string.size();
	const size_t minPartSize = std::clamp(rules.getMinInputSize(), 1ULL, 255ULL);
	const size_t maxPartSize = std::clamp(rules.getMaxInputSize(), 1ULL, 255ULL);

	for(size_t partCount = stringLength; partCount > 0; --partCount)
	{
		auto possiblePartitions = integerPartitions(stringLength, partCount, minPartSize, maxPartSize);
		for(auto& partition : possiblePartitions)
		{
			do
			{
				std::vector<size_t> ruleIndices(partCount, 0);
				auto incrementIndices = [&](size_t _index = 0) -> bool
				{
					auto impl = [&](auto& _impl) -> bool
					{
						if(_index == ruleIndices.size())
						{
							return false;
						}
						++ruleIndices[_index];
						if(ruleIndices[_index] == rules.size())
						{
							ruleIndices[_index] = 0;
							++_index;
							return _impl(_impl);
						}
						return true;
					};
					return impl(impl); // TODO check removal of recursion else nolint (also for other functions)
				};

				do
				{
					std::string converted;
					size_t partOffset = 0;
					for(size_t i = 0; i < partCount; ++i)
					{
						const std::string_view stringPart = string.substr(partOffset, partition[i]);
						const std::string convertedPart = ConversionRule::convert(rules[ruleIndices[i]], stringPart);
						if(convertedPart.empty())
						{
							break; // TODO move checks out before loop similar to estimate to avoid some conversions?
						}
						partOffset += partition[i];
						converted.append(convertedPart).append(" ");
					}

					if(partOffset == stringLength)
					{
						converted.erase(converted.size() - 1);
						++conversions;
						outputFunc(std::move(converted));
					}
				} while(incrementIndices());
			} while(std::next_permutation(rbegin(partition), rend(partition)));
		}
	}

	return conversions;
}
