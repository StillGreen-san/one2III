#include <catch.hpp>

#include "converter.hpp"

// TODO redo all these tests
// TODO check for no rules

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

	// TODO come up with more tests because they don't cover everything aperantly!
	// LookAndSayConversion in random can fail after chaning calculatePossibilities without this failing
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

	rules = RuleBook();
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
	// CHECK(Converter::singleConversion(rules, "1234", 50) == "");
	// CHECK(Converter::singleConversion(rules, "1234", 8) == "");

	rules.add(RuleType::RomanNumeralConversion);
	CHECK(Converter::singleConversion(rules, "1234", 4) == "I II XXXIV");
	CHECK(Converter::singleConversion(rules, "1234", 8) == "MCCXXXIV");

	rules.add(RuleType::NumberToEnglishConversion);
	CHECK(Converter::singleConversion(rules, "1234", 12) == "one two III four");
	CHECK(Converter::singleConversion(rules, "1234", 666) == "one XXIII four");
}

TEST_CASE("allConversions")
{
	using sv = std::vector<std::string>;
	using Catch::Matchers::Contains;
	using Catch::Matchers::UnorderedEquals;
	// "1234" = 1,1,1,1 2,1,1 1,2,1 1,1,2 2,2 3,1 1,3 4
	RuleBook rules;
	std::string_view string = "1234";
	CHECK(Converter::allConversions(rules, string).empty());

	rules.add(RuleType::AsNumberConversion);
	CHECK_THAT(
	    Converter::allConversions(rules, string),
	    UnorderedEquals(sv{"1 2 3 4", "12 3 4", "1 23 4", "1 2 34", "12 34", "123 4", "1 234", "1234"}));

	rules.add(RuleType::AsRunLengthEncodingConversion);
	CHECK_THAT(
	    Converter::allConversions(rules, string),
	    UnorderedEquals(
	        sv{"1 2 3 4", "12 3 4", "1 2 3 4", "1 23 4", "1 2 3 4", "1 2 34", "1 2 3 4", "12 34", "1 2 34", "12 3 4",
	           "1 2 3 4", "123 4", "1 234", "1234", "1 2 3 4"}));

	rules = RuleBook();
	rules.add(RuleType::AsNumberConversion);
	rules.add(RuleType::RomanNumeralConversion);
	CHECK_THAT(
	    Converter::allConversions(rules, string),
	    UnorderedEquals(sv{"1 2 3 4",    "I 2 3 4",    "1 II 3 4",    "1 2 III 4",   "1 2 3 IV",  "I II 3 4",
	                       "1 2 III IV", "I 2 3 IV",   "1 II III 4",  "I 2 III 4",   "1 II 3 IV", "I II III 4",
	                       "I II 3 IV",  "I 2 III IV", "1 II III IV", "I II III IV", "12 3 4",    "XII 3 4",
	                       "12 III 4",   "12 3 IV",    "XII III 4",   "12 III IV",   "XII 3 IV",  "XII III IV",
	                       "1 23 4",     "I 23 4",     "1 XXIII 4",   "1 23 IV",     "I XXIII 4", "1 XXIII IV",
	                       "I 23 IV",    "I XXIII IV", "1 2 34",      "I 2 34",      "1 II 34",   "1 2 XXXIV",
	                       "I II 34",    "1 II XXXIV", "I 2 XXXIV",   "I II XXXIV",  "12 34",     "XII 34",
	                       "12 XXXIV",   "XII XXXIV",  "123 4",       "CXXIII 4",    "123 IV",    "CXXIII IV",
	                       "1 234",      "I 234",      "1 CCXXXIV",   "I CCXXXIV",   "1234",      "MCCXXXIV"}));

	rules.add(RuleType::NumberToEnglishConversion);
	CHECK_THAT(
	    Converter::allConversions(rules, string),
	    Contains(
	        sv{"1 2 3 4", "I two 3 4", "one 2 three four", "I II thirty four", "one twenty three four", "one XXIII 4",
	           "I II 34", "one hundred twenty three IV", "1 234", "one 234", "one CCXXXIV"}));
}
