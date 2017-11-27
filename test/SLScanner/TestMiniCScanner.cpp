#include <gtest/gtest.h>
#include <SLScanner/MiniCScanner.hpp>

using namespace Silly;

TEST(MiniCScanner, LengthCountTest) {
    RE testRE("a*");
    ASSERT_EQ(testRE["aaaaaa"], RegularExpression::Accepted);
    ASSERT_EQ(6, testRE.length());
}

TEST(MiniCScanner, StandardInputTest) {
    PRINTR(\n);
    std::istringstream istream;
    istream.str("int main() {"
                        "int a=0;"
                        "int b=0; // fuck\n"
                        "float f=4.321\n"
                        "char *str= \"hello world\"\n"
                        "char ch=\'a\'"
                        "/* geyyyy "
                        "*/"
                        "return a+b;"
                        "}");
    MiniCScanner scanner(istream, std::cout);
    scanner.scan();
    scanner.display();
    PRINTR(\n);
}