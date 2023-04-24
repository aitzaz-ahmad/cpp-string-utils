#include <gtest/gtest.h>
#include "string_utils.h"

namespace str_utils {

    TEST(string_utils_unittests, is_int32) {

        //valid inputs
        ASSERT_TRUE(utils::is_int32("0"));
        ASSERT_TRUE(utils::is_int32("125"));
        ASSERT_TRUE(utils::is_int32("-128"));

        //legal, but queer inputs
        ASSERT_TRUE(utils::is_int32("-00"));
        ASSERT_TRUE(utils::is_int32("-01"));
        ASSERT_TRUE(utils::is_int32("0000000"));

        //INT32 bounds checking inputs
        ASSERT_TRUE(utils::is_int32("2147483647")); //INT32_MAX
        ASSERT_TRUE(utils::is_int32("-2147483648")); //INT32_MIN

        ASSERT_FALSE(utils::is_int32("2147483648")); //INT32_MAX + 1
        ASSERT_FALSE(utils::is_int32("-2147483650")); //INT32_MIN - 2

        //invalid inputs
        ASSERT_FALSE(utils::is_int32(""));
        ASSERT_FALSE(utils::is_int32("-"));
        ASSERT_FALSE(utils::is_int32("--"));
        ASSERT_FALSE(utils::is_int32("--1"));
        ASSERT_FALSE(utils::is_int32("12cxz"));
        ASSERT_FALSE(utils::is_int32("bummer!"));
    }

    TEST(string_utils_unittests, is_boolalpha) {

        //valid inputs
        ASSERT_TRUE(utils::is_bool_alpha("true"));
        ASSERT_TRUE(utils::is_bool_alpha("false"));

        ASSERT_TRUE(utils::is_bool_alpha(utils::to_lowercase("TRUE")));
        ASSERT_TRUE(utils::is_bool_alpha(utils::to_lowercase("FALSE")));

        //invalid inputs
        ASSERT_FALSE(utils::is_bool_alpha("0"));
        ASSERT_FALSE(utils::is_bool_alpha("-1"));
        ASSERT_FALSE(utils::is_bool_alpha("101"));

        ASSERT_FALSE(utils::is_bool_alpha("TRUE"));
        ASSERT_FALSE(utils::is_bool_alpha("FALSE"));

        ASSERT_FALSE(utils::is_bool_alpha("TrUe"));
        ASSERT_FALSE(utils::is_bool_alpha("fALsE"));

        ASSERT_FALSE(utils::is_bool_alpha("T"));
        ASSERT_FALSE(utils::is_bool_alpha("F"));
        ASSERT_FALSE(utils::is_bool_alpha("true!"));
        ASSERT_FALSE(utils::is_bool_alpha("false!"));
        ASSERT_FALSE(utils::is_bool_alpha("!true"));
        ASSERT_FALSE(utils::is_bool_alpha("!false"));
        ASSERT_FALSE(utils::is_bool_alpha("bummer!"));
    }

    TEST(string_utils_unittests, is_24h_time) {

        //valid inputs
        ASSERT_TRUE(utils::is_24h_time("00:00:00"));
        ASSERT_TRUE(utils::is_24h_time("23:59:59"));

        //invalid inputs
        ASSERT_FALSE(utils::is_24h_time(""));
        ASSERT_FALSE(utils::is_24h_time("bummer!"));

        ASSERT_FALSE(utils::is_24h_time("23:01"));
        ASSERT_FALSE(utils::is_24h_time("13:01:"));
        ASSERT_FALSE(utils::is_24h_time("23:01"));
        ASSERT_FALSE(utils::is_24h_time("23:01"));

        ASSERT_FALSE(utils::is_24h_time("24:01:30"));
        ASSERT_FALSE(utils::is_24h_time("12:60:10"));
        ASSERT_FALSE(utils::is_24h_time("15:10:60"));
    }

    TEST(string_utils_unittests, is_ipv4_mask) {

        //valid inputs
        ASSERT_TRUE(utils::is_ipv4_mask("0.0.0."));
        ASSERT_TRUE(utils::is_ipv4_mask("0.1.1."));
        ASSERT_TRUE(utils::is_ipv4_mask("72.68.21."));
        ASSERT_TRUE(utils::is_ipv4_mask("192.168.1."));
        ASSERT_TRUE(utils::is_ipv4_mask("255.255.255."));

        //invalid inputs
        ASSERT_FALSE(utils::is_ipv4_mask("355.0.0."));
        ASSERT_FALSE(utils::is_ipv4_mask("15.33.019."));
        ASSERT_FALSE(utils::is_ipv4_mask("35.10.300."));
        ASSERT_FALSE(utils::is_ipv4_mask("55.310.19."));
        ASSERT_FALSE(utils::is_ipv4_mask("55.310.19."));
        ASSERT_FALSE(utils::is_ipv4_mask("5.031.109."));
        ASSERT_FALSE(utils::is_ipv4_mask("15.33.019."));
        ASSERT_FALSE(utils::is_ipv4_mask("15.33.019."));

        ASSERT_FALSE(utils::is_ipv4_mask(""));
        ASSERT_FALSE(utils::is_ipv4_mask("bummer!"));
        ASSERT_FALSE(utils::is_ipv4_mask(".7235255."));
        ASSERT_FALSE(utils::is_ipv4_mask("ab.33.f0."));
        ASSERT_FALSE(utils::is_ipv4_mask("72:35:255."));
        ASSERT_FALSE(utils::is_ipv4_mask("abc.de.fg."));
        ASSERT_FALSE(utils::is_ipv4_mask("1234567890"));
    }

