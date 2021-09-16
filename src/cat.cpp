#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/str.hpp"

#include <cstdlib>
#include <iostream>

static constexpr auto parse = [] {
  using namespace m4c0::parser;

  constexpr const auto spaces = many(skip(match_any_of(" \t\r\n")));

  constexpr const auto lparen = skip(match('('));
  constexpr const auto rparen = skip(match(')'));
  constexpr const auto colon = skip(match(':'));
  constexpr const auto id = tokenise(at_least_one(skip(match_none_of(" \t\r\n():"))));

  constexpr const auto ids = spaces + many(skip(id) + spaces);
  static_assert(ids("R1 R2"));

  // No space before lparen to avoid ambiguity
  constexpr const auto statement = skip(id) & lparen & ids & rparen + spaces;
  static_assert(statement("test()"));
  static_assert(statement("test(a b)"));
  static_assert(statement("test( a b )"));

  constexpr const auto spec = ids & colon & spaces & at_least_one(statement);
  static_assert(spec("R1: ok()"));

  constexpr const auto file = many(spec) & eof() | "Invalid statement";
  static_assert(spec("R1: ok() R2: also(ok)"));

  return file;
}();

struct print {
  int operator()(m4c0::parser::nil /*n*/, m4c0::parser::input_t /*rem*/) {
    std::cerr << "SUCCESS\n";
    return EXIT_SUCCESS;
  }
  int operator()(m4c0::parser::input_t n, m4c0::parser::input_t rem) {
    using namespace m4c0::parser;
    constexpr const auto line_parser = tokenise(many(skip(match_none_of("\n"))));
    line_parser(rem) % [n](auto line) {
      const auto err = std::string(n.begin(), n.end());
      const auto ctx = std::string(line.begin(), line.end());
      std::cerr << err << " around this:\n    " << ctx << "\n";
    };

    return EXIT_FAILURE;
  }
};

int main() {
  std::string str(std::istreambuf_iterator<char> { std::cin }, {});

  return parse({ str.data(), str.length() }) % print {};
}
