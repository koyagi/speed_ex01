// #include "mysafestack.hpp"
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
    auto tmp = MySafeStack(std::vector{1,2,3});
    std::cout << "pop() result: " << tmp.safePop() << std::endl;

    auto tmp2 = std::vector(std::begin(tmp), std::end(tmp));
    for( auto el : tmp2) {
        std::cout << el << ", "s;
    }
    std::cout << std::endl;

    std::cout << "bye!"s << std::endl;
    return EXIT_SUCCESS;
}
