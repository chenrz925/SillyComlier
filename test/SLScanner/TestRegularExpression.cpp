#include <gtest/gtest.h>
#include <memory>
#include <SLScanner/RegularExpression.h>
using namespace Silly;

TEST(RegularExpression, BaseFunctionTest) {
    EXPECT_EQ(RegularExpression("1+3+5+(2+6)*").toPostfix(), "13526+*+++");
    EXPECT_EQ(RegularExpression("a+(b|(c+a))*").toPostfix(), "abca+|*+");
    EXPECT_EQ(RegularExpression("0+3+1+2+3+((1+2)|(7+4))*").toPostfix(), "0312312+74+|*+++++");
    EXPECT_EQ(RegularExpression("(1+(7|(5+6+(5|3)*)))*").toPostfix(), "175653|*++|+*");
}