#include <catch.hpp>

#include "conversionfunctions.hpp"

TEST_CASE("runLengthEncode")
{
	CHECK(runLengthEncode("") == "");
	CHECK(runLengthEncode("1") == "1 1");
	CHECK(runLengthEncode("0") == "1 0");
	CHECK(runLengthEncode("12") == "1 1 1 2");
	CHECK(runLengthEncode("22") == "2 2");
	CHECK(runLengthEncode("123") == "1 1 1 2 1 3");
	CHECK(runLengthEncode("111") == "3 1");
	CHECK(runLengthEncode("0000") == "4 0");
	CHECK(runLengthEncode("995551") == "2 9 3 5 1 1");
	CHECK(runLengthEncode("641668") == "1 6 1 4 1 1 2 6 1 8");
	CHECK(runLengthEncode("1233444") == "1 1 1 2 2 3 3 4");
	CHECK(runLengthEncode("1000000000033") == "1 1 10 0 2 3");
	CHECK(runLengthEncode("0000000000000") == "13 0");
	CHECK(runLengthEncode("1111122111111211") == "5 1 2 2 6 1 1 2 2 1");
	CHECK(runLengthEncode("1000000000033333333333") == "1 1 10 0 11 3");
}

TEST_CASE("asRunLengthEncode")
{
	CHECK(asRunLengthEncode("") == "");
	CHECK(asRunLengthEncode("1234") == "1 2 3 4");
	CHECK(asRunLengthEncode("12345") == "");
	CHECK(asRunLengthEncode("6481") == "6 4 8 1");
	CHECK(asRunLengthEncode("13684684") == "1 3 6 8 4 6 8 4");
	CHECK(asRunLengthEncode("99999888") == "");
	CHECK(asRunLengthEncode("1121") == "");
}

TEST_CASE("romanNumerals")
{
	CHECK(romanNumerals("") == "");
	CHECK(romanNumerals("0") == "");
	CHECK(romanNumerals("000") == "");
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
	CHECK(romanNumerals("02014") == "MMXIV");
	CHECK(romanNumerals("2421") == "MMCDXXI");
	CHECK(romanNumerals("3999") == "MMMCMXCIX");
	CHECK(romanNumerals("5432") == "");
	CHECK(romanNumerals("4444555666") == "");
}

TEST_CASE("numberToEnglish")
{
	CHECK(numberToEnglish("0") == "zero");
	CHECK(numberToEnglish("000") == "zero");
	CHECK(numberToEnglish("11") == "eleven");
	CHECK(numberToEnglish("18") == "eighteen");
	CHECK(numberToEnglish("018") == "eighteen");
	CHECK(numberToEnglish("126") == "one hundred twenty six");
	CHECK(numberToEnglish("216") == "two hundred sixteen");
	CHECK(numberToEnglish("500") == "five hundred");
	CHECK(numberToEnglish("999") == "nine hundred ninety nine");
	CHECK(numberToEnglish("00999") == "nine hundred ninety nine");
	CHECK(numberToEnglish("9875") == "");
	CHECK(numberToEnglish("4444555666") == "");
}

TEST_CASE("lookAndSay")
{
	CHECK(lookAndSay("5336666") == "one five two threes four sixes");
	CHECK(lookAndSay("9999999") == "seven nines");
	CHECK(lookAndSay("000000000000000000") == "eighteen zeros");
	CHECK(lookAndSay("888000") == "three eights three zeros");
	CHECK(lookAndSay("1") == "one one");
	CHECK(lookAndSay("") == "");

	std::string longSequence(256, '0');
	longSequence.append(64, '1').append(128, '2').append(61, '6');
	CHECK(lookAndSay(longSequence) ==
	      "two hundred fifty six zeros sixty four ones one hundred twenty eight twos sixty one sixes");
}
