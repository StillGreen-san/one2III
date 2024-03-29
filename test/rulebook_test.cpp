#include <catch2/catch_test_macros.hpp>

#include "conversionrule.hpp"
#include "rulebook.hpp"

TEST_CASE("RuleBook")
{
	RuleBook rules;

	SECTION("empty")
	{
		CHECK(rules.getMinInputSize() == std::numeric_limits<size_t>::max());
		CHECK(rules.getMaxInputSize() == std::numeric_limits<size_t>::min());
		CHECK(rules.size() == 0);
	}

	SECTION("add none")
	{
		CHECK_FALSE(rules.add(RuleType::None));

		CHECK(rules.getMinInputSize() == std::numeric_limits<size_t>::max());
		CHECK(rules.getMaxInputSize() == std::numeric_limits<size_t>::min());

		CHECK(rules.size() == 0);
	}

	SECTION("one rule")
	{
		CHECK(rules.add(RuleType::RunLengthDecodingConversion));

		CHECK(rules.getMaxInputSize() == ConversionRule::maxInputSize(RuleType::RunLengthDecodingConversion));
		CHECK(rules.getMinInputSize() == ConversionRule::minInputSize(RuleType::RunLengthDecodingConversion));

		CHECK(rules.size() == 1);
	}

	SECTION("one rule duplicate")
	{
		CHECK(rules.add(RuleType::RunLengthEncodingConversion));
		CHECK_FALSE(rules.add(RuleType::RunLengthEncodingConversion));

		CHECK(rules.getMaxInputSize() == ConversionRule::maxInputSize(RuleType::RunLengthEncodingConversion));
		CHECK(rules.getMinInputSize() == ConversionRule::minInputSize(RuleType::RunLengthEncodingConversion));

		auto ruleIt = rules.begin();

		REQUIRE(rules.size() == 1);

		CHECK(*ruleIt == RuleType::RunLengthEncodingConversion);
		CHECK(rules[0] == RuleType::RunLengthEncodingConversion);
	}

	SECTION("two rules")
	{
		CHECK(rules.add(RuleType::RomanNumeralConversion));
		CHECK(rules.add(RuleType::NumberToEnglishConversion));

		CHECK(rules.getMaxInputSize() == ConversionRule::maxInputSize(RuleType::RomanNumeralConversion));
		CHECK(rules.getMinInputSize() == ConversionRule::minInputSize(RuleType::NumberToEnglishConversion));

		auto ruleIt = rules.begin();

		REQUIRE(rules.size() == 2);

		CHECK(*ruleIt == RuleType::RomanNumeralConversion);
		CHECK(rules[0] == RuleType::RomanNumeralConversion);
		std::advance(ruleIt, 1);
		CHECK(*ruleIt == RuleType::NumberToEnglishConversion);
		CHECK(rules[1] == RuleType::NumberToEnglishConversion);
	}
}