    TEST(string_utils_unittests, is_ipv4_address) {

        //valid inputs
        ASSERT_TRUE(utils::is_ipv4_address("0.0.0.0"));
        ASSERT_TRUE(utils::is_ipv4_address("0.1.1.0"));
        ASSERT_TRUE(utils::is_ipv4_address("15.33.19.10"));
        ASSERT_TRUE(utils::is_ipv4_address("192.168.1.20"));
        ASSERT_TRUE(utils::is_ipv4_address("255.255.255.255"));

        //invalid inputs
        ASSERT_FALSE(utils::is_ipv4_address("72.68.21."));
        ASSERT_FALSE(utils::is_ipv4_address("355.0.0.1"));
        ASSERT_FALSE(utils::is_ipv4_address("15.33.019.0"));
        ASSERT_FALSE(utils::is_ipv4_address("35.10.300.0"));
        ASSERT_FALSE(utils::is_ipv4_address("55.310.19.1"));
        ASSERT_FALSE(utils::is_ipv4_address("55.3.19.261"));
        ASSERT_FALSE(utils::is_ipv4_address("055.31.19.1"));
        ASSERT_FALSE(utils::is_ipv4_address("5.031.109.1"));
        ASSERT_FALSE(utils::is_ipv4_address("15.33.019.2"));

        ASSERT_FALSE(utils::is_ipv4_address(""));
        ASSERT_FALSE(utils::is_ipv4_address("bummer!"));
        ASSERT_FALSE(utils::is_ipv4_address(".7235255."));
        ASSERT_FALSE(utils::is_ipv4_address("1234567890"));
        ASSERT_FALSE(utils::is_ipv4_address("ab.33.f0.10"));
        ASSERT_FALSE(utils::is_ipv4_address("72:35:255.1"));
        ASSERT_FALSE(utils::is_ipv4_address("abc.de.fg.hi"));
    }

    TEST(string_utils_unittests, is_mac_address) {

        //valid inputs
        ASSERT_TRUE(utils::is_mac_address("00-00-00-00-00-00"));
        ASSERT_TRUE(utils::is_mac_address("0a-f0-cb-e1-d9-fa"));
        ASSERT_TRUE(utils::is_mac_address("ff-ff-ff-ff-ff-ff"));

        //invalid inputs
        ASSERT_FALSE(utils::is_mac_address(""));
        ASSERT_FALSE(utils::is_mac_address("bummer!"));
        ASSERT_FALSE(utils::is_mac_address("1234567890abcdef"));

        ASSERT_FALSE(utils::is_mac_address("0a-f0cbe1f92c"));
        ASSERT_FALSE(utils::is_mac_address("0a-f0-cb-e1-f9"));
        ASSERT_FALSE(utils::is_mac_address("0a-f0-cb-ei-h9-fa"));
        ASSERT_FALSE(utils::is_mac_address("ff:ff:ff:ff:ff:ff"));
    }

    TEST(string_utils_unittests, are_int32_csvs) {

        //valid inputs
        ASSERT_TRUE(utils::are_int32_csvs("0,0"));
        ASSERT_TRUE(utils::are_int32_csvs("-128,127"));
        ASSERT_TRUE(utils::are_int32_csvs("-01,0127"));
        ASSERT_TRUE(utils::are_int32_csvs("-127,-128"));
        ASSERT_TRUE(utils::are_int32_csvs("-0128,00,256"));
        ASSERT_TRUE(utils::are_int32_csvs("-2147483648,2147483646,2147483647"));
        ASSERT_TRUE(utils::are_int32_csvs(utils::remove_whitespaces("123,456, 7890")));

        //invalid inputs
        ASSERT_FALSE(utils::are_int32_csvs(""));
        ASSERT_FALSE(utils::are_int32_csvs("oh,bummer!"));
        ASSERT_FALSE(utils::are_int32_csvs("123,456, 7890"));
        ASSERT_FALSE(utils::are_int32_csvs("--128,-00,256"));
        ASSERT_FALSE(utils::are_int32_csvs("-128;-0,02:56"));
    }

    TEST(string_utils_unittests, are_ipv4_mask_csvs) {

        //valid inputs
        ASSERT_TRUE(utils::are_ipv4_mask_csvs("0.0.0.,0.1.0."));
        ASSERT_TRUE(utils::are_ipv4_mask_csvs("0.1.1.,192.168.8."));
        ASSERT_TRUE(utils::are_ipv4_mask_csvs("0.0.0.,255.255.255."));
        ASSERT_TRUE(utils::are_ipv4_mask_csvs("10.25.45.,192.168.1.,127.0.1."));
        ASSERT_TRUE(utils::are_ipv4_mask_csvs(utils::remove_whitespaces("10.25.45., 192.168.1.,192.168.8.")));

        //invalid inputs
        ASSERT_FALSE(utils::are_ipv4_mask_csvs(""));
        ASSERT_FALSE(utils::are_ipv4_mask_csvs("oh,bummer!"));
        ASSERT_FALSE(utils::are_ipv4_mask_csvs("123,456,7890"));
        ASSERT_FALSE(utils::are_ipv4_mask_csvs("0.1.1.1,192.168.8.1"));
        ASSERT_FALSE(utils::are_ipv4_mask_csvs("0.1.1.1;192.168.8.1,192.168.8."));
        ASSERT_FALSE(utils::are_ipv4_mask_csvs("10.25.45., 192.168.1.,192.168.8."));
    }
}