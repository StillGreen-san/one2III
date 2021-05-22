#include <catch.hpp>

#include "converter.hpp"

// TODO add RLE decode to test

TEST_CASE("estimatePossibilities")
{
	RuleBook rules;

	SECTION("no rule")
	{
		CHECK(Converter::estimatePossibilities(rules, "1234") == 0);
		CHECK(Converter::estimatePossibilities(rules, "") == 0);
	}

	SECTION("one rule RNC")
	{
		rules.add(RuleType::RomanNumeralConversion);
		CHECK(Converter::estimatePossibilities(rules, "1234") == 8);
		CHECK(Converter::estimatePossibilities(rules, "12345678") == 108);
	}

	SECTION("one rule asRLE")
	{
		rules.add(RuleType::AsRunLengthEncodingConversion);
		CHECK(Converter::estimatePossibilities(rules, "1234") == 2);
		CHECK(Converter::estimatePossibilities(rules, "") == 0);
	}

	SECTION("two rules RNC,asRLE")
	{
		rules.add(RuleType::RomanNumeralConversion);
		rules.add(RuleType::AsRunLengthEncodingConversion);
		CHECK(Converter::estimatePossibilities(rules, "1234") == 17);
		CHECK(Converter::estimatePossibilities(rules, "") == 0);
	}

	SECTION("nullptr view")
	{
		CHECK(Converter::estimatePossibilities(rules, {}) == 0);
		rules.add(RuleType::NumberToEnglishConversion);
		CHECK(Converter::estimatePossibilities(rules, {}) == 0);
	}
}

TEST_CASE("calculatePossibilities")
{
	RuleBook rules;

	SECTION("no rule")
	{
		CHECK(Converter::calculatePossibilities(rules, "1234") == 0);
		CHECK(Converter::calculatePossibilities(rules, "") == 0);
	}

	SECTION("one rule RNC")
	{
		rules.add(RuleType::RomanNumeralConversion);
		CHECK(Converter::calculatePossibilities(rules, "1234") == 8);
		CHECK(Converter::calculatePossibilities(rules, "12345678") == 96);
	}

	SECTION("one rule NTE")
	{
		rules.add(RuleType::NumberToEnglishConversion);
		CHECK(Converter::calculatePossibilities(rules, "1234") == 7);
		CHECK(Converter::calculatePossibilities(rules, "") == 0);
	}

	SECTION("two rules RNC,asRLE")
	{
		rules.add(RuleType::RomanNumeralConversion);
		rules.add(RuleType::AsRunLengthEncodingConversion);
		CHECK(Converter::calculatePossibilities(rules, "1234") == 15);
		CHECK(Converter::calculatePossibilities(rules, "") == 0);
	}

	SECTION("two rules LAS,RLE")
	{
		rules.add(RuleType::LookAndSayConversion);
		rules.add(RuleType::RunLengthEncodingConversion);
		CHECK(Converter::calculatePossibilities(rules, "1234") == 54);
		CHECK(Converter::calculatePossibilities(rules, "12345678") == 4374);
	}

	SECTION("three rules asNum,RNC,NTE")
	{
		rules.add(RuleType::AsNumberConversion);
		rules.add(RuleType::RomanNumeralConversion);
		rules.add(RuleType::NumberToEnglishConversion);
		CHECK(Converter::calculatePossibilities(rules, "1234") == 191);
		CHECK(Converter::calculatePossibilities(rules, "12345678") == 47586);
	}

	SECTION("nullptr view")
	{
		CHECK(Converter::calculatePossibilities(rules, {}) == 0);
		rules.add(RuleType::LookAndSayConversion);
		CHECK(Converter::calculatePossibilities(rules, {}) == 0);
	}
}

TEST_CASE("randomConversion")
{
	RuleBook rules;

	SECTION("no rules")
	{
		CHECK(Converter::randomConversion(rules, "1234") == "");
		CHECK(Converter::randomConversion(rules, "") == "");
		CHECK(Converter::randomConversion(rules, {}) == "");
	}

	SECTION("one rule NTE")
	{
		rules.add(RuleType::NumberToEnglishConversion);
		CHECK(Converter::randomConversion(rules, "1234") != "");
		CHECK(Converter::randomConversion(rules, "") == "");
		CHECK(Converter::randomConversion(rules, {}) == "");
	}

	SECTION("two rules NTE,LAS")
	{
		rules.add(RuleType::NumberToEnglishConversion);
		rules.add(RuleType::LookAndSayConversion);
		CHECK(Converter::randomConversion(rules, "1234") != "");
		CHECK(Converter::randomConversion(rules, "") == "");
		CHECK(Converter::randomConversion(rules, {}) == "");
	}

	SECTION("three rules RNC,asNum,asRLE")
	{
		rules.add(RuleType::RomanNumeralConversion);
		rules.add(RuleType::AsNumberConversion);
		rules.add(RuleType::AsRunLengthEncodingConversion);
		CHECK(Converter::randomConversion(rules, "1234") != "");
		CHECK(Converter::randomConversion(rules, "12345678") != "");
		CHECK(Converter::randomConversion(rules, "") == "");
		CHECK(Converter::randomConversion(rules, {}) == "");
	}
}

