/**
 * @file rulebook_test.cpp
 * @brief gathers all tests for rulebook.hpp
 */

#include <catch.hpp>

#include "ruletype.hpp"

TEST_CASE("enumCount(RuleType)")
{
	CHECK(enumCount(RuleType::None) == static_cast<enumType<RuleType>>(RuleType::None));
}

TEST_CASE("enumName(RuleType)")
{
	CHECK(enumName(RuleType::AsNumberConversion) == "AsNumberConversion");
	CHECK(enumName(RuleType::AsRunLengthEncodingConversion) == "AsRunLengthEncodingConversion");
	CHECK(enumName(RuleType::LookAndSayConversion) == "LookAndSayConversion");
	CHECK(enumName(RuleType::NumberToEnglishConversion) == "NumberToEnglishConversion");
	CHECK(enumName(RuleType::RomanNumeralConversion) == "RomanNumeralConversion");
	CHECK(enumName(RuleType::RunLengthEncodingConversion) == "RunLengthEncodingConversion");
	CHECK(enumName(RuleType::None) == "invalid");
	CHECK(enumName(static_cast<RuleType>(99)) == "invalid");
}

TEST_CASE("enumDescription(RuleTyp)")
{
	CHECK(enumName(RuleType::AsNumberConversion) == "returns a number sequence as is");
	CHECK(enumName(RuleType::AsRunLengthEncodingConversion) == "interprets a number sequence as run length encoding");
	CHECK(enumName(RuleType::LookAndSayConversion) == "converts a number sequence with run length encoding then to english words");
	CHECK(enumName(RuleType::NumberToEnglishConversion) == "converts a number sequence to english words");
	CHECK(enumName(RuleType::RomanNumeralConversion) == "converts a number sequence to roman numerals");
	CHECK(enumName(RuleType::RunLengthEncodingConversion) == "converts a number sequence as run length encoding");
	CHECK(enumName(RuleType::None) == "invalid");
	CHECK(enumName(static_cast<RuleType>(99)) == "invalid");
}
