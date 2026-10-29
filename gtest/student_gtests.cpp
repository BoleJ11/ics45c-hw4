#include <gtest/gtest.h>
#include <string.h>

#include <algorithm>

#include "string.hpp"
#include "alloc.hpp"

TEST(StringFunction, strlen) {
    EXPECT_EQ(String::strlen(""), 0);
    EXPECT_EQ(String::strlen("foo"), 3);
}

TEST(StringFunction, strcpy) {
    char result[10];
    EXPECT_EQ(String::strcpy(result, "foo"), result);
    EXPECT_STREQ(result, "foo");

    EXPECT_EQ(String::strcpy(result, "a"), result);
    EXPECT_STREQ(result, "a");

    EXPECT_EQ(String::strcpy(result, ""), result);
    EXPECT_STREQ(result, "");
}

TEST(StringFunction, reverse_cpy) {
    char dest[20];
    String::reverse_cpy(dest, "hello");
    EXPECT_STREQ(dest, "olleh");

    String::reverse_cpy(dest, "");
    EXPECT_STREQ(dest, "");
}

TEST(StringFunction, strdup) {
    const char *orig = "ics45c";
    char *duped = String::strdup(orig);
    ASSERT_NE(duped, nullptr);
    EXPECT_STREQ(duped, orig);
    EXPECT_NE(duped, orig);
    delete[] duped;

    char *empty_duped = String::strdup("");
    ASSERT_NE(empty_duped, nullptr);
    EXPECT_STREQ(empty_duped, "");
    delete[] empty_duped;
}

TEST(StringFunction, strchr) {
    const char *s = "banana";
    EXPECT_EQ(String::strchr(s, 'b'), s);
    EXPECT_EQ(String::strchr(s, 'n'), s + 2);
    EXPECT_EQ(String::strchr(s, 'z'), nullptr);
    EXPECT_EQ(*String::strchr(s, '\0'), '\0');
}

TEST(StringFunction, strncpy) {
    char dest[20] = "abcdefgh";
    String::strncpy(dest, "hi", 2);
    EXPECT_STREQ(dest, "hi");

    char dest2[20] = "abcdefgh";
    String::strncpy(dest2, "xyz", 5);
    EXPECT_STREQ(dest2, "xyz");
}

TEST(StringFunction, strstr) {
    const char *haystack = "mississippi";
    EXPECT_EQ(String::strstr(haystack, "miss"), haystack);
    EXPECT_EQ(String::strstr(haystack, "issip"), haystack + 1);
    EXPECT_EQ(String::strstr("ababcabc", "abc"), haystack - haystack + "ababcabc" + 2);
    EXPECT_STREQ(String::strstr("banana", "nan"), "nan");
    EXPECT_EQ(String::strstr(haystack, "foo"), nullptr);
}

TEST(StringFunction, strcat) {
    char dest[30] = "Hello";
    String::strcat(dest, " World");
    EXPECT_STREQ(dest, "Hello World");

    char dest2[20] = "";
    String::strcat(dest2, "test");
    EXPECT_STREQ(dest2, "test");
}

TEST(StringFunction, strncat) {
    char dest[30] = "Hello";
    String::strncat(dest, " World!", 3);
    EXPECT_STREQ(dest, "Hello Wo");
}

TEST(StringFunction, strcmp) {
    EXPECT_EQ(String::strcmp("abc", "abc"), 0);
    EXPECT_LT(String::strcmp("abc", "abd"), 0);
    EXPECT_GT(String::strcmp("abd", "abc"), 0);
    EXPECT_LT(String::strcmp("abc", "abcd"), 0);
}
