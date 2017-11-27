//
// Created by 陈润泽 on 27/11/2017.
//
#include <gtest/gtest.h>
#include <SLParser/TokenWrapper.hpp>

TEST(TokenWrapper, TokenList) {
    Silly::TokenWrapper tokenWrapper("test.c", "output.log");
    tokenWrapper.tokens();
}