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
	CHECK(runLengthEncode("1") == "1 1");
	CHECK(runLengthEncode("12") == "1 1 1 2");
	CHECK(runLengthEncode("22") == "2 2");
	CHECK(runLengthEncode("123") == "1 1 1 2 1 3");
	CHECK(runLengthEncode("111") == "3 1");
	CHECK(runLengthEncode("995551") == "2 9 3 5 1 1");
	CHECK(runLengthEncode("641668") == "1 6 1 4 1 1 2 6 1 8");
	CHECK(runLengthEncode("1233444") == "1 1 1 2 2 3 3 4");
	CHECK(runLengthEncode("1000000000033") == "1 1 10 0 2 3");
	CHECK(runLengthEncode("1111122111111211") == "5 1 2 2 6 1 1 2 2 1");
	CHECK(runLengthEncode("1000000000033333333333") == "1 1 10 0 11 3");
}

TEST_CASE("romanNumerals")
{
	CHECK(romanNumerals("") == "");
	CHECK(romanNumerals("39") == "XXXIX");
	CHECK(romanNumerals("160") == "CLX");
	CHECK(romanNumerals("207") == "CCVII");
	CHECK(romanNumerals("246") == "CCXLVI");
	CHECK(romanNumerals("789") == "DCCLXXXIX");
	CHECK(romanNumerals("1009") == "MIX");
	CHECK(romanNumerals("1066") == "MLXVI");
	CHECK(romanNumerals("1776") == "MDCCLXXVI");
	CHECK(romanNumerals("1918") == "MCMXVIII");
	CHECK(romanNumerals("1954") == "MCMLIV");
	CHECK(romanNumerals("2014") == "MMXIV");
	CHECK(romanNumerals("2421") == "MMCDXXI");
	CHECK(romanNumerals("3999") == "MMMCMXCIX");
	CHECK(romanNumerals("5432") == "");
}

TEST_CASE("numberToEnglish")
{
	CHECK(numberToEnglish("0") == "zero");
	CHECK(numberToEnglish("000") == "zero");
	CHECK(numberToEnglish("11") == "eleven");
	CHECK(numberToEnglish("18") == "eighteen");
	CHECK(numberToEnglish("018") == "eighteen");
	CHECK(numberToEnglish("126") == "one hundred twenty six");
	CHECK(numberToEnglish("909") == "nine hundred nine");
	CHECK(numberToEnglish("216") == "two hundred sixteen");
}