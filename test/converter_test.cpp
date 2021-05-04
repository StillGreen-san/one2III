#include <catch.hpp>

#include "converter.hpp"

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
		CHECK(Converter::calculatePossibilities(rules, "12345678") == 96);
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
	}

	SECTION("three rules asNum,RNC,NTE")
	{
		rules.add(RuleType::AsNumberConversion);
		rules.add(RuleType::RomanNumeralConversion);
		rules.add(RuleType::NumberToEnglishConversion);
		CHECK(Converter::calculatePossibilities(rules, "1234") == 191);
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

// TODO redo all these tests
// TODO check for no rules

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
	sv output;
	auto outputFunc = [&](std::string&& conversion)
	{
		output.emplace_back(std::move(conversion));
	};

	CHECK(Converter::allConversions(rules, string, outputFunc) == 0);

	rules.add(RuleType::AsNumberConversion);
	output.clear();
	CHECK(Converter::allConversions(rules, string, outputFunc) == 8);
	CHECK_THAT(output, UnorderedEquals(sv{"1 2 3 4", "12 3 4", "1 23 4", "1 2 34", "12 34", "123 4", "1 234", "1234"}));

	rules.add(RuleType::AsRunLengthEncodingConversion);
	output.clear();
	CHECK(Converter::allConversions(rules, string, outputFunc) == 15);
	CHECK_THAT(
	    output, UnorderedEquals(
	                sv{"1 2 3 4", "12 3 4", "1 2 3 4", "1 23 4", "1 2 3 4", "1 2 34", "1 2 3 4", "12 34", "1 2 34",
	                   "12 3 4", "1 2 3 4", "123 4", "1 234", "1234", "1 2 3 4"}));

	rules = RuleBook();
	rules.add(RuleType::AsNumberConversion);
	rules.add(RuleType::RomanNumeralConversion);
	output.clear();
	CHECK(Converter::allConversions(rules, string, outputFunc) == 54);
	CHECK_THAT(
	    output, UnorderedEquals(sv{"1 2 3 4",    "I 2 3 4",    "1 II 3 4",    "1 2 III 4",   "1 2 3 IV",  "I II 3 4",
	                               "1 2 III IV", "I 2 3 IV",   "1 II III 4",  "I 2 III 4",   "1 II 3 IV", "I II III 4",
	                               "I II 3 IV",  "I 2 III IV", "1 II III IV", "I II III IV", "12 3 4",    "XII 3 4",
	                               "12 III 4",   "12 3 IV",    "XII III 4",   "12 III IV",   "XII 3 IV",  "XII III IV",
	                               "1 23 4",     "I 23 4",     "1 XXIII 4",   "1 23 IV",     "I XXIII 4", "1 XXIII IV",
	                               "I 23 IV",    "I XXIII IV", "1 2 34",      "I 2 34",      "1 II 34",   "1 2 XXXIV",
	                               "I II 34",    "1 II XXXIV", "I 2 XXXIV",   "I II XXXIV",  "12 34",     "XII 34",
	                               "12 XXXIV",   "XII XXXIV",  "123 4",       "CXXIII 4",    "123 IV",    "CXXIII IV",
	                               "1 234",      "I 234",      "1 CCXXXIV",   "I CCXXXIV",   "1234",      "MCCXXXIV"}));

	rules.add(RuleType::NumberToEnglishConversion);
	output.clear();
	Converter::allConversions(rules, string, outputFunc);
	CHECK_THAT(
	    output, Contains(
	                sv{"1 2 3 4", "I two 3 4", "one 2 three four", "I II thirty four", "one twenty three four",
	                   "one XXIII 4", "I II 34", "one hundred twenty three IV", "1 234", "one 234", "one CCXXXIV"}));
}

TEST_CASE("TEST MEM USAGE", "[.]") //! temporary manual testing function
{
	RuleBook rules;
	std::vector<std::string> output;
	auto outputFunc = [&](std::string&& conversion)
	{
		output.emplace_back(std::move(conversion));
	};
	size_t calculated = 0;
	// size_t estimated;
	size_t actual = 0;
	constexpr std::string_view svShort = "12345";
	constexpr std::string_view svMedium = "1337420690";
	constexpr std::string_view svLong = "11112223344445556666";
	auto DOIT = [&]()
	{
		std::swap(calculated, actual);
		// estimated = Converter::estimatePossibilities(rules, svShort);
		// calculated = Converter::calculatePossibilities(rules, svShort);
		// output.clear();
		// output.reserve(calculated);
		// actual = Converter::allConversions(rules, svShort, outputFunc);

		// estimated = Converter::estimatePossibilities(rules, svMedium);
		// calculated = Converter::calculatePossibilities(rules, svMedium);
		// output.clear();
		// output.reserve(calculated);
		// actual = Converter::allConversions(rules, svMedium, outputFunc);

		// estimated = Converter::estimatePossibilities(rules, svLong);
		calculated = Converter::calculatePossibilities(rules, svLong);
		// output.clear();
		// actual = Converter::allConversions(rules, svLong, outputFunc);
	};

	rules.add(RuleType::AsNumberConversion);
	DOIT();
	REQUIRE(calculated > actual);

	rules.add(RuleType::NumberToEnglishConversion);
	DOIT();
	REQUIRE(calculated > actual);

	rules.add(RuleType::RomanNumeralConversion);
	DOIT();
	REQUIRE(calculated > actual);

	rules.add(RuleType::RunLengthEncodingConversion);
	DOIT();
	REQUIRE(calculated > actual);

	rules.add(RuleType::LookAndSayConversion);
	DOIT();
	REQUIRE(calculated > actual);

	rules.add(RuleType::AsRunLengthEncodingConversion);
	DOIT();
	REQUIRE(calculated > actual);

	SUCCEED();
}
