#include "rulebook.hpp"
#include "conversionrule.hpp"

bool RuleBook::add(RuleType rule)
{
	if(rule == RuleType::None)
	{
		return false;
	}
	auto result = rules.insert(rule);
	if(!result.second)
	{
		return false;
	}
	minInputSize = std::min(minInputSize, ConversionRule::minInputSize(*(result.first)));
	maxInputSize = std::max(maxInputSize, ConversionRule::maxInputSize(*(result.first)));
	return true;
}

size_t RuleBook::getMinInputSize() const
{
	return minInputSize;
}

size_t RuleBook::getMaxInputSize() const
{
	return maxInputSize;
}

std::set<RuleType>::const_iterator RuleBook::begin() const
{
	return rules.cbegin();
}

std::set<RuleType>::const_iterator RuleBook::end() const
{
	return rules.cend();
}

size_t RuleBook::size() const
{
	return rules.size();
}

RuleType RuleBook::operator[](size_t index) const
{
	auto iterator = rules.begin();
	if(index > static_cast<size_t>(std::numeric_limits<ptrdiff_t>::max()))
	{
		std::advance(iterator, std::numeric_limits<ptrdiff_t>::max());
		index -= std::numeric_limits<ptrdiff_t>::max();
	}
	return *std::next(iterator, index);
}
