#include "helper.h"

int main() {
    std::shared_ptr<Expr> ast = std::make_shared<Binary>(
        std::make_shared<Unary>(
            Token{MINUS, "-", nullptr, 1},
            std::make_shared<Literal>(123)),
        Token{STAR, "*", nullptr, 1},
        std::make_shared<Grouping>(
            std::make_shared<Literal>(45.67)));

    std::cout << AstPrinter{}.print(ast) << "\n";
}