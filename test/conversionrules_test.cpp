/**
 * @file conversionrules_test.cpp
 * @brief gathers all tests for conversionrules.hpp
 */

#include <catch.hpp>

#include "conversionrules.hpp"

TEST_CASE("RomanNumeralConversion")
{
	RomanNumeralConversion rnc;
	CHECK(rnc.convert("789") == "DCCLXXXIX");
	CHECK(rnc.convert("1009") == "MIX");
}

TEST_CASE("RunLengthEncodingConversion")
{
	RunLengthEncodingConversion rlec;
	CHECK(rlec.convert("22") == "2 2");
	CHECK(rlec.convert("123") == "1 1 1 2 1 3");
}
