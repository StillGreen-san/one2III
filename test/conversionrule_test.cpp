/**
 * @file conversionrule_test.cpp
 * @brief gathers all tests for conversionrule.hpp
 */

#include <catch.hpp>

#include "conversionrule.hpp"
#include "conversionfunctions.hpp"

TEST_CASE("RomanNumeralConversion")
{
	auto rnc = RuleType::RomanNumeralConversion;
	CHECK(ConversionRule::convert(rnc, "789") == romanNumerals("789"));
	CHECK(ConversionRule::convert(rnc, "1009") == romanNumerals("1009"));
}

TEST_CASE("RunLengthEncodingConversion")
{
	auto rlec = RuleType::RunLengthEncodingConversion;
	CHECK(ConversionRule::convert(rlec, "22") == runLengthEncode("22"));
	CHECK(ConversionRule::convert(rlec, "123") == runLengthEncode("123"));
}

TEST_CASE("AsRunLengthEncodingConversion")
{
	auto arlec = RuleType::AsRunLengthEncodingConversion;
	CHECK(ConversionRule::convert(arlec, "1234") == asRunLengthEncode("1234"));
	CHECK(ConversionRule::convert(arlec, "12345") == asRunLengthEncode("12345"));
}

TEST_CASE("NumbersToEnglishConversion")
{
	auto nte = RuleType::NumberToEnglishConversion;
	CHECK(ConversionRule::convert(nte, "126") == numberToEnglish("126"));
	CHECK(ConversionRule::convert(nte, "216") == numberToEnglish("216"));
}

TEST_CASE("AsNumberConversion")
{
	auto an = RuleType::AsNumberConversion;
	CHECK(ConversionRule::convert(an, "126") == "126");
	CHECK(ConversionRule::convert(an, "12345") == "12345");
}

TEST_CASE("LookAndSayConversion")
{
	auto las = RuleType::LookAndSayConversion;
	CHECK(ConversionRule::convert(las, "5336666") == lookAndSay("5336666"));
	CHECK(ConversionRule::convert(las, "9999999") == lookAndSay("9999999"));
	CHECK(ConversionRule::convert(las, "888000") == lookAndSay("888000"));
	CHECK(ConversionRule::convert(las, "1") == lookAndSay("1"));
	CHECK(ConversionRule::convert(las, "") == lookAndSay(""));
}

TEST_CASE("ConversionRule")
{
	SECTION("convert")
	{
		CHECK(ConversionRule::convert(RuleType::None, "12342453") == "");
		CHECK(ConversionRule::convert(RuleType::None, "12") == "");
		CHECK(ConversionRule::convert(RuleType::None, "") == "");
	}

	SECTION("minInputSize")
	{
		CHECK(ConversionRule::minInputSize(RuleType::RomanNumeralConversion) == 1);
		CHECK(ConversionRule::minInputSize(RuleType::RunLengthEncodingConversion) == 1);
		CHECK(ConversionRule::minInputSize(RuleType::NumberToEnglishConversion) == 1);
		CHECK(ConversionRule::minInputSize(RuleType::AsRunLengthEncodingConversion) == 2);
		CHECK(ConversionRule::minInputSize(RuleType::LookAndSayConversion) == 1);
		CHECK(ConversionRule::minInputSize(RuleType::AsNumberConversion) == 1);
		CHECK(ConversionRule::minInputSize(RuleType::None) == std::numeric_limits<size_t>::max());
	}

	SECTION("maxInputSize")
	{
		CHECK(ConversionRule::maxInputSize(RuleType::RomanNumeralConversion) == 4);
		CHECK(ConversionRule::maxInputSize(RuleType::RunLengthEncodingConversion) == std::numeric_limits<size_t>::max());
		CHECK(ConversionRule::maxInputSize(RuleType::NumberToEnglishConversion) == 3);
		CHECK(ConversionRule::maxInputSize(RuleType::AsRunLengthEncodingConversion) == std::numeric_limits<size_t>::max());
		CHECK(ConversionRule::maxInputSize(RuleType::LookAndSayConversion) == std::numeric_limits<size_t>::max());
		CHECK(ConversionRule::maxInputSize(RuleType::AsNumberConversion) == std::numeric_limits<size_t>::max());
		CHECK(ConversionRule::maxInputSize(RuleType::None) == std::numeric_limits<size_t>::min());
	}
}
