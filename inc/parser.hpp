#pragma once

#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/str.hpp"

#include <concepts>
#include <cstdlib>
#include <iostream>
#include <type_traits>

static std::ostream & operator<<(std::ostream & o, m4c0::parser::input_t val) {
  return o << std::string(val.begin(), val.end());
}

namespace brot::parser {
  using input_t = m4c0::parser::input_t;

  namespace impl {
    using namespace m4c0::parser;

    static constexpr const auto spaces = many(skip(match_any_of(" \t\r\n")));

    static constexpr const auto lparen = skip(match('('));
    static constexpr const auto rparen = skip(match(')'));
    static constexpr const auto colon = skip(match(':'));
    static constexpr const auto param_chars = many(skip(match_none_of("\r\n():")));
    static constexpr const auto token_chars = at_least_one(skip(match_none_of(" \t\r\n():")));

    static constexpr const auto token = tokenise(token_chars);

    static constexpr const auto params = lparen & tokenise(param_chars) + rparen + spaces;

    static constexpr auto name = token + colon;
  }

  template<typename P>
  concept valid_processor = requires(P p, input_t str) {
    P();
    { p.begin_spec(str) } -> std::same_as<void>;
    { p.add_parameter(str, str) } -> std::same_as<void>;
    { p.finish() } -> std::same_as<bool>;
  };

  template<typename P>
  requires valid_processor<P>
  static auto parse(std::istream & in) noexcept {
    P p {};

    const auto name = impl::name & [p = &p](input_t name) {
      p->begin_spec(name);
      return m4c0::parser::nil {};
    };
    const auto param = combine(impl::token, impl::params, [p = &p](input_t name, input_t value) {
      p->add_parameter(name, value);
      return m4c0::parser::nil {};
    });
    const auto component = skip(name & impl::spaces & at_least_one(param));
    const auto file = impl::spaces & many(component) & m4c0::parser::eof() | "Invalid statement";

    std::string str { std::istreambuf_iterator<char> { in }, {} };
    return file({ str.data(), str.length() }) % [p = &p](auto n, input_t rem) {
      if constexpr (!std::is_same_v<std::decay_t<decltype(n)>, brot::parser::input_t>) {
        return p->finish() ? EXIT_SUCCESS : EXIT_FAILURE;
      } else {
        using namespace m4c0::parser;
        constexpr const auto line_parser = tokenise(many(skip(match_none_of("\n"))));
        line_parser(rem) % [n](auto line) {
          std::cerr << n << " around this:\n    " << line << "\n";
        };
        return EXIT_FAILURE;
      }
    };
  }
}
