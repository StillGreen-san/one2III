#pragma once

#include <string>

// TODO increase supported number sizes/ranges
// TODO add example in descriptions?

/**
 * @brief returns a number sequence encoded with RLE, space separated
 *
 * @param number 1<=len=>inf
 * @return std::string the converted string
 */
std::string runLengthEncode(std::string_view number);

/**
 * @brief returns a number sequence decoded with RLE
 *
 * @param number 2<=len=>inf
 * @return std::string the converted string
 */
std::string runLengthDecode(std::string_view number);

/**
 * @brief returns a number sequence as roman numerals
 *
 * @param number "0" <=> "3999"
 * @return std::string the converted string
 */
std::string romanNumerals(std::string_view number);

/**
 * @brief returns a number in english words
 *
 * @param number "0" <=> "999"
 * @return std::string the converted string
 */
std::string numberToEnglish(std::string_view number);

/**
 * @brief returns a number sequence converted with run length encoding then to english words
 *
 * @param number 1<=len=>inf
 * @return std::string the converted string
 */
std::string lookAndSay(std::string_view number);
