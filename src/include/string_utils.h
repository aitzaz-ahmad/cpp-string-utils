// cpp_string_utils.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <set>
#include <string>

namespace utils {

#pragma region - string format validation helpers
    bool is_int32(const std::string& src);
    bool is_bool_alpha(const std::string& src);
    bool is_24h_time(const std::string& src);
    bool is_ipv4_mask(const std::string& src);
    bool is_ipv4_address(const std::string& src);
    bool is_mac_address(const std::string& src);

    bool are_int32_csvs(const std::string& src);
    bool are_ipv4_mask_csvs(const std::string& src);
#pragma endregion - string format validation helpers

#pragma region - string manipulation functions
    std::string to_lowercase(const std::string& src);
    std::string remove_whitespaces(const std::string& src);
    std::set<std::string, std::less<>> split(const std::string& src,
                                             const char delimiter);
#pragma endregion - string manipulation functions
}