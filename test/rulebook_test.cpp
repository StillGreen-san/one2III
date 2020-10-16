/**
 * @file rulebook_test.cpp
 * @brief gathers all tests for rulebook.hpp
 */

#include <catch.hpp>

#include "rulebook.hpp"
#include "conversionrule.hpp"

TEST_CASE("RuleBook")
{
	RuleBook rules;

	SECTION("empty")
	{
		CHECK(rules.getMinInputSize() == std::numeric_limits<size_t>::max());
		CHECK(rules.getMaxInputSize() == std::numeric_limits<size_t>::min());
	}

	SECTION("add none")
	{
		CHECK(rules.add(RuleType::None) == false);

		CHECK(rules.getMinInputSize() == std::numeric_limits<size_t>::max());
		CHECK(rules.getMaxInputSize() == std::numeric_limits<size_t>::min());

		CHECK(std::distance(rules.begin(), rules.end()) == 0);
	}

	SECTION("one rule")
	{
		CHECK(rules.add(RuleType::AsRunLengthEncodingConversion) == true);

		CHECK(rules.getMaxInputSize() == ConversionRule::maxInputSize(RuleType::AsRunLengthEncodingConversion));
		CHECK(rules.getMinInputSize() == ConversionRule::minInputSize(RuleType::AsRunLengthEncodingConversion));
	}

	SECTION("one rule duplicate")
	{
		CHECK(rules.add(RuleType::RunLengthEncodingConversion) == true);
		CHECK(rules.add(RuleType::RunLengthEncodingConversion) == false);

		CHECK(rules.getMaxInputSize() == ConversionRule::maxInputSize(RuleType::RunLengthEncodingConversion));
		CHECK(rules.getMinInputSize() == ConversionRule::minInputSize(RuleType::RunLengthEncodingConversion));

		auto ruleIt = rules.begin();

		REQUIRE(std::distance(ruleIt, rules.end()) == 1);

		CHECK(*ruleIt == RuleType::RunLengthEncodingConversion);
	}

	SECTION("two rules")
	{
		CHECK(rules.add(RuleType::RomanNumeralConversion) == true);
		CHECK(rules.add(RuleType::NumberToEnglishConversion) == true);

		CHECK(rules.getMaxInputSize() == ConversionRule::maxInputSize(RuleType::RomanNumeralConversion));
		CHECK(rules.getMinInputSize() == ConversionRule::minInputSize(RuleType::NumberToEnglishConversion));

		auto ruleIt = rules.begin();

		REQUIRE(std::distance(ruleIt, rules.end()) == 2);

		CHECK(*ruleIt == RuleType::RomanNumeralConversion);
		std::advance(ruleIt, 1);
		CHECK(*ruleIt == RuleType::NumberToEnglishConversion);
	}
}
