#include <catch.hpp>

#include "helperfunctions.hpp"

TEST_CASE("integerPartitions")
{
	using ptn = std::vector<std::vector<size_t>>;

	CHECK(integerPartitions(0, 1) == ptn{});
	CHECK(integerPartitions(5, 3) == ptn{{3, 1, 1}, {2, 2, 1}});
	CHECK(integerPartitions(7, 2) == ptn{{6, 1}, {5, 2}, {4, 3}});
	CHECK(
	    integerPartitions(16, 6, 2) ==
	    ptn{{6, 2, 2, 2, 2, 2}, {5, 3, 2, 2, 2, 2}, {4, 4, 2, 2, 2, 2}, {4, 3, 3, 2, 2, 2}, {3, 3, 3, 3, 2, 2}});
	CHECK(
	    integerPartitions(10, 4) == ptn{{7, 1, 1, 1},
	                                    {6, 2, 1, 1},
	                                    {5, 3, 1, 1},
	                                    {4, 4, 1, 1},
	                                    {5, 2, 2, 1},
	                                    {4, 3, 2, 1},
	                                    {3, 3, 3, 1},
	                                    {4, 2, 2, 2},
	                                    {3, 3, 2, 2}}); // TODO find clang-tidy setting for this
	CHECK(integerPartitions(10, 4, 2, 3) == ptn{{3, 3, 2, 2}});
}

TEST_CASE("partitionString")
{
	using svv = std::vector<std::string_view>;

	CHECK(partitionString("1234", {}) == svv{});
	CHECK(partitionString("1234", {1, 1, 1, 1}) == svv{"1", "2", "3", "4"});
	CHECK(partitionString("1234", {2, 2}) == svv{"12", "34"});
	CHECK(partitionString("1234", {2, 2, 2, 2}) == svv{});
	CHECK(partitionString("12345678", {3, 1, 4}) == svv{"123", "4", "5678"});
}
