#pragma once

#include <string>

// TODO increase supported number sizes/ranges

/**
 * @brief returns a number sequence encoded with RLE, space separated.
 * e.g. from '335' to '2:2 1:5'
 *
 * @param number 1 <= len => inf
 * @return std::string the converted string
 */
std::string runLengthEncode(std::string_view number);

/**
 * @brief returns a number sequence decoded with RLE.
 * e.g. from '3211' to '2221'
 *
 * @param number 2 <= len => inf
 * @return std::string the converted string
 */
std::string runLengthDecode(std::string_view number);

/**
 * @brief returns a number sequence as roman numerals.
 * e.g. from '123' to 'CXXIII'
 *
 * @param number "0" <=> "3999"
 * @return std::string the converted string
 */
std::string romanNumerals(std::string_view number);

/**
 * @brief returns a number in english words.
 * e.g. from '321' to 'three hundred twenty one'
 *
 * @param number "0" <=> "999"
 * @return std::string the converted string
 */
std::string numberToEnglish(std::string_view number);

/**
 * @brief returns a number sequence converted with run length encoding then to english words.
 * e.g. from '770' to 'two sevens one zero'
 *
 * @param number 1 <= len => inf
 * @return std::string the converted string
 */
std::string lookAndSay(std::string_view number);
