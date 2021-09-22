#include "parser.hpp"
#include "printer.hpp"

using namespace brot::parser;

struct cat {
  static constexpr auto begin_spec() -> nil (*)(tokens::spec) {
    return brot::printer::begin_spec;
  }
  static constexpr auto add_parameter() -> nil (*)(tokens::param_name, tokens::param_value) {
    return brot::printer::add_parameter;
  }
  static constexpr bool finish() {
    return true;
  }
};

int main() {
  return parse<cat>(std::cin);
}
