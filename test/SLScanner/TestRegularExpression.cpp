#include <gtest/gtest.h>
#include <SLScanner/RegularExpression.h>

using namespace Silly;

TEST(RegularExpression, BaseFunctionTest) {
    RegularExpression testingRegularExpression0 = RegularExpression("1+3+5+(2+6)*");
    RegularExpression testingRegularExpression1 = RegularExpression("a+(b|(c+a))*");
    RegularExpression testingRegularExpression2 = RegularExpression("0+3+1+2+3+((1+2)|(7+4))*");
    RegularExpression testingRegularExpression3 = RegularExpression("(1+(7|(5+6+(5|3)*)))*");
#if SL_GTEST_PROTECTED_OPEN_RE
    EXPECT_EQ(testingRegularExpression0.toPostfix(), "13526+*+++");
    EXPECT_EQ(testingRegularExpression1.toPostfix(), "abca+|*+");
    EXPECT_EQ(testingRegularExpression2.toPostfix(), "0312312+74+|*+++++");
    EXPECT_EQ(testingRegularExpression3.toPostfix(), "175653|*++|+*");
    EXPECT_EQ(testingRegularExpression0.toPostfixFromTree(testingRegularExpression0.tree),
              testingRegularExpression0.toPostfix());
    EXPECT_EQ(testingRegularExpression0.toMidfixFromTree(testingRegularExpression0.tree), "1+3+5+2+6*");
    EXPECT_EQ(testingRegularExpression1.toPostfixFromTree(testingRegularExpression1.tree),
              testingRegularExpression1.toPostfix());
    EXPECT_EQ(testingRegularExpression1.toMidfixFromTree(testingRegularExpression1.tree), "a+b|c+a*");
    EXPECT_EQ(testingRegularExpression2.toPostfixFromTree(testingRegularExpression2.tree),
              testingRegularExpression2.toPostfix());
    EXPECT_EQ(testingRegularExpression2.toMidfixFromTree(testingRegularExpression2.tree), "0+3+1+2+3+1+2|7+4*");
    EXPECT_EQ(testingRegularExpression3.toPostfixFromTree(testingRegularExpression3.tree),
              testingRegularExpression3.toPostfix());
    EXPECT_EQ(testingRegularExpression3.toMidfixFromTree(testingRegularExpression3.tree), "1+7|5+6+5|3**");
#endif
}

TEST(RegularExpression, BaseTest) {
    RegularExpression testingRegularExpression0 = RegularExpression("1+3+5+(2+6)*");
    RegularExpression testingRegularExpression1 = RegularExpression("a+(b|(c+a))*");
    RegularExpression testingRegularExpression2 = RegularExpression("0+3+1+2+3+((1+2)|(7+4))*");
    RegularExpression testingRegularExpression3 = RegularExpression("(1+(7|(5+6+(5|3)*)))*");
    RegularExpression testingRegularExpression4 = RegularExpression("(a|b)*");
    EXPECT_EQ(testingRegularExpression0["13526262626262626"], true);
    EXPECT_EQ(testingRegularExpression1["abcabbbbbcacacacacacab"], true);
    EXPECT_EQ(testingRegularExpression1["a"], true);
    EXPECT_EQ(testingRegularExpression3[""], true);
    EXPECT_EQ(testingRegularExpression4["aaaaa"], true);
    EXPECT_EQ(testingRegularExpression3["15633333333333171717171717171717"], true);
#if SL_GTEST_PRINT_FA_RE
    testingRegularExpression.printDFA();
    testingRegularExpression.printNFA();
#endif
}