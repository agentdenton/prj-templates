#include <iostream>
#include <string>
#include <format>

#include <fmt/core.h>

using namespace std::literals;

int main() {
    fmt::print("{} {}\n", "Hello"s, "world"s);
    return 0;
}