TEST_CASE("singleConversion")
{
	RuleBook rules;

	SECTION("no rules")
	{
		CHECK(Converter::singleConversion(rules, "1234", 16) == "");
		CHECK(Converter::singleConversion(rules, "", 8) == "");
		CHECK(Converter::singleConversion(rules, {}, 4) == "");
	}

	SECTION("one rule RNC")
	{
		rules.add(RuleType::RomanNumeralConversion);
		CHECK(Converter::singleConversion(rules, "1234", 4) == "I II XXXIV");
		CHECK(Converter::singleConversion(rules, "1234", 4096) == "I II III IV");
		CHECK(Converter::singleConversion(rules, "", 4) == "");
		CHECK(Converter::singleConversion(rules, {}, 8) == "");
	}

	SECTION("two rules RNC,numToEng")
	{
		rules.add(RuleType::RomanNumeralConversion);
		rules.add(RuleType::NumberToEnglishConversion);
		CHECK(Converter::singleConversion(rules, "1234", 12) == "one two III four");
		CHECK(Converter::singleConversion(rules, "1234", 66666) == "I CCXXXIV");
		CHECK(Converter::singleConversion(rules, "", 666) == "");
		CHECK(Converter::singleConversion(rules, {}, 12) == "");
	}

	SECTION("three rules RLE,LAS,asRLE")
	{
		rules.add(RuleType::RunLengthEncodingConversion);
		rules.add(RuleType::LookAndSayConversion);
		rules.add(RuleType::AsRunLengthEncodingConversion);
		CHECK(Converter::singleConversion(rules, "1234", 4096) == "1 2 1 3 1 4");
		CHECK(Converter::singleConversion(rules, "12345678", 16384) ==
		      "one one one two one three one four one five one six one seven one eight");
		CHECK(Converter::singleConversion(rules, "", 1024) == "");
		CHECK(Converter::singleConversion(rules, {}, 16) == "");
	}
}

TEST_CASE("allConversions")
{
	using sv = std::vector<std::string>;
	using Catch::Matchers::Contains;
	using Catch::Matchers::UnorderedEquals;

	RuleBook rules;
	sv output;
	auto outputFunc = [&](std::string&& conversion)
	{
		output.emplace_back(std::move(conversion));
		return true;
	};

	SECTION("no rules")
	{
		CHECK(Converter::allConversions(rules, "1234", outputFunc) == 0);
		CHECK(output.empty());
	}

	SECTION("one rule asNum")
	{
		rules.add(RuleType::AsNumberConversion);
		CHECK(Converter::allConversions(rules, "1234", outputFunc) == 8);
		CHECK_THAT(
		    output, UnorderedEquals(sv{"1 2 3 4", "12 3 4", "1 23 4", "1 2 34", "12 34", "123 4", "1 234", "1234"}));
	}

	SECTION("two rules asNum,asRLE")
	{
		rules.add(RuleType::AsNumberConversion);
		rules.add(RuleType::AsRunLengthEncodingConversion);
		CHECK(Converter::allConversions(rules, "1234", outputFunc) == 15);
		CHECK_THAT(output, UnorderedEquals(sv{"1 2 3 4", "12 3 4", "1 2 3 4", "1 23 4", "1 2 3 4", "1 2 34", "1 2 3 4",
		                       "12 34", "1 2 34", "12 3 4", "1 2 3 4", "123 4", "1 234", "1234", "1 2 3 4"}));
	}

	SECTION("two rules asNum,RNC")
	{
		rules.add(RuleType::AsNumberConversion);
		rules.add(RuleType::RomanNumeralConversion);
		CHECK(Converter::allConversions(rules, "1234", outputFunc) == 54);
		CHECK_THAT(output,
		    UnorderedEquals(sv{"1 2 3 4", "I 2 3 4", "1 II 3 4", "1 2 III 4", "1 2 3 IV", "I II 3 4", "1 2 III IV",
		        "I 2 3 IV", "1 II III 4", "I 2 III 4", "1 II 3 IV", "I II III 4", "I II 3 IV", "I 2 III IV",
		        "1 II III IV", "I II III IV", "12 3 4", "XII 3 4", "12 III 4", "12 3 IV", "XII III 4", "12 III IV",
		        "XII 3 IV", "XII III IV", "1 23 4", "I 23 4", "1 XXIII 4", "1 23 IV", "I XXIII 4", "1 XXIII IV",
		        "I 23 IV", "I XXIII IV", "1 2 34", "I 2 34", "1 II 34", "1 2 XXXIV", "I II 34", "1 II XXXIV",
		        "I 2 XXXIV", "I II XXXIV", "12 34", "XII 34", "12 XXXIV", "XII XXXIV", "123 4", "CXXIII 4", "123 IV",
		        "CXXIII IV", "1 234", "I 234", "1 CCXXXIV", "I CCXXXIV", "1234", "MCCXXXIV"}));
	}

	SECTION("three rules asNum,RNC,NTE")
	{
		rules.add(RuleType::AsNumberConversion);
		rules.add(RuleType::RomanNumeralConversion);
		rules.add(RuleType::NumberToEnglishConversion);
		CHECK(Converter::allConversions(rules, "1234", outputFunc) == 191);
		CHECK_THAT(output,
		    Contains(sv{"one II three IV", "I two 3 4", "one 2 three four", "I II thirty four", "one twenty three four",
		        "one XXIII 4", "I II 34", "one hundred twenty three IV", "1 234", "one 234", "one CCXXXIV", "1234",
		        "twelve XXXIV", "I 2 thirty four", "one 23 four", "XII III four", "I 2 3 four", "1 2 3 4"}));
	}
}
