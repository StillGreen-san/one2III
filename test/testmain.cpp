/**
 * @file testmain.cpp
 * @brief gathers all tests for one2III
 */

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "converter.hpp"

TEST_CASE("PLACEHOLDER")
{
	CHECK(true);
}

TEST_CASE("runLengthEncode")
{
	CHECK(runLengthEncode("") == "");
	CHECK(runLengthEncode("123") == "1 1 1 2 1 3");
	CHECK(runLengthEncode("111") == "3 1");
	CHECK(runLengthEncode("1233444") == "1 1 1 2 2 3 3 4");
	CHECK(runLengthEncode("1000000000033") == "1 1 10 0 2 3");
	CHECK(runLengthEncode("1000000000033333333333") == "1 1 10 0 11 3");
	CHECK(runLengthEncode("995551") == "2 9 3 5 1 1");
	CHECK(runLengthEncode("641668") == "1 6 1 4 1 1 2 6 1 8");
	CHECK(runLengthEncode("1111122111111211") == "5 1 2 2 6 1 1 2 2 1");
}