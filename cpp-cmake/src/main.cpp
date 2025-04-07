#include <vector>

#include <spdlog/spdlog.h>
#include <fmt/core.h>

int main() {
  fmt::println("START");
  std::vector v{1, 2, 3, 4};
  for (const auto &i : v) {
    v.push_back(i * 2);
    fmt::println("{}", i);
  }
  fmt::println("--------------");
  for (const auto &i : v) {
    fmt::println("{}", i);
  }
}
