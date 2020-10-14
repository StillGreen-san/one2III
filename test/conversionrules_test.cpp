/**
 * @file conversionrules_test.cpp
 * @brief gathers all tests for conversionrules.hpp
 */

#include <catch.hpp>

#include "conversionrules.hpp"
#include "converter.hpp"

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
	CHECK(ConversionRule::convert(las, "5336666") == "one five two three four six");
	CHECK(ConversionRule::convert(las, "9999999") == "seven nine");
	CHECK(ConversionRule::convert(las, "888000") == "three eight three zero");
	CHECK(ConversionRule::convert(las, "1") == "one one");
	CHECK(ConversionRule::convert(las, "") == "");
}

//TODO add RuleBook test
