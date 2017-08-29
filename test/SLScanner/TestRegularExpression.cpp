#include <gtest/gtest.h>
#include <memory>
#include <SLScanner/RegularExpression.h>
using namespace Silly;

TEST(RegularExpression, BaseFunctionTest) {
    RegularExpression testingRegularExpression0 = RegularExpression("1+3+5+(2+6)*");
    RegularExpression testingRegularExpression1 = RegularExpression("a+(b|(c+a))*");
    RegularExpression testingRegularExpression2 = RegularExpression("0+3+1+2+3+((1+2)|(7+4))*");
    RegularExpression testingRegularExpression3 = RegularExpression("(1+(7|(5+6+(5|3)*)))*");
    EXPECT_EQ(testingRegularExpression0.toPostfix(), "13526+*+++");
    EXPECT_EQ(testingRegularExpression1.toPostfix(), "abca+|*+");
    EXPECT_EQ(testingRegularExpression2.toPostfix(), "0312312+74+|*+++++");
    EXPECT_EQ(testingRegularExpression3.toPostfix(), "175653|*++|+*");
#if SL_GTEST_PROTECTED_OPEN_RE
    EXPECT_EQ(testingRegularExpression0.toPostfixFromTree(testingRegularExpression0.tree), testingRegularExpression0.toPostfix());
    EXPECT_EQ(testingRegularExpression1.toPostfixFromTree(testingRegularExpression1.tree), testingRegularExpression1.toPostfix());
    EXPECT_EQ(testingRegularExpression2.toPostfixFromTree(testingRegularExpression2.tree), testingRegularExpression2.toPostfix());
    EXPECT_EQ(testingRegularExpression3.toPostfixFromTree(testingRegularExpression3.tree), testingRegularExpression3.toPostfix());
#endif
}