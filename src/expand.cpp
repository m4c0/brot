#include "brot/iostream.hpp"
#include "brot/parser.hpp"

#include <string_view>
#include <unordered_map>

namespace brot::tools::expand {
  using namespace brot::parser;

  static constexpr const auto cname = compo_name(name);

  static constexpr const auto include_name = m4c0::parser::match("include");
  static constexpr const auto include_param = parameter(skip(include_name), skip(value));

  static constexpr const auto other_param = parameter(skip(name), skip(value));

  static constexpr const auto param = skip(include_param) | skip(other_param);

  static constexpr const auto init = constant(m4c0::parser::nil {});
  static constexpr const auto compo = component(cname, skip(param));
  static constexpr const auto parser = tokenise<void>(file(init, skip(compo))) & iostream::print();

  static auto run() {
    std::unordered_map<std::string_view, std::string_view> specs {};

    return iostream::parse_cin(parser);
  }
}

int main() {
  return brot::tools::expand::run();
}
