// Copyright 2021 GNDavydov


#include <gtest/gtest.h>
#include <string>

#include <optional.hpp>

TEST(Optional, Init) {
    int a = 6;
    optional::optional<int> optional_int_1;
    optional::optional<int> optional_int_2(std::nullopt);
    optional::optional<int> optional_int_3(3);
    optional::optional<int> optional_int_4(optional_int_3);
    optional::optional<int> optional_int_5(std::move(optional_int_3));
    optional::optional<int> optional_int_6(a);

    EXPECT_TRUE(optional_int_4.operator bool());
    EXPECT_TRUE(optional_int_5.operator bool());
    EXPECT_TRUE(optional_int_6.operator bool());
    EXPECT_FALSE(optional_int_1.operator bool());
    EXPECT_FALSE(optional_int_2.operator bool());
    EXPECT_FALSE(optional_int_3.operator bool());

    std::string str = "123";
    optional::optional<std::string> optional_str_1;
    optional::optional<std::string> optional_str_2(std::nullopt);
    optional::optional<std::string> optional_str_3("123");
    optional::optional<std::string> optional_str_4(optional_str_3);
    optional::optional<std::string> optional_str_5(std::move(optional_str_3));
    optional::optional<std::string> optional_str_6(str);

    EXPECT_TRUE(optional_str_4.operator bool());
    EXPECT_TRUE(optional_str_5.operator bool());
    EXPECT_TRUE(optional_str_6.operator bool());
    EXPECT_FALSE(optional_str_1.operator bool());
    EXPECT_FALSE(optional_str_2.operator bool());
    EXPECT_FALSE(optional_str_3.operator bool());
}

TEST(Optional, Equality) {
    int a = 6;
    optional::optional<int> optional_int_1;
    optional::optional<int> optional_int_2;
    optional::optional<int> optional_int_3;
    optional::optional<int> optional_int_4(3);

    optional_int_1 = a;
    optional_int_2 = 3;
    optional_int_3 = optional_int_4;
    EXPECT_TRUE(optional_int_1.operator bool());
    EXPECT_TRUE(optional_int_2.operator bool());
    EXPECT_TRUE(optional_int_3.operator bool());
    EXPECT_TRUE(optional_int_3.operator bool());

    std::string str = "123";
    optional::optional<std::string> optional_str_1;
    optional::optional<std::string> optional_str_2;
    optional::optional<std::string> optional_str_3;
    optional::optional<std::string> optional_str_4("qwerty");

    optional_str_1 = str;
    optional_str_2 = "1234";
    optional_str_3 = optional_str_4;
    EXPECT_TRUE(optional_str_1.operator bool());
    EXPECT_TRUE(optional_str_2.operator bool());
    EXPECT_TRUE(optional_str_3.operator bool());
    EXPECT_TRUE(optional_str_4.operator bool());
}

TEST(Optional, Access) {
    optional::optional<std::string> optional_1("123");
    optional::optional<std::string> optional_2(optional_1);

    EXPECT_EQ(*optional_1, "123");
    EXPECT_EQ(*optional_2, "123");

    *optional_1 = "50000";
    EXPECT_EQ(*optional_1, "50000");
    EXPECT_EQ(*optional_2, "123");

    optional_1 = optional_1->substr(2);
    EXPECT_EQ(*optional_1, "000");
}

TEST(Optional, Value) {
    optional::optional<int> optional_1(90);
    optional::optional<int> optional_2(optional_1);
    optional::optional<int> optional_3;

    EXPECT_EQ(optional_1.value(), 90);
    EXPECT_EQ(optional_2.value(), 90);
    EXPECT_THROW(optional_3.value(), std::runtime_error);

    optional_1.value() = 800;
    EXPECT_EQ(optional_1.value(), 800);
    EXPECT_EQ(optional_2.value(), 90);

    optional_3 = 5;
    EXPECT_EQ(optional_3.value(), 5);
}

TEST(Optional, ValueOr) {
    optional::optional<int> optional_1(90);
    optional::optional<int> optional_2(optional_1);
    optional::optional<int> optional_3;

    EXPECT_EQ(optional_1.value_or(12.4), 90);
    EXPECT_EQ(optional_2.value_or(12.4), 90);
    EXPECT_EQ(optional_3.value_or(12.4), 12);
}
