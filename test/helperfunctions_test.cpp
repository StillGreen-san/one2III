/**
 * @file helperfunctions_test.cpp
 * @brief gathers all tests for helperfunctions.hpp
 */

#include <catch.hpp>

#include "helperfunctions.hpp"

TEST_CASE("integerPartitions")
{
	using ptn = std::vector<std::vector<uint8_t>>;

	CHECK_THAT(integerPartitions(0, 1), Catch::UnorderedEquals(ptn{}));
	CHECK_THAT(integerPartitions(5, 3), Catch::UnorderedEquals(ptn{{3,1,1},{2,2,1}}));
	CHECK_THAT(integerPartitions(7, 2), Catch::UnorderedEquals(ptn{{6,1},{5,2},{4,3}}));
	CHECK_THAT(integerPartitions(16, 6, 2), Catch::UnorderedEquals(
		ptn{{6,2,2,2,2,2},{5,3,2,2,2,2},{4,3,3,2,2,2},{3,3,3,3,2,2},{4,4,2,2,2,2}}));
	CHECK_THAT(integerPartitions(10, 4), Catch::UnorderedEquals(
		ptn{{7,1,1,1},{6,2,1,1},{5,3,1,1},{4,4,1,1},{5,2,2,1},{4,3,2,1},{3,3,3,1},{4,2,2,2},{3,3,2,2}}));
	CHECK_THAT(integerPartitions(10, 4, 2, 3), Catch::UnorderedEquals(ptn{{3,3,2,2}}));
}//TODO check if unordered makes sense

TEST_CASE("partitionString")
{
	using svv = std::vector<std::string_view>;

	const char* tc_1234 = "1234";
	CHECK_THAT(partitionString(tc_1234, {}), Catch::UnorderedEquals(svv{}));
	CHECK_THAT(partitionString(tc_1234, {1,1,1,1}), Catch::UnorderedEquals(svv{{tc_1234+0,1},{tc_1234+1,1},{tc_1234+2,1},{tc_1234+3,1}}));
	CHECK_THAT(partitionString(tc_1234, {2,2}), Catch::UnorderedEquals(svv{{tc_1234+0,2},{tc_1234+2,2}}));
	CHECK_THAT(partitionString(tc_1234, {2,2,2,2}), Catch::UnorderedEquals(svv{}));

}//TODO check if unordered makes sense

TEST_CASE("isValidNumberSequence")
{
	CHECK(isValidNumberSequence("") == false);
	CHECK(isValidNumberSequence("123456") == true);
	CHECK(isValidNumberSequence("1 34 6") == false);
	CHECK(isValidNumberSequence("abcdef") == false);
	CHECK(isValidNumberSequence("1b3d5e") == false);
	CHECK(isValidNumberSequence("ABCDEF") == false);
	CHECK(isValidNumberSequence("0") == true);
	CHECK(isValidNumberSequence("12==56") == false);
	CHECK(isValidNumberSequence("$%&/)") == false);
}
