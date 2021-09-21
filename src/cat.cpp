#include "parser.hpp"

struct cat {
  void begin_spec(auto name) {
    std::cout << "\n" << name << ":\n";
  }
  void add_parameter(auto name, auto value) {
    std::cout << "  " << name << "(" << value << ")\n";
  }
  static bool finish() {
    return true;
  }
};

int main() {
  return brot::parser::parse<cat>(std::cin);
}
