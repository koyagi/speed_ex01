#include "dealer.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

int main() {
    using namespace std::string_literals;
    std::cout << "howdy!"s << std::endl;

    auto [pile_red, pile_black] = create_akakuro_decks();

    for(const auto & el : pile_red ) {
        std::cout << el << ", "s;
    }
    std::cout << std::endl;
    for(const auto & el : pile_black ) {
        std::cout << el << ", "s;
    }
    std::cout << std::endl;
    std::cout << "bye!"s << std::endl;
    return EXIT_SUCCESS;
}
