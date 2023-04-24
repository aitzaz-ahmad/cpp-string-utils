// cpp_string_utils.cpp : Defines the entry point for the application.
//

#include <regex>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "string_utils.h"

namespace utils {

#pragma region - string format validation helpers
    bool is_int32(const std::string& src) {

        if (src.empty())
            return false;

        auto is_invalid = [](const char val) {

            //neither minus, nor a digit
            return (val != '-')
                && !std::isdigit(static_cast<int>(val));
        };
        auto has_illegal_chars = std::any_of(src.cbegin(),
                                             src.cend(),
                                             is_invalid);
        if (has_illegal_chars)
            return false;

        auto integer = int32_t{};
        auto ss = std::stringstream{ src };
        ss >> integer;

        return ss.fail() != true;
    }

    bool is_bool_alpha(const std::string& src) {

        //TODO: Consider improving this rudimentary implementation. - Aitzaz Ahmad
        return src == "true" || src == "false";
    }

    bool is_24h_time(const std::string& src) {

        if (src.empty())
            return false;

        constexpr auto re_24h_format = "^(([01]\\d)|(2[0-3]))(:[0-5]\\d){2}$";
        return std::regex_match(src, std::regex{ re_24h_format });
    }

    bool is_ipv4_mask(const std::string& src) {

        if (src.empty())
            return false;

        constexpr auto re_ipv4_mask = "^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)\\.){3}$";
        return std::regex_match(src, std::regex{ re_ipv4_mask });
    }

    bool is_ipv4_address(const std::string& src) {

        if (src.empty())
            return false;

        constexpr auto re_ipv4 = "^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)\\.){3}(25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)$";
        return std::regex_match(src, std::regex{ re_ipv4 });
    }

    bool is_mac_address(const std::string& src) {

        if (src.empty())
            return false;

        //TODO: Consider updating the regex to allow the usage of ':' instead of '-'. - Aitzaz Ahmad
        constexpr auto re_mac = "^([[:xdigit:]]{2}-){5}[[:xdigit:]]{2}$";
        return std::regex_match(src, std::regex{ re_mac });
    }

    bool are_int32_csvs(const std::string& src) {

        if (src.empty())
            return false;

        auto tokens = split(src, ',');
        for (const auto& token : tokens) {
            if (!is_int32(token))
                return false;
        }

        return true;
    }

    bool are_ipv4_mask_csvs(const std::string& src) {

        if (src.empty())
            return false;

        auto tokens = split(src, ',');
        for (const auto& token : tokens) {
            if (!is_ipv4_mask(token))
                return false;
        }

        return true;
    }
#pragma endregion - string format validation helpers

#pragma region - string manipulation functions
    std::string to_lowercase(const std::string& src) {

        auto to_lower = [](const char ch) {
            return std::tolower(static_cast<unsigned char>(ch));
        };
        auto dest = std::string{};
        dest.reserve(src.size());

        auto it_dest = std::back_inserter(dest);
        for (auto ch : src) {
            *it_dest = to_lower(ch);
        }

        return dest;
    }

    std::string remove_whitespaces(const std::string& src) {

        auto trimmed = std::string{ src };

        constexpr auto is_whitespace = [](const char ch) {

            return std::isspace(static_cast<unsigned char>(ch));
        };

        auto start = std::remove_if(trimmed.begin(), trimmed.end(), is_whitespace);
        trimmed.erase(start, trimmed.end());

        return trimmed;
    }

    std::set<std::string, std::less<>> split(const std::string& src,
                                             const char delimiter) {
        if (src.empty())
            return std::set<std::string, std::less<>>{};

        auto offset = size_t{ 0 };
        auto position = src.find_first_of(delimiter, offset);
        auto tokens = std::set<std::string, std::less<>>{};

        while (position != std::string::npos) {

            tokens.emplace(src.substr(offset, position - offset));

            offset = position + 1;
            position = src.find_first_of(delimiter, offset);
        }

        //parse the last token
        tokens.emplace(src.substr(offset, src.size() - offset));

        return tokens;
    }
#pragma endregion - string manipulation functions
}
