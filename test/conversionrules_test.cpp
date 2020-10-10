/**
 * @file conversionrules_test.cpp
 * @brief gathers all tests for conversionrules.hpp
 */

#include <catch.hpp>

#include "conversionrules.hpp"
#include "converter.hpp"

TEST_CASE("RomanNumeralConversion")
{
	RomanNumeralConversion rnc;
	CHECK(rnc.convert("789") == romanNumerals("789"));
	CHECK(rnc.convert("1009") == romanNumerals("1009"));
}

TEST_CASE("RunLengthEncodingConversion")
{
	RunLengthEncodingConversion rlec;
	CHECK(rlec.convert("22") == runLengthEncode("22"));
	CHECK(rlec.convert("123") == runLengthEncode("123"));
}

TEST_CASE("AsRunLengthEncodingConversion")
{
	AsRunLengthEncodingConversion arlec;
	CHECK(arlec.convert("1234") == asRunLengthEncode("1234"));
	CHECK(arlec.convert("12345") == asRunLengthEncode("12345"));
}

TEST_CASE("NumbersToEnglishConversion")
{
	NumberToEnglishConversion nte;
	CHECK(nte.convert("126") == numberToEnglish("126"));
	CHECK(nte.convert("216") == numberToEnglish("216"));
}

TEST_CASE("AsNumberConversion")
{
	AsNumberConversion an;
	CHECK(an.convert("126") == "126");
	CHECK(an.convert("12345") == "12345");
}

//TODO add LookAndSayConversion test

//TODO add RuleBookIterator test

//TODO add RuleBook test
