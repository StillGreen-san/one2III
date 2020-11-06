/**
 * @file converter_test.cpp
 * @brief gathers all tests for converter.hpp
 */

#include <catch.hpp>

#include "converter.hpp"

TEST_CASE("estimatePossibilities")
{
	RuleBook rules;
	// "1234" = 1,1,1,1 2,1,1 1,2,1 1,1,2 2,2 3,1 1,3 4
	SECTION("one rule Roman")
	{
		rules.add(RuleType::RomanNumeralConversion);
		CHECK(Converter::estimatePossibilities(rules, "1234") == 8);
	}

	SECTION("one rule asRLE")
	{
		rules.add(RuleType::AsRunLengthEncodingConversion);
		CHECK(Converter::estimatePossibilities(rules, "1234") == 2);
	}

	SECTION("two rules Roman,asRLE")
	{
		rules.add(RuleType::RomanNumeralConversion);
		rules.add(RuleType::AsRunLengthEncodingConversion);
		CHECK(Converter::estimatePossibilities(rules, "1234") == 17);
	}
}

TEST_CASE("calculatePossibilities")
{
	RuleBook rules;
	// "1234" = 1,1,1,1 2,1,1 1,2,1 1,1,2 2,2 3,1 1,3 4
	SECTION("one rule Roman")
	{
		rules.add(RuleType::RomanNumeralConversion);
		CHECK(Converter::calculatePossibilities(rules, "1234") == 8);
	}

	SECTION("one rule numToEng")
	{
		rules.add(RuleType::NumberToEnglishConversion);
		CHECK(Converter::calculatePossibilities(rules, "1234") == 7);
	}

	SECTION("two rules Roman,asRLE")
	{
		rules.add(RuleType::RomanNumeralConversion);
		rules.add(RuleType::AsRunLengthEncodingConversion);
		CHECK(Converter::calculatePossibilities(rules, "1234") == 15);
	}
}

TEST_CASE("randomConversion")
{
	RuleBook rules;
	rules.add(RuleType::NumberToEnglishConversion);
	CHECK(Converter::randomConversion(rules, "1234") != "");

	rules.add(RuleType::LookAndSayConversion);
	CHECK(Converter::randomConversion(rules, "1234") != "");

	rules.add(RuleType::RunLengthEncodingConversion);
	CHECK(Converter::randomConversion(rules, "1234") != "");

	rules.add(RuleType::AsNumberConversion);
	CHECK(Converter::randomConversion(rules, "1234") != "");

	rules.add(RuleType::AsRunLengthEncodingConversion);
	CHECK(Converter::randomConversion(rules, "1234") != "");

	rules.add(RuleType::RomanNumeralConversion);
	CHECK(Converter::randomConversion(rules, "1234") != "");
}

TEST_CASE("singleConversion")
{
	RuleBook rules;
	//TODO implement better checks when logic has been 'found'

	rules.add(RuleType::RomanNumeralConversion);
	CHECK(Converter::singleConversion(rules, "1234", 4) == "I II XXXIV");
	CHECK(Converter::singleConversion(rules, "1234", 8) == "MCCXXXIV");

	rules.add(RuleType::NumberToEnglishConversion);
	CHECK(Converter::singleConversion(rules, "1234", 12) == "one two III four");
	CHECK(Converter::singleConversion(rules, "1234", 666) == "one XXIII four");
}
