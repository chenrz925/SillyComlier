#include <SLScanner/MiniCScanner.hpp>
#include <fstream>

int main(const int argc, const char **argv) {
    std::istream *in;
    std::ostream *out;
    if (argc == 1) {
        in = &std::cin;
        out = &std::cout;
    } else if (argc == 2) {
        in = new std::ifstream(argv[1]);
        out = &(std::cout);
    } else {
        in = new std::ifstream(argv[1]);
        out = new std::ofstream(argv[2]);
    }
    Silly::MiniCScanner scanner(*in, *out);
    scanner.scan();
    scanner.display();
    scanner.stat();
    return 0;
}