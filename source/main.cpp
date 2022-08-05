#include "lexer.h"

int main() {
    std::vector<token> tokens_vector;
    parseFile("assets/test.dapperc", tokens_vector);
    return 0;
}