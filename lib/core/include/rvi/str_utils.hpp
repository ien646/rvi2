#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>
#include <cinttypes>
#include <cctype>

/**
 * @brief String handling and manipulation methods
 */
namespace rvi::str_utils
{
    /**
     * @brief String vector typedef
     */
    typedef std::vector<std::string> str_vec_t;

    /**
     * @brief String pair typedef
     */
    typedef std::pair<std::string, std::string> str_pair_t;

    /**
     * @brief Split a string into segments, using the 
     * provided separator character. Separator characters
     * are ommited from the output.
     * 
     * @param strv Source string view
     * @param delim Delimiter character
     * @return str_vec_t Resulting segments
     */
    [[nodiscard]]
    str_vec_t split(
        std::string_view strv, 
        char delim);

    /**
     * @brief Split a string into two segments, using the 
     * provided separator character. Separator characters
     * are ommited from the output. The string is split at the 
     * first ocurrence of the delimiter character, starting from
     * the beggining of the string.
     * 
     * @param strv Source string view
     * @param delim Delimiter character
     * @return str_pair_t Resulting segment pair
     */
    [[nodiscard]]
    str_pair_t split_once_beg(
        std::string_view strv, 
        char delim);

    /**
     * @brief Split a string into two segments, using the 
     * provided separator character. Separator characters
     * are ommited from the output. The string is split at the 
     * first ocurrence of the delimiter character, starting backwards
     * from the end of the string.
     * 
     * @param strv Source string view
     * @param delim Delimiter character
     * @return str_pair_t Resulting segment pair
     */
    [[nodiscard]]
    str_pair_t split_once_end(
        std::string_view strv, 
        char delim);

    /**
     * @brief Obtain a substring from the first ocurrence
     * of the delimiter character. If no ocurrence is found,
     * the entire string is returned.
     * 
     * @param strv Source string view
     * @param delim Delimiter character
     * @return std::string_view Resulting substring
     */
    [[nodiscard]]
    std::string_view substr_from_delim(
        std::string_view strv, 
        char delim);

    /**
     * @brief Obtain a substring from the first character of
     * the string, until the first ocurrence of the delimiter character. 
     * If no ocurrence is found, the entire string is returned.
     * 
     * @param strv Source string view
     * @param delim Delimiter character
     * @return std::string_view Resulting substring
     */
    [[nodiscard]]
    std::string_view substr_until_delim(
        std::string_view strv, 
        char delim);

    /**
     * @brief Trim whitespace characters from the beggining
     * of the string
     * 
     * @param strv Source string view
     * @return std::string_view Resulting trimmed string
     */
    [[nodiscard]]
    std::string_view trim_ws_beg(std::string_view strv) noexcept;
 
    /**
     * @brief Trim whitespace characters from the end
     * of the string
     * 
     * @param strv Source string view
     * @return std::string_view Resulting trimmed string
     */
    [[nodiscard]]
    std::string_view trim_ws_end(std::string_view strv) noexcept;

    /**
     * @brief Trim whitespace characters from both the 
     * beggining and the end of the string
     * 
     * @param strv Source string view
     * @return std::string_view Resulting trimmed string
     */
    [[nodiscard]]
    std::string_view trim_ws(std::string_view strv);

    /**
     * @brief Replace ocurrences of a character with another
     * character within a string.
     * 
     * @param strv Source string view
     * @param ocurrence Character ocurrence
     * @param replacement Character replacement
     * @return std::string Resulting string
     */
    [[nodiscard]]
    std::string replace(
        std::string_view strv, 
        char ocurrence, 
        char replacement);

    /**
     * @brief Replace ocurrences of a string with another
     * string within a string.
     * 
     * @param strv Source string view
     * @param ocurrence String ocurrence
     * @param replacement String replacement
     * @return std::string Resulting string
     */
    [[nodiscard]]
    std::string replace(
        std::string_view strv,
        std::string_view ocurrence,
        std::string_view replacement);
}