#include "brot/iostream.hpp"
#include "brot/parser.hpp"

namespace brot::tools::cat {
  using namespace brot::parser;

  static constexpr const auto cname = compo_name(name);
  static constexpr const auto param = parameter(skip(name), skip(value));

  static constexpr const auto init = constant(m4c0::parser::nil {});
  static constexpr const auto compo = component(skip(cname), skip(param));
  static constexpr const auto parser = tokenise<void>(file(init, compo)) & iostream::print();

  static auto run() {
    return iostream::parse_cin(parser);
  }
}

int main() {
  return brot::tools::cat::run();
}
